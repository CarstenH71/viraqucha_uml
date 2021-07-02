//---------------------------------------------------------------------------------------------------------------------
// UmlPrimitiveType.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlPrimitiveType.
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
#include "UmlPrimitiveType.h"

#include "../UmlCommon/PropertyStrings.h"
#include "../UmlCommon/SignatureTools.h"
#include "../UmlCommon/UmlKeywords.h"

/**
 * @class UmlPrimitiveType
 * @brief The UmlPrimitiveType class stores information about a primitive type.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 * In UML, a primitive type is a kind of a data type. In ViraquchaUML however, 
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct UmlPrimitiveType::Data
{
   Data()
   : visibility(VisibilityKind::Public)
   {}

   QString         name;
   QString         comment;
   VisibilityKind  visibility;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlSignal class.
 *
 * Sets keyword /"primitive/" automatically.
 */
UmlPrimitiveType::UmlPrimitiveType()
: data(new Data())
{
   setKeywords(KwdPrimitive);
}

/**
 * Initializes a new instance of the UmlSignal class with a given identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlAttribute() instead. Sets keyword 
 * /"primitive/" automatically.
 *
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlPrimitiveType::UmlPrimitiveType(QUuid id)
: super(id)
, data(new Data())
{
   setKeywords(KwdPrimitive);
}

/** Finalizes an instance of the UmlPrimitiveType class. */
UmlPrimitiveType::~UmlPrimitiveType()
{
   delete data;
}

QString UmlPrimitiveType::className() const
{
   return staticMetaObject.className();
}

/** Gets the name of the primitive type. */
QString UmlPrimitiveType::name() const
{
   return data->name;
}

/** Sets the name of the primitive type. */
void UmlPrimitiveType::setName(QString value)
{
   data->name = value;
}

/** Gets the comment of the primitive type. */
QString UmlPrimitiveType::comment() const
{
   return data->comment;
}

/** Sets the comment of the primitive type. */
void UmlPrimitiveType::setComment(QString value)
{
   data->comment = value;
}

/** Gets the visibility of the primitive type. */
VisibilityKind UmlPrimitiveType::visibility() const
{
   return data->visibility;
}

/** Sets the visibility of the primitive type. */
void UmlPrimitiveType::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

/**
 * Serializes properties of the UmlPrimitiveType instance to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlPrimitiveType::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
   if (read)
   { 
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->visibility = (VisibilityKind)json[KPropVisibility].toInt();
   }
   else
   { 
      json[KPropName] = data->name;
      json[KPropComment] = data->comment;
      json[KPropVisibility] = (int)data->visibility;
   }
}

QString UmlPrimitiveType::toString() const
{
   return makeAnnotation(keywords(), "") + name();
}
