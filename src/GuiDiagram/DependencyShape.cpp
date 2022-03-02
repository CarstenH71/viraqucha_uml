//---------------------------------------------------------------------------------------------------------------------
// DependencyShape.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class DependencyShape.
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
#include "DependencyShape.h"

#include <QPainter>

/**
 * @class DependencyShape
 * @brief Draws a shape for a UML Dependency.
 * @since 0.1.0
 * @ingroup GuiDiagram
 *
 * The DependencyShape class draws a shape for UML Dependency links. A UML Dependency link is drawn as a dashed line
 * with an open arrow at one end. A UML Dependency is always directed.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the DependencyShape class.
 *
 * @param parent Parent graphics item
 * @param node DiaNode object containing data from the data model
 */
DependencyShape::DependencyShape(QGraphicsItem* parent, DiaEdge* edge)
: super(parent, edge)
{
   setEndingStyle(EdgeShape::ArrowAtEnd);
   setLineStyle(Qt::DashLine);
}

DependencyShape::~DependencyShape()
{
}

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Overwritten to do nothing - this function is unused.
 *
 * @param painter This parameter is unused
 * @param line This parameter is unused
 */
void DependencyShape::drawLineStart(QPainter* painter, const QLineF& line)
{
   Q_UNUSED(painter);
   Q_UNUSED(line);
}

/**
 * Overwritten to draw an arrow at the end of the line.
 *
 * @param painter QPainter object needed for drawing
 * @param line Line receiving the arrow
 */
void DependencyShape::drawLineEnd(QPainter* painter, const QLineF& line)
{
   drawArrow(painter, line, false);
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Builds a DependencyShape object.
 *
 * This function is called by the shape factory each time a new DependencyShape object needs to be created.
 * @param shape DiaShape object needed for construction.
 */
Shape* DependencyShapeBuilder::build(DiaShape* shape)
{
   return new DependencyShape(nullptr, dynamic_cast<DiaEdge*>(shape));
}
