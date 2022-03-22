//---------------------------------------------------------------------------------------------------------------------
// UmlTemplateBinding.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlTemplateBinding.
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
#include "UmlTemplateBinding.h"
#include "UmlParameterSubstitution.h"
#include "UmlKeywords.h"
#include "PropertyStrings.h"

#include <QJsonArray>

/**
 * @class UmlTemplateBinding
 * @brief The UmlTemplateBinding class models a UML template binding in the UML database.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 *
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlTemplateBinding::Data
{
   QList<UmlParameterSubstitution*> substitutions;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlTemplateBinding class with a new unique identifier.
 */
UmlTemplateBinding::UmlTemplateBinding()
: data(new Data())
{
   setKeywords(KwdBind);
}

/**
 * Initializes a new instance of the UmlTemplateBinding class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlPackage() instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlTemplateBinding::UmlTemplateBinding(QUuid id)
: super(id)
, data(new Data())
{
   setKeywords(KwdBind);
}

UmlTemplateBinding::~UmlTemplateBinding()
{
   delete data;
}

QString UmlTemplateBinding::className() const
{
   return staticMetaObject.className();
}

/**
 * Returns true, since template bindings are always directed.
 */
bool UmlTemplateBinding::isDirected() const
{
   return true;
}

/**
 * Gets a list of parameter substitutions of the template binding.
 */
QList<UmlParameterSubstitution*> UmlTemplateBinding::substitutions() const
{
   return QList<UmlParameterSubstitution*>(data->substitutions);
}

/**
 * Appends a parameter substitution to the template binding.
 */
void UmlTemplateBinding::append(UmlParameterSubstitution* subst)
{
   if (subst != nullptr)
   {
      data->substitutions.append(subst);
   }
}

/**
 * Removes a parameter substitution from the template binding.
 */
void UmlTemplateBinding::remove(UmlParameterSubstitution* subst)
{
   if (subst != nullptr)
   {
      data->substitutions.removeOne(subst);
   }
}

/**
 * Clears all parameter substitutions from the template binding.
 */
void UmlTemplateBinding::clear()
{
   for (auto* subst : data->substitutions)
   {
      delete subst;
   }

   data->substitutions.clear();
}

/**
 * Disposes the template binding.
 *
 * This function is called by UmlProject::dispose() to reset all intrusive pointers owned by the binding. Do not call
 * it directly.
 */
void UmlTemplateBinding::dispose(bool disposing)
{
   clear();
   super::dispose(disposing);
}

/**
 * Serializes properties of the UmlTemplateBinding instance to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlTemplateBinding::serialize(QJsonObject& json, bool read, bool flat, int version)
{
   QJsonArray array;

   super::serialize(json, read, flat, version);
   if (read)
   {
      array = json[KPropSubstitutions].toArray();
      for (int index = 0; index < array.size(); ++index)
      {
         auto obj = array[index].toObject();
         auto* subst = new UmlParameterSubstitution();
         subst->serialize(obj, read, version);
         append(subst);
      }
   }
   else
   {
      for (auto* subst : data->substitutions)
      {
         QJsonObject obj;
         subst->serialize(obj, read, version);
         array.append(obj);
      }

      json[KPropSubstitutions] = array;
   }
}
