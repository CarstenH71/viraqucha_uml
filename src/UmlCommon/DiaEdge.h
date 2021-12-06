//---------------------------------------------------------------------------------------------------------------------
// DiaEdge.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class DiaEdge.
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
#include "DiaShape.h"
#include "RoutingKind.h"

#include <QPointF>
#include <QVector>

class DiaNode;
class Label;
class UmlLink;

class UMLCOMMON_EXPORT DiaEdge : public DiaShape
{
   typedef DiaShape super;
public:
   DiaEdge();
   virtual ~DiaEdge();

public: // Properties
   UmlLink* link() const;
   void setLink(UmlLink* value);

   DiaShape* shape1() const;
   void setShape1(DiaShape* value);

   DiaShape* shape2() const;
   void setShape2(DiaShape* value);

   RoutingKind routing() const;
   void setRouting(RoutingKind value);

   QVector<QPointF> points() const;
   void setPoints(QVector<QPointF> value);

   QVector<Label*> labels() const;

public: // Methods
   void clear();
   void serialize(QJsonObject& json, bool read, int version) override;

private: // Attributes
   struct Data;
   Data* data;
};
