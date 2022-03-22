//---------------------------------------------------------------------------------------------------------------------
// UmlComment.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlComment.
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
#include "UmlComment.h"
#include "PropertyStrings.h"

#include <QJsonObject>

/**
 * @class UmlComment
 * @brief The UmlComment class represents a comment.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * The UmlComment class represents a comment in a diagram. It corresponds to the modeling concept "Comment" in the UML 
 * specification and, like this one, has a "body" property that contains the text of the comment.
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlComment::Data
{
   QString body;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the UmlComment class with a new identifier.
 */
UmlComment::UmlComment()
: data(new Data())
{
}

/**
 * Initializes a new object of the UmlComment class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new object with a new unique identifier, use the constructor without parameters instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlComment::UmlComment(QUuid id)
: super(id)
, data(new Data())
{
}

UmlComment::~UmlComment()
{
   delete data;
}

/** Gets the class name from the static meta object. */
QString UmlComment::className() const
{
   return staticMetaObject.className();
}

/** 
 * Gets a value indicating whether this element is hidden. 
 *
 * This is a GUI feature. It is used to distinguish elements which shall be shown in a project tree view from
 * others. Normally all unnamed elements like this one are hidden, so this function always returns true.
 * @returns Always true.
 */
bool UmlComment::isHidden() const
{
   return true;
}

/**
 * Gets the body of the comment.
 */
QString UmlComment::body() const
{
   return data->body;
}

/**
 * Sets the body of the comment.
 * @param value Body of the comment, i.e. its text.
 */
void UmlComment::setBody(QString value)
{
   data->body = value;
}

/**
 * Serializes properties of the UmlComment object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlComment::serialize(QJsonObject& obj, bool read, int version)
{
   super::serialize(obj, read, version);
   if (read)
   {
      data->body = obj[KPropBody].toString();
   }
   else
   {
      obj[KPropBody] = data->body;
   }
}
