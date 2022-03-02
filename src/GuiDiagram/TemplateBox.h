//---------------------------------------------------------------------------------------------------------------------
// TemplateBox.h
//
// Copyright (C) 2020 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class TemplateBox.
// Compiles with: MSVC 15.2 (2018) or newer, GNU GCC 5.1 or newer
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
#pragma once

#include "ITemplatableElement.h"
#include "DiaNode.h"

#include <QBrush>
#include <QFont>
#include <QGraphicsItem>
#include <QPen>

class TemplateBox : public QGraphicsItem
{
   ///@cond
   typedef QGraphicsItem super;
   ///@endcond
public: // Constructors
   TemplateBox(QGraphicsItem* parent, DiaNode* node, QFont& font, QPen& linePen, QPen& textPen);
   virtual ~TemplateBox();

public: // Properties
   void setTextBoxSize(QSizeF value);
   QRectF boundingRect() const override;

public: // Methods
   void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
   
private:
   void computeSize();

private: // Attributes
   ///@cond
   DiaNode*             _node;
   ITemplatableElement* _element;
   QSizeF               _size;
   QSizeF               _textBoxSize;
   QBrush               _brush;
   QFont&               _font;
   QPen&                _linePen;
   QPen&                _textPen;
   double               _padding;
   ///@endcond
};
