//---------------------------------------------------------------------------------------------------------------------
// TreeIconProvider.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class TreeIconProvider.
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
#include "TreeIconProvider.h"

/**
 * @class TreeIconProvider
 * @brief Provides icons for tree items in the project tree.
 * @since 1.0
 * @ingroup GUI
 */

struct TreeIconProvider::Item
{
   Item(QString cls, QString res) 
   : className(cls), resource(res) 
   {}

   QString className;
   QString resource;
};

/** Initializes a new instance of the TreeIconProvider class. */
TreeIconProvider::TreeIconProvider()
{
   _items.resize(11);
   _items[0] = new Item("UmlClass", ":/images/class_16x16.png");
   _items[1] = new Item("UmlDatatype", ":/images/datatype_16x16.png");
   _items[2] = new Item("UmlDiagram", ":/images/diagram_16x16.png");
   _items[3] = new Item("UmlEnumeration", ":/images/enum_16x16.png");
   _items[4] = new Item("UmlInterface", ":/images/interface_16x16.png");
   _items[5] = new Item("UmlModel", ":/images/model_16x16.png");
   _items[6] = new Item("UmlPackage", ":/images/package_16x16.png");
   _items[7] = new Item("UmlPrimitiveType", ":/images/primitive_16x16.png");
   _items[8] = new Item("UmlSignal", ":/images/signal_16x16.png");
   _items[9] = new Item("UmlAttribute", ":/images/attribute_16x16.png");
   _items[10] = new Item("UmlOperation", ":/images/operation_16x16.png");
}

TreeIconProvider::~TreeIconProvider()
{
   for (int index = 0; index < _items.count(); ++index)
   {
      delete _items[index];
   }
}

/** Provides an icon for a specified class name. */
QIcon TreeIconProvider::icon(QString className) const
{
   int index = 0;
   bool found = false;
   while (index < _items.count() && !found)
   {
      if (_items[index]->className == className)
      {
         found = true;
         break;
      }

      ++index;
   }

   if (found)
   {
      return QIcon(_items[index]->resource);
   }

   return QIcon();
}
