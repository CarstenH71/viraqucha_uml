//---------------------------------------------------------------------------------------------------------------------
// UmlComponent.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlComponent.
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
#include "UmlComponent.h"
#include "PropertyStrings.h"

/**
 * @class UmlComponent
 * @brief The UmlComponent class stores properties of a UML Component element.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 * This class extends its base class by further properties specific to UML Component elements.
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlComponent::Data
{
   Data()
   : isActive(false)
   , isDirectlyInstantiated(false)
   {}

   bool isActive;
   bool isDirectlyInstantiated;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** Initializes a new object of the UmlComponent class. */
UmlComponent::UmlComponent()
: data(new Data())
{
}

/** 
 * Initializes a new object of the UmlComponent class with an identifier. 
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new object with a new unique identifier, use constructor UmlClassifier() instead.
 * @param id Identifier.
 */
UmlComponent::UmlComponent(QUuid id)
: super(id)
, data(new Data())
{
}

UmlComponent::~UmlComponent()
{
   delete data;
}

/** Gets the class name. */
QString UmlComponent::className() const
{
   return staticMetaObject.className();
}

/** Gets a value indicating whether the component is active. */
bool UmlComponent::isActive() const
{
   return data->isActive;
}

/** Sets a value indicating whether the component is active. */
void UmlComponent::isActive(bool value)
{
   data->isActive = value;
}

/** Gets a value indicating whether the component is directly instantiated. */
bool UmlComponent::isDirectlyInstantiated() const
{
   return data->isDirectlyInstantiated;
}

/** Sets a value indicating whether the component is directly instantiated. */
void UmlComponent::isDirectlyInstantiated(bool value)
{
   data->isDirectlyInstantiated = value;
}

/**
 * Serializes properties of the UmlComponent object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlComponent::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
   if (read)
   {
      data->isActive = json[KPropIsActive].toBool();
      data->isDirectlyInstantiated = json[KPropIsDirectlyInst].toBool();
   }
   else
   {
      json[KPropIsActive] = data->isActive;
      json[KPropIsDirectlyInst] = data->isDirectlyInstantiated;
   }
}
