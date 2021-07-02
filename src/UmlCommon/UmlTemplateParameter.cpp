//---------------------------------------------------------------------------------------------------------------------
// UmlTemplateParameter.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlTemplateParameter.
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
#include "UmlTemplateParameter.h"
#include "PropertyStrings.h"
#include "SignatureChars.h"

#include <QAtomicInteger>
#include <QJsonObject>
#include <QTextStream>

/**
 * @class UmlTemplateParameter
 * @brief The UmlTemplateParameter class represents an UML template parameter.
 * @since 1.0
 * @ingroup UmlCommon
 *
 *
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlTemplateParameter::Data
{
   QString                 name;
   QString                 type;
   QString                 defaultValue;
   QString                 constraints;
   QAtomicInteger<quint32> refCount;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** Initializes a new instance of the UmlTemplateParameter class. */
UmlTemplateParameter::UmlTemplateParameter()
: data(new Data())
{
}

UmlTemplateParameter::~UmlTemplateParameter()
{
   delete data;
}

/** Gets the name of the template parameter. */
QString UmlTemplateParameter::name() const
{
   return data->name;
}

/** Sets the name of the template parameter. */
void UmlTemplateParameter::setName(QString value)
{
   data->name = value;
}

/** Gets the type of the template parameter. */
QString UmlTemplateParameter::type() const
{
   return data->type;
}

/** Sets the type of the template parameter. */
void UmlTemplateParameter::setType(QString value)
{
   data->type = value;
}

/** Gets the default value of the template parameter. */
QString UmlTemplateParameter::defaultValue() const
{
   return data->defaultValue;
}

/** Sets the default value of the template parameter. */
void UmlTemplateParameter::setDefaultValue(QString value)
{
   data->defaultValue = value;
}

/** Gets constraints of the template parameter. */
QString UmlTemplateParameter::constraints() const
{
   return data->constraints;
}

/** Sets constraints of the template parameter. */
void UmlTemplateParameter::setConstraints(QString value)
{
   data->constraints = value;
}

/**
 * Serializes properties of the UmlTemplateParameter instance to a JSON object.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlTemplateParameter::serialize(QJsonObject& json, bool read, int version)
{
   Q_UNUSED(version);
   
   if (read)
   {
      data->name = json[KPropName].toString();
      data->type = json[KPropType].toString();
      data->defaultValue = json[KPropDefault].toString();
      data->constraints = json[KPropConstraints].toString();
   }
   else
   {
      json[KPropName] = data->name;
      json[KPropType] = data->type;
      json[KPropDefault] = data->defaultValue;
      json[KPropConstraints] = data->constraints;
   }
}

/**
 * Increments reference count.
 * 
 * Used internally only, do not call!
 */
void UmlTemplateParameter::incRefCount()
{
   ++(data->refCount);
}

/**
 * Decrements reference count and deletes the object if reference count is null.
 * 
 * Used internally only, do not call!
 */
void UmlTemplateParameter::decRefCount()
{
   if (data->refCount > 0) --(data->refCount);
   if (data->refCount == 0)
   {
      delete this;
   }
}

/** Gets the reference count. */
quint32 UmlTemplateParameter::refCount() const
{
   return data->refCount;
}

/** Gets a string representation of the template parameter. */
QString UmlTemplateParameter::toString() const
{
   QString     result;
   QTextStream stream(&result);
   
   stream << data->name << ChColon << " " << data->type;
   if (!data->defaultValue.isEmpty())
   {
      stream << " " << ChEqual << " " << data->defaultValue;
   }
   stream.flush();
   return result;
}
