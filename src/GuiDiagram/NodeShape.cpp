//---------------------------------------------------------------------------------------------------------------------
// NodeShape.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class NodeShape.
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
#include "NodeShape.h"

#include "Compartment.h"
#include "EdgeShape.h"
#include "TextBox.h"
#include "UmlElement.h"

#include <QFontMetricsF>

/**
 * @class NodeShape
 * @brief Base class for node shapes.
 * @since 0.1.0
 * @ingroup GuiDiagram
 *
 * The NodeShape class is a base class which can be used to draw UML elements like Class, Enumeration, Use Case, etc.
 * It needs a DiaNode instance on construction to compute the overall size of the shape. The shape itself can be of any
 * geometric form, like rectangle, ellipse or diamond and it can even be of free form (e.g. a &quot;stick man&quot;).
 *
 * Derived classes must implement the paint() function of the QGraphicsItem super class. The boundingRect() function is
 * already implemented and returns a bounding rectangle based on the node's height and width values plus the size of 
 * the pen used for drawing the shape. 
 * 
 * The DiaNode's size and position is set automatically on construction of this class and each time when calling 
 * function computeSize(). The function also computes the size of a text box using font metrics of the currently used
 * font and sets property textBoxSize() accordingly.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the NodeShape class.
 * 
 * @param parent Parent graphics item.
 * @param node DiaNode object to be displayed by this shape.
 */
NodeShape::NodeShape(QGraphicsItem* parent, DiaNode* node)
: super(parent, node)
, _node(node)
, _padding(5.0)
{
   Q_ASSERT(_node != nullptr);
   // Property DiaNode::itemData() must be set in derived classes!

   // Set the size of the node to the computed size:
   computeSize(false);
   setPos(_node->pos());
   setFlag(QGraphicsItem::ItemIsMovable, true);
}

NodeShape::~NodeShape()
{
}

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** Gets the UML element displayed by this node. */
UmlElement* NodeShape::element() const
{
   return _node->element();
}

/** Gets the DiaNode instance. */
DiaNode* NodeShape::diaNode() const
{
   return _node;
}

/** Gets the size of the DiaNode instance (convenience function). */
QSizeF NodeShape::nodeSize() const
{
   return _node->size();
}

/** Sets the size of the DiaNode instance (convenience function). */
void NodeShape::setNodeSize(QSizeF value)
{
   _node->setSize(value);
}

/**
 * Gets the padding.
 */
double NodeShape::padding() const
{
   return _padding;
}

/**
 * Sets the padding.
 * 
 * The padding is used inside the shape to position text boxes such that no overlapping occurs. The default padding is 
 * 5 pixels.
 * @param value Padding value.
 */
void NodeShape::setPadding(double value)
{
   _padding = value;
}

/** Gets the text box size. */
QSizeF NodeShape::textBoxSize() const
{
   return _textBoxSize;
}

/** Sets the text box size. */
void NodeShape::setTextBoxSize(QSizeF value)
{
   _textBoxSize = value;
}

/** Gets the bounding rectangle of the node shape. */
QRectF NodeShape::boundingRect() const
{
   double w = _node->size().width();
   double h = _node->size().height();
   double p = _linePen.width() / 2.0;
   return QRectF(-(w / 2.0) - p, -(h / 2.0) - p, w + p, h + p);
}

/** 
 * Handles itemChange events. 
 * 
 * Sets the position of the node and updates positions of all edges attached to this node.
 * @param change
 * @param value
 * @returns A QVariant value 
 */
QVariant NodeShape::itemChange(GraphicsItemChange change, const QVariant& value)
{
   if (change == ItemPositionHasChanged)
   {
      _node->setPos(value.toPointF());
      
      auto edges = _node->edges();
      for (DiaEdge* edge : edges)
      {
         auto shape = static_cast<EdgeShape*>(edge->itemData());
         if (shape != nullptr) shape->updatePosition();
      }
   }

   return super::itemChange(change, value);
}

/**
 * Draws a selection frame around the shape using the bounding rectangle of the shape.
 * 
 * @param painter QPainter instance needed for drawing.
 */
void NodeShape::drawSelectionFrame(QPainter* painter)
{
   QRectF selectFrame = boundingRect();
   selectFrame += QMarginsF(KSFMargin, KSFMargin, KSFMargin, KSFMargin);
   _linePen.setStyle(Qt::DashDotLine);
   painter->setPen(_linePen);
   painter->setBrush(Qt::NoBrush);
   painter->drawRect(selectFrame);
   
   QRectF sizingBox;
   sizingBox.setX(selectFrame.x() + selectFrame.width() - KSBSize2);
   sizingBox.setY(selectFrame.y() + selectFrame.height() - KSBSize2);
   sizingBox.setWidth(KSBSize);
   sizingBox.setHeight(KSBSize);
   _linePen.setStyle(Qt::SolidLine);
   painter->setPen(_linePen);
   painter->setBrush(Qt::white);
   painter->drawRect(sizingBox);
}

/**
 * Computes the size of the shape including compartments and text sizes.
 *
 * The function  sets property size of the DiaNode instance to the computed size if the computed size differs from the
 * size of the DiaNode instance. It also sets property textBoxSize which provides the size of a single text box in a
 * compartment.
 * 
 * @param templated True: adds some space for template parameters to the height of the shape; false otherwise.
 */
void NodeShape::computeSize(bool templated)
{
   QString text;
   int x = 0, c = 0;
   bool save1 = _font.bold();
   bool save2 = _font.italic();

   _node->update();

   // Find longest text in compartments first:
   auto comps = _node->compartments();
   for (int i = 0; i < comps.size(); ++i)
   {
      if (comps[i]->isHidden()) continue;
      ++c;

      auto boxes = comps[i]->lines();
      for (int j = 0; j < boxes.size(); ++j)
      {
         auto* box = boxes[j];
         if (box->text().length() > text.length())
         {
            text = box->text();
         }

         ++x;
      }
   }

   // Compute size of the rectangle needed to paint the text:
   _font.setBold(true);
   _font.setItalic(true);
   QFontMetricsF metrics(_font);
   QRectF rect = metrics.boundingRect(QRectF(0.0, 0.0, 10.0, 10.0), AlignmentFlag::AlignLeft, text);
   _font.setBold(save1);
   _font.setItalic(save2);

   // Compute overall height and width of the shape's rectangle:
   double oh = (x * (metrics.height() + _padding)) + c * 2.0 * _padding - metrics.height();
   double ow = rect.width() + 2.0 * _padding;
   auto ovs = QSizeF(ow, oh);
   auto tbs = QSizeF(rect.width(), rect.height());

   // Add a little bit more space if template parameters must be drawn:
   if (templated)
   {
      ovs.setHeight(ovs.height() + tbs.height() + _padding);
   }
   
   setNodeSize(ovs);
   setTextBoxSize(tbs);
}
