//---------------------------------------------------------------------------------------------------------------------
// ParameterTab.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class ParameterTab.
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
#include "ParameterTab.h"
#include "ComboBoxDelegate.h"
#include "Globals.h"
#include "MessageBox.h"
#include "MultiplicityUtils.h"
#include "StringProvider.h"

#include "UmlOperation.h"
#include "UmlParameter.h"
#include "UmlProject.h"

/**
 * @class ParameterTab
 * @brief The ParameterTab class implements a properties tab for editing parameters of an UML operation.
 * @since 0.1
 * @ingroup GUI
 *
 * TODO1: Multiplicity column needs to be evaluated. Currently a false multiplicity is silently rejected.
 * TODO2: A properties dialog for parameters is needed, since only the most significant properties are shown in the 
 * table.
 */

//---------------------------------------------------------------------------------------------------------------------
// PATableItem implementation
//---------------------------------------------------------------------------------------------------------------------
class PATableItem
{
public:
   PATableItem()
   : _param(nullptr)
   {
      _name         = "param";
      _direction    = ParameterDirectionKind::In;
      _effect       = ParameterEffectKind::Undefined;
      _isException  = false;
      _isStream     = false;
      _multiplicity = StringProvider::defaultMultiplicity();
      _type         = StringProvider::defaultPrimitiveType();
   }

   PATableItem(UmlParameter* param)
   : _param(param)
   {
      _name         = _param->name();
      _comment      = _param->comment();
      _default      = _param->defaultValue();
      _direction    = _param->direction();
      _effect       = _param->effect();
      _isException  = _param->isException();
      _isStream     = _param->isStream();
      _multiplicity = MultiplicityUtils::toString(_param->lower(), _param->upper());
      _type         = _param->type();
   }

public: // Properties
   QString name() const { return _name; }
   void setName(QString value) { _name = value; }

   QString comment() const { return _comment; }
   void setComment(QString value) { _comment = value; }

   QString defaultValue() const { return _default; }
   void setDefaultValue(QString value) { _default = value; }

   int direction() const { return (int)_direction; }
   void setDirection(int value) { _direction = (ParameterDirectionKind)value; }

   int effect() const { return (int)_effect; }
   void setEffect(int value) { _effect = (ParameterEffectKind)value; }

   QString multiplicity() const { return _multiplicity; }
   void setMultiplicity(QString value) { _multiplicity = value; }

   bool isException() const { return _isException; }
   void isException(bool value) { _isException = value; }

   bool isStream() const { return _isStream; }
   void isStream(bool value) { _isStream = value; }

   QString type() const { return _type; }
   void setType(QString value) { _type = value; }

public: // Methods
   void flush(UmlOperation& elem)
   {
      if (_param.isNull())
      {
         _param = new UmlParameter();
      }

      unsigned int lower = 1, upper = 1;
      _param->setName(_name);
      _param->setComment(_comment);
      _param->setDefaultValue(_default);
      _param->setDirection(_direction);
      _param->setEffect(_effect);
      _param->isException(_isException);
      _param->isStream(_isStream);
      if (MultiplicityUtils::tryParse(_multiplicity, lower, upper))
      {
         _param->setLower(lower);
         _param->setUpper(upper);
      }
      _param->setType(_type);
      elem.append(_param);
   }

private:
   UmlParameterPtr        _param;
   QString                _comment;
   QString                _default;
   ParameterDirectionKind _direction;
   ParameterEffectKind    _effect;
   QString                _multiplicity;
   QString                _name;
   QString                _type;
   bool                   _isException;
   bool                   _isStream;
};

//---------------------------------------------------------------------------------------------------------------------
// PATableModel implementation
//---------------------------------------------------------------------------------------------------------------------
class PATableModel : public QAbstractTableModel
{
public:
   static const int KDirColumn    = 0;
   static const int KNameColumn   = 1;
   static const int KTypeColumn   = 2;
   static const int KMultiColumn  = 3;
   static const int KDefColumn    = 4;
   static const int KEffectColumn = 5;

public: // Constructors
   PATableModel(UmlOperation* elem)
   : _elem(elem)
   {
      Q_ASSERT(_elem != nullptr);
      QListIterator<UmlParameter*> iter(_elem->parameter());
      while (iter.hasNext())
      {
         _items.append(QSharedPointer<PATableItem>(new PATableItem(iter.next())));
      }
   }

   virtual ~PATableModel()
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
      return 6;
   }

   /** Gets data for a given model index. */
   QVariant data(const QModelIndex& index, int role) const override
   {
      if (index.isValid())
      {
         auto item = _items[index.row()];
         if (role == Qt::DisplayRole)
         {
            switch (index.column())
            {
            case KDirColumn:    return StringProvider::directions()[item->direction()];
            case KNameColumn:   return item->name();
            case KTypeColumn:   return item->type();
            case KMultiColumn:  return item->multiplicity();
            case KDefColumn:    return item->defaultValue();
            case KEffectColumn: return StringProvider::effects()[item->effect()];
            default: break;
            }
         }
         else if (role == Qt::EditRole)
         {
            switch (index.column())
            {
            case KDirColumn:    return item->direction();
            case KNameColumn:   return item->name();
            case KTypeColumn:   return item->type();
            case KMultiColumn:  return item->multiplicity();
            case KDefColumn:    return item->defaultValue();
            case KEffectColumn: return item->effect();
            default: break;
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
            case KDirColumn:
               item->setDirection(value.toInt());
               break;
            case KNameColumn:
               item->setName(value.toString());
               if (item->name() == "") return false;
               break;
            case KTypeColumn:
               item->setType(value.toString());
               if (item->type() == "") return false;
               break;
            case KMultiColumn:
               item->setMultiplicity(value.toString());
               break;
            case KDefColumn:
               item->setDefaultValue(value.toString());
               break;
            case KEffectColumn:
               item->setEffect(value.toInt());
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
         case KDirColumn:    return tr("Direction");
         case KNameColumn:   return tr("Name");
         case KTypeColumn:   return tr("Type");
         case KMultiColumn:  return tr("Multiplicity");
         case KDefColumn:    return tr("Default");
         case KEffectColumn: return tr("Effect");
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
         _items.insert(row, QSharedPointer<PATableItem>(new PATableItem()));
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
      QListIterator<QSharedPointer<PATableItem>> iter(_items);
      while (iter.hasNext()) iter.next()->flush(*_elem);
   }

private:
   UmlOperation*                      _elem;
   QList<QSharedPointer<PATableItem>> _items;
};

//---------------------------------------------------------------------------------------------------------------------
// ParameterTab implementation
//---------------------------------------------------------------------------------------------------------------------
ParameterTab::ParameterTab(QWidget* parent, UmlOperation* elem)
: super(parent)
, _elem(elem)
, _model(new PATableModel(elem))
{
   Q_ASSERT(_elem != nullptr);

   _directionsDelegate = new ComboBoxDelegate(this, StringProvider::directions(), ComboBoxDelegate::IndexBased);
   _effectsDelegate = new ComboBoxDelegate(this, StringProvider::effects(), ComboBoxDelegate::IndexBased);
   _multiDelegate = new ComboBoxDelegate(this, StringProvider::multiplicities(), ComboBoxDelegate::TextBased);
   _typesDelegate = new ComboBoxDelegate(this, StringProvider::primitiveTypes(), ComboBoxDelegate::TextBased);

   ui.setupUi(this);
   ui.tableView->setModel(_model);
   ui.tableView->setItemDelegateForColumn(PATableModel::KDirColumn, _directionsDelegate);
   ui.tableView->setItemDelegateForColumn(PATableModel::KEffectColumn, _effectsDelegate);
   ui.tableView->setItemDelegateForColumn(PATableModel::KMultiColumn, _multiDelegate);
   ui.tableView->setItemDelegateForColumn(PATableModel::KTypeColumn, _typesDelegate);
   ui.tableView->horizontalHeader()->resizeSection(0, 80);

   connect(ui.addItem, &QPushButton::clicked, this, &ParameterTab::addItem);
   connect(ui.removeItems, &QPushButton::clicked, this, &ParameterTab::removeItems);
   connect(ui.moveItemsUp, &QPushButton::clicked, this, &ParameterTab::moveItemsUp);
   connect(ui.moveItemsDown, &QPushButton::clicked, this, &ParameterTab::moveItemsDown);
   connect(ui.tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &ParameterTab::updateButtons);
}

ParameterTab::~ParameterTab()
{
   delete _directionsDelegate;
   delete _effectsDelegate;
   delete _multiDelegate;
   delete _typesDelegate;
   delete _model;
}

bool ParameterTab::validateInput()
{
   return true;
}

void ParameterTab::applyChanges()
{
   // This will delete all removed parameters:
   _elem->clearParameter();
   _model->flush();
}

void ParameterTab::addItem()
{
   _model->insertRow(_model->rowCount());
   ui.tableView->selectRow(_model->rowCount() - 1);
}

void ParameterTab::removeItems()
{
   auto result = MessageBox::warning(
      this,
      tr("Delete parameter"),
      tr("Are you sure you want to delete the selected parameters?"),
      QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
   if (result == QMessageBox::Ok)
   {
      while (ui.tableView->selectionModel()->selectedIndexes().size() > 0)
      {
         _model->removeRow(ui.tableView->selectionModel()->selectedIndexes().first().row());
      }
   }
}

void ParameterTab::moveItemsUp()
{
   auto index = ui.tableView->currentIndex();
   if (index.isValid() && index.row() > 0)
   {
      _model->moveRow(QModelIndex(), index.row(), QModelIndex(), index.row() - 1);
   }

   updateButtons(ui.tableView->currentIndex(), QModelIndex());
}

void ParameterTab::moveItemsDown()
{
   auto index = ui.tableView->currentIndex();
   if (index.isValid() && index.row() < _model->rowCount() - 1)
   {
      _model->moveRow(QModelIndex(), index.row(), QModelIndex(), index.row() + 1);
   }

   updateButtons(ui.tableView->currentIndex(), QModelIndex());
}

void ParameterTab::updateButtons(const QModelIndex& current, const QModelIndex& previous)
{
   Q_UNUSED(previous);
   if (current.isValid())
   {
      ui.moveItemsDown->setEnabled(current.row() < _model->rowCount() - 1);
      ui.moveItemsUp->setEnabled(current.row() > 0);
   }
}
