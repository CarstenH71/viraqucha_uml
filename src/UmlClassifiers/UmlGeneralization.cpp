//---------------------------------------------------------------------------------------------------------------------
// UmlGeneralization.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlGeneralization.
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
#include "UmlGeneralization.h"

#include "../UmlCommon/PropertyStrings.h"

/**
 * @class UmlGeneralization
 * @brief The UmlGeneralization class stores information about a generalization relationship between two UML classifier.
 * @since 0.1.0
 * @ingroup UmlClassifiers
 *
 * In the ViraquchaUML datamodel a generalization is defined as a named and stereotyped element. Since it is named, it 
 * also has a visibility (public by default).
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlGeneralization::Data
{
   Data()
   : visibility(VisibilityKind::Public)
   {}

   QString        name;
   QString        comment;
   VisibilityKind visibility;
   QString        stereotype;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

UmlGeneralization::UmlGeneralization()
: data(new Data())
{
}

UmlGeneralization::UmlGeneralization(QUuid id)
: super(id)
, data(new Data())
{
}

UmlGeneralization::~UmlGeneralization()
{
   delete data;
}

QString UmlGeneralization::className() const
{
   return staticMetaObject.className();
}

/** Gets the name of the generalization. */
QString UmlGeneralization::name() const
{
   return data->name;
}

/** Sets the name of the generalization. */
void UmlGeneralization::setName(QString value)
{
   data->name = value;
}

/** Gets the comment of the generalization. */
QString UmlGeneralization::comment() const
{
   return data->comment;
}

/** Sets the comment of the generalization. */
void UmlGeneralization::setComment(QString value)
{
   data->comment = value;
}

/** Gets the visibility of the generalization. */
VisibilityKind UmlGeneralization::visibility() const
{
   return data->visibility;
}

/** Sets the visibility of the generalization. */
void UmlGeneralization::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

/** Gets the stereotype of the generalization. */
QString UmlGeneralization::stereotype() const
{
   return data->stereotype;
}

/** Sets the stereotype of the generalization. */
void UmlGeneralization::setStereotype(QString value)
{
   data->stereotype = value;
}

/**
 * Serializes properties of the UmlGeneralization object to a JSON file.
 * 
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlGeneralization::serialize(QJsonObject& json, bool read, bool flat, int version)
{
   super::serialize(json, read, flat, version);
   if (read)
   {
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->visibility = (VisibilityKind)json[KPropVisibility].toInt();
      data->stereotype = json[KPropStereotype].toString();
   }
   else
   {
      json[KPropName] = data->name;
      json[KPropComment] = data->comment;
      json[KPropVisibility] = (int)data->visibility;
      json[KPropStereotype] = data->stereotype;
   }
}
