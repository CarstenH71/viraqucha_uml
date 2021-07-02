//---------------------------------------------------------------------------------------------------------------------
// UmlPort.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlPort.
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
#include "UmlPort.h"
#include "PropertyStrings.h"

#include "../UmlCommon/PropertyStrings.h"

/**
 * @class UmlAttribute
 * @brief The UmlPort class stores information about a port of a UML classifier.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlPort::Data
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
      , isBehavior(false)
      , isConjugated(false)
      , isService(false)
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
   bool            isBehavior;
   bool            isConjugated;
   bool            isService;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

UmlPort::UmlPort()
: data(new Data())
{
}

UmlPort::UmlPort(QUuid id)
: super(id)
, data(new Data())
{
}

UmlPort::~UmlPort()
{
   delete data;
}

QString UmlPort::className() const
{
   return staticMetaObject.className();
}

QString UmlPort::name() const
{
   return data->name;
}

void UmlPort::setName(QString value)
{
   data->name = value;
}

QString UmlPort::comment() const
{
   return data->comment;
}

void UmlPort::setComment(QString value)
{
   data->comment = value;
}

VisibilityKind UmlPort::visibility() const
{
   return data->visibility;
}

void UmlPort::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

bool UmlPort::isOrdered() const
{
   return data->isOrdered;
}

void UmlPort::isOrdered(bool value)
{
   data->isOrdered = value;
}

bool UmlPort::isUnique() const
{
   return data->isUnique;
}

void UmlPort::isUnique(bool value)
{
   data->isUnique = value;
}

quint32 UmlPort::lower() const
{
   return data->lower;
}

void UmlPort::setLower(quint32 value)
{
   data->lower = value;
}

quint32 UmlPort::upper() const
{
   return data->upper;
}

void UmlPort::setUpper(quint32 value)
{
   data->upper = value;
}

QString UmlPort::stereotype() const
{
   return data->stereotype;
}

void UmlPort::setStereotype(QString value)
{
   data->stereotype = value;
}

AggregationKind UmlPort::aggregation() const
{
   return data->aggregation;
}

void UmlPort::setAggregation(AggregationKind value)
{
   data->aggregation = value;
}

bool UmlPort::isComposite() const
{
   return data->isComposite;
}

void UmlPort::isComposite(bool value)
{
   data->isComposite = value;
}

bool UmlPort::isDerived() const
{
   return data->isDerived;
}

void UmlPort::isDerived(bool value)
{
   data->isDerived = value;
}

bool UmlPort::isDerivedUnion() const
{
   return data->isDerivedUnion;
}

void UmlPort::isDerivedUnion(bool value)
{
   data->isDerivedUnion = value;
}

bool UmlPort::isID() const
{
   return data->isID;
}

void UmlPort::isID(bool value)
{
   data->isID = value;
}

bool UmlPort::isStatic() const
{
   return data->isStatic;
}

void UmlPort::isStatic(bool value)
{
   data->isStatic = value;
}

bool UmlPort::isReadOnly() const
{
   return data->isReadOnly;
}

void UmlPort::isReadOnly(bool value)
{
   data->isReadOnly = value;
}

QString UmlPort::type() const
{
   return data->type;
}

void UmlPort::setType(QString value)
{
   data->type = value;
}

bool UmlPort::isBehavior() const
{
   return data->isBehavior;
}

void UmlPort::isBehavior(bool value)
{
   data->isBehavior = value;
}

bool UmlPort::isConjugated() const
{
   return data->isConjugated;
}

void UmlPort::isConjugated(bool value)
{
   data->isConjugated = value;
}

bool UmlPort::isService() const
{
   return data->isService;
}

void UmlPort::isService(bool value)
{
   data->isService = value;
}

void UmlPort::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
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
      data->isBehavior = json[KPropIsBehavior].toBool();
      data->isConjugated = json[KPropIsConjugated].toBool();
      data->isService = json[KPropIsService].toBool();
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
      json[KPropIsBehavior] = data->isBehavior;
      json[KPropIsConjugated] = data->isConjugated;
      json[KPropIsService] = data->isService;
   }
}
