//---------------------------------------------------------------------------------------------------------------------
// AssociationEnd.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class AssociationEnd.
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
#include "AssociationEnd.h"
#include "UmlAttribute.h"
#include "PropertyStrings.h"

#include "../UmlCommon/UmlProject.h"
#include "../UmlCommon/PropertyStrings.h"

#include <QJsonArray>

/**
 * @class AssociationEnd
 * @brief Stores information about an UML association end.
 * @since 1.0
 * @ingroup UmlClassifiers
 * 
 * In the Unified Modeling Language an association end corresponds to a property of a classifier. The association end 
 * describes the property of the classifier and visualizes its dependency to other classifier elements in the model. 
 * The AssociationEnd class stores information about such a dependency in the ViraquchaUML data model.
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct AssociationEnd::Data
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

   QString              name;
   QString              comment;
   VisibilityKind       visibility;
   QString              stereotype;
   bool                 isOrdered;
   bool                 isUnique;
   quint32              lower;
   quint32              upper;
   AggregationKind      aggregation;
   bool                 isComposite;
   bool                 isDerived;
   bool                 isDerivedUnion;
   bool                 isID;
   bool                 isStatic;
   bool                 isReadOnly;
   QString              type;
   UmlAttribute*        attribute; // TODO: lieber intrusive pointer?
   QList<UmlAttribute*> qualifiers;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the AssociationEnd class.
 */
AssociationEnd::AssociationEnd()
: data(new Data())
{
}

AssociationEnd::~AssociationEnd()
{
   delete data;
}

/** Gets the name of the association end. */
QString AssociationEnd::name() const
{
   return data->name;
}

/** Sets the name of the association end. */
void AssociationEnd::setName(QString value)
{
   data->name = value;
}

/** Gets the comment of the association end. */
QString AssociationEnd::comment() const
{
   return data->comment;
}

/** Sets the comment of the association end. */
void AssociationEnd::setComment(QString value)
{
   data->comment = value;
}

/** Gets the visibility of the association end. */
VisibilityKind AssociationEnd::visibility() const
{
   return data->visibility;
}

/** Sets the visibility of the association end. */
void AssociationEnd::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

/** Gets a value indicating whether the multiplicity of the association end is ordered. */
bool AssociationEnd::isOrdered() const
{
   return data->isOrdered;
}

/** Sets a value indicating whether the multiplicity of the association end is ordered. */
void AssociationEnd::isOrdered(bool value)
{
   data->isOrdered = value;
}

/** Gets a value indicating whether the multiplicity of the association end is unique. */
bool AssociationEnd::isUnique() const
{
   return data->isUnique;
}

/** Sets a value indicating whether the multiplicity of the association end is unique. */
void AssociationEnd::isUnique(bool value)
{
   data->isUnique = value;
}

/** Gets the lower value of the multiplicity of the association end. */
quint32 AssociationEnd::lower() const
{
   return data->lower;
}

/** Sets the lower value of the multiplicity of the association end. */
void AssociationEnd::setLower(quint32 value)
{
   data->lower = value;
}

/** Gets the upper value of the multiplicity of the association end. */
quint32 AssociationEnd::upper() const
{
   return data->upper;
}

/** Sets the upper value of the multiplicity of the association end. */
void AssociationEnd::setUpper(quint32 value)
{
   data->upper = value;
}

/** Gets the stereotype of the association end. */
QString AssociationEnd::stereotype() const
{
   return data->stereotype;
}

/** Sets the stereotype of the association end. */
void AssociationEnd::setStereotype(QString value)
{
   data->stereotype = value;
}

/** Gets the aggregation kind of the association end. */
AggregationKind AssociationEnd::aggregation() const
{
   return data->aggregation;
}

/** Sets the aggregation kind of the association end. */
void AssociationEnd::setAggregation(AggregationKind value)
{
   data->aggregation = value;
}

/** Gets a value indicating whether the association end is a composite. */
bool AssociationEnd::isComposite() const
{
   return data->isComposite;
}

/** Sets a value indicating whether the association end is a composite. */
void AssociationEnd::isComposite(bool value)
{
   data->isComposite = value;
}

/** Gets a value indicating whether the association end is derived. */
bool AssociationEnd::isDerived() const
{
   return data->isDerived;
}

/** Sets a value indicating whether the association end is derived. */
void AssociationEnd::isDerived(bool value)
{
   data->isDerived = value;
}

/** Gets a value indicating whether the association end is a derived union. */
bool AssociationEnd::isDerivedUnion() const
{
   return data->isDerivedUnion;
}

/** Sets a value indicating whether the association end is a derived union. */
void AssociationEnd::isDerivedUnion(bool value)
{
   data->isDerivedUnion = value;
}

/** Gets a value indicating whether the association end is an identifier. */
bool AssociationEnd::isID() const
{
   return data->isID;
}

/** Sets a value indicating whether the association end is an identifier. */
void AssociationEnd::isID(bool value)
{
   data->isID = value;
}

/** Gets a value indicating whether the association end is static. */
bool AssociationEnd::isStatic() const
{
   return data->isStatic;
}

/** Sets a value indicating whether the association end is static. */
void AssociationEnd::isStatic(bool value)
{
   data->isStatic = value;
}

/** Gets a value indicating whether the association end is read-only. */
bool AssociationEnd::isReadOnly() const
{
   return data->isReadOnly;
}

/** Sets a value indicating whether the association end is read-only. */
void AssociationEnd::isReadOnly(bool value)
{
   data->isReadOnly = value;
}

/** Gets the data type of the association end. */
QString AssociationEnd::type() const
{
   return data->type;
}

/** Sets the data type of the association end. */
void AssociationEnd::setType(QString value)
{
   data->type = value;
}

/** Gets the attribute assigned to the association end. */
UmlAttribute* AssociationEnd::attribute() const
{
   return data->attribute;
}

/** Sets the attribute assigned to the association end. */
void AssociationEnd::setAttribute(UmlAttribute* value)
{
   data->attribute = value;
}

/** Gets the list of qualifiers of the association end. */
QList<UmlAttribute*> AssociationEnd::qualifiers() const
{
   return QList<UmlAttribute*>(data->qualifiers);
}

/** Appends an UmlAttribute instance to the list of qualifiers of the association end. */
void AssociationEnd::append(UmlAttribute* obj)
{
   if (obj != nullptr)
   {
      data->qualifiers.append(obj);
   }
}

/** Removes an UmlAttribute instance from the list of qualifiers of the association end. */
void AssociationEnd::remove(UmlAttribute* obj)
{
   if (obj != nullptr) 
   {
      data->qualifiers.removeOne(obj);
   }
}

/** Clears the list of qualifiers of the association end. */
void AssociationEnd::clear()
{
   data->qualifiers.clear();
}

/**
 * Serializes the association end to a JSON file.
 *
 * Note that this function is not implementing interface ISerializable! It has an extra parameter and therefore does 
 * not conform to the interface.
 *
 * @param json The JSON file to be serialized to.
 * @param read True if the JSON file shall be read, false if it shall be written.
 * @param version Serialization version, needed for detecting changes in the file format in future releases.
 * @param project A pointer to the project. Needed for serialization.
 */
void AssociationEnd::serialize(QJsonObject& json, bool read, int version, UmlProject* project)
{
   QJsonArray array;
   if (read)
   {
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->visibility = (VisibilityKind)json[KPropVisibility].toInt();
      data->stereotype = json[KPropStereotype].toString();
      data->isOrdered = json[KPropIsOrdered].toBool();
      data->isUnique = json[KPropIsUnique].toBool();
      data->lower = (quint32)json[KPropLower].toDouble();
      data->upper = (quint32)json[KPropUpper].toDouble();
      data->aggregation = (AggregationKind)json[KPropAggregation].toInt();
      data->isComposite = json[KPropIsComposite].toBool();
      data->isDerived = json[KPropIsDerived].toBool();
      data->isDerivedUnion = json[KPropIsDerivedUnion].toBool();
      data->isID = json[KPropIsID].toBool();
      data->isStatic = json[KPropIsStatic].toBool();
      data->isReadOnly = json[KPropIsReadOnly].toBool();
      data->type = json[KPropType].toString();
      // TODO: Attribute
      
      // Qualifier
      {
         array = json[KPropQualifier].toArray();
         for (int index = 0; index < array.size(); ++index)
         {
            // Get the identifier of the element:
            QUuid ident = QUuid(array[index].toString());

            // Get the element itself from the project...
            UmlElement* elem = nullptr;
            if (project->find(ident, &elem))
            {
               // ... and add it to the list of elements:
               append(dynamic_cast<UmlAttribute*>(elem));
            }
         }

      }
   }
   else
   {
      json[KPropName] = data->name;
      json[KPropComment] = data->comment;
      json[KPropVisibility] = (int)data->visibility;
      json[KPropStereotype] = data->stereotype;
      json[KPropIsOrdered] = data->isOrdered;
      json[KPropIsUnique] = data->isUnique;
      json[KPropLower] = (double)data->lower;
      json[KPropUpper] = (double)data->upper;
      json[KPropAggregation] = (int)data->aggregation;
      json[KPropIsComposite] = data->isComposite;
      json[KPropIsDerived] = data->isDerived;
      json[KPropIsDerivedUnion] = data->isDerivedUnion;
      json[KPropIsID] = data->isID;
      json[KPropIsStatic] = data->isStatic;
      json[KPropIsReadOnly] = data->isReadOnly;
      json[KPropType] = data->type;
      // TODO: Attribute
      
      // Qualifier
      {
         QListIterator<UmlAttribute*> iter(data->qualifiers);
         while (iter.hasNext())
         {
            array.append(QJsonValue(iter.next()->identifier().toString()));
         }

         json[KPropQualifier] = array;
      }
   }
}
