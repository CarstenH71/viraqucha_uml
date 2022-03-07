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
   Item(QString name, QString resource)
   : _name(name), _resource(resource)
   {}

   QString _name;
   QString _resource;
};

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** Initializes a new instance of the TreeIconProvider class. */
IconProvider::IconProvider()
{
   int index = -1;

   // Add new resources here - list should be sorted by name to make searching faster. Set only base name of the
   // resource file, size ("_16x16", "_24x24", "_32x32") and extension (".png") will be added by function resourceAt()!
   _items.resize(23);
   _items[++index] = new Item("UmlAssociation", "association");
   _items[++index] = new Item("UmlAssociation::Aggregation", "aggregation");
   _items[++index] = new Item("UmlAssociation::Composition", "composition");
   _items[++index] = new Item("UmlAttribute", "attribute");
   _items[++index] = new Item("UmlClass", "class");
   _items[++index] = new Item("UmlComment", "comment");
   _items[++index] = new Item("UmlDatatype", "datatype");
   _items[++index] = new Item("UmlDependency", "dependency");
   _items[++index] = new Item("UmlDependency::Usage", "usage");
   _items[++index] = new Item("UmlDependency::Abstraction", "abstraction");
   _items[++index] = new Item("UmlDiagram", "diagram");
   _items[++index] = new Item("UmlEnumeration", "enum");
   _items[++index] = new Item("UmlGeneralization", "generalization");
   _items[++index] = new Item("UmlInterface", "interface");
   _items[++index] = new Item("UmlLink", "link");
   _items[++index] = new Item("UmlModel", "model");
   _items[++index] = new Item("UmlNesting", "nesting");
   _items[++index] = new Item("UmlOperation", "operation");
   _items[++index] = new Item("UmlPackage", "package");
   _items[++index] = new Item("UmlPrimitiveType", "primitivetype");
   _items[++index] = new Item("UmlRealization", "realization");
   _items[++index] = new Item("UmlSignal", "signal");
   _items[++index] = new Item("UmlTemplateBinding", "templbind");
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

/**
 * Returns the index of a specified name.
 * @param name
 * @returns
 */
int IconProvider::indexOf(QString name) const
{
   for (int index = 0; index < _items.count(); ++index)
   {
      if (_items[index]->_name == name)
      {
         return index;
      }
   }

   return -1;
}

/**
 * Returns the resource name at a specified index.
 * @param index
 * @param size
 * @returns
 */
QString IconProvider::resourceAt(int index, IconSize size) const
{
   QString format;
   switch (size)
   {
   case IconSize::Small:
      format = ":/images/%1_16x16.png";
      break;
   case IconSize::Medium:
      format = ":/images/%1_24x24.png";
      break;
   case IconSize::Big:
      format = ":/images/%1_32x32.png";
      break;
   default:
      break;
   }

   return format.arg(_items[index]->_resource);
}

/** Looks up an icon for a secified name. */
QIcon IconProvider::getIcon(QString name, IconSize size)
{
   int index = instance().indexOf(name);
   if (index != -1)
   {
      return QIcon(instance().resourceAt(index, size));
   }

   return QIcon();
}

/** Looks up a pixmap for a secified name. */
QPixmap IconProvider::getPixmap(QString name, IconSize size)
{
   int index = instance().indexOf(name);
   if (index != -1)
   {
      return QPixmap(instance().resourceAt(index, size));
   }

   return QPixmap();
}
