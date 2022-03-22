//---------------------------------------------------------------------------------------------------------------------
// DiaNode.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class DiaNode.
// Compiles with: MSVC 15.2 (2017) or newer, GNU GCC 5.1 or newer
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This library is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
// * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
// * option) any later version.                                                                                      *
// *                                                                                                                 *
// * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
// * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
// * for more details.                                                                                               *
// *                                                                                                                 *
// * You should have received a copy of the GNU General Public License along with this library; if not, see          *
// * http://www.gnu.org/licenses/gpl                                                                                 *
// *                                                                                                                 *
// *******************************************************************************************************************
//
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#include "DiaNode.h"

#include "UmlElement.h"
#include "ICompartmentProvider.h"
#include "PropertyStrings.h"

#include <QJsonArray>

/**
 * @class DiaNode
 * @brief The DiaNode class holds information about a node in a diagram.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * In a UML diagram, a node represents the information of a single UML element. 
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct DiaNode::Data
{
   Data() 
   : element(nullptr)
   {}

   UmlElementPtr         element;
   QSizeF                size;
   QVector<Compartment*> compartments;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the DiaNode class.
 */
DiaNode::DiaNode()
: data(new Data())
{
}

DiaNode::~DiaNode()
{
   clear();
   delete data;
}

/**
 * Gets the UmlElement instance associated with the node.
 */
UmlElement* DiaNode::element() const
{
   return data->element.pointee();
}

/**
 * Sets the UmlElement instance associated with the node.
 *
 * The function also resets the vector of compartments to the compartments provided by the new instance. Note that
 * this will only work if the UmlElement instance implements interface ICompartmentProvider. If it does not, nothing
 * will happen, except that the vector will be reset to nullptr values.
 */
void DiaNode::setElement(UmlElement* value)
{
   data->element = value;

   clear();
   if (value != nullptr)
   {
      // Reset compartments:
      auto* provider = dynamic_cast<ICompartmentProvider*>(value);
      if (provider != nullptr)
      {
         data->compartments = provider->compartments();
      }
   }
}

/** Gets the size of the (rectangular, elliptic) node. */
QSizeF DiaNode::size()
{
   return data->size;
}

/** Sets the size of the node. */
void DiaNode::setSize(const QSizeF& value)
{
   data->size = value;
}

/** Gets the vector of compartments. */
QVector<Compartment*> DiaNode::compartments() const
{
   return QVector<Compartment*>(data->compartments);
}

/** Updates all compartments in the node. */
void DiaNode::update()
{
   auto* provider = dynamic_cast<ICompartmentProvider*>(data->element.pointee());
   if (provider != nullptr)
   {
      for (int index = 0; index < data->compartments.size(); ++index)
      {
         provider->update(index, data->compartments[index]);
      }
   }
}

/** Clears the vector of compartments. */
void DiaNode::clear()
{
   int end = data->compartments.size();
   for (int index = 0; index < end; ++index)
   {
      delete data->compartments[index];
   }
   data->compartments.clear();
}

/**
 * Serializes properties of the DiaNode instance to a JSON file.
 *
 * The function serializes all data in compartments except text boxes, which will be updated from the UmlElement instance
 * associated with this node.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void DiaNode::serialize(QJsonObject& json, bool read, int version)
{
   auto* provider = dynamic_cast<ICompartmentProvider*>(data->element.pointee());
   
   super::serialize(json, read, version);
   if (read)
   {
      QSizeF size;
      size.setWidth(json[KPropW].toDouble());
      size.setHeight(json[KPropH].toDouble());
      data->size = size;

      // Read compartments only if element implements interface ICompartmentProvider:
      if (provider != nullptr)
      {
         auto array = json[KPropCompartments].toArray();
         if (data->compartments.size() == array.size())
         {
            for (int index = 0; index < array.size(); ++index)
            {
               auto obj = array[index].toObject();
               bool ok = false;

               auto* comp = data->compartments[index];
               comp->setName(obj[KPropName].toString());
               comp->isHidden(obj[KPropHidden].toBool(false));
               comp->setFlags(obj[KPropFlags].toString("0").toULongLong(&ok, 16));
               provider->update(index, comp);
            }
         }
      }
   }
   else
   {
      json[KPropW] = data->size.width();
      json[KPropH] = data->size.height();

      // Write compartments only if element implements interface ICompartmentProvider:
      if (provider != nullptr)
      {
         QJsonArray array;
         for (int index = 0; index < data->compartments.size(); ++index)
         {
            auto* comp = data->compartments[index];

            QJsonObject obj;
            obj[KPropName] = comp->name();
            obj[KPropHidden] = comp->isHidden();
            obj[KPropFlags] = QString::number(comp->flags(), 16);
            array.append(obj);
         }
         json[KPropCompartments] = array;
      }
   }
}
