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

/**
 * Initializes a new object of the ComboBoxDelegate class.
 *
 * @param parent Parent object.
 * @param items String items to be shown in the Combo Box.
 * @param mode Mode (text based or index based).
 */
ComboBoxDelegate::ComboBoxDelegate(QObject* parent, QStringList items, Mode mode)
: super(parent)
, _items(items)
, _mode(mode)
{
}

ComboBoxDelegate::~ComboBoxDelegate()
{
}

/**
 * Creates a QComboBox object and fills it with the items passed in on construction.
 *
 * @param parent The parent widget.
 * @param modelIndex This parameter is unused.
 * @returns A QComboBox object.
 */
QWidget* ComboBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& modelIndex) const
{
   Q_UNUSED(modelIndex);
   auto box = new QComboBox(parent);
   box->insertItems(0, _items);
   box->setFocusPolicy(Qt::StrongFocus);
   box->setEditable(_mode == TextBased);
   return box;
}

/**
 * Sets editor data.
 *
 * @param editor
 * @param modelIndex
 */
void ComboBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& modelIndex) const
{
   auto box = static_cast<QComboBox*>(editor);
   switch (_mode)
   {
   case IndexBased:
      box->setCurrentIndex(modelIndex.model()->data(modelIndex, Qt::EditRole).toInt());
      break;
   case TextBased:
   {
      auto text = modelIndex.model()->data(modelIndex, Qt::EditRole).toString();
      int index = _items.indexOf(text);
      if (index != -1) box->setCurrentIndex(index);
      box->setCurrentText(text);
      break;
   }
   default:
      break;
   }
}

/**
 * Sets model data.
 *
 * @param editor
 * @param model
 * @param modelIndex
 */
void ComboBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& modelIndex) const
{
   auto box = static_cast<QComboBox*>(editor);
   switch (_mode)
   {
   case IndexBased:
      model->setData(modelIndex, box->currentIndex(), Qt::EditRole);
      break;
   case TextBased:
      model->setData(modelIndex, box->currentText(), Qt::EditRole);
      break;
   default:
      break;
   }
}

/**
 * Updates the editor's geometry.
 *
 * @param editor
 * @param option
 * @param modelIndex This parameter is unused.
 */
void ComboBoxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& modelIndex) const
{
   Q_UNUSED(modelIndex);
   editor->setGeometry(option.rect);
}
