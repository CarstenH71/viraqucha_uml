//---------------------------------------------------------------------------------------------------------------------
// Shape.h
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class Shape.
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

#include "DiaShape.h"
#include "IShapeObserver.h"

#include <QBrush>
#include <QFont>
#include <QMenu>
#include <QGraphicsItem>
#include <QPen>

class UmlElement;

class Shape : public QGraphicsItem, public IShapeObserver
{
   typedef QGraphicsItem super;
public: // Constructors
    Shape(QGraphicsItem* parent, DiaShape* shape);
    virtual ~Shape();

public: // Properties
   virtual UmlElement* element() const = 0;
   DiaShape* diaShape() const;
   
   QMenu* contextMenu() const;
   void setContextMenu(QMenu* value);

protected: // Methods
   void savePenStyle();
   void restorePenStyle();
   void aboutToDestroy() override;
   void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

protected: // Attributes
   DiaShape*    _shape;
   QBrush       _brush;
   QFont        _font;
   QPen         _linePen;
   QPen         _textPen;
   Qt::PenStyle _savedLine;
   Qt::PenStyle _savedText;
   
private:
   QMenu*       _contextMenu;
};
