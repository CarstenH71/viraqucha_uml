//---------------------------------------------------------------------------------------------------------------------
// UmlDependency.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlDependency.
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
#include "UmlDependency.h"
#include "UmlKeywords.h"

#include "Label.h"
#include "PropertyStrings.h"
#include "SignatureChars.h"
#include "SignatureTools.h"

#include <QTextStream>

/**
 * @class UmlDependency
 * @brief The UmlDependency class models a dependency relationship between two UML elements.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * The UmlDependency class models a dependency relationship between two UML elements, e.g. two UML packages. A 
 * dependency is always directed. It may have different keywords or stereotypes, depending on the semantics of the 
 * dependency (e.g. &quot;use&quot;, &quot;import&quot;, &quot;merge&quot;), a name, a comment and a visibility.
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlDependency::Data
{
   QString        name;
   QString        comment;
   VisibilityKind visibility;
   QString        stereotype;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlDependency class with a new identifier.
 */
UmlDependency::UmlDependency()
: data(new Data())
{
}

/**
 * Initializes a new instance of the UmlDependency class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlComment() instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlDependency::UmlDependency(QUuid id)
: super(id)
, data(new Data())
{
}

UmlDependency::~UmlDependency()
{
   delete data;
}

/** Gets the class name from the static meta object. */
QString UmlDependency::className() const
{
   return staticMetaObject.className();
}

/** Gets the name of the UML dependency. */
QString UmlDependency::name() const 
{
   return data->name;
}

/** Sets the name of the UML dependency. */
void UmlDependency::setName(QString value)
{
   data->name = value;
}

/** Gets the comment of the UML dependency. */
QString UmlDependency::comment() const
{
   return data->comment;
}

/** Sets the comment of the UML dependency. */
void UmlDependency::setComment(QString value)
{
   data->comment = value;
}

/** Gets the visibility of the UML dependency. */
VisibilityKind UmlDependency::visibility() const
{
   return data->visibility;
}

/** Sets the visibility of the UML dependency. */
void UmlDependency::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

/** Gets the stereotype of the UML dependency. */
QString UmlDependency::stereotype() const
{
   return data->stereotype;
}

/** Sets the stereotype of the UML dependency. */
void UmlDependency::setStereotype(QString value)
{
   data->stereotype = value;
}

/**
 * Returns true, since UML dependencies are always directed.
 */
bool UmlDependency::isDirected() const
{
   return true;
}

/** 
 * Gets the vector of labels.
 */
QVector<Label*> UmlDependency::labels()
{
   QVector<Label*> result(5);
   for (int index = 0; index < result.length(); ++index)
   {
      result[index] = new Label();
      update(index, result[index]);
   }

   return result;
}

/**
 * Serializes properties of the UmlDependency instance to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlDependency::serialize(QJsonObject& json, bool read, int version)
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

/** Updates a single label. */
void UmlDependency::update(int index, Label* label)
{
   switch (index)
   {
   case 0:
      label->setText(makeAnnotation(keywords(), stereotype()) + name());
      break;
   case 1:
   case 2:
   case 3:
   case 4:
   default:
      break;
   }
}
