//---------------------------------------------------------------------------------------------------------------------
// UmlModel.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlModel.
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
#include "UmlModel.h"
#include "UmlKeywords.h"
#include "PropertyStrings.h"

/**
 * @class UmlModel
 * @brief The UmlModel class represents a model with a viewpoint in the UML project.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * The UmlModel class represents a model of a UML project. Models are packages with a viewpoint that determines the
 * view on a system.
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlModel::Data
{
   QString viewpoint;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlModel class.
 */
UmlModel::UmlModel()
: data(new Data())
{
   setKeywords(KwdModel);
}

/**
 * Initializes a new instance of the UmlModel class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlComment() instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlModel::UmlModel(QUuid id)
: super(id)
, data(new Data())
{
   setKeywords(KwdModel);
}

UmlModel::~UmlModel()
{
   delete data;
}

QString UmlModel::className() const
{
   return staticMetaObject.className();
}

/**
 * Gets the viewpoint of the model.
 */
QString UmlModel::viewpoint() const
{
   return data->viewpoint;
}

/**
 * Sets the viewpoint of the model.
 */
void UmlModel::setViewpoint(QString value)
{
   data->viewpoint = value;
}

/**
 * Serializes properties of the UmlModel instance to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlModel::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
   if (read)
   {
      data->viewpoint = json[KPropViewpoint].toString();
   }
   else
   {
      json[KPropViewpoint] = data->viewpoint;
   }
}
