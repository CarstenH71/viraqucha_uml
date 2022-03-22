//---------------------------------------------------------------------------------------------------------------------
// UmlParameter.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlParameter.
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
#include "UmlParameter.h"
#include "SignatureChars.h"
#include "PropertyStrings.h"

#include "../UmlCommon/PropertyStrings.h"

#include <QTextStream>

/**
 * @class UmlParameter
 * @brief The UmlParameter class stores information about a parameter of an operation in the ViraquchaUML database.
 * @since 0.1.0
 * @ingroup UmlClassifiers
 *
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct UmlParameter::Data
{
   Data()
   : direction(ParameterDirectionKind::Undefined)
   , effect(ParameterEffectKind::Undefined)
   , isException(false)
   , isStream(false)
   , isOrdered(false)
   , isUnique(false)
   , lower(1)
   , upper(1)
   {}

   QString                 name;
   QString                 comment;
   QString                 defaultValue;
   ParameterDirectionKind  direction;
   ParameterEffectKind     effect;
   bool                    isException;
   bool                    isStream;
   QString                 type;
   bool                    isOrdered;
   bool                    isUnique;
   quint32                 lower;
   quint32                 upper;
   QAtomicInteger<quint32> refCount;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

UmlParameter::UmlParameter()
: data(new Data())
{
}

UmlParameter::~UmlParameter()
{
   delete data;
}

/**
 * Gets the name of the parameter.
 */
QString UmlParameter::name() const
{
   return data->name;
}

/**
 * Sets the name of the parameter.
 */
void UmlParameter::setName(QString value)
{
   data->name = value;
}

/**
 * Gets the comment of the parameter.
 */
QString UmlParameter::comment() const
{
   return data->comment;
}

/**
 * Sets the comment of the parameter.
 */
void UmlParameter::setComment(QString value)
{
   data->comment = value;
}

/**
 * Gets the default value of the parameter.
 */
QString UmlParameter::defaultValue() const
{
   return data->defaultValue;
}

/**
 * Sets the default value of the parameter.
 */
void UmlParameter::setDefaultValue(QString value)
{
   data->defaultValue = value;
}

/**
 * Gets the direction (in, out, inout) of the parameter.
 */
ParameterDirectionKind UmlParameter::direction() const
{
   return data->direction;
}

/**
 * Sets the direction (in, out, inout) of the parameter.
 */
void UmlParameter::setDirection(ParameterDirectionKind value)
{
   data->direction = value;
}

/**
 * Gets the effect of the parameter.
 */
ParameterEffectKind UmlParameter::effect() const
{
   return data->effect;
}

/**
 * Sets the effect of the parameter.
 */
void UmlParameter::setEffect(ParameterEffectKind value)
{
   data->effect = value;
}

/**
 * Gets a value indicating whether the parameter is an exception.
 */
bool UmlParameter::isException() const
{
   return data->isException;
}

/**
 * Sets a value indicating whether the parameter is an exception.
 */
void UmlParameter::isException(bool value)
{
   data->isException = value;
}

/**
 * Gets a value indicating whether the parameter is a stream.
 */
bool UmlParameter::isStream() const
{
   return data->isStream;
}

/**
 * Sets a value indicating whether the parameter is a stream.
 */
void UmlParameter::isStream(bool value)
{
   data->isStream = value;
}

/**
 * Gets the data type of the parameter.
 */
QString UmlParameter::type() const
{
   return data->type;
}

/**
 * Sets the data type of the parameter.
 */
void UmlParameter::setType(QString value)
{
   data->type = value;
}

bool UmlParameter::isOrdered() const
{
   return data->isOrdered;
}

void UmlParameter::isOrdered(bool value)
{
   data->isOrdered = value;
}

bool UmlParameter::isUnique() const
{
   return data->isUnique;
}

void UmlParameter::isUnique(bool value)
{
   data->isUnique = value;
}

quint32 UmlParameter::lower() const
{
   return data->lower;
}

void UmlParameter::setLower(quint32 value)
{
   data->lower = value;
}

quint32 UmlParameter::upper() const
{
   return data->upper;
}

void UmlParameter::setUpper(quint32 value)
{
   data->upper = value;
}

/**
 * Gets the signature of the parameter.
 */
QString UmlParameter::signature() const
{
   QString result;
   QTextStream stream(&result);

   stream << name() << ChColon << ChSpace << type();
   if (!defaultValue().isEmpty())
   {
      stream << ChSpace << ChEqual << ChSpace << defaultValue();
   }

   stream.flush();
   return result;
}

/**
 * Serializes properties of the UmlParameter instance to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlParameter::serialize(QJsonObject& json, bool read, int version)
{
   Q_UNUSED(version);
   
   if (read)
   {
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->defaultValue = json[KPropDefault].toString();
      data->direction = (ParameterDirectionKind)json[KPropDirectionKind].toInt();
      data->effect = (ParameterEffectKind)json[KPropEffektKind].toInt();
      data->isException = json[KPropIsException].toBool();
      data->isStream = json[KPropIsStream].toBool();
      data->type = json[KPropType].toString();
      data->isOrdered = json[KPropIsOrdered].toBool();
      data->isUnique = json[KPropIsUnique].toBool();
      data->lower = (quint32)json[KPropLower].toDouble();
      data->upper = (quint32)json[KPropUpper].toDouble();
   }
   else
   {
      json[KPropName] = data->name;
      json[KPropComment] = data->comment;
      json[KPropDefault] = data->defaultValue;
      json[KPropDirectionKind] = (int)data->direction;
      json[KPropEffektKind] = (int)data->effect;
      json[KPropIsException] = data->isException;
      json[KPropIsStream] = data->isStream;
      json[KPropType] = data->type;
      json[KPropIsOrdered] = data->isOrdered;
      json[KPropIsUnique] = data->isUnique;
      json[KPropLower] = (double)data->lower;
      json[KPropUpper] = (double)data->upper;
   }
}

 void UmlParameter::incRefCount()
 {
    ++(data->refCount);
 }

 void UmlParameter::decRefCount()
 {
    if (data->refCount > 0) --(data->refCount);
    if (data->refCount == 0)
    {
       delete this;
    }
 }

 quint32 UmlParameter::refCount() const
 {
    return data->refCount;
 }
