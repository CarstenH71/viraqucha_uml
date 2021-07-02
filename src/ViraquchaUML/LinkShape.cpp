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

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------
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
void LinkShape::drawLineStart(QPainter* painter, const QLineF& line)
{
   Q_UNUSED(painter);
   Q_UNUSED(line);
}

void LinkShape::drawLineEnd(QPainter* painter, const QLineF& line)
{
   Q_UNUSED(painter);
   Q_UNUSED(line);
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------
Shape* LinkShapeBuilder::build(DiaShape* shape)
{
   return new LinkShape(nullptr, dynamic_cast<DiaEdge*>(shape));
}
