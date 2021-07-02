//---------------------------------------------------------------------------------------------------------------------
// PrimitiveTypeShape.cpp
//
// Copyright (C) 2020 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class PrimitiveTypeShape.
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
#include "PrimitiveTypeShape.h"

#include "DiaNode.h"
#include "SignatureTools.h"
#include "UmlPrimitiveType.h"

#include <QPainter>
#include <QPointF>
#include <QSizeF>

/**
 * @class PrimitiveTypeShape
 * @brief Implements a shape for UML primitive type elements.
 * @since 1.0
 * @ingroup GUI
 *
 * The PrimitiveTypeShape class draws a shape for UML primitive type elements. It is derived from QGraphicsItem to be 
 * used in a QGraphicsScene.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
PrimitiveTypeShape::PrimitiveTypeShape(QGraphicsItem* parent, DiaNode* node)
: super(parent, node)
{
   Q_ASSERT(node != nullptr);
   node->setItemData(static_cast<void*>(this));
   node->setSize(QSizeF(100.0, 50.0)); // Set some default size... may be adjusted by user
   
   _element = dynamic_cast<UmlPrimitiveType*>(node->element());
   Q_ASSERT(_element != nullptr);
   
   _keyword = makeAnnotation(_element->keywords(), "");
}

PrimitiveTypeShape::~PrimitiveTypeShape()
{
}

UmlElement* PrimitiveTypeShape::element() const
{
   return _element;
}

void PrimitiveTypeShape::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
   Q_UNUSED(option);
   Q_UNUSED(widget);

   computeSize();
   double x = -(nodeSize().width() / 2.0);
   double y = -(nodeSize().height() / 2.0);
   double w = nodeSize().width();
   double h = nodeSize().height();

   _linePen.setStyle(Qt::SolidLine);
   painter->setPen(_linePen);
   painter->setFont(_font);
   painter->fillRect(x, y, w, h, _brush);
   painter->drawRect(x, y, w, h);
   
   x += padding();
   y += padding();
   painter->setFont(_font);
   painter->setPen(_textPen);
   painter->drawText(x, y, textBoxSize().width(), textBoxSize().height(), AlignmentFlag::AlignCenter, _keyword);
   _font.setBold(true);
   painter->setFont(_font);
   y += textBoxSize().height() + padding();
   painter->drawText(x, y, textBoxSize().width(), textBoxSize().height(), AlignmentFlag::AlignCenter, _element->name());

   // Draw selection frame around the shape:
   if (isSelected()) drawSelectionFrame(painter);
}

void PrimitiveTypeShape::computeSize(bool templated)
{
   QString text = _element->name();
   if (text.length() < _keyword.length())
   {
      text = _keyword;
   }
   
   _font.setBold(true);
   _font.setItalic(true);
   QFontMetricsF metrics(_font);
   QRectF rect = metrics.boundingRect(QRectF(0.0, 0.0, 10.0, 10.0), AlignmentFlag::AlignCenter, text);
   _font.setBold(false);
   _font.setItalic(false);

   // Compute overall height and width of the shape's rectangle:
   double oh = 2 * (metrics.height() + padding()) + padding();
   double ow = rect.width() + 2.0 * padding();
   setNodeSize(QSizeF(ow, oh));
   setTextBoxSize(QSizeF(rect.width(), rect.height()));
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------

Shape* PrimitiveTypeShapeBuilder::build(DiaShape* shape)
{
   return new PrimitiveTypeShape(nullptr, dynamic_cast<DiaNode*>(shape));
}
