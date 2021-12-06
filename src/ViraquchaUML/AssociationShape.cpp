//---------------------------------------------------------------------------------------------------------------------
// AssociationShape.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class AssociationShape.
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
#include "AssociationShape.h"

#include "AssociationEnd.h"

/**
 * @class AssociationShape
 * @brief Draws an Association shape.
 * @since 1.0
 * @ingroup GUI
 *
 * The AssociationShape class draws a UML Association: a solid line connecting two node shapes, decorated with a
 * diamond at one end representing the aggregation kind, and (if the connection is directed) an open arrow at the other
 * end.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the AssociationShape class.
 *
 * @param parent
 * @param edge
 */
AssociationShape::AssociationShape(QGraphicsItem* parent, DiaEdge* edge)
: super(parent, edge)
{
   _link = dynamic_cast<UmlAssociation*>(edge->link());
   Q_ASSERT(_link != nullptr);

   setEndingStyle(EdgeShape::ArrowAtBoth);
   setLineStyle(Qt::SolidLine);
}

AssociationShape::~AssociationShape()
{
}

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Draws an arrow or a diamond at the start (first line segment) of the polyline of the shape.
 *
 * @param painter QPainter object needed for drawing
 * @param line Line segment where to draw the arrow or diamond
 */
void AssociationShape::drawLineStart(QPainter* painter, const QLineF& line)
{
   if (_link->sourceEnd().aggregation() != AggregationKind::None)
   {
      drawDiamond(painter, line, _link->sourceEnd().aggregation() == AggregationKind::Composite);
   }
   else if (_link->isDirected())
   {
      drawArrow(painter, line, false);
   }
}

/**
 * Draws an arrow at the end (last line segment) of the polyline of the shape.
 *
 * @param painter QPainter object needed for drawing
 * @param line Line segment where to draw the arrow
 */
void AssociationShape::drawLineEnd(QPainter* painter, const QLineF& line)
{
   if (_link->isDirected())
   { 
      drawArrow(painter, line, false);
   }
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Builds an AssociationShape object.
 *
 * This function is called by the shape factory each time a new AssociationShape object needs to be created.
 * @param shape DiaShape object needed for construction.
 */
Shape* AssociationShapeBuilder::build(DiaShape* shape)
{
   return new AssociationShape(nullptr, dynamic_cast<DiaEdge*>(shape));
}
