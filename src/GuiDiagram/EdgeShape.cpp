//---------------------------------------------------------------------------------------------------------------------
// EdgeShape.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class EdgeShape.
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
#include "EdgeShape.h"

#include "Label.h"
#include "UmlLink.h"

#include <qmath.h>
#include <QFontMetricsF>
#include <QPainter>

/**
 * @class EdgeShape
 * @brief Abstract base class for edge shapes.
 * @since 0.1.0
 * @ingroup GuiDiagram
 *
 * The EdgeShape class is an abstract base class that can be used for drawing UML relationships like Generalization, 
 * Realization, Association etc. It needs a DiaEdge object on construction that must contain pointers to the graphics
 * items of the two nodes to which the edge is attached to.
 *
 * Ending style as well as line style can be set in the constructor of a derived class using functions setEndingStyle()
 * and setLineStyle(). These styles are used for drawing the line and for optimization (ending style).
 *
 * The paint() function is implemented such, that it draws a polyline according to the RoutingKind set at the DiaEdge
 * object first. Then it calls abstract functions drawLineStart() and drawLineEnd() to draw the arrows at the start and
 * end of the polyline respectively. These functions must be implemented by derived classes to draw suitable arrows or
 * line endings (e.g. the diamond of an UML association). After drawing polyline and line endings, it draws the text
 * boxes for name, multiplicity and attributes and finally - if selected - the selection boxes (small rectangles at
 * each end of the polyline).
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the EdgeShape class.
 *
 * Parameter edge must not be nullptr!
 * @param parent The parent graphics item in the graphics scene.
 * @param edge The DiaEdge object associated with this object.
 */
EdgeShape::EdgeShape(QGraphicsItem* parent, DiaEdge* edge)
: super(parent, edge)
, _edge(edge)
{
   Q_ASSERT(_edge != nullptr);
   _edge->setItemData(static_cast<void*>(this));

   _solidBrush.setColor(QColor(_edge->lineColor()));
   _solidBrush.setStyle(Qt::SolidPattern);
   
   _items[0] = static_cast<QGraphicsItem*>(_edge->shape1()->itemData());
   _items[1] = static_cast<QGraphicsItem*>(_edge->shape2()->itemData());

   switch (_edge->routing())
   {
   case RoutingKind::Auto:
      makeAutoRoute();
      break;
   case RoutingKind::Custom:
      loadPoints();
      break;
   case RoutingKind::Direct:
   default:
      makeDirectLine();
      break;
   }
}

EdgeShape::~EdgeShape()
{
}

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** Gets the UmlElement object. */
UmlElement* EdgeShape::element() const
{
   return _edge != nullptr ? _edge->link() : nullptr;
}

/** Gets the DiaEdge object. */
DiaEdge* EdgeShape::diaEdge() const
{
   return _edge;
}

/** Gets the bounding rectangle of the edge shape. */
QRectF EdgeShape::boundingRect() const
{
   /*
   double extra = (_linePen.width() + 30) / 2.0;
   QLineF temp(_line.first(), _line.last());
   return QRectF(
      temp.p1(), 
      QSizeF(temp.p2().x() - temp.p1().x(), temp.p2().y() - temp.p1().y())).normalized().adjusted(-extra, -extra, extra, extra);
   */
   return shape().controlPointRect() + QMarginsF(5.0, 5.0, 5.0, 5.0);
}

/** Gets the shape of the edge shape as a painter path. */
QPainterPath EdgeShape::shape() const
{
   QPainterPath path;
   path.addPolygon(_line);
   path.addPolygon(_arrow);

   if (diaEdge() != nullptr)
   {
      auto boxes = diaEdge()->labels();
      if (boxes.size() == 5)
      {
         path.addText(findMidPoint(), _font, boxes[0]->text());
      }
   }

   QPainterPathStroker stroker(_linePen);
   return stroker.createStroke(path);
}

/** Gets the ending style of the edge shape. */
EdgeShape::EndingStyle EdgeShape::endingStyle() const
{
   return _style;
}

/** Sets the ending style of the edge shape. */
void EdgeShape::setEndingStyle(EdgeShape::EndingStyle value)
{
   _style = value;
}

/** Gets the line style of the edge shape. */
Qt::PenStyle EdgeShape::lineStyle() const
{
   return _linePen.style();
}

/** Sets the line style of the edge shape. */
void EdgeShape::setLineStyle(Qt::PenStyle value)
{
    _linePen.setStyle(value);
}

/** Gets the line of the edge shape. */
QPolygonF EdgeShape::line() const
{
   return _line;
}

/** Sets the line of the edge shape. */
void EdgeShape::setLine(QPolygonF value)
{
   _line = value;
}

/** Handles the itemChange event. */
QVariant EdgeShape::itemChange(GraphicsItemChange change, const QVariant& value)
{
   if (change == ItemPositionHasChanged)
   {
   }

   return super::itemChange(change, value);
}

/** Updates the position of the edge shape. */
void EdgeShape::updatePosition()
{
   if (diaEdge() != nullptr)
   {
      switch (diaEdge()->routing())
      {
      case RoutingKind::Auto:
         makeAutoRoute();
         break;
      case RoutingKind::Custom:
         updateCustomLine();
         break;
      case RoutingKind::Direct:
      default:
         makeDirectLine();
         break;
      }
   }
}

/**
 * Paints the edge shape.
 *
 * @param painter QPainter object needed for painting.
 * @param option This parameter is unused.
 * @param widget This parameter is unused.
 */
void EdgeShape::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
   Q_UNUSED(option);
   Q_UNUSED(widget);

   // Don't even try to draw a line between colliding nodes!
   if (_items[0] != _items[1] && _items[0]->collidesWithItem(_items[1])) return;

   // Draw line and line endings:
   painter->setPen(_linePen);
   painter->setBrush(_brush);
   painter->drawPolyline(_line);
   if (_style == EndingStyle::ArrowAtStart || _style == EndingStyle::ArrowAtBoth)
   {
      drawLineStart(painter, QLineF(_line[0], _line[1]));
   }
   if (_style == EndingStyle::ArrowAtEnd || _style == EndingStyle::ArrowAtBoth)
   {
      drawLineEnd(painter, QLineF(_line[_line.length() - 1], _line[_line.length() - 2]));
   }

   // Draw text boxes at each end and in the middle of the line:
   auto boxes = diaEdge()->labels();
   if (boxes.size() == 5)
   {
      QFontMetricsF metrics(_font);
      drawCenterBox(painter, metrics, boxes[0]->text());
      drawMuliplicityBox(painter, metrics, 0, boxes[1]->text());
      drawAttributeBox(painter, metrics, 0, boxes[2]->text());
      drawMuliplicityBox(painter, metrics, 1, boxes[3]->text());
      drawAttributeBox(painter, metrics, 1, boxes[4]->text());
   }

   // Draw small rectangles around each point of the line if selected:
   if (isSelected())
   {
      painter->setBrush(Qt::white);
      for (const QPointF& point : _line)
      {
         painter->drawRect(point.x() - KSBSize2, point.y() - KSBSize2, KSBSize, KSBSize);
      }
   }
}

/**
 * Makes a direct line between the two nodes attached but does not draw it.
 * 
 * The resulting line is stored in the _line attribute of this class.
 * @param start Starting point of the line.
 * @param end Ending point of the line.
 */
void EdgeShape::makeDirectLine()
{
   auto p0 = computeIntersection(_items[0]);
   auto p1 = computeIntersection(_items[1]);

   setPos(p0);
   diaEdge()->setPos(p0);
   _line.clear();
   _line << mapFromScene(p0) << mapFromScene(p1);
   savePoints();
}

/**
 * Makes an auto route line between the two nodes attached but does not draw it.
 * 
 * The resulting line is stored in the _line attribute of this class.
 * @param start Starting point of the line.
 * @param end Ending point of the line.
 */
void EdgeShape::makeAutoRoute()
{
   if (_items[0] == _items[1])
   {
      const double k = 25.0;
      const double k2 = 2.0 * k;

      // Edge points to the same item!
      QRectF rect = _items[0]->boundingRect();
      if (_items[0]->childItems().count() != 0 && _items[0]->childItems().first()->isVisible())
      {
         // Shape has a template box at the top: draw line around upper left corner
         QPointF p0(_items[0]->pos().x() - rect.width() / 2.0, _items[0]->pos().y() - rect.height() / 2.0 + k);
         setPos(p0);
         diaEdge()->setPos(p0);
         _line.clear();
         _line << QPointF(0.0, 0.0) << QPointF(-k, 0.0) << QPointF(-k, -k2) << QPointF(k, -k2) << QPointF(k, -k);
      }
      else
      {
         // Draw line around upper right corner
         QPointF p0(_items[0]->pos().x() + rect.width() / 2.0, _items[0]->pos().y() - rect.height() / 2.0 + k);
         setPos(p0);
         diaEdge()->setPos(p0);
         _line.clear();
         _line << QPointF(0.0, 0.0) << QPointF(k, 0.0) << QPointF(k, -k2) << QPointF(-k, -k2) << QPointF(-k, -k);
      }
   }
   else
   {
       // TODO: Find auto route between items
   }
   savePoints();
}

/**
 * Updates the points of a custom line between the two nodes attached but does not draw it.
 * 
 * A custom line can be modified by dragging midpoints of the line. The resulting line is stored in the _line attribute
 * of this class.
 * @param start Starting point of the line.
 * @param end Ending point of the line.
 */
void EdgeShape::updateCustomLine()
{
   Q_ASSERT(!_line.isEmpty());

   // TODO: Update only start and end point of the custom line and leave all other points unmodified?
   // Like this:
   _line.first() = mapFromScene(computeIntersection(_items[0]));
   _line.last()  = mapFromScene(computeIntersection(_items[1]));
   savePoints();
}

/**
 * Draws the center text box containing name and stereotype of the edge.
 * 
 * @param painter
 * @param metrics
 * @param text
 */
void EdgeShape::drawCenterBox(QPainter* painter, QFontMetricsF& metrics, QString text)
{
   if (_line.length() > 1)
   {
      auto pos = findMidPoint();
      auto rect = metrics.boundingRect(QRectF(0.0, 0.0, 10.0, 10.0), Qt::AlignLeft, text);
      painter->drawText(
         pos.x() - rect.width() / 2.0,
         pos.y() - rect.height() - 5.0,
         rect.width(),
         rect.height(),
         Qt::AlignLeft,
         text);
   }
}

/**
 * Draws a multiplicity box at one end of the edge.
 * 
 * The multiplicity box contains the multiplicity (0, 1 or many) information of an association.
 * @param painter A QPainter object needed for drawing.
 * @param metrics Font metrics needed to render the text.
 * @param item Number of the item at which the multiplicity box shall be drawn (0 or 1).
 * @param text Text to be rendered.
 */
void EdgeShape::drawMuliplicityBox(QPainter* painter, QFontMetricsF& metrics, int item, QString text)
{
   int     side = 0;
   QPointF pos = computeIntersection(_items[item], &side, true);
   QRectF  rect = metrics.boundingRect(QRectF(0.0, 0.0, 10.0, 10.0), Qt::AlignLeft, text);

   // Move text box according to side number:
   switch (side)
   {
      case 1: // Top
         pos.setY(pos.y() - rect.height());
         break;
      case 2: // Right
         break;
      case 3: // Bottom
         break;
      case 4: // Left
         pos.setX(pos.x() - rect.width());
         break;
      default:
         break;
   }
   
   painter->drawText(pos.x(), pos.y(), rect.width() + 5.0, rect.height() + 5.0, Qt::AlignLeft, text);
}

/**
 * Draws the attribute box at one end of the line.
 *
 * This function is currently not implemented.
 * @param painter
 * @param metrics
 * @param item
 * @param text
 */
void EdgeShape::drawAttributeBox(QPainter* painter, QFontMetricsF& metrics, int item, QString text)
{
   Q_UNUSED(painter);
   Q_UNUSED(metrics);
   Q_UNUSED(item);
   Q_UNUSED(text);
   // TODO: Draw the attribute box
}

/** 
 * Draws an opened or closed arrow at one end of a given line.
 *
 * If drawn closed, the arrow is automatically filled with the fill color set at the DiaShape object attached to
 * this object.
 * @param painter QPainter object needed for drawing.
 * @param line Line to attach the arrow to.
 * @param closed True, if the arrow shall be drawn closed, false otherwise.
 */
void EdgeShape::drawArrow(QPainter* painter, const QLineF& line, bool closed)
{
   double angle1, angle2;
   computeAngles(line, angle1, angle2);

   QPointF arrowP1 = line.p1() + QPointF(sin(angle1) * KArrowSize, cos(angle1) * KArrowSize);
   QPointF arrowP2 = line.p1() + QPointF(sin(angle2) * KArrowSize, cos(angle2) * KArrowSize);

   _arrow.clear();
   _arrow << arrowP1 << line.p1() << arrowP2;

   auto saved = _linePen.style();
   _linePen.setStyle(Qt::SolidLine);
   painter->setPen(_linePen);
   if (closed)
   { 
      painter->drawPolygon(_arrow);
   }
   else
   {
      painter->drawPolyline(_arrow);
   }
   _linePen.setStyle(saved);
}

/**
 * Draws a circle at one end of a given line.
 * 
 * The circle is filled with the fill color set at the DiaShape object attached to this object.
 * @param painter QPainter object needed for drawing.
 * @param line Line to attach the arrow to.
 * @param crossed If true, draws a cross into the circle.
 */
void EdgeShape::drawCircle(QPainter* painter, const QLineF& line, bool crossed)
{
   Q_UNUSED(painter);
   Q_UNUSED(line);
   Q_UNUSED(crossed);
   // TODO: Draw the circle
}

/**
 * Draws a filled or unfilled diamond at one end of a given line.
 *
 * The diamond is filled either with the fill color or the line color of the DiaShape object attached to this object.
 * @param painter QPainter object needed for drawing.
 * @param line Line to attach the arrow to.
 * @param filled True, if the arrow shall be filled with the line color; false if it shall be filled with the fill color.
 */
void EdgeShape::drawDiamond(QPainter* painter, const QLineF& line, bool filled)
{
   double angle1, angle2;
   computeAngles(line, angle1, angle2);

   QPointF tempPt  = QPointF(sin(angle2) * KArrowSize, cos(angle2) * KArrowSize);
   QPointF arrowP1 = line.p1() + QPointF(sin(angle1) * KArrowSize, cos(angle1) * KArrowSize);
   QPointF arrowP2 = arrowP1 + tempPt;
   QPointF arrowP3 = line.p1() + tempPt;

   _arrow.clear();
   _arrow << line.p1() << arrowP1 << arrowP2 << arrowP3;

   if (filled) painter->setBrush(_solidBrush);
   
   savePenStyle();
   _linePen.setStyle(Qt::SolidLine);
   painter->setPen(_linePen);
   painter->drawPolygon(_arrow);
   restorePenStyle();
}

void EdgeShape::aboutToDestroy()
{
   // Reset DiaEdge object, since it is not used any more:
   _edge = nullptr;
   super::aboutToDestroy();
}

/**
 * Computes the two angles needed for drawing arrows and diamonds.
 * 
 * @param line
 * @param angle1
 * @param angle2
 */
void EdgeShape::computeAngles(const QLineF& line, double& angle1, double& angle2)
{
   double angle0 = std::atan2(-line.dy(), line.dx());
   angle1 = angle0 + KPi13;
   angle2 = angle0 + KPi23;
}

/**
 * Computes the intersection point between a line and a graphics item in scene coordinates.
 * 
 * This function assumes that the two graphics items are connected with a direct line pointing to the midpoint of
 * each graphics item. It then computes the intersection point with the bounding rectangle of the given graphics
 * item with the direct line.<br/>
 * The function also computes on which side of the bounding rectangle of the given item the intersection point lies:
 * - Top: side = 1;
 * - Right: side = 2;
 * - Bottom: side = 3;
 * - Left: side = 4.
 *
 * Note that the resulting intersection point is in scene coordinates! Use function mapFromScene() to map the point
 * to item coordinates.
 *
 * @param item Graphics item to compute the intersection point.
 * @param side Number of the side of the bounding rectangle where the intersection point lies.
 * @param margin True, if margins shall be added to the bounding rectangle of the given item.
 */
QPointF EdgeShape::computeIntersection(QGraphicsItem* item, int* side, bool margin)
{
   QRectF      rect = item->boundingRect();
   if (margin) rect += QMarginsF(5.0, 5.0, 5.0, 5.0);
   
   QPolygonF boundary(rect);
   QLineF    connector(_items[0]->pos(), _items[1]->pos());
   QPointF   p1 = boundary.first() + item->pos();
   QPointF   p2;
   QLineF    line;
   QPointF   result;
   int       index;
   
   for (index = 1; index < boundary.count(); ++index)
   {
      p2   = boundary.at(index) + item->pos();
      line = QLineF(p1, p2);
      if (line.intersect(connector, &result) == QLineF::BoundedIntersection) break;
      p1 = p2;
   }

   if (side != nullptr) *side = index;
   return result;
}

int EdgeShape::findNearestCorner(QGraphicsItem* item, QPointF pos)
{
   QPolygonF boundary(item->boundingRect());
   double    lastDist = 0.0;
   int       result = -1;

   for (int index = 0; index < boundary.length(); ++index)
   {
      auto corner = boundary.at(index) + item->pos();
      double dist = QPointF::dotProduct(corner, pos);
      if (dist < lastDist || index == 0)
      {
         result = index;
         lastDist = dist;
      }
   }

   return result;
}

QPointF EdgeShape::findMidPoint() const
{
   int midIndex = _line.length() / 2;
   return QLineF(_line[midIndex - 1], _line[midIndex]).center();
}

/** Loads points from the DiaEdge object. */
void EdgeShape::loadPoints()
{
   if (diaEdge() != nullptr)
   {
      auto points = diaEdge()->points();
      for (const QPointF& point : points)
      {
         _line << point;
      }

      setPos(diaEdge()->pos());
   }
}

/** Saves points to the DiaEdge object. */
void EdgeShape::savePoints()
{
   if (diaEdge() != nullptr)
   {
      QVector<QPointF> points;
      for (const QPointF& point : _line)
      {
         points.append(point);
      }

      diaEdge()->setPos(pos());
      diaEdge()->setPoints(points);
   }
}
