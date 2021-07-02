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

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------
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
void DependencyShape::drawLineStart(QPainter* painter, const QLineF& line)
{
   Q_UNUSED(painter);
   Q_UNUSED(line);
}

void DependencyShape::drawLineEnd(QPainter* painter, const QLineF& line)
{
   drawArrow(painter, line, false);
}

void DependencyShape::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
   Q_UNUSED(event);
   // TODO: Implementieren
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------
Shape* DependencyShapeBuilder::build(DiaShape* shape)
{
   return new DependencyShape(nullptr, dynamic_cast<DiaEdge*>(shape));
}
