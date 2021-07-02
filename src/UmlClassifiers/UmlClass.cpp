//---------------------------------------------------------------------------------------------------------------------
// UmlClass.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlClass.
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
#include "UmlClass.h"
#include "PropertyStrings.h"

/**
 * @class UmlClass
 * @brief The UmlClass class stores properties of a UML Class element.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 * This class extends its base class by further properties specific to UML Class elements, namely UML Ports which are
 * stored as UmlElement objects in the list of elements of the class. You may obtain a list of the UmlPort objects
 * associated with this class by calling function ports(). If you wish to add or remove UmlPort objects to and from an 
 * object of this class, use base functions UmlCompositeElement::append() and UmlCompositeElement::remove().
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlClass::Data
{
   Data() 
   : isActive(false) 
   {}
   
   bool isActive;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** 
 * Initializes a new object of the UmlClass class. 
 */
UmlClass::UmlClass()
: data(new Data())
{
}

/** 
 * Initializes a new object of the UmlClass class with an identifier. 
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new object with a new unique identifier, use constructor UmlClassifier() instead.
 * @param id Identifier.
 */
UmlClass::UmlClass(QUuid id)
: super(id)
, data(new Data())
{
}

UmlClass::~UmlClass()
{
   delete data;
}

/** Gets the class name. */
QString UmlClass::className() const
{
   return staticMetaObject.className();
}

/** Gets a list of ports of the class. */
QList<UmlPort*> UmlClass::ports() const
{
   QList<UmlPort*> list;

   QList<UmlElement*> elems = elements();
   QListIterator<UmlElement*> iter(elems);
   while (iter.hasNext())
   {
      auto* port = dynamic_cast<UmlPort*>(iter.next());
      if (port != nullptr)
      {
         list.append(port);
      }
   }

   return list;
}

/** Gets a value indicating whether the class is active. */
bool UmlClass::isActive() const
{
   return data->isActive;
}

/** Sets a value indicating whether the class is active. */
void UmlClass::isActive(bool value)
{
   data->isActive = value;
}

/**
 * Serializes properties of the UmlClass object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlClass::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
   if (read)
   { 
      data->isActive = json[KPropIsActive].toBool();
   }
   else
   { 
      json[KPropIsActive] = data->isActive;
   }
}
