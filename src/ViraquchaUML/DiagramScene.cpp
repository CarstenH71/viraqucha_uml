//---------------------------------------------------------------------------------------------------------------------
// DiagramScene.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class DiagramScene.
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
#include "DiagramScene.h"

#include "ProjectTreeView.h"
#include "Shape.h"
#include "ShapeFactory.h"

#include "DiaEdge.h"
#include "DiaNode.h"
#include "NameBuilder.h"
#include "UmlCompositeElement.h"
#include "UmlElement.h"
#include "UmlDiagram.h"
#include "UmlLink.h"
#include "UmlProject.h"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QUuid>

/**
 * @class DiagramScene
 * @brief Extends the QGraphicsScene class by functionality needed for drawing UML diagrams.
 * @since 1.0
 * @ingroup GUI
 *
 * The DiagramScene class extends the QGraphicsScene class by functions for drawing the UML diagrams of ViraquchaUML,
 * that is functions for...
 * - dragging and dropping of UML elements from the project tree into the scene;
 * - mouse handling needed to create new UML elements as well as their shapes;
 * - rebuilding a complete diagram scene from stored UML project data.
 * 
 * DiagramScene knows the following edit modes:
 * - NoEditing: No editing is done. This is the default edit mode.
 * - InsertElement: Inserts a new UmlElement object (+ DiaNode + Shape objects) into the scene by simple mouse click.
 * - LinkElements: Inserts a new UmlLink object (+ DiaEdge + Shape objects) and connects two UmlElement objects with
 *   each other using a &quot;rubber line&quot;.
 * 
 * The size of the diagram scene is currently set to a maximum width and height of 5000 points each.
 */

//---------------------------------------------------------------------------------------------------------------------
// Constructors
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the DiagramScene class.
 * 
 * @param diagram UmlDiagram to be drawn by the scene.
 * @param contextMenu Context menu to be shown when a shape was clicked with the right mouse button.
 */
DiagramScene::DiagramScene(UmlDiagram* diagram, QMenu* contextMenu)
: super(nullptr)
, _diagram(diagram)
, _editMode(NoEditing)
, _rubberLine(nullptr)
, _linePen(QColor(Qt::black))
, _contextMenu(contextMenu)
{
   Q_ASSERT(_diagram != nullptr);
   setSceneRect(QRectF(0.0, 0.0, 5000.0, 5000.0));

   _linePen.setWidth(1);
   _linePen.setStyle(Qt::DashLine);

   if (_diagram->open())
   {
      ShapeFactory::instance().buildScene(this, _diagram);
   }
}

DiagramScene::~DiagramScene()
{
   _diagram->close();
}

//---------------------------------------------------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------------------------------------------------

/** Gets the context menu of the diagram scene. */
QMenu* DiagramScene::contextMenu() const
{
   return _contextMenu;
}

/** 
 * Sets the class name of the object to be inserted into the diagram scene. 
 * 
 * The class name is needed by the mouse event handler to create a UmlElement object. It is set by the DiagramPage 
 * object owning this object.
 * @param value Class name.
 */
void DiagramScene::setClassName(QString value)
{
    _className = value;
}

/**
 * Sets the edit mode of the diagram scene.
 */
void DiagramScene::setEditMode(EditMode value)
{
    _editMode = value;
}

/**
 * Handles the DragEnter event of the Drag & Drop mechanism.
 * 
 * Accepts the event if event source is an object of the ProjectTreeView class. Other event sources are ignored.
 * @param event The event to be handled.
 */
void DiagramScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
   auto* source = qobject_cast<ProjectTreeView*>(event->source());
   if (source != nullptr)
   {
      event->setDropAction(Qt::LinkAction);
      event->accept();
      return;
   }

   super::dragEnterEvent(event);
}

/**
 * Handles the DragMove event of the Drag & Drop mechanism.
 * 
 * Accepts the event if event source is an object of the ProjectTreeView class. Other event sources are ignored.
 * @param event The event to be handled.
 */
void DiagramScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
   auto* source = qobject_cast<ProjectTreeView*>(event->source());
   if (source != nullptr)
   {
      event->setDropAction(Qt::LinkAction);
      event->accept();
      return;
   }

   super::dragMoveEvent(event);
}

/**
 * Handles the Drop event of the Drag & Drop mechanism.
 * 
 * Accepts the event if event source is an object of the ProjectTreeView class. Other event sources are ignored.
 * Creates a new shape for the UML element dropped, if it is not already contained in the UML diagram.
 * @param event The event to be handled.
 */
void DiagramScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
   auto* source = qobject_cast<ProjectTreeView*>(event->source());
   if (source != nullptr)
   {
      QUuid id(event->mimeData()->data("application/uuid"));
      
      UmlElement* elem = nullptr;
      _diagram->project()->find(id, &elem);
      if (elem != nullptr)
      {
         // Reject if element is already contained
         if (_diagram->contains(id)) 
         {
            // TODO: Error message?
            return;
         }
         
         auto* node = _diagram->addNode(elem);
         node->setPos(event->scenePos());

         // Create new shape for the edge or node:
         auto* item = ShapeFactory::instance().buildShape(node);
         item->setContextMenu(_contextMenu);
         addItem(item);
      }

      return;
   }

   super::dropEvent(event);
}

/**
 * Processes a mouse press event sent by the QGraphicsScene object.
 * 
 * Emits elementInserted and insertAborted signals. The mouse press event is processed depending on the current edit 
 * mode:
 * 
 * - If mode is EditMode::InsertElement it creates a new UmlElement object using the class name set and adds it to the
 *   project. Then it creates a DiaNode object which represents the UmlElement object in the diagram and adds it to the
 *   UmlDiagram object. Finally it creates a Shape object using the ShapeFactory and adds it to the graphics scene.
 * - If mode is EditMode::LinkElements it adds a new QGraphicsLineItem (the rubber line) at the current mouse position 
 *   to the graphics scene. 
 * 
 * See also setClassName() and setEditMode().
 * @param event Event arguments.
 */
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
   if (event->button() != Qt::LeftButton) return;
   switch (_editMode)
   {
   case InsertElement:
   {
      auto* project = _diagram->project();
      auto* element = project->insertNew(_className);
      if (element != nullptr)
      {
         auto* named = dynamic_cast<INamedElement*>(element);
         if (named != nullptr)
         {
            Q_ASSERT(_diagram->owner() != nullptr);
            NameBuilder builder(_diagram->owner());
            builder.buildFor(named, _className.remove("Uml"));
         }

         auto* node = _diagram->addNode(element);
         node->setPos(event->scenePos());

         // Create new shape for the node:
         auto* item = ShapeFactory::instance().buildShape(node);
         item->setContextMenu(_contextMenu);
         addItem(item);
         
         emit elementInserted(element);
      }
      else
      {
         emit insertAborted();
      }
      break;
   }
   case LinkElements:
      _rubberLine = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
      _rubberLine->setPen(_linePen);
      addItem(_rubberLine);
      break;
   default:
      break;
   }

   super::mousePressEvent(event);
}

/**
 * Processes a mouse move event sent by the QGraphicsScene object.
 * 
 * If edit mode is EditMode::LinkElements updates the position of the second (end) point of the rubber line to the 
 * current mouse position.
 * @param event Event arguments.
 */
void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
   if (_editMode == LinkElements && _rubberLine != nullptr)
   {
      _rubberLine->setLine(QLineF(_rubberLine->line().p1(), event->scenePos()));
      return;
   }

   super::mouseMoveEvent(event);
}

/**
 * Processes a mouse release event sent by the QGraphicsScene object.
 * 
 * Emits elementInserted and insertAborted signals. If edit mode is EditMode::LinkElements creates a new UmlLink object
 * and adds it to the project. Then it creates a DiaEdge object and connects it with the DiaNode objects selected by
 * the user. Finally it creates a Shape object using the ShapeFactory and adds it to the graphics scene.
 * @param event Event arguments.
 */
void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
   if (_editMode == LinkElements && _rubberLine != nullptr)
   {
      QList<QGraphicsItem*> startItems = items(_rubberLine->line().p1());
      if (startItems.count() != 0 && startItems.first() == _rubberLine)
      {
         startItems.removeFirst();
      }

      QList<QGraphicsItem*> endItems = items(_rubberLine->line().p2());
      if (endItems.count() != 0 && endItems.first() == _rubberLine)
      {
         endItems.removeFirst();
      }

      removeItem(_rubberLine);
      delete _rubberLine;
      _rubberLine = nullptr;

      if (!startItems.empty() && !endItems.empty())
      {
         // Create new link, connect DiaShapes etc.:
         auto* project = _diagram->project();
         auto* element = project->insertNew(_className);
         if (element != nullptr)
         {
            auto* link = dynamic_cast<UmlLink*>(element);
            auto* item1 = dynamic_cast<Shape*>(startItems.first());
            auto* item2 = dynamic_cast<Shape*>(endItems.first());
            link->setSource(item1->element());
            link->setTarget(item2->element());

            auto* edge = _diagram->addEdge(link);
            edge->setPos(event->scenePos());
            edge->setShape1(item1->diaShape());
            edge->setShape2(item2->diaShape());
            edge->setRouting(item1 == item2 ? RoutingKind::Auto : RoutingKind::Direct);

            // Create new shape for the edge:
            auto* item3 = ShapeFactory::instance().buildShape(edge);
            item3->setContextMenu(_contextMenu);
            addItem(item3);

            emit elementInserted(element);
         }
      }
      else
      {
         emit insertAborted();
      }
   }

   _editMode = NoEditing;
   super::mouseReleaseEvent(event);
}
