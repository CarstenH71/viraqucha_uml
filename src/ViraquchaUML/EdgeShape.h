//---------------------------------------------------------------------------------------------------------------------
// EdgeShape.h
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
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
#pragma once

#include "Shape.h"
#include "DiaEdge.h"

#include <qmath.h>
#include <QPolygonF>

class UmlElement;

class EdgeShape : public Shape
{
   ///@cond
   typedef Shape super;
   ///@endcond
public:
   enum EndingStyle { NoArrows = 0x00, ArrowAtStart = 0x01, ArrowAtEnd = 0x02, ArrowAtBoth = 0x03 };

protected:
   const double KArrowSize = 12.0;
   const double KPi13 = M_PI / 3.0;
   const double KPi23 = 2.0 * M_PI / 3.0;

public:
   EdgeShape(QGraphicsItem* parent, DiaEdge* edge);
   virtual ~EdgeShape();

public: // Properties
   UmlElement* element() const override;
   DiaEdge* diaEdge() const;
   
   QRectF boundingRect() const override;
   QPainterPath shape() const override;

   EndingStyle endingStyle() const;
   void setEndingStyle(EndingStyle value);

   Qt::PenStyle lineStyle() const;
   void setLineStyle(Qt::PenStyle value);

   QPolygonF line() const;
   void setLine(QPolygonF value);

public: // Methods
   QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
   void updatePosition();

protected:
   void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

   void makeDirectLine(const QPointF& start, const QPointF& end);
   void makeAutoRoute(const QPointF& start, const QPointF& end);
   void makeCustomLine(const QPointF& start, const QPointF& end);

   void drawTextBoxes(QPainter* painter);
   void drawCenterBox(QPainter* painter, QFontMetricsF& metrics, QString text);
   void drawMuliplicityBox(QPainter* painter, QFontMetricsF& metrics, int item, QString text);
   void drawAttributeBox(QPainter* painter, QFontMetricsF& metrics, int item, QString text);
   
   void drawArrow(QPainter* painter, const QLineF& line, bool closed);
   void drawCircle(QPainter* painter, const QLineF& line, bool crossed);
   void drawDiamond(QPainter* painter, const QLineF& line, bool filled);

   virtual void drawLineStart(QPainter* painter, const QLineF& line) = 0;
   virtual void drawLineEnd(QPainter* painter, const QLineF& line) = 0;
   
private:
   void computeAngles(const QLineF& line, double& angle1, double& angle2);
   QPointF computeIntersection(QGraphicsItem* item, int* side = nullptr, bool margin = false);
   
private: // Attributes
   ///@cond
   DiaEdge*       _edge;
   QPolygonF      _arrow;
   QPolygonF      _line;
   QGraphicsItem* _items[2];
   EndingStyle    _style;
   QBrush         _solidBrush;
   ///@endcond
};

