//---------------------------------------------------------------------------------------------------------------------
// UmlAssociation.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlAssociation.
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
#include "UmlAssociation.h"
#include "AssociationEnd.h"
#include "PropertyStrings.h"

#include "../UmlCommon/Label.h"
#include "../UmlCommon/PropertyStrings.h"
#include "../UmlCommon/SignatureTools.h"

#include <QJsonArray>

/**
 * @class UmlAssociation
 * @brief The UmlAssociation class stores information about an association relationship between two UML classifier.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlAssociation::Data
{
   Data()
   : visibility(VisibilityKind::Public)
   , isDerived(false)
   {}

   QString        name;
   QString        comment;
   VisibilityKind visibility;
   QString        stereotype;
   bool           isDerived;
   AssociationEnd sourceEnd;
   AssociationEnd targetEnd;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

UmlAssociation::UmlAssociation()
: data(new Data())
{
}

UmlAssociation::UmlAssociation(QUuid id)
: super(id)
, data(new Data())
{
}

UmlAssociation::~UmlAssociation()
{
   delete data;
}

QString UmlAssociation::className() const
{
   return staticMetaObject.className();
}

/** Gets the name of the association. */
QString UmlAssociation::name() const
{
   return data->name;
}

/** Sets the name of the association. */
void UmlAssociation::setName(QString value)
{
   data->name = value;
}

/** Gets the comment of the association. */
QString UmlAssociation::comment() const
{
   return data->comment;
}

/** Sets the comment of the association. */
void UmlAssociation::setComment(QString value)
{
   data->comment = value;
}

/** Gets the visibility of the association. */
VisibilityKind UmlAssociation::visibility() const
{
   return data->visibility;
}

/** Sets the visibility of the association. */
void UmlAssociation::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

/** Gets the stereotype of the association. */
QString UmlAssociation::stereotype() const
{
   return data->stereotype;
}

/** Sets the stereotype of the association. */
void UmlAssociation::setStereotype(QString value)
{
   data->stereotype = value;
}

/** Gets the association end at the source element. */
AssociationEnd& UmlAssociation::sourceEnd() const
{
   return data->sourceEnd;
}

/** Gets the association end at the target element. */
AssociationEnd& UmlAssociation::targetEnd() const
{
   return data->targetEnd;
}

/** Gets a value indicating whether the association is derived. */
bool UmlAssociation::isDerived() const
{
   return data->isDerived;
}

/** Sets a value indicating whether the association is derived. */
void UmlAssociation::isDerived(bool value)
{
   data->isDerived = value;
}

/** Gets a vector of labels. */
QVector<Label*> UmlAssociation::labels()
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
 * Serializes properties of the UmlAssociation instance to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlAssociation::serialize(QJsonObject& json, bool read, bool flat, int version)
{
   super::serialize(json, read, flat, version);
   if (read)
   {
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->visibility = (VisibilityKind)json[KPropVisibility].toInt();
      data->stereotype = json[KPropStereotype].toString();
      data->isDerived = json[KPropIsDerived].toBool();
      
      // Association ends:
      {
         auto array = json[KPropAssocEnds].toArray();
         auto objSrc = array[0].toObject();
         auto objTgt = array[1].toObject();
         data->sourceEnd.serialize(objSrc, read, version, project());
         data->targetEnd.serialize(objTgt, read, version, project());
      }
   }
   else
   {
      json[KPropName] = data->name;
      json[KPropComment] = data->comment;
      json[KPropVisibility] = (int)data->visibility;
      json[KPropStereotype] = data->stereotype;
      json[KPropIsDerived] = data->isDerived;
      
      // Association ends:
      {
         QJsonArray array;
         QJsonObject end1, end2;
         data->sourceEnd.serialize(end1, read, version, nullptr);
         data->targetEnd.serialize(end2, read, version, nullptr);
         array.append(end1);
         array.append(end2);
         json[KPropAssocEnds] = array;
      }
   }
}

/** Updates a single label. */
void UmlAssociation::update(int index, Label* label)
{
   switch (index)
   {
   case 0: // Name and stereotype of the association
      label->setText(makeAnnotation(keywords(), stereotype()) + name());
      break;
   case 1: // Multiplicity of source end
      label->setText(makeRange(sourceEnd().lower(), sourceEnd().upper(), false));
      break;
   case 2: // Attribute name at source end
      label->setText(sourceEnd().name());
      break;
   case 3: // Multiplicity of target end
      label->setText(makeRange(targetEnd().lower(), targetEnd().upper(), false));
      break;
   case 4: // Attribute name at target end
      label->setText(targetEnd().name());
      break;
   default:
      break;
   }
}
