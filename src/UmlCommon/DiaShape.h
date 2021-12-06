//---------------------------------------------------------------------------------------------------------------------
// DiaShape.h
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class DiaShape.
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

#include "umlcommon_globals.h"
#include "ISerializable.h"

#include <QPointF>
#include <QSizeF>

class DiaEdge;
class IShapeObserver;

class UMLCOMMON_EXPORT DiaShape : public ISerializable
{
public: // Constructors
   DiaShape();
   virtual ~DiaShape();

public: // Properties
   QList<DiaEdge*> edges() const;

   QPointF pos() const;
   void setPos(const QPointF& value);

   QString fontFamily() const;
   void setFontFamily(const QString& value);

   int fontSize() const;
   void setFontSize(int value);

   double penWidth() const;
   void setPenWidth(double value) const;

   uint fillColor() const;
   void setFillColor(uint value);

   uint lineColor() const;
   void setLineColor(uint value);

   uint textColor() const;
   void setTextColor(uint value);

   void* itemData() const;
   void setItemData(void* value);

public: // Methods
   void attach(DiaEdge* edge);
   void detach(DiaEdge* edge);
   
   void subscribe(IShapeObserver* observer);
   void unsubscribe(IShapeObserver* observer);

   void serialize(QJsonObject& json, bool read, int version) override;

private:
   void informObserver();

private: // Attributes
   /// @cond
   struct Data;
   Data* data;
   /// @endcond
};
