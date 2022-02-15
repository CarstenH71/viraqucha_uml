//---------------------------------------------------------------------------------------------------------------------
// AttributesTab.cpp
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
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
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#include "AttributesTab.h"
#include "Globals.h"
#include "MessageBox.h"
#include "ProjectTreeModel.h"

#include "ComboBoxDelegate.h"
#include "InsertCommand.h"
#include "MoveCommand.h"
#include "RemoveCommand.h"
#include "StringProvider.h"

#include "UmlClassifier.h"

#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QSharedPointer>
#include <QString>
#include <QStringList>

/**
 * @class AttributesTab
 * @brief The AttributesTab class implements a widget for editing UML attributes of a UML classifier.
 * @since 1.0
 * @ingroup GUI
 * @see PropertiesDialog
 *
 * The AttributesTab class provides a table view and some buttons for adding, removing and editing attributes of an
 * UML classifier. It is added to the properties dialog, if the object to be edited is a UmlClassifier.
 */

//---------------------------------------------------------------------------------------------------------------------
// ATTableItem implementation
//---------------------------------------------------------------------------------------------------------------------
class ATTableItem
{
public:
   ATTableItem(int count)
   : _attr(new UmlAttribute())
   , _isNew(true)
   {
      _name = QString("attribute%1").arg(count);
      _type = StringProvider::defaultPrimitiveType();
      _visibility = VisibilityKind::Private;
   }

   ATTableItem(UmlAttribute* attr)
   : _attr(attr)
   , _isNew(false)
   {
      _name = _attr->name();
      _comment = attr->comment();
      _type = _attr->type();
      _default = _attr->defaultValue();
      _visibility = _attr->visibility();
   }

   ~ATTableItem()
   {
      if (_isNew) _attr->dispose();
   }

public: // Properties
   UmlAttribute* attribute() { return _attr; }
   bool isNew() const { return _isNew; }

   QString name() const { return _name; }
   void setName(QString value) { _name = value; }

   QString comment() const { return _comment; }
   void setComment(QString value) { _comment = value; }

   QString type() const { return _type; }
   void setType(QString value) { _type = value; }

   QString defaultValue() const { return _default; }
   void setDefaultValue(QString value) { _default = value; }

   VisibilityKind visibility() const { return _visibility; }
   void setVisibility(VisibilityKind value) { _visibility = value; }

public: // Methods
   void flush()
   {
      _attr->setName(_name);
      _attr->setComment(_comment);
      _attr->setType(_type);
      _attr->setDefaultValue(_default);
      _attr->setVisibility(_visibility);
   }

private:
   UmlAttributePtr _attr;
   bool            _isNew;
   QString         _name;
   QString         _comment;
   QString         _type;
   QString         _default;
   VisibilityKind  _visibility;
};

//---------------------------------------------------------------------------------------------------------------------
// ATTableModel implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * The ATTableModel class implements QAbstractTableModel for an attribute table.
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
   /** Gets the row count. */
   int rowCount(const QModelIndex& parent = QModelIndex()) const override
   {
      Q_UNUSED(parent);
      return _items.count();
   }

   /** Gets the column count. */
   int columnCount(const QModelIndex& parent = QModelIndex()) const override
   {
      Q_UNUSED(parent);
      return 5;
   }

   /** Gets data for a given model index. */
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

   /** Sets data for a given model index. */
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

   /** Gets flags for a given model index. */
   Qt::ItemFlags flags(const QModelIndex& index) const override
   {
      if (!index.isValid()) return 0;
      return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
   }

   /** Gets header data. */
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

   /** Inserts rows into the model. */
   bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override
   {
      beginInsertRows(parent, row, row + count - 1);
      while (count > 0)
      {
         _items.insert(row, QSharedPointer<ATTableItem>(new ATTableItem(_items.count() + 1)));
         --count;
      }
      endInsertRows();
      return true;
   }

   /** Moves rows in the model. */
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

   /** Removes rows from the model. */
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

   /** Gets the item at a specified row. */
   ATTableItem* itemAt(int row) const
   {
      Q_ASSERT(_items.count() > 0);
      Q_ASSERT(row < _items.count());
      return _items.at(row).data();
   }

private:
   QList<QSharedPointer<ATTableItem>> _items;
};

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the AttributesTab class.
 *
 * @param parent The parent widget.
 * @param classifier The UmlClassifier object to be edited.
 * @param project The project that shall receive new UmlAttribute objects.
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

   connect(ui.addButton, &QPushButton::clicked, this, &AttributesTab::addItem);
   connect(ui.editButton, &QPushButton::clicked, this, &AttributesTab::editItem);
   connect(ui.removeButton, &QPushButton::clicked, this, &AttributesTab::removeItems);
   connect(ui.moveUpButton, &QPushButton::clicked, this, &AttributesTab::moveItemUp);
   connect(ui.moveDownButton, &QPushButton::clicked, this, &AttributesTab::moveItemDown);
   connect(ui.tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &AttributesTab::updateButtons);
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
 * @returns True, if input is valid; false otherwise.
 */
bool AttributesTab::validateInput()
{
   return true;
}

/**
 * Applies changes to the properties of the UmlAttribute object.
 */
void AttributesTab::applyChanges()
{
   _model->flush();

   // No need to keep them now, they will currently not be added to the global
   // Undo/Redo command stack. This may be done in future versions.
   while (!_commands.isEmpty())
   {
      auto cmd = _commands.takeFirst();
      cmd->redo();
      delete cmd;
   }
}

/** Adds a new item to the table and the data model. */
void AttributesTab::addItem()
{
   _model->insertRow(_model->rowCount());
   ui.tableView->selectRow(_model->rowCount() - 1);
   _commands.append(new InsertCommand(
     _model->lastItem()->attribute(),
     _project,
     _project.indexOf(_classifier)));
}

/** Opens the properties dialog of the currently selected item. */
void AttributesTab::editItem()
{}

/** Removes all selected items from the table and the data model. */
void AttributesTab::removeItems()
{
   auto result = MessageBox::warning(
      this,
      tr("Delete attributes"),
      tr("Are you sure you want to delete the selected attributes?"),
      QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
   if (result == QMessageBox::Ok)
   {
      while (ui.tableView->selectionModel()->selectedIndexes().size() > 0)
      {
         auto row = ui.tableView->selectionModel()->selectedIndexes().first().row();
         auto item = _model->itemAt(row);
         if (item->isNew())
         {
            int index = 1;
            while ((index = findElementId(_commands, item->attribute()->identifier())) != -1)
            {
               _commands.removeAt(index);
            }
         }
         else
         {
            _commands.append(new RemoveCommand(
               item->attribute(),
               _project,
               _project.indexOf(_classifier)));
         }
         _model->removeRow(row);
      }
   }
}

/** Moves the currently selected item up by one row. */
void AttributesTab::moveItemUp()
{
   auto index = ui.tableView->currentIndex();
   if (index.isValid() && index.row() > 0)
   {
      auto item = _model->itemAt(index.row());
      _commands.append(new MoveCommand(
         item->attribute(),
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
      auto item = _model->itemAt(index.row());
      _commands.append(new MoveCommand(
         item->attribute(),
         _project,
         true));
      _model->moveRow(QModelIndex(), index.row(), QModelIndex(), index.row() + 1);
   }

   updateButtons(ui.tableView->currentIndex(), QModelIndex());

}

/** Enables or disables move up and down buttons depending on the currently selected item. */
void AttributesTab::updateButtons(const QModelIndex& current, const QModelIndex& previous)
{
   Q_UNUSED(previous);
   if (current.isValid())
   {
      ui.moveDownButton->setEnabled(current.row() < _model->rowCount() - 1);
      ui.moveUpButton->setEnabled(current.row() > 0);
   }
}
