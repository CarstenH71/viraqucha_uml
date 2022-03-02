//---------------------------------------------------------------------------------------------------------------------
// CommentShape.cpp
//
// Copyright (C) 2020 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class EdgeShape.
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
#include "CommentShape.h"

#include <QPainter>
#include <QPolygonF>
#include <QSizeF>
#include <QTextOption>

/**
 * @class CommentShape
 * @brief Draws a shape for a UML Comment.
 * @since 0.1.0
 * @ingroup GuiDiagram
 *
 * The CommentShape class draws a shape for UML Comment elements. A UML Comment shape is drawn as a rectangle with an
 * inward bent triangle at the upper right corner so that it resembles a sheet of paper. The text of the comment is
 * drawn inside the rectangle.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the CommentShape class.
 *
 * @param parent Parent graphics item
 * @param node DiaNode object containing data from the data model
 */
CommentShape::CommentShape(QGraphicsItem* parent, DiaNode* node)
: super(parent, node)
{
   Q_ASSERT(node != nullptr);
   node->setItemData(static_cast<void*>(this));
   node->setSize(QSizeF(100.0, 50.0)); // Set some default size... may be adjusted by user
   
   _element = dynamic_cast<UmlComment*>(node->element());
   Q_ASSERT(_element != nullptr);
}

CommentShape::~CommentShape()
{
}

/** Gets the element associated with this shape. */
UmlElement* CommentShape::element() const
{
   return _element;
}

/**
 * Paints the CommentShape object.
 *
 * @param painter QPainter object needed for drawing
 * @param option This parameter is unused
 * @param widget This parameter is unused
 */
void CommentShape::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
   Q_UNUSED(option);
   Q_UNUSED(widget);

   double x1 = -(nodeSize().width() / 2.0);
   double x2 = -x1 - 15.0;
   double x3 = -x1;
   double y1 = -(nodeSize().height() / 2.0);
   double y2 = y1 + 15.0;
   double y3 = -y1;

   _linePen.setStyle(Qt::SolidLine);
 
   // Draw polygon surrounding the comment:
   QPolygonF poly1, poly2;
   poly1 << QPointF(x1, y1) << QPointF(x2, y1) << QPointF(x3, y2) << QPointF(x3, y3) << QPointF(x1, y3);
   poly2 << QPointF(x2, y1) << QPointF(x3, y2) << QPointF(x2, y2) << QPointF(x2, y1);
   painter->setBrush(_brush);
   painter->setPen(_linePen);
   painter->setFont(_font);
   painter->drawPolygon(poly1, FillRule::OddEvenFill);
   painter->drawPolygon(poly2, FillRule::OddEvenFill);
   
   // Draw text of the comment into the polygon:
   QRectF rect(x1 + padding(), y1 + padding(), x2 - x1, y3 - y1);
   QTextOption opt;
   opt.setWrapMode(QTextOption::WordWrap);
   
   painter->setFont(_font);
   painter->setPen(_textPen);
   painter->drawText(rect, _element->body(), opt);   

   // Draw selection frame around the shape:
   if (isSelected()) drawSelectionFrame(painter);   
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Builds a CommentShape object.
 *
 * This function is called by the shape factory each time a new CommentShape object needs to be created.
 * @param shape DiaShape object needed for construction.
 */
Shape* CommentShapeBuilder::build(DiaShape* shape)
{
   return new CommentShape(nullptr, dynamic_cast<DiaNode*>(shape));
}
