//---------------------------------------------------------------------------------------------------------------------
// UmlRealization.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlRealization.
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
#include "UmlRealization.h"

#include "../UmlCommon/PropertyStrings.h"

/**
 * @class UmlRealization
 * @brief The UmlRealization class stores information about a realization relationship between two UML elements.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 * In the ViraquchaUML datamodel a realization is defined as a named and stereotyped element. Since it is named, it 
 * also has a visibility (public by default).
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlRealization::Data
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

UmlRealization::UmlRealization()
: data(new Data())
{
}

UmlRealization::UmlRealization(QUuid id)
: super(id)
, data(new Data())
{
}

UmlRealization::~UmlRealization()
{
   delete data;
}

QString UmlRealization::className() const
{
   return staticMetaObject.className();
}

QString UmlRealization::name() const
{
   return data->name;
}

void UmlRealization::setName(QString value)
{
   data->name = value;
}

QString UmlRealization::comment() const
{
   return data->comment;
}

void UmlRealization::setComment(QString value)
{
   data->comment = value;
}

VisibilityKind UmlRealization::visibility() const
{
   return data->visibility;
}

void UmlRealization::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

QString UmlRealization::stereotype() const
{
   return data->stereotype;
}

void UmlRealization::setStereotype(QString value)
{
   data->stereotype = value;
}

void UmlRealization::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
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
