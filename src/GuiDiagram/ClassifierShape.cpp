//---------------------------------------------------------------------------------------------------------------------
// ClassifierShape.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class ClassifierShape.
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
#include "ClassifierShape.h"
#include "TemplateBox.h"

#include "Compartment.h"
#include "DiaNode.h"
#include "TextBox.h"
#include "ITemplatableElement.h"

#include "UmlElement.h"
#include "UmlClassifier.h"

#include <QPainter>
#include <QSizeF>

/**
 * @class ClassifierShape
 * @brief Implements a shape for UML classifier elements.
 * @since 1.0
 * @ingroup GUI
 *
 * The ClassifierShape class draws a shape for UML classifier elements. It is derived from QGraphicsItem to be used
 * in a QGraphicsScene.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

ClassifierShape::ClassifierShape(QGraphicsItem* parent, DiaNode* node)
: super(parent, node)
{
   Q_ASSERT(node != nullptr);
   node->setItemData(static_cast<void*>(this));
   
   _classifier = dynamic_cast<UmlClassifier*>(node->element());
   Q_ASSERT(_classifier != nullptr);

   _templateBox = new TemplateBox(this, node, _font, _linePen, _textPen);
   _templateBox->setVisible(_classifier->isTemplated());
}

ClassifierShape::~ClassifierShape()
{
}

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** Gets the element associated with this shape. */
UmlElement* ClassifierShape::element() const
{
   return _classifier;
}

/**
 * Paints the classifier shape.
 *
 * @param painter QPainter instance needed for painting.
 * @param option Currently unused.
 * @param widget Currently unused.
 */
void ClassifierShape::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
   Q_UNUSED(option);
   Q_UNUSED(widget);

   computeSize(_classifier->isTemplated());
   _templateBox->setTextBoxSize(textBoxSize());
   _templateBox->setVisible(_classifier->isTemplated());
   
   double x1 = -(nodeSize().width() / 2.0);
   double x2 = -x1;
   double y1 = -(nodeSize().height() / 2.0);
   double y2 = y1 + padding();
   double dy = textBoxSize().height() + padding();
   if (_classifier->isTemplated()) y2 += dy;

   // Draw classifier shape:
   _linePen.setStyle(Qt::SolidLine);
   painter->setPen(_linePen);
   painter->setFont(_font);
   painter->fillRect(x1, y1, nodeSize().width(), nodeSize().height(), _brush);
   painter->drawRect(x1, y1, nodeSize().width(), nodeSize().height());

   QPointF p(x1 + padding(), y2);
   auto comps = diaNode()->compartments();
   for (int i = 0; i < comps.size(); ++i)
   {
      if (comps[i]->isHidden()) continue;

      // Draw separator line between compartments:
      if (i > 0)
      {
         QLineF line(x1 + 1, p.y(), x2, p.y());
         painter->setPen(_linePen);
         painter->drawLine(line);
         p.setY(p.y() + padding());
      }

      // Draw the text boxes of each compartment:
      auto boxes = comps[i]->lines();
      for (int j = 0; j < boxes.size(); ++j)
      {
         auto* box = boxes[j];
         _font.setBold(box->isBold());
         _font.setItalic(box->isItalic());
         _font.setUnderline(box->isUnderline());
         painter->setFont(_font);
         painter->setPen(_textPen);
         painter->drawText(p.x(), p.y(), textBoxSize().width(), textBoxSize().height(), box->alignment(), box->text());
         p.setY(p.y() + dy);
      }
   }

   // Draw selection frame around the shape:
   if (isSelected()) drawSelectionFrame(painter);
}

//---------------------------------------------------------------------------------------------------------------------
// Builder implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Builds a ClassifierShape object.
 *
 * This function is called by the shape factory each time a new ClassifierShape object needs to be created.
 * @param shape DiaShape object needed for construction.
 */
Shape* ClassifierShapeBuilder::build(DiaShape* shape)
{
   return new ClassifierShape(nullptr, dynamic_cast<DiaNode*>(shape));
}
