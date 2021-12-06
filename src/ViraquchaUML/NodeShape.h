//---------------------------------------------------------------------------------------------------------------------
// NodeShape.h
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class NodeShape.
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
#pragma once

#include "Shape.h"
#include "DiaNode.h"

#include <QSizeF>
#include <QRectF>
#include <QPainter>
#include <QVariant>

class UmlElement;

class NodeShape : public Shape
{
   typedef Shape super;   
public: // Constructors
   NodeShape(QGraphicsItem* parent, DiaNode* node);
   virtual ~NodeShape();

public: // Properties
   UmlElement* element() const override;

   DiaNode* diaNode() const;

   QSizeF nodeSize() const;
   void setNodeSize(QSizeF value);
   
   double padding() const;
   void setPadding(double value);

   QSizeF textBoxSize() const;
   void setTextBoxSize(QSizeF value);
   
   QRectF boundingRect() const override;

public: // Methods
   QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

protected:
   virtual void drawSelectionFrame(QPainter* painter);
   virtual void computeSize(bool templated = false);

private: // Attributes
   DiaNode* _node;
   double   _padding;
   QSizeF   _textBoxSize;
};

