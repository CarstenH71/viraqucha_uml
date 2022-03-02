//---------------------------------------------------------------------------------------------------------------------
// IconProvider.cpp
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class IconProvider.
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
#include "IconProvider.h"

/**
 * @class IconProvider
 * @brief Provides icons for tree items in the project tree view or for buttons in the toolbox.
 * @since 0.2.0
 * @ingroup GuiResources
 *
 * The IconProvider class is used by the project tree view and the toolbox for looking up icons for tree items or
 * buttons.
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal data types
//---------------------------------------------------------------------------------------------------------------------

struct IconProvider::Item
{
   Item(QString name, QString res16)
   : _name(name), _res16(res16)
   {}

   QString _name;
   QString _res16;
};

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** Initializes a new instance of the TreeIconProvider class. */
IconProvider::IconProvider()
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

IconProvider::~IconProvider()
{
   for (int index = 0; index < _items.count(); ++index)
   {
      delete _items[index];
   }
}

/** Gets the only object of this class (singleton). */
IconProvider& IconProvider::instance()
{
   static IconProvider provider;
   return provider;
}

/** Finds an icon for a specified name in the vector of icons. */
QIcon IconProvider::find(QString name) const
{
   int  index = 0;
   bool found = false;
   while (index < _items.count() && !found)
   {
      if (_items[index]->_name == name)
      {
         found = true;
         break;
      }

      ++index;
   }

   if (found)
   {
      return QIcon(_items[index]->_res16);
   }

   return QIcon();
}

/** Looks up an icon for a secified name. */
QIcon IconProvider::get(QString name)
{
   return instance().find(name);
}
