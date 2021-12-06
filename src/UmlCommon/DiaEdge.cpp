//---------------------------------------------------------------------------------------------------------------------
// DiaEdge.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class DiaEdge.
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
#include "DiaEdge.h"

#include "DiaNode.h"
#include "ILabelProvider.h"
#include "Label.h"
#include "PropertyStrings.h"
#include "UmlLink.h"

#include <QJsonArray>

/**
 * @class DiaEdge
 * @brief The DiaEdge class holds information about an edge in a diagram.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * In a diagram, edges are used to connect nodes with each other. An edge is drawn as a line between two nodes. The
 * line may be drawn straight or dotted or dashed, depending on the line style used for the edge. At each end, it
 * may have further graphical elements like dots or circles or arrows depicting the direction of the edge.
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct DiaEdge::Data
{
   Data()
   : link(nullptr)
   , shape1(nullptr)
   , shape2(nullptr)
   , routing(RoutingKind::Direct)
   {}

   UmlLinkPtr       link;
   DiaShape*        shape1;
   DiaShape*        shape2;
   QVector<QPointF> points;
   QVector<Label*>  labels;
   RoutingKind      routing;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the DiaEdge class.
 */
DiaEdge::DiaEdge()
: data(new Data())
{
}

DiaEdge::~DiaEdge()
{
   delete data;
}

/**
 * Gets the UmlLink instance associated with this edge.
 */
UmlLink* DiaEdge::link() const
{
   return data->link.pointee();
}

/**
 * Sets the UmlLink instance associated with this edge.
 */
void DiaEdge::setLink(UmlLink* value)
{
   data->link = value;

   clear();
   if (value != nullptr)
   {
      // Reset labels:
      auto* provider = dynamic_cast<ILabelProvider*>(value);
      if (provider != nullptr)
      {
         data->labels = provider->labels();
      }
   }
}

/**
 * Gets the first node.
 */
DiaShape* DiaEdge::shape1() const
{
   return data->shape1;
}

/**
 * Sets the first node and attaches itself to the node.
 */
void DiaEdge::setShape1(DiaShape* value)
{
   if (data->shape1 != nullptr)
   {
      data->shape1->detach(this);
   }
   data->shape1 = value;
   if (data->shape1 != nullptr)
   {
      data->shape1->attach(this);
   }
}

/**
 * Gets the second node.
 */
DiaShape* DiaEdge::shape2() const
{
   return data->shape2;
}

/**
 * Sets the second node and attaches itself to the node.
 */
void DiaEdge::setShape2(DiaShape* value)
{
   if (data->shape2 != nullptr)
   {
      data->shape2->detach(this);
   }
   data->shape2 = value;
   if (data->shape2 != nullptr)
   {
      data->shape2->attach(this);
   }
}

/**
 * Gets the routing information of the edge.
 */
RoutingKind DiaEdge::routing() const
{
   return data->routing;
}

/**
 * Sets the routing information of the edge.
 */
void DiaEdge::setRouting(RoutingKind value)
{
   data->routing = value;
}

/** Gets the vector of points of the edge's line. */
QVector<QPointF> DiaEdge::points() const
{
   return data->points;
}

/** Sets the vector of points of the edge's line. */
void DiaEdge::setPoints(QVector<QPointF> value)
{
   data->points = value;
}

/**
 * Gets the vector of labels.
 */
QVector<Label*> DiaEdge::labels() const
{
   return data->labels;
}

/**
 * Clears all labels from the edge.
 */
void DiaEdge::clear()
{
   int end = data->labels.size();
   for (int index = 0; index < end; ++index)
   {
      delete data->labels[index];
   }
   data->labels.clear();
}

/**
 * Serializes properties of the DiaEdge instance to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void DiaEdge::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
   if (read)
   {
      data->routing = (RoutingKind)json[KPropRouting].toInt();
      if (data->routing == RoutingKind::Custom)
      {
         // Read points only if routing kind is "Custom":
         auto array = json[KPropPoints].toArray();
         data->points.clear();
         for (int index = 0; index < array.size(); ++index)
         {
            auto obj = array[index].toObject();

            QPointF point;
            point.setX(obj[KPropX].toDouble());
            point.setY(obj[KPropY].toDouble());
            data->points.append(point);
         }
      }

      auto* provider = dynamic_cast<ILabelProvider*>(data->link.pointee());
      if (provider != nullptr)
      {
         // TODO
      }
   }
   else
   {
      json[KPropRouting] = (int)data->routing;
      if (data->routing == RoutingKind::Custom)
      {
         // Write points only if routing kind is "Custom":
         QJsonArray array;
         for (int index = 0; index < data->points.length(); ++index)
         {
            auto& point = data->points[index];

            QJsonObject obj;
            obj[KPropX] = point.x();
            obj[KPropY] = point.y();
            array.append(obj);
         }
         json[KPropPoints] = array;
      }
   }
}
