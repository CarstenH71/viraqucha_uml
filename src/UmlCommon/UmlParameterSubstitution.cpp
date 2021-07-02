//---------------------------------------------------------------------------------------------------------------------
// UmlParameterSubstitution.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlParameterSubstitution.
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
#include "UmlParameterSubstitution.h"
#include "PropertyStrings.h"

/**
 * @class UmlParameterSubstitution
 * @brief The UmlParameterSubstitution class models a parameter substitution for templated UML elements.
 * @since 1.0
 * @ingroup Common
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct UmlParameterSubstitution::Data
{
   QString templParam;
   QString actualParam;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
UmlParameterSubstitution::UmlParameterSubstitution()
: data(new Data())
{
}

UmlParameterSubstitution::~UmlParameterSubstitution()
{
   delete data;
}

/**
 * @brief Gets the name of the template parameter that shall be substituted.
 */
QString UmlParameterSubstitution::templParam() const
{
   return data->templParam;
}

/**
 * @brief Sets the name of the template parameter that shall be substituted.
 */
void UmlParameterSubstitution::setTemplParam(QString value)
{
   data->templParam = value;
}

/**
 * @brief Gets the name of the actual parameter that substitutes the template parameter.
 */
QString UmlParameterSubstitution::actualParam() const
{
   return data->actualParam;
}

/**
 * @brief Sets the name of the actual parameter that substitutes the template parameter.
 */
void UmlParameterSubstitution::setActualParam(QString value)
{
   data->actualParam = value;
}

/**
 * @brief Serializes properties of the UmlParameterSubstitution instance to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlParameterSubstitution::serialize(QJsonObject& json, bool read, int version)
{
   if (read)
   {
      data->actualParam = json[KPropActualParam].toString();
      data->templParam = json[KPropTemplParam].toString();
   }
   else
   {
      json[KPropActualParam] = data->actualParam;
      json[KPropTemplParam] = data->templParam;
   }
}
