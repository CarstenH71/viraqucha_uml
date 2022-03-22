//---------------------------------------------------------------------------------------------------------------------
// TemplateParameterTab.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class TemplateParameterTab.
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
#include "TemplateParameterTab.h"
#include "MessageBox.h"

#include "ITemplatableElement.h"
#include "NameBuilder.h"
#include "UmlTemplateParameter.h"

#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include <QList>
#include <QSharedPointer>
#include <QString>

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

//---------------------------------------------------------------------------------------------------------------------
// TPTableItem implementation
//---------------------------------------------------------------------------------------------------------------------
class TPTableItem
{
public:
   TPTableItem(QString name)
   : _name(name)
   , _param(nullptr)
   {}

   TPTableItem(UmlTemplateParameter* param) 
   : _param(param)
   {
      _name = _param->name();
      _type = _param->type();
      _default = _param->defaultValue();
      _constraint = _param->constraints();
   }

public: // Properties
   QString name() const { return _name; }
   void setName(QString value) { _name = value; }

   QString type() const { return _type; }
   void setType(QString value) { _type = value; }

   QString defaultValue() const { return _default; }
   void setDefaultValue(QString value) { _default = value; }

   QString constraints() const { return _constraint; }
   void setConstraints(QString value) { _constraint = value; }

public: // Methods
   void flush(ITemplatableElement& elem)
   {
      if (_param.isNull())
      {
         _param = new UmlTemplateParameter();
      }

      _param->setName(_name);
      _param->setType(_type);
      _param->setDefaultValue(_default);
      _param->setConstraints(_constraint);
      elem.append(_param.pointee());
   }

private:
   UmlTemplateParameterPtr _param;
   QString _name, _type, _default, _constraint;
};

//---------------------------------------------------------------------------------------------------------------------
// TPTableModel implementation
//---------------------------------------------------------------------------------------------------------------------
class TPTableModel : public QAbstractTableModel
{
private:
   static const int KNameColumn = 0;
   static const int KTypeColumn = 1;
   static const int KDefaultColumn = 2;
   static const int KConstraintsColumn = 3;

public: // Constructors
   TPTableModel(ITemplatableElement* elem) 
   : _elem(elem)
   {
      Q_ASSERT(_elem != nullptr);
      for (auto param : _elem->templateParameter())
      {
         _items.append(QSharedPointer<TPTableItem>(new TPTableItem(param)));
      }
   }

   virtual ~TPTableModel() 
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
      return 4;
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
            case KDefaultColumn: return item->defaultValue();
            case KConstraintsColumn: return item->constraints();
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
            case KDefaultColumn:
               item->setDefaultValue(value.toString());
               break;
            case KConstraintsColumn:
               item->setConstraints(value.toString());
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
         case KDefaultColumn: return tr("Default");
         case KConstraintsColumn: return tr("Constraints");
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
         _items.insert(row, QSharedPointer<TPTableItem>(new TPTableItem(createName())));
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
      QListIterator<QSharedPointer<TPTableItem>> iter(_items);
      while (iter.hasNext()) iter.next()->flush(*_elem);
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
      return builder.build(tr("T"));
   }

private:
   ITemplatableElement*               _elem;
   QList<QSharedPointer<TPTableItem>> _items;
};

//---------------------------------------------------------------------------------------------------------------------
// TemplateParameterTab implementation
//---------------------------------------------------------------------------------------------------------------------
TemplateParameterTab::TemplateParameterTab(QWidget* parent, ITemplatableElement* elem)
: super(parent)
, _elem(elem)
, _model(new TPTableModel(elem))
{
   ui.setupUi(this);
   ui.tableView->setModel(_model);
   ui.tableView->horizontalHeader()->resizeSection(0, 80);
   ui.tableView->resizeColumnsToContents();
   ui.tableView->selectRow(0);

   connect(ui.addButton, &QPushButton::clicked, this, &TemplateParameterTab::addItem);
   connect(ui.removeButton, &QPushButton::clicked, this, &TemplateParameterTab::removeItems);
   connect(ui.moveUpButton, &QPushButton::clicked, this, &TemplateParameterTab::moveItemsUp);
   connect(ui.moveDownButton, &QPushButton::clicked, this, &TemplateParameterTab::moveItemsDown);
   connect(ui.tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &TemplateParameterTab::updateButtons);
}

TemplateParameterTab::~TemplateParameterTab()
{
   delete _model;
}

bool TemplateParameterTab::validateInput()
{
   return true;
}

void TemplateParameterTab::applyChanges()
{
   // This will delete all removed parameters:
   _elem->clearTemplate();
   _model->flush();
}

/** Adds a new item to the table. */
void TemplateParameterTab::addItem()
{
   _model->insertRow(_model->rowCount());
   ui.tableView->selectRow(_model->rowCount() - 1);
}

/** Removes all selected items from the table. */
void TemplateParameterTab::removeItems()
{
   auto result = MessageBox::warning(
      this, 
      tr("Are you sure you want to delete the selected template parameters?"), 
      QString(), // No additional information
      QMessageBox::Ok | QMessageBox::Cancel,
      QMessageBox::Cancel);
   if (result == QMessageBox::Ok)
   {
      while (ui.tableView->selectionModel()->selectedIndexes().size() > 0)
      {
         _model->removeRow(ui.tableView->selectionModel()->selectedIndexes().first().row());
      }
   }
}

/** Moves selected items one up. */
void TemplateParameterTab::moveItemsUp()
{
   auto index = ui.tableView->currentIndex();
   if (index.isValid() && index.row() > 0)
   {
      _model->moveRow(QModelIndex(), index.row(), QModelIndex(), index.row() - 1);
   }

   updateButtons(ui.tableView->currentIndex(), QModelIndex());
}

/** Moves selected items one down. */
void TemplateParameterTab::moveItemsDown()
{
   auto index = ui.tableView->currentIndex();
   if (index.isValid() && index.row() < _model->rowCount() - 1)
   {
      _model->moveRow(QModelIndex(), index.row(), QModelIndex(), index.row() + 1);
   }

   updateButtons(ui.tableView->currentIndex(), QModelIndex());
}

/** Updates the buttons of the tab. */
void TemplateParameterTab::updateButtons(const QModelIndex& current, const QModelIndex& previous)
{
   Q_UNUSED(previous);
   if (current.isValid())
   {
      ui.moveDownButton->setEnabled(current.row() < _model->rowCount() - 1);
      ui.moveUpButton->setEnabled(current.row() > 0);
   }
}
