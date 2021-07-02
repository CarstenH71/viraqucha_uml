//---------------------------------------------------------------------------------------------------------------------
// Shape.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class Shape.
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
#include "Shape.h"

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>

/**
 * @class Shape
 * @brief Abstract base class of all diagram shapes of ViraquchaUML
 * @since 1.0
 * @ingroup GUI
 *
 * The Shape class is the abstract base class of all diagram shapes of ViraquchaUML. It provides properties needed by
 * all diagram shapes.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the Shape class.
 *
 * @param parent Parent item of the instance. May be null.
 * @param shape DiaShape instance needed for initializing brushes, fonts and pens. Must not be null.
 */
Shape::Shape(QGraphicsItem* parent, DiaShape* shape)
: super(parent)
, _shape(shape)
{
   Q_ASSERT(_shape != nullptr);
   _shape->subscribe(this);
   
   _brush.setColor(QColor(shape->fillColor()));
   _brush.setStyle(Qt::SolidPattern);
   
   _font.setFamily(shape->fontFamily());
   _font.setPointSize(shape->fontSize());

   _linePen.setWidthF(shape->penWidth());
   _linePen.setColor(shape->lineColor());
    
   _textPen.setColor(shape->textColor());

   setFlag(QGraphicsItem::ItemIsSelectable, true);
   setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

Shape::~Shape()
{
   _shape->unsubscribe(this);
}

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** Gets the DiaShape object associated. */
DiaShape* Shape::diaShape() const
{
   return _shape;
}

/** Gets the context menu. */
QMenu* Shape::contextMenu() const
{
   return _contextMenu;
}

/** Sets the context menu. */
void Shape::setContextMenu(QMenu* value)
{
   _contextMenu = value;
}

/** Saves line and text pen styles. */
void Shape::savePenStyle()
{
   _savedLine = _linePen.style();
   _savedText = _textPen.style();
}

/** Restores line and text pen styles. */
void Shape::restorePenStyle()
{
   _linePen.setStyle(_savedLine);
   _textPen.setStyle(_savedText);
}

/** Called by the DiaNode object if destroyed, removes the shape from the diagram scene and deletes itself. */
void Shape::aboutToDestroy()
{
   scene()->removeItem(this);
   delete this;
}

/**
 * Handles context menu events sent by the QGraphicsScene object.
 * 
 * Opens the context menu set at the current mouse position. Asserts if the context menu was not set.
 * @param event Context menu event of the QGraphicsScene object.
 */
void Shape::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
   scene()->clearSelection();
   setSelected(true);
   
   Q_ASSERT(_contextMenu != nullptr);
   _contextMenu->exec(event->screenPos());
}
