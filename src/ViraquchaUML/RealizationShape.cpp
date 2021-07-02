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

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------
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
void RealizationShape::drawLineStart(QPainter* painter, const QLineF& line)
{
   // Unused
}

void RealizationShape::drawLineEnd(QPainter* painter, const QLineF& line)
{
   drawArrow(painter, line, true);
}

void RealizationShape::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------

Shape* RealizationShapeBuilder::build(DiaShape* shape)
{
   return new RealizationShape(nullptr, dynamic_cast<DiaEdge*>(shape));
}
