//---------------------------------------------------------------------------------------------------------------------
// UmlAttribute.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlAttribute.
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
#include "UmlAttribute.h"
#include "PropertyStrings.h"
#include "SignatureChars.h"
#include "SignatureTools.h"

#include "../UmlCommon/PropertyStrings.h"

#include <QTextStream>

/**
 * @class UmlAttribute
 * @brief The UmlAttribute class stores information about an attribute of a UML classifier.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct UmlAttribute::Data
{
   Data()
   : visibility(VisibilityKind::Public)
   , isOrdered(false)
   , isUnique(false)
   , lower(1)
   , upper(1)
   , aggregation(AggregationKind::None)
   , isComposite(false)
   , isDerived(false)
   , isDerivedUnion(false)
   , isID(false)
   , isStatic(false)
   , isReadOnly(false)
   {}

   QString         name;
   QString         comment;
   VisibilityKind  visibility;
   QString         stereotype;
   bool            isOrdered;
   bool            isUnique;
   quint32         lower;
   quint32         upper;
   AggregationKind aggregation;
   bool            isComposite;
   bool            isDerived;
   bool            isDerivedUnion;
   bool            isID;
   bool            isStatic;
   bool            isReadOnly;
   QString         type;
   QString         defaultValue;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlAttribute class with a new identifier.
 */
UmlAttribute::UmlAttribute()
: data(new Data())
{
}

/**
 * Initializes a new instance of the UmlAttribute class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlAttribute() instead.
 *
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlAttribute::UmlAttribute(QUuid id)
: super(id)
, data(new Data())
{
}

UmlAttribute::~UmlAttribute()
{
   delete data;
}

QString UmlAttribute::className() const
{
   return staticMetaObject.className();
}

/** Gets the name of the attribute. */
QString UmlAttribute::name() const
{
   return data->name;
}

/** Sets the name of the attribute. */
void UmlAttribute::setName(QString value)
{
   data->name = value;
}

/** Gets the comment of the attribute. */
QString UmlAttribute::comment() const
{
   return data->comment;
}

/** Sets the comment of the attribute. */
void UmlAttribute::setComment(QString value)
{
   data->comment = value;
}

/** Gets the visibility of the attribute. */
VisibilityKind UmlAttribute::visibility() const
{
   return data->visibility;
}

/** Sets the visibility of the attribute. */
void UmlAttribute::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

/** Gets the stereotype of the attribute. */
QString UmlAttribute::stereotype() const
{
   return data->stereotype;
}

/** Sets the stereotype of the attribute. */
void UmlAttribute::setStereotype(QString value)
{
   data->stereotype = value;
}

/** Gets a value indicating whether the attribute is ordered (collection). */
bool UmlAttribute::isOrdered() const
{
   return data->isOrdered;
}

/** Sets a value indicating whether the attribute is ordered (collection). */
void UmlAttribute::isOrdered(bool value)
{
   data->isOrdered = value;
}

/** Gets a value indicating whether the attribute is unique. */
bool UmlAttribute::isUnique() const
{
   return data->isUnique;
}

/** Sets a value indicating whether the attribute is unique. */
void UmlAttribute::isUnique(bool value)
{
   data->isUnique = value;
}

/** Gets the lower bound of the multiplicity. */
quint32 UmlAttribute::lower() const
{
   return data->lower;
}

/** Sets the lower bound of the multiplicity. */
void UmlAttribute::setLower(quint32 value)
{
   data->lower = value;
}

/** Gets the upper bound of the multiplicity. */
quint32 UmlAttribute::upper() const
{
   return data->upper;
}

/** Sets the upper bound of the multiplicity. */
void UmlAttribute::setUpper(quint32 value)
{
   data->upper = value;
}

/** Gets the aggregation kind of the attribute. */
AggregationKind UmlAttribute::aggregation() const
{
   return data->aggregation;
}

/** Sets the aggregation kind of the attribute. */
void UmlAttribute::setAggregation(AggregationKind value)
{
   data->aggregation = value;
}

/** Gets a value indicating whether the attribute is composite. */
bool UmlAttribute::isComposite() const
{
   return data->isComposite;
}

/** Sets a value indicating whether the attribute is composite. */
void UmlAttribute::isComposite(bool value)
{
   data->isComposite = value;
}

/** Gets a value indicating whether the attribute is derived. */
bool UmlAttribute::isDerived() const
{
   return data->isDerived;
}

/** Sets a value indicating whether the attribute is derived. */
void UmlAttribute::isDerived(bool value)
{
   data->isDerived = value;
}

/** Gets a value indicating whether the attribute is derived union. */
bool UmlAttribute::isDerivedUnion() const
{
   return data->isDerivedUnion;
}

/** Sets a value indicating whether the attribute is derived union. */
void UmlAttribute::isDerivedUnion(bool value)
{
   data->isDerivedUnion = value;
}

/** Gets a value indicating whether the attribute is an identifier. */
bool UmlAttribute::isID() const
{
   return data->isID;
}

/** Sets a value indicating whether the attribute is an identifier. */
void UmlAttribute::isID(bool value)
{
   data->isID = value;
}

/** Gets a value indicating whether the attribute is static. */
bool UmlAttribute::isStatic() const
{
   return data->isStatic;
}

/** Sets a value indicating whether the attribute is static. */
void UmlAttribute::isStatic(bool value)
{
   data->isStatic = value;
}

/** Gets a value indicating whether the attribute is read-only. */
bool UmlAttribute::isReadOnly() const
{
   return data->isReadOnly;
}

/** Sets a value indicating whether the attribute is read-only. */
void UmlAttribute::isReadOnly(bool value)
{
   data->isReadOnly = value;
}

/** Gets the (data)type of the attribute. */
QString UmlAttribute::type() const
{
   return data->type;
}

/** Sets the (data)type of the attribute. */
void UmlAttribute::setType(QString value)
{
   data->type = value;
}

/** Gets the default value of the attribute. */
QString UmlAttribute::defaultValue() const
{
   return data->defaultValue;
}

/** Sets the default value of the attribute. */
void UmlAttribute::setDefaultValue(QString value)
{
   data->defaultValue = value;
}

/**
 * Gets the signature of the attribute.
 *
 * The signature of an attribute is a concatenation of its visibility, name, type, multiplicity, default value and its
 * property modifiers. It is shown in the &quot;attributes&quot; compartment of a classifier.
 */
QString UmlAttribute::signature() const
{
   QString result;
   QTextStream stream(&result);

   stream << toChar(visibility()) << ChSpace;
   if (isDerived()) stream << ChSlash;
   stream << name() << ChColon << ChSpace << type() << makeRange(lower(), upper());
   if (!defaultValue().isEmpty())
   {
      stream << ChSpace << ChEqual << ChSpace << defaultValue();
   }

   // Prop modifier... TODO

   stream.flush();
   return result;
}

/** Gets a string representation of this object. */
QString UmlAttribute::toString() const
{
   return signature();
}

/**
 * Serializes properties of the UmlAttribute object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlAttribute::serialize(QJsonObject& json, bool read, bool flat, int version)
{
   super::serialize(json, read, flat, version);
   if (read)
   {
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->visibility = (VisibilityKind)json[KPropVisibility].toInt();
      data->stereotype = json[KPropStereotype].toString();
      data->isOrdered = json[KPropIsOrdered].toBool();
      data->isUnique = json[KPropIsUnique].toBool();
      data->lower = (quint32)json[KPropLower].toInt();
      data->upper = (quint32)json[KPropUpper].toInt();
      data->aggregation = (AggregationKind)json[KPropAggregation].toInt();
      data->isComposite = json[KPropIsComposite].toBool();
      data->isDerived = json[KPropIsDerived].toBool();
      data->isDerivedUnion = json[KPropIsDerivedUnion].toBool();
      data->isID = json[KPropIsID].toBool();
      data->isStatic = json[KPropIsStatic].toBool();
      data->isReadOnly = json[KPropIsReadOnly].toBool();
      data->type = json[KPropType].toString();
      data->defaultValue = json[KPropDefault].toString();
   }
   else
   {
      json[KPropName] = data->name;
      json[KPropComment] = data->comment;
      json[KPropVisibility] = (int)data->visibility;
      json[KPropStereotype] = data->stereotype;
      json[KPropIsOrdered] = data->isOrdered;
      json[KPropIsUnique] = data->isUnique;
      json[KPropLower] = (int)data->lower;
      json[KPropUpper] = (int)data->upper;
      json[KPropAggregation] = (int)data->aggregation;
      json[KPropIsComposite] = data->isComposite;
      json[KPropIsDerived] = data->isDerived;
      json[KPropIsDerivedUnion] = data->isDerivedUnion;
      json[KPropIsID] = data->isID;
      json[KPropIsStatic] = data->isStatic;
      json[KPropIsReadOnly] = data->isReadOnly;
      json[KPropType] = data->type;
      json[KPropDefault] = data->defaultValue;
   }
}
