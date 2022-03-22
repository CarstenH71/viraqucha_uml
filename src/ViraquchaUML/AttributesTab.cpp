//---------------------------------------------------------------------------------------------------------------------
// AttributesTab.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class AttributesTab.
// Compiles with: MSVC 15.2 (2017) or newer, GNU GCC 5.1 or newer
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This file is part of ViraquchaUML.                                                                              *
// *                                                                                                                 *
// * ViraquchaUML is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
// * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
// * option) any later version.                                                                                      *
// *                                                                                                                 *
// * ViraquchaUML is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
// * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
// * for more details.                                                                                               *
// *                                                                                                                 *
// * You should have received a copy of the GNU General Public License along with ViraquchaUML; if not, see          *
// * http://www.gnu.org/licenses/gpl                                                                                 *
// *                                                                                                                 *
// *******************************************************************************************************************
//
// See https://github.com/carstenhuber/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#include "AttributesTab.h"
#include "MessageBox.h"
#include "ProjectTreeModel.h"
#include "PropertiesDialog.h"

#include "ComboBoxDelegate.h"
#include "InsertCommand.h"
#include "MoveCommand.h"
#include "RemoveCommand.h"
#include "StringProvider.h"

#include "UmlAttribute.h"
#include "UmlClassifier.h"

#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QString>
#include <QStringList>

/**
 * @class AttributesTab
 * @brief The AttributesTab class implements a widget for editing UML attributes of a UML classifier.
 * @since 0.2.0
 * @ingroup ViraquchaUML
 * @see PropertiesDialog, AttributeTab
 *
 * The AttributesTab class provides a table view and buttons for adding, deleting, moving and editing attributes of a
 * UML classifier. Its intention is to edit attributes of a classifier in a comfortable list or table view instead of
 * the project's tree view (thus the name &quot;Attribute-S-Tab&quot; because it allows editing of several attributes
 * in one dialog). It is added to the PropertiesDialog object, if the object to be edited is a UmlClassifier.
 *
 * The table view only shows the most important properties of a UmlAttribute object, to avoid cluttering the GUI.
 * These are:
 * - Name (text edit)
 * - Type (editable combo box)
 * - Visibility (fixed combo box)
 * - Default value (text edit)
 * - Comment (text edit)
 *
 * Remaining properties (flags etc.) of a UmlAttribute object can be edited using the properties dialog of the object.
 * This dialog can be opened on a selected UmlAttribute object by clicking on the [Edit...] button to the right of the
 * table view.
 */

//---------------------------------------------------------------------------------------------------------------------
// ATTableItem implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * @brief The ATTableItem class provides information of a single item (or row) in an attribute table.
 * @since 0.2.0
 * @ingroup ViraquchaUML
 *
 * The ATTableItem class is used by class ATTableModel of the AttributesTab class for managing UmlAttribute objects to
 * be edited.
 */
class ATTableItem
{
public:
   /**
    * Initializes a new object of the ATTableItem class with a name.
    *
    * This constructor creates a new UmlAttribute object and sets its name, its default primitive type and its default
    * visibility. It also creates a clone of the UmlAttribute object to be used for buffering. After calling this
    * constructor function isNew() returns true.
    * @param name Name
    */
   ATTableItem(QString name)
   : _original(new UmlAttribute())
   , _clone(new UmlAttribute())
   , _isNew(true)
   {
      _clone->setName(name);
      _clone->setType(StringProvider::defaultPrimitiveType());
      _clone->setVisibility(VisibilityKind::Private);
   }

   /**
    * Initializes a new object of the ATTableItem class with a UmlAttribute object.
    *
    * This constructor uses an existing UmlAttribute object and creates a clone, that receives all properties of the
    * existing one. After calling this constructor function isNew() returns false.
    * @param attr UmlAttribute object
    */
   ATTableItem(UmlAttribute* attr)
   : _original(attr)
   , _clone(new UmlAttribute())
   , _isNew(false)
   {
      _original->copyTo(_clone);
   }

   ~ATTableItem()
   {
      if (_isNew) _original->dispose();
      _clone->dispose();
   }

public: // Properties
   /** Gets the original (new or existing) UmlAttribute object. */
   UmlAttribute* original() const { return _original.pointee(); }

   /** Gets a clone of the original (new or existing) UmlAttribute object. */
   UmlAttribute* clone() const { return _clone.pointee(); }

   /** Gets a value indicating whether the UmlAttribute object is new or not. */
   bool isNew() const { return _isNew; }

   /** Gets the name of the clone. */
   QString name() const { return _clone->name(); }
   /** Sets the name of the clone. */
   void setName(QString value) { _clone->setName(value); }

   /** Gets the comment of the clone. */
   QString comment() const { return _clone->comment(); }
   /** Sets the comment of the clone. */
   void setComment(QString value) { _clone->setComment(value); }

   /** Gets the type of the clone. */
   QString type() const { return _clone->type(); }
   /** Sets the type of the clone. */
   void setType(QString value) { _clone->setType(value); }

   /** Gets the default value of the clone. */
   QString defaultValue() const { return _clone->defaultValue(); }
   /** Sets the default value of the clone. */
   void setDefaultValue(QString value) { _clone->setDefaultValue(value); }

   /** Gets the visibility of the clone. */
   VisibilityKind visibility() const { return _clone->visibility(); }
   /** Sets the visibility of the clone. */
   void setVisibility(VisibilityKind value) { _clone->setVisibility(value); }

public: // Methods
   /**
    * Flushes modified properties from the clone to the original UmlAttribute object.
    *
    * After calling this function all properties of the clone are copied to the original (new or existing)
    * UmlAttribute object and function isNew() returns false.
    */
   void flush()
   {
      _clone->copyTo(_original);
      _isNew = false;
   }

private:
   ///@cond
   UmlAttributePtr _original;
   UmlAttributePtr _clone;
   bool            _isNew;
   ///@endcond
};

//---------------------------------------------------------------------------------------------------------------------
// ATTableModel implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * @brief The ATTableModel class implements QAbstractTableModel for a table viewing UmlAttribute objects.
 * @since 0.2.0
 * @ingroup ViraquchaUML
 *
 * The ATTableModel class provides an implementation of class QAbstractTableModel needed for the table view of class
 * AttributesTab. It uses ATTableItem objects for managing UmlAttribute objects of a UmlClassifier object.
 */
class ATTableModel : public QAbstractTableModel
{
public:
   static const int KNameColumn = 0;
   static const int KTypeColumn = 1;
   static const int KVisibilityColumn = 2;
   static const int KDefaultColumn = 3;
   static const int KCommentColumn = 4;

public: // Constructors
   /**
    * Initializes a new object of the ATTableModel class with a UmlClassifier object.
    * @param elem UmlClassifier object
    */
   ATTableModel(UmlClassifier* elem)
   {
      Q_ASSERT(elem != nullptr);
      for (auto attr : elem->attributes())
      {
         _items.append(QSharedPointer<ATTableItem>(new ATTableItem(attr)));
      }
   }

   virtual ~ATTableModel()
   {
      _items.clear();
   }

public: // Methods
   /**
    * Gets the row count.
    *
    * @param parent This parameter is unused.
    */
   int rowCount(const QModelIndex& parent = QModelIndex()) const override
   {
      Q_UNUSED(parent);
      return _items.count();
   }

   /**
    * Gets the column count.
    *
    * @param parent This parameter is unused.
    */
   int columnCount(const QModelIndex& parent = QModelIndex()) const override
   {
      Q_UNUSED(parent);
      return 5;
   }

   /**
    * Gets data stored under the given role for the item referred to by the index.
    *
    * See Qt documentation of class QAbstractItemModel for more details on this function.
    * @param index Model index referring an item
    * @param role Role
    * @returns Data stored under the given role and index
    */
   QVariant data(const QModelIndex& index, int role) const override
   {
      if (index.isValid())
      {
         auto item = _items[index.row()];
         if (role == Qt::DisplayRole || role == Qt::EditRole)
         {
            switch (index.column())
            {
            case KNameColumn: return item->name();
            case KTypeColumn: return item->type();
            case KVisibilityColumn:
               if (role == Qt::EditRole) return (int)item->visibility() - 1;
               return StringProvider::visibilities()[(int)item->visibility() - 1];
            case KDefaultColumn: return item->defaultValue();
            case KCommentColumn: return item->comment();
            default:
               break;
            }
         }
      }

      return QVariant();
   }

   /**
    * Sets the role data for the item at index to value.
    *
    * See Qt documentation of class QAbstractItemModel for more details on this function.
    * @param index Model index referring an item
    * @param value Value to be set
    * @param role Role
    * @returns True if successful; false otherwise.
    */
   bool setData(const QModelIndex& index, const QVariant& value, int role) override
   {
      if (index.isValid())
      {
         auto item = _items[index.row()];
         if (role == Qt::EditRole)
         {
            switch (index.column())
            {
            case KNameColumn:
               item->setName(value.toString());
               if (item->name() == "") return false;
               break;
            case KTypeColumn:
               item->setType(value.toString());
               if (item->type() == "") return false;
               break;
            case KVisibilityColumn:
               item->setVisibility((VisibilityKind)(value.toInt() + 1));
               break;
            case KDefaultColumn:
               item->setDefaultValue(value.toString());
               break;
            case KCommentColumn:
               item->setComment(value.toString());
               break;
            default:
               break;
            }
         }
      }

      return true;
   }

   /**
    * Gets flags for a given model index.
    *
    * See Qt documentation of class QAbstractItemModel for more details on this function.
    * @param index
    */
   Qt::ItemFlags flags(const QModelIndex& index) const override
   {
      if (!index.isValid()) return 0;
      return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
   }

   /**
    * Gets data for a given role and section in the header with the specified orientation.
    *
    * See Qt documentation of class QAbstractItemModel for more details on this function.
    * This implementation of the function supports only horizontal orientation of the header.
    * @param section
    * @param orientation
    * @param role
    */
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override
   {
      if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
      {
         switch (section)
         {
         case KNameColumn: return tr("Name");
         case KTypeColumn: return tr("Type");
         case KVisibilityColumn: return tr("Visibility");
         case KDefaultColumn: return tr("Default");
         case KCommentColumn: return tr("Comment");
         default:
            break;
         }
      }

      return QVariant();
   }

   /**
    * Inserts count rows into the model before the given row.
    *
    * See Qt documentation of class QAbstractItemModel for more details on this function.
    * This implementation of the function creates a new ATTableItem object for each row to be inserted and stores it
    * at the same position specified by parameter row in the internal list of ATTableItem objects.
    * @param row Row to be inserted before
    * @param count Count of rows to be inserted
    * @param parent Parent index
    */
   bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override
   {
      beginInsertRows(parent, row, row + count - 1);
      while (count > 0)
      {
         _items.insert(row, QSharedPointer<ATTableItem>(new ATTableItem(createName())));
         --count;
      }
      endInsertRows();
      return true;
   }

   /**
    * Moves count rows in the model from a source row to a target row.
    *
    * See Qt documentation of class QAbstractItemModel for more details on this function.
    * This implementation of the function moves count rows starting with the given srcRow under parent srcParent to row
    * tgtRow under parent tgtParent.
    * @param srcParent
    * @param srcRow
    * @param count
    * @param tgtParent
    * @param tgtRow
    */
   bool moveRows(const QModelIndex& srcParent, int srcRow, int count, const QModelIndex& tgtParent, int tgtRow) override
   {
      // Pre: source and target row must be different:
      if (srcRow == tgtRow) return false;

      beginMoveRows(srcParent, srcRow, srcRow + count - 1, tgtParent, tgtRow > srcRow ? tgtRow + 1 : tgtRow);
      while (count > 0)
      {
         _items.move(srcRow + count - 1, tgtRow);
         --count;
      }
      endMoveRows();
      return true;
   }

   /**
    * Removes count rows from the model.
    *
    * See Qt documentation of class QAbstractItemModel for more details on this function.
    * Note that the rows are removed in consecutive order! If you want to remove the rows in non consecutive order,
    * call this function for each row to be removed separately.
    * @param row First row to be removed
    * @param count Count of following rows to be removed
    * @param parent Parent index
    */
   bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override
   {
      beginRemoveRows(parent, row, row + count - 1);
      while (count > 0)
      {
         _items.removeOne(_items[row]);
         --count;
      }
      endRemoveRows();
      return true;
   }

   /** Flushes the model to the ViraquchaUML data model. */
   void flush()
   {
      for (auto item : _items)
      {
         item->flush();
      }
   }

   /** Gets the last item in the table. */
   ATTableItem* lastItem() const
   {
      Q_ASSERT(_items.count() > 0);
      return _items.last().data();
   }

   /**
    * Gets the item at a specified row.
    *
    * @param row Row referring to the item
    * @returns The ATTableItem object at the specified row
    */
   ATTableItem* itemAt(int row) const
   {
      Q_ASSERT(_items.count() > 0);
      Q_ASSERT(row < _items.count());
      return _items.at(row).data();
   }
private:
   /** Creates a unique name for a new ATTableItem object. */
   QString createName()
   {
      QStringList names;
      for (auto item : _items)
      {
         names.append(item->name());
      }

      NameBuilder builder(names);
      return builder.build(tr("attribute"));
   }

private:
   ///@cond
   QList<QSharedPointer<ATTableItem>> _items;
   ///@endcond
};

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the AttributesTab class.
 *
 * @param parent The parent widget
 * @param classifier The UmlClassifier object to be edited
 * @param project The project that shall receive new UmlAttribute objects
 */
AttributesTab::AttributesTab(QWidget* parent, UmlClassifier* classifier, ProjectTreeModel& project)
: super(parent)
, _classifier(classifier)
, _project(project)
, _model(new ATTableModel(classifier))
{
   _typeDelegate = new ComboBoxDelegate(this, StringProvider::primitiveTypes(), ComboBoxDelegate::TextBased);
   _visibilityDelegate = new ComboBoxDelegate(this, StringProvider::visibilities(), ComboBoxDelegate::IndexBased);

   ui.setupUi(this);
   ui.tableView->setModel(_model);
   ui.tableView->setItemDelegateForColumn(ATTableModel::KTypeColumn, _typeDelegate);
   ui.tableView->setItemDelegateForColumn(ATTableModel::KVisibilityColumn, _visibilityDelegate);
   ui.tableView->horizontalHeader()->resizeSection(0, 80);
   ui.tableView->resizeColumnsToContents();
   ui.tableView->selectRow(0);

   connect(ui.addButton, &QPushButton::clicked, this, &AttributesTab::addItem);
   connect(ui.editButton, &QPushButton::clicked, this, &AttributesTab::editItem);
   connect(ui.removeButton, &QPushButton::clicked, this, &AttributesTab::removeItems);
   connect(ui.moveUpButton, &QPushButton::clicked, this, &AttributesTab::moveItemUp);
   connect(ui.moveDownButton, &QPushButton::clicked, this, &AttributesTab::moveItemDown);
   connect(ui.tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &AttributesTab::updateButtons);
   updateButtons(ui.tableView->currentIndex(), QModelIndex());
}

AttributesTab::~AttributesTab()
{
   delete _model;
   delete _typeDelegate;
   delete _visibilityDelegate;
}

/**
 * Validates user input.
 *
 * @returns True, if input is valid; false otherwise
 */
bool AttributesTab::validateInput()
{
   return true;
}

/** Applies changes to the properties of the UmlClassifier object. */
void AttributesTab::applyChanges()
{
   _model->flush();

   // No need to keep them now, they will currently not be added to the global
   // Undo/Redo command stack. This may be done in future versions.
   _commands.redoOnce();
}

/** Adds a new item to the table and the data model. */
void AttributesTab::addItem()
{
   _model->insertRow(_model->rowCount());
   ui.tableView->selectRow(_model->rowCount() - 1);
   _commands.push(new InsertCommand(
     _model->lastItem()->original(),
     _project,
     _project.indexOf(_classifier)));
}

/** Opens the properties dialog of the currently selected item. */
void AttributesTab::editItem()
{
   if (ui.tableView->selectionModel()->selectedIndexes().size() > 0)
   {
      auto row = ui.tableView->selectionModel()->selectedIndexes().first().row();
      auto item = _model->itemAt(row);

      // Always edit the clone, not the original. Properties will be copied to the original as
      // soon as the model is flushed to the data model of ViraquchaUML:
      QScopedPointer<PropertiesDialog> dialog(new PropertiesDialog(this, _project, item->clone()));
      dialog->exec();
   }
}

/** Removes all selected items from the table and the data model. */
void AttributesTab::removeItems()
{
   auto result = MessageBox::warning(
      this,
      tr("Are you sure you want to delete the selected attributes?"),
      QString(), // No additional information
      QMessageBox::Ok | QMessageBox::Cancel,
      QMessageBox::Cancel);
   if (result == QMessageBox::Ok)
   {
      int firstRow = -1;
      while (ui.tableView->selectionModel()->selectedIndexes().size() > 0)
      {
         auto row = ui.tableView->selectionModel()->selectedIndexes().first().row();
         if (firstRow == -1) firstRow = row;
         auto item = _model->itemAt(row);
         if (item->isNew())
         {
            _commands.setObsolete(item->original()->identifier());
         }
         else
         {
            _commands.push(new RemoveCommand(
               item->original(),
               _project,
               _project.indexOf(_classifier)));
         }
         _model->removeRow(row);
      }

      if (firstRow > _model->rowCount() - 1) firstRow = _model->rowCount() - 1;
      ui.tableView->selectRow(firstRow);
   }
}

/** Moves the currently selected item up by one row. */
void AttributesTab::moveItemUp()
{
   auto index = ui.tableView->currentIndex();
   if (index.isValid() && index.row() > 0)
   {
      auto item = _model->itemAt(index.row());     // Item to be moved up
      auto succ = _model->itemAt(index.row() - 1); // Successor to be moved down
      _commands.push(new MoveCommand(
         item->original(),
         succ->original()->identifier(), // Needed in case an item is removed, to obsolete the command
         _project,
         false));
      _model->moveRow(QModelIndex(), index.row(), QModelIndex(), index.row() - 1);
   }

   updateButtons(ui.tableView->currentIndex(), QModelIndex());
}

/** Moves the currently selected item down by one row. */
void AttributesTab::moveItemDown()
{
   auto index = ui.tableView->currentIndex();
   if (index.isValid() && index.row() < _model->rowCount() - 1)
   {
      auto item = _model->itemAt(index.row());     // Item to be moved down
      auto pred = _model->itemAt(index.row() + 1); // Predecessor to be moved up
      _commands.push(new MoveCommand(
         item->original(),
         pred->original()->identifier(), // Needed in case an item is removed, to obsolete the command
         _project,
         true));
      _model->moveRow(QModelIndex(), index.row(), QModelIndex(), index.row() + 1);
   }

   updateButtons(ui.tableView->currentIndex(), QModelIndex());
}

/**
 * Enables or disables the buttons of this widget depending on the currently selected model index.
 * @param current Model index currently selected
 * @param previous Model index previously selected
 */
void AttributesTab::updateButtons(const QModelIndex& current, const QModelIndex& previous)
{
   Q_UNUSED(previous);
   if (current.isValid())
   {
      ui.editButton->setEnabled(true);
      ui.moveDownButton->setEnabled(current.row() < _model->rowCount() - 1);
      ui.moveUpButton->setEnabled(current.row() > 0);
      ui.removeButton->setEnabled(true);
   }
   else
   {
      ui.editButton->setEnabled(false);
      ui.moveDownButton->setEnabled(false);
      ui.moveUpButton->setEnabled(false);
      ui.removeButton->setEnabled(false);
   }
}
