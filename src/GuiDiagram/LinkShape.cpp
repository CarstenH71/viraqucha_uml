//---------------------------------------------------------------------------------------------------------------------
// LinkShape.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class LinkShape.
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
#include "LinkShape.h"

#include <QPainter>

/**
 * @class LinkShape
 * @brief Draws a shape for a UML Link.
 * @since 0.1.0
 * @ingroup GuiDiagram
 *
 * The LinkShape class draws a shape for UML Links. A UML Link is drawn as a dashed line with no arrows at all.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the LinkShape class.
 *
 * @param parent Parent graphics item
 * @param node DiaNode object containing data from the data model
 */
LinkShape::LinkShape(QGraphicsItem* parent, DiaEdge* edge)
: super(parent, edge)
{
   setEndingStyle(EdgeShape::NoArrows);
   setLineStyle(Qt::DashLine);
}

LinkShape::~LinkShape()
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
void LinkShape::drawLineStart(QPainter* painter, const QLineF& line)
{
   Q_UNUSED(painter);
   Q_UNUSED(line);
}

/**
 * Overwritten to do nothing - this function is unused.
 *
 * @param painter This parameter is unused
 * @param line This parameter is unused
 */
void LinkShape::drawLineEnd(QPainter* painter, const QLineF& line)
{
   Q_UNUSED(painter);
   Q_UNUSED(line);
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Builds a LinkShape object.
 *
 * This function is called by the shape factory each time a new LinkShape object needs to be created.
 * @param shape DiaShape object needed for construction.
 */
Shape* LinkShapeBuilder::build(DiaShape* shape)
{
   return new LinkShape(nullptr, dynamic_cast<DiaEdge*>(shape));
}
