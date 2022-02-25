//---------------------------------------------------------------------------------------------------------------------
// UmlEnumeration.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlEnumeration.
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
#include "UmlEnumeration.h"
#include "Literal.h"
#include "PropertyStrings.h"

#include "../UmlCommon/UmlKeywords.h"

#include <QJsonArray>
#include <QList>
#include <QListIterator>

/**
 * @class UmlEnumeration
 * @brief The UmlEnumeration class stores properties of a UML Enumeration element.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 * This class extends its base class by further properties specific to UML Enumeration elements, namely literals. You
 * may obtain the list of Literal objects stored by this class by calling function literals(). Base functions append()
 * and remove() are overloaded to accept Literal objects as well. To clear the list of Literal objects use function 
 * clearLiterals().
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlEnumeration::Data
{
   QList<Literal*> literals;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the UmlEnumeration class.
 */
UmlEnumeration::UmlEnumeration()
: data(new Data())
{
   setKeywords(KwdEnumeration);
}

/**
 * Initializes a new instance of the UmlEnumeration class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlClassifier() instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlEnumeration::UmlEnumeration(QUuid id)
: super(id)
, data(new Data())
{
   setKeywords(KwdEnumeration);
}

UmlEnumeration::~UmlEnumeration()
{
   clearLiterals();
   delete data;
}

/** Gets the class name. */
QString UmlEnumeration::className() const
{
   return staticMetaObject.className();
}

/** Gets the list of Literal objects of the enumeration. */
QList<Literal*> UmlEnumeration::literals() const
{
   return QList<Literal*>(data->literals);
}

/** 
 * Appends a Literal object to the enumeration. 
 * 
 * UmlEnumeration takes ownership of the Literal object. That is, if it is not removed, it will be deleted on 
 * destruction of the UmlEnumeration object.
 * @param obj Literal object to be added.
 */
void UmlEnumeration::append(Literal* obj)
{
   if (obj != nullptr)
   {
      data->literals.append(obj);
   }
}

/** 
 * Removes a Literal object from the enumeration. 
 * 
 * The Literal object is not deleted: the ownership is passed to the caller which must delete it!
 * @param obj Literal object to be removed.
 */
void UmlEnumeration::remove(Literal* obj)
{
   if (obj != nullptr)
   {
      data->literals.removeOne(obj);
   }
}

/** Clears all Literal objects from the enumeration. */
void UmlEnumeration::clearLiterals()
{
   for (auto* lit : data->literals)
   {
      delete lit;
   }

   data->literals.clear();
}

/**
 * Serializes properties of the UmlEnumeration object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlEnumeration::serialize(QJsonObject& json, bool read, bool flat, int version)
{
   QJsonArray array;
   
   super::serialize(json, read, flat, version);
   if (read)
   { 
      array = json[KPropLiterals].toArray();
      for (int index = 0; index < array.count(); ++index)
      {
         auto obj = array[index].toObject();
         append(new Literal(obj[KPropNumber].toInt(), obj[KPropSymbol].toString()));
      }
   }
   else
   { 
      for (auto* lit : data->literals)
      {
         QJsonObject obj;
         obj[KPropNumber] = lit->number();
         obj[KPropSymbol] = lit->symbol();
         array.append(obj);
      }

      json[KPropLiterals] = array;
   }
}
