//---------------------------------------------------------------------------------------------------------------------
// OperationsTab.cpp
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class OperationsTab.
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
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#include "OperationsTab.h"

#include "MessageBox.h"
#include "ProjectTreeModel.h"
#include "PropertiesDialog.h"

#include "ComboBoxDelegate.h"
#include "InsertCommand.h"
#include "MoveCommand.h"
#include "RemoveCommand.h"
#include "StringProvider.h"

#include "UmlClassifier.h"
#include "UmlOperation.h"

#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QString>
#include <QStringList>

/**
 * @class OperationsTab
 * @brief Provides a widget for editing the list of operations of a UML classifier.
 * @since 0.2.0
 * @ingroup ViraquchaUML
 *
 * The OperationsTab class provides a table widget and buttons for editing the list of operations of a UML classifier.
 * It is added to the properties dialog (see class PropertiesDialog) for every UML classifier instance in the data
 * model of ViraquchaUML.
 */

//---------------------------------------------------------------------------------------------------------------------
// OPTableItem implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * @brief The OPTableItem class provides information of a single item (or row) in an operations table.
 * @since 0.2.0
 * @ingroup ViraquchaUML
 *
 * The OPTableItem class is used by class OPTableModel of the OperationsTab class for managing UmlOperation objects to
 * be edited.
 */
class OPTableItem
{
public:
   /**
    * Initializes a new object of the OPTableItem class with a name.
    *
    * This constructor creates a new UmlOperation object and sets its name, its default primitive type and its default
    * visibility. It also creates a clone of the UmlOperation object to be used for buffering. After calling this
    * constructor function isNew() returns true.
    * @param name Name
    */
   OPTableItem(QString name)
   : _original(new UmlOperation())
   , _clone(new UmlOperation())
   , _isNew(true)
   {
      _clone->setName(name);
      _clone->setReturnType(StringProvider::defaultPrimitiveType());
      _clone->setVisibility(VisibilityKind::Private);
   }

   /**
    * Initializes a new object of the OPTableItem class with a UmlOperation object.
    *
    * This constructor uses an existing UmlOperation object and creates a clone, that receives all properties of the
    * existing one. After calling this constructor function isNew() returns false.
    * @param attr UmlOperation object
    */
   OPTableItem(UmlOperation* oper)
   : _original(oper)
   , _clone(new UmlOperation())
   , _isNew(false)
   {
      _original->copyTo(_clone);
   }

   ~OPTableItem()
   {
      if (_isNew) _original->dispose();
      _clone->dispose();
   }

public: // Properties
   /** Gets the original (new or existing) UmlOperation object. */
   UmlOperation* original() const { return _original.pointee(); }

   /** Gets a clone of the original (new or existing) UmlOperation object. */
   UmlOperation* clone() const { return _clone.pointee(); }

   /** Gets a value indicating whether the UmlOperation object is new or not. */
   bool isNew() const { return _isNew; }

   /** Gets the name of the clone. */
   QString name() const { return _clone->name(); }
   /** Sets the name of the clone. */
   void setName(QString value) { _clone->setName(value); }

   /** Gets the comment of the clone. */
   QString comment() const { return _clone->comment(); }
   /** Sets the comment of the clone. */
   void setComment(QString value) { _clone->setComment(value); }

   /** Gets the parameter list of the clone. */
   QString parameterList() const
   {
      QString ret;

      auto list = _clone->parameter();
      bool first = true;
      for (auto param : list)
      {
         ret += first ? param->signature() : QString(", %1").arg(param->signature());
         first = false;
      }

      return ret;
   }
   /** Sets the parameter list of the clone. */
   void setParameterList(QString value)
   {
      const QString KParameterPattern =
            QString("[A-Za-z_][\\w]*")                   // Name
          + QString("\\s*:\\s*")                         // Colon
          + QString("[A-Za-z_][\\w]*(\\^|&)?")           // Type (optional as pointer^ or reference&)
          + QString("(")                                 // Default value (optional) either as
          + QString("(\\s*=\\s*(\\d\\d*)(\\.\\d\\d*)?)") // a number
          + QString("|")                                 // or
          + QString("(\\s*=\\s*((\"[^\"\r\n]*\")))")     // a string
          + QString("|")                                 // or
          + QString("(\\s*=\\s*nil)")                    // a "nil" pointer constant.
          + QString(")?");
      QRegularExpression exp(KParameterPattern);
      QList<UmlParameterPtr> params;

      auto iter = exp.globalMatch(value);
      while (iter.hasNext())
      {
         auto match = iter.next();
         QString name, type, value;
         QString sub = match.captured(0);
         int pos1 = sub.indexOf(':');
         int pos2 = sub.indexOf('=');
         if (pos1 > -1)
         {
            name = sub.left(pos1).trimmed(); // TODO: validate name?
         }
         if (name.isEmpty()) continue; // Reject nameless parameters.
         if (pos2 > -1)
         {
            type = sub.mid(pos1 + 1, pos2 - pos1 - 1).trimmed();
            value = sub.right(sub.length() - pos2 - 1).trimmed();
         }
         else
         {
            type = sub.right(sub.length() - pos1 - 1).trimmed();
         }
         if (type.isEmpty()) continue; // Reject typeless parameters.

         UmlParameter* param = _clone->findParameter(name);
         if (param != nullptr)
         {
            // Modify type and default value only:
            param->setType(type);
            param->setDefaultValue(value);
         }
         else
         {
            param = new UmlParameter();
            param->setName(name);
            param->setType(type);
            param->setDefaultValue(value);
            param->setDirection(ParameterDirectionKind::In);
         }

         params.append(UmlParameterPtr(param));
      }

      _clone->clearParameter();
      for (auto param : params)
      {
         _clone->append(param);
      }
   }

   /** Gets the type of the clone. */
   QString returnType() const { return _clone->returnType(); }
   /** Sets the type of the clone. */
   void setReturnType(QString value) { _clone->setReturnType(value); }

   /** Gets the visibility of the clone. */
   VisibilityKind visibility() const { return _clone->visibility(); }
   /** Sets the visibility of the clone. */
   void setVisibility(VisibilityKind value) { _clone->setVisibility(value); }

public: // Methods
   /**
    * Flushes modified properties from the clone to the original UmlOperation object.
    *
    * After calling this function all properties of the clone are copied to the original (new or existing)
    * UmlOperation object and function isNew() returns false.
    */
   void flush()
   {
      _clone->copyTo(_original);
      _isNew = false;
   }

private:
   ///@cond
   UmlOperationPtr _original;
   UmlOperationPtr _clone;
   bool            _isNew;
   ///@endcond
};

//---------------------------------------------------------------------------------------------------------------------
// OPTableModel implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * @brief The OPTableModel class implements QAbstractTableModel for a table viewing UmlOperation objects.
 * @since 0.2.0
 * @ingroup ViraquchaUML
 *
 * The OPTableModel class provides an implementation of class QAbstractTableModel needed for the table view of class
 * OperationsTab. It uses OPTableItem objects for managing UmlOperation objects of a UmlClassifier object.
 */
class OPTableModel : public QAbstractTableModel
{
public:
   static const int KNameColumn = 0;
   static const int KParameterColumn = 1;
   static const int KReturnTypeColumn = 2;
   static const int KVisibilityColumn = 3;
   static const int KCommentColumn = 4;

public: // Constructors
   /**
    * Initializes a new object of the OPTableModel class with a UmlClassifier object.
    * @param elem UmlClassifier object
    */
   OPTableModel(UmlClassifier* elem)
   {
      Q_ASSERT(elem != nullptr);
      for (auto oper : elem->operations())
      {
         _items.append(QSharedPointer<OPTableItem>(new OPTableItem(oper)));
      }
   }

   virtual ~OPTableModel()
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
            case KParameterColumn: return item->parameterList();
            case KReturnTypeColumn: return item->returnType();
            case KVisibilityColumn:
               if (role == Qt::EditRole) return (int)item->visibility() - 1;
               return StringProvider::visibilities()[(int)item->visibility() - 1];
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
               if (item->name().isEmpty()) return false;
               break;
            case KParameterColumn:
               item->setParameterList(value.toString());
               break;
            case KReturnTypeColumn:
               item->setReturnType(value.toString());
               if (item->returnType().isEmpty()) return false;
               break;
            case KVisibilityColumn:
               item->setVisibility((VisibilityKind)(value.toInt() + 1));
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
         case KParameterColumn: return tr("Parameters");
         case KReturnTypeColumn: return tr("Return Type");
         case KVisibilityColumn: return tr("Visibility");
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
    * This implementation of the function creates a new OPTableItem object for each row to be inserted and stores it
    * at the same position specified by parameter row in the internal list of OPTableItem objects.
    * @param row Row to be inserted before
    * @param count Count of rows to be inserted
    * @param parent Parent index
    */
   bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override
   {
      beginInsertRows(parent, row, row + count - 1);
      while (count > 0)
      {
         _items.insert(row, QSharedPointer<OPTableItem>(new OPTableItem(createName())));
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
   OPTableItem* lastItem() const
   {
      Q_ASSERT(_items.count() > 0);
      return _items.last().data();
   }

   /**
    * Gets the item at a specified row.
    *
    * @param row Row referring to the item
    * @returns The OPTableItem object at the specified row
    */
   OPTableItem* itemAt(int row) const
   {
      Q_ASSERT(_items.count() > 0);
      Q_ASSERT(row < _items.count());
      return _items.at(row).data();
   }

private:
   /** Creates a unique name for a new OPTableItem object. */
   QString createName()
   {
      QStringList names;
      for (auto item : _items)
      {
         names.append(item->name());
      }

      NameBuilder builder(names);
      return builder.build(tr("operation"));
   }

private:
   ///@cond
   QList<QSharedPointer<OPTableItem>> _items;
   ///@endcond
};

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the OperationsTab class.
 *
 * @param parent The parent widget
 * @param classifier The UmlClassifier object to be edited
 * @param project The project that shall receive new UmlOperation objects
 */
OperationsTab::OperationsTab(QWidget* parent, UmlClassifier* classifier, ProjectTreeModel& project)
: super(parent)
, _classifier(classifier)
, _project(project)
, _model(new OPTableModel(classifier))
{
   _returnTypeDelegate = new ComboBoxDelegate(this, StringProvider::primitiveTypes(), ComboBoxDelegate::TextBased);
   _visibilityDelegate = new ComboBoxDelegate(this, StringProvider::visibilities(), ComboBoxDelegate::IndexBased);

   ui.setupUi(this);
   ui.tableView->setModel(_model);
   ui.tableView->setItemDelegateForColumn(OPTableModel::KReturnTypeColumn, _returnTypeDelegate);
   ui.tableView->setItemDelegateForColumn(OPTableModel::KVisibilityColumn, _visibilityDelegate);
   ui.tableView->horizontalHeader()->resizeSection(0, 80);
   ui.tableView->resizeColumnsToContents();
   ui.tableView->selectRow(0);

   connect(ui.addButton, &QPushButton::clicked, this, &OperationsTab::addItem);
   connect(ui.editButton, &QPushButton::clicked, this, &OperationsTab::editItem);
   connect(ui.removeButton, &QPushButton::clicked, this, &OperationsTab::removeItems);
   connect(ui.moveUpButton, &QPushButton::clicked, this, &OperationsTab::moveItemUp);
   connect(ui.moveDownButton, &QPushButton::clicked, this, &OperationsTab::moveItemDown);
   connect(ui.tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &OperationsTab::updateButtons);
   updateButtons(ui.tableView->currentIndex(), QModelIndex());
}

OperationsTab::~OperationsTab()
{
   delete _model;
   delete _returnTypeDelegate;
   delete _visibilityDelegate;
}

/**
 * Validates user input.
 *
 * @returns True, if input is valid; false otherwise
 */
bool OperationsTab::validateInput()
{
   return true;
}

/** Applies changes to the properties of the UmlClassifier object. */
void OperationsTab::applyChanges()
{
   _model->flush();

   // No need to keep them now, they will currently not be added to the global
   // Undo/Redo command stack. This may be done in future versions.
   _commands.redoOnce();
}

/** Adds a new item to the table and the data model. */
void OperationsTab::addItem()
{
   _model->insertRow(_model->rowCount());
   ui.tableView->selectRow(_model->rowCount() - 1);
   _commands.push(new InsertCommand(
     _model->lastItem()->original(),
     _project,
     _project.indexOf(_classifier)));
}

/** Opens the properties dialog of the currently selected item. */
void OperationsTab::editItem()
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
void OperationsTab::removeItems()
{
   auto result = MessageBox::warning(
      this,
      tr("Are you sure you want to delete the selected operations?"),
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
void OperationsTab::moveItemUp()
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
void OperationsTab::moveItemDown()
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
void OperationsTab::updateButtons(const QModelIndex& current, const QModelIndex& previous)
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
