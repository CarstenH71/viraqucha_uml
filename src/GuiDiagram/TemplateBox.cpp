//---------------------------------------------------------------------------------------------------------------------
// TemplateBox.cpp
//
// Copyright (C) 2020 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class TemplateBox.
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
#include "TemplateBox.h"
#include "UmlElement.h"
#include "UmlTemplateParameter.h"

#include <QPainter>
#include <QTextStream>

/**
 * @class TemplateBox
 * @brief Draws a box displaying template parameters of a UML Classifier.
 * @since 0.1.0
 * @ingroup GuiDiagram
 *
 * The TemplateBox class draws the rectangular area of a UML Classifier displaying template parameters of the UML
 * Classifier. The rectangular area is always positioned right above the shape of the UML Classifier. Its size grows
 * only upwards, depending on the count of text lines to be shown in the box.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the TemplateBox class.
 * 
 * @param parent Parent graphics item, must not be null.
 * @param node Associated DiaNode instance from the UML datamodel.
 * @param font Font to be used for drawing text.
 * @param linePen Pen used for drawing the line around the rectangulare area.
 * @param textPen Pen used for drawing the text.
 */
TemplateBox::TemplateBox(QGraphicsItem* parent, DiaNode* node, QFont& font, QPen& linePen, QPen& textPen)
: super(parent)
, _node(node)
, _element(nullptr)
, _font(font)
, _linePen(linePen)
, _textPen(textPen)
, _padding(5)
{
   Q_ASSERT(_node != nullptr);
   Q_ASSERT(_node->element() != nullptr);

   _element = dynamic_cast<ITemplatableElement*>(_node->element());
   Q_ASSERT(_element != nullptr);
}

TemplateBox::~TemplateBox()
{
}

/**
 * Sets the text box size computed by the parent shape.
 * 
 * @param value Computed text box size.
 */
void TemplateBox::setTextBoxSize(QSizeF value)
{
   _textBoxSize = value;
}

/** Gets the bounding rectangle of the template box. */
QRectF TemplateBox::boundingRect() const
{
   return QRectF(0, 0, _size.width(), _size.height());
}

/**
 * Paints the template box to the graphics scene.
 * 
 * @param painter QPainter instance needed for painting.
 * @param option Unused.
 * @param widget Unused.
 */
void TemplateBox::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
   Q_UNUSED(option);
   Q_UNUSED(widget);
   
   if (_element->isTemplated())
   {
      // Compute size of template box and position it relative to the parent shape:
      computeSize();
      setPos(10, -_node->size().height() / 2.0 - _size.height() + _textBoxSize.height());      
      
      // Draw a filled rectangle surrounded by a dashed line using line pen and fill color:
      _linePen.setStyle(Qt::DashLine);
      painter->setPen(_linePen);
      painter->fillRect(0.0, 0.0, _size.width(), _size.height(), _node->fillColor());
      painter->drawRect(0, 0, _size.width(), _size.height());

      // Local variables needed for drawing the text boxes:
      double x  = _padding;
      double y  = _padding;
      double w  = _size.width() - _padding;
      double h  = _size.height() - _padding;
      double dy = _textBoxSize.height() + _padding;

      // Then draw all text boxes using the given font and text pen:
      _font.setBold(false);
      _font.setItalic(false);
      _font.setUnderline(false);
      painter->setFont(_font);
      painter->setPen(_textPen);
      auto params = _element->templateParameter();
      for (int i = 0; i < params.size(); ++i)
      {
         painter->drawText(x, y, w, h, Qt::AlignLeft, params[i]->toString());
         y += dy;
      }
   }
}

/** Computes the size of the template box. */
void TemplateBox::computeSize()
{
   QString text;
   
   // Find longest text first. It will determine the maximum width of the template box:
   auto params = _element->templateParameter();
   for (int i = 0; i < params.size(); ++i)
   {
      QString current = params[i]->toString();
      if (text.length() < current.length()) text = current;
   }

   // Compute width and height of the template box using font metrics of the text found above:
   _font.setBold(true);
   _font.setItalic(true);
   QFontMetricsF metrics(_font);
   QRectF rect = metrics.boundingRect(QRectF(0.0, 0.0, 10.0, 10.0), AlignmentFlag::AlignLeft, text);
   _size.setWidth(rect.width() + 2.0 * _padding);
   _size.setHeight((_textBoxSize.height() + _padding) * params.length() + 2.0 * _padding);
}
