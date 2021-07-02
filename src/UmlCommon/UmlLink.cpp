//---------------------------------------------------------------------------------------------------------------------
// UmlLink.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlLink.
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
#include "UmlLink.h"
#include "UmlElement.h"
#include "UmlProject.h"
#include "PropertyStrings.h"

#include <QJsonArray>
#include <QJsonObject>

/**
 * @class UmlLink
 * @brief The UmlLink class is the base class for all connectors.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * The UmlLink class is the base class for all connectors in the data model. It corresponds to the modeling concept 
 * "Relationship" in the UML specification and is similar to this derived from the class UmlElement. In this way, an 
 * object of this class can also be linked to another object of the same class (Link -> Link/Element).
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlLink::Data
{
   UmlElementPtr source;
   UmlElementPtr target;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlLink class with a new identifier.
 */
UmlLink::UmlLink()
: data(new Data())
{
}

/**
 * Initializes a new instance of the UmlLink class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlLink() instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlLink::UmlLink(QUuid id)
: super(id)
, data(new Data())
{
}

UmlLink::~UmlLink()
{
   delete data;
}

QString UmlLink::className() const
{
   return staticMetaObject.className();
}

/**
 * Gets the source element.
 */
UmlElement* UmlLink::source() const
{
   return data->source.pointee();
}

/**
 * Sets the source element and connects the element with this link.
 */
void UmlLink::setSource(UmlElement* element)
{
   if (!data->source.isNull()) data->source->unlink(this);
   data->source = UmlElementPtr(element);
   if (!data->source.isNull()) data->source->linkto(this);
}

/**
 * Gets the target element.
 */
UmlElement* UmlLink::target() const
{
   return data->target.pointee();
}

/**
 * Sets the target element and connects the element with this link.
 */
void UmlLink::setTarget(UmlElement* element)
{
   if (!data->target.isNull()) data->target->unlink(this);
   data->target = UmlElementPtr(element);
   if (!data->target.isNull()) data->target->linkto(this);
}

/**
 * Gets a value indicating whether the link is directed or not. Default is false.
 */
bool UmlLink::isDirected() const
{
   return false;
}

/** Always returns true. */
bool UmlLink::isHidden() const
{
   return true;
}

/** Gets a value indicating whether the element is a link or not. */
bool UmlLink::isLink() const
{
   return true;
}

/**
 * Swaps source and target element if the link is not directed.
 */
void UmlLink::swap()
{
   if (isDirected()) return;
   UmlElementPtr src(data->source);
   data->source = data->target;
   data->target = src;
}

/**
 * Disposes the link.
 *
 * This function is called by UmlProject::dispose() to reset all intrusive pointers owned by the link. Do not call
 * directly.
 */
void UmlLink::dispose(bool disposing)
{
   if (!data->source.isNull())
   {
      data->source->unlink(this);
      data->source = nullptr;
   }
   
   if (!data->target.isNull())
   {
      data->target->unlink(this);
      data->target = nullptr;
   }

   super::dispose(disposing);
}

/**
 * Serializes properties of the UmlLink instance to a JSON file.
 *
 * @param json QJsonObject instance to be used for serialization.
 * @param read If true: reads from the QJsonObject; otherwise writes to the QJsonObject.
 * @param version Version of the JSON file format.
*/
void UmlLink::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
   if (read)
   {
      QUuid srcId(json[KPropSource].toString());
      QUuid tgtId(json[KPropTarget].toString());

      UmlElement* src = nullptr;
      UmlElement* tgt = nullptr;
      if (project()->find(srcId, &src) && project()->find(tgtId, &tgt))
      {
         setSource(src);
         setTarget(tgt);
      }
   }
   else
   {
      json[KPropSource] = data->source->identifier().toString();
      json[KPropTarget] = data->target->identifier().toString();
   }
}
