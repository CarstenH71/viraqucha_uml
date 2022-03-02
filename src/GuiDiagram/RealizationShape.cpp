//---------------------------------------------------------------------------------------------------------------------
// RealizationShape.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class RealizationShape.
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
#include "RealizationShape.h"

#include <QPainter>

/**
 * @class RealizationShape
 * @brief Draws a Realization shape.
 * @since 1.0
 * @ingroup GUI
 *
 * The RealizationShape class draws a UML Realization: a dashed line with a closed arrow at one end pointing to a node
 * shape representing the base classifier to be realized.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the RealizationShape class.
 *
 * @param parent Parent graphics item
 * @param edge Associated DiaEdge object
 */
RealizationShape::RealizationShape(QGraphicsItem* parent, DiaEdge* edge)
: super(parent, edge)
{
   _link = dynamic_cast<UmlRealization*>(edge->link());
   Q_ASSERT(_link != nullptr);

   setEndingStyle(EdgeShape::ArrowAtEnd);
   setLineStyle(Qt::DashLine);
}

RealizationShape::~RealizationShape()
{
}

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Draws an arrow at the start (first line segment) of the polyline of the shape.
 *
 * This function is unused.
 * @param painter This parameter is unused
 * @param line This parameter is unused
 */
void RealizationShape::drawLineStart(QPainter* painter, const QLineF& line)
{
   Q_UNUSED(painter);
   Q_UNUSED(line);
}

/**
 * Draws an arrow at the end (last line segment) of the polyline of the shape.
 *
 * This implementation draws a closed arrow at the last line segment of the polyline of the shape by calling function
 * drawArrow() of the base class.
 * @param painter QPainter object needed for drawing
 * @param line The last line segment of the polygon of the edge shape
 */
void RealizationShape::drawLineEnd(QPainter* painter, const QLineF& line)
{
   drawArrow(painter, line, true);
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Builds a RealizationShape object.
 *
 * This function is called by the shape factory each time a new RealizationShape object needs to be created.
 * @param shape DiaShape object needed for construction.
 */
Shape* RealizationShapeBuilder::build(DiaShape* shape)
{
   return new RealizationShape(nullptr, dynamic_cast<DiaEdge*>(shape));
}
