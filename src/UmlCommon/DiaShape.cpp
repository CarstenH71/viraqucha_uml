//---------------------------------------------------------------------------------------------------------------------
// DiaShape.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class DiaShape.
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
#include "DiaShape.h"
#include "DiaEdge.h"
#include "PropertyStrings.h"
#include "IShapeObserver.h"

/**
 * @class DiaShape
 * @brief The DiaShape class provides basic properties for shapes in UML diagrams.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * The DiaShape class is a base class providing common properties for classes DiaNode and DiaEdge.
 */
 
//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct DiaShape::Data
{
   Data()
   : fontFamily("Arial")
   , fontSize(10)
   , penWidth(1.5)
   , fillColor(0xffffffbc) // A very light yellow
   , lineColor(0xff005000) // A darker green
   , textColor(0xff005000) // Same as line color
   , itemData(nullptr)
   {}

   QList<DiaEdge*>        edges;
   QString                fontFamily;
   int                    fontSize;
   double                 penWidth;
   uint                   fillColor;
   uint                   lineColor;
   uint                   textColor;
   QList<IShapeObserver*> observer;
   void*                  itemData;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
DiaShape::DiaShape()
: data(new Data())
{
}

DiaShape::~DiaShape()
{
   informObserver();
   delete data;
}

/** Gets the list of edges attached to the shape. */
QList<DiaEdge*> DiaShape::edges() const
{
   return QList<DiaEdge*>(data->edges);
}

/** Gets the font family used for drawing text. */
QString DiaShape::fontFamily() const
{
   return data->fontFamily;
}

/** 
 * Sets the font family used for drawing text.
 *
 * Every shape may have its own font setting. This can be set by the user.
 * Default font family is Arial with a font size of 10pt.
 * @param value Name of the font family to be set.
 */
void DiaShape::setFontFamily(const QString& value)
{
   data->fontFamily = value;
}

/** Gets the font size. */
int DiaShape::fontSize() const
{
   return data->fontSize;
}

/**
 * Sets the font size.
 * 
 * Default font size is 10pt.
 * @param value Font size to be set.
 */
void DiaShape::setFontSize(int value)
{
   data->fontSize = value;
}

/** Gets the pen width in pixels. */
double DiaShape::penWidth() const
{
   return data->penWidth;
}

/** Sets the pen width in pixels. */
void DiaShape::setPenWidth(double value) const
{
   data->penWidth = value;
}

/** Gets the background or fill color. */
uint DiaShape::fillColor() const
{
   return data->fillColor;
}

/**
 * Sets the background or fill color.
 *
 * The fill color is used for filling the shape's rectangle or ellipse. The default 
 * fill color is a very light yellow.
 * @param Fill color as unsigned integer.
 */
void DiaShape::setFillColor(uint value)
{
   data->fillColor = value;
}

/** Gets the line color. */
uint DiaShape::lineColor() const
{
   return data->lineColor;
}

/**
 * Sets the line color.
 *
 * The line color is used for drawing the rectangle or ellipse of the shape. The default 
 * line color is a dark green.
 * @param value Line color as unsigned integer.
 */
void DiaShape::setLineColor(uint value)
{
   data->lineColor = value;
}

/** Gets the text color. */
uint DiaShape::textColor() const
{
   return data->textColor;
}

/**
 * Sets the text color.
 *
 * The default text color is the same as the line color, i.e. a dark green.
 * @param value Text color as an unsigned int value.
 */
void DiaShape::setTextColor(uint value)
{
   data->textColor = value;
}

/** Gets associated item data. */
void* DiaShape::itemData() const
{
   return data->itemData;
}

/** Sets associated item data. */
void DiaShape::setItemData(void* value)
{
   data->itemData = value;
}

/** 
 * Attaches a DiaEdge object. 
 * 
 * Each DiaEdge object can be attached only once. More than one attempt to attach the object will be silently ignored.
 * The DiaShape object does not take ownership of the DiaEdge object.
 * @param edge DiaEdge object to be attached. Must not be nullptr.
 */
void DiaShape::attach(DiaEdge* edge)
{
   if (edge != nullptr && !data->edges.contains(edge))
   {
      data->edges.append(edge);
   }
}

/** 
 * Detaches a DiaEdge object. 
 * 
 * @param edge DiaEdge object to be detached.
 */
void DiaShape::detach(DiaEdge* edge)
{
   if (edge != nullptr)
   {
      data->edges.removeOne(edge);
   }
}

/** 
 * Subscribes an observer. 
 * 
 * Each IShapeObserver object can be subscribed only once. More than one attempt to subscribe the object will be 
 * silently ignored. The DiaShape object does not take ownership of the IShapeObserver object.
 * @param observer IShapeObserver object to be subscribed. Must not be nullptr.
 */
void DiaShape::subscribe(IShapeObserver* observer)
{
   if (observer != nullptr && !data->observer.contains(observer))
   {
      data->observer.append(observer);
   }
}

/** 
 * Unsubscribes an observer. 
 * 
 * @param observer IShapeObserver object to be unsubscribed. Must not be nullptr.
 */
void DiaShape::unsubscribe(IShapeObserver* observer)
{
   if (observer != nullptr)
   {
      data->observer.removeOne(observer);
   }
}

/**
 * Serializes properties of the DiaShape object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void DiaShape::serialize(QJsonObject& json, bool read, int version)
{
   Q_UNUSED(version);
   
   QString hexColor;
   if (read)
   {
      data->fontFamily = json[KPropFont].toString();
      data->fontSize = json[KPropFontSize].toInt();
      data->penWidth = json[KPropPenWidth].toDouble();
    
      bool ok;
      hexColor = json[KPropFillColor].toString();
      data->fillColor = hexColor.toUInt(&ok, 16);
      hexColor = json[KPropLineColor].toString();
      data->lineColor = hexColor.toUInt(&ok, 16);
      hexColor = json[KPropTextColor].toString();
      data->textColor = hexColor.toUInt(&ok, 16);
   }
   else
   {
      json[KPropFont] = data->fontFamily;
      json[KPropFontSize] = data->fontSize;
      json[KPropPenWidth] = data->penWidth;
      
      hexColor.setNum(data->fillColor, 16);
      json[KPropFillColor] = hexColor;
      hexColor.setNum(data->lineColor, 16);
      json[KPropLineColor] = hexColor;
      hexColor.setNum(data->textColor, 16);
      json[KPropTextColor] = hexColor;
   }
}

void DiaShape::informObserver()
{
   for (IShapeObserver* obs : data->observer)
   {
      obs->aboutToDestroy();
   }
}
