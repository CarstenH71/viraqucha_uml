//---------------------------------------------------------------------------------------------------------------------
// ComboBoxDelegate.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class ComboBoxDelegate.
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
#include "ComboBoxDelegate.h"

#include <QComboBox>

/**
 * @class ComboBoxDelegate
 * @brief The ComboBoxDelegate class implements an item delegate creating a combo box editor.
 * @since 0.1
 * @ingroup GUI
 *
 * The ComboBoxDelegate class is used for QTableView objects containing columns which need to be edited using a combo 
 * box instead of a simple line edit box. It provides two editing modes: Index based and text based.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
ComboBoxDelegate::ComboBoxDelegate(QObject* parent, QStringList items, Mode mode)
: super(parent)
, _items(items)
, _mode(mode)
{
}

ComboBoxDelegate::~ComboBoxDelegate()
{
}

QWidget* ComboBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const
{
   auto box = new QComboBox(parent);
   box->insertItems(0, _items);
   box->setEditable(_mode == TextBased);
   return box;
}

void ComboBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
   auto box = static_cast<QComboBox*>(editor);
   switch (_mode)
   {
   case IndexBased:
      box->setCurrentIndex(index.model()->data(index, Qt::EditRole).toInt());
      break;
   case TextBased:
      box->setCurrentText(index.model()->data(index, Qt::EditRole).toString());
      break;
   default:
      break;
   }
}

void ComboBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
   auto box = static_cast<QComboBox*>(editor);
   switch (_mode)
   {
   case IndexBased:
      model->setData(index, box->currentIndex(), Qt::EditRole);
      break;
   case TextBased:
      model->setData(index, box->currentText(), Qt::EditRole);
      break;
   default:
      break;
   }
}

void ComboBoxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   editor->setGeometry(option.rect);
}
