//---------------------------------------------------------------------------------------------------------------------
// DiagramPage.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class DiagramPage.
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
#include "DiagramPage.h"
#include "DiagramScene.h"
#include "PropertiesDialog.h"
#include "Shape.h"
#include "ToolBoxManager.h"

#include "UmlDiagram.h"

//#define _USE_OPENGL
#ifdef _USE_OPENGL
#include <QOpenGLWidget>
#endif

/**
 * @class DiagramPage
 * @brief Implements a diagram page.
 * @since 1.0
 * @ingroup GUI
 *
 * The DiagramPage class manages the DiagramScene object which draws all elements associated with a UmlDiagram object.
 * It also provides slots needed for handling context menu events of the DiagramScene.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the DiagramPage class.
 * 
 * @param diagram The UmlDiagram object to be visualized.
 * @param index The model index of the UmlDiagram object in the project tree model.
 * @param parent A parent widget.
 */
DiagramPage::DiagramPage(UmlDiagram* diagram, const QModelIndex& index, QWidget* parent)
: super(parent)
, _diagram(diagram)
, _index(index)
{
   ui.setupUi(this);
   setObjectName("DiagramPage");

   _contextMenu = new QMenu(this);
   _contextMenu->addAction(ui.actionDeleteFromDiagram);
   _contextMenu->addAction(ui.actionDeleteFromModel);
   _contextMenu->addSeparator();
   _contextMenu->addAction(ui.actionEditShape);
   _contextMenu->addSeparator();
   _contextMenu->addAction(ui.actionEditProperties);
   connect(ui.actionDeleteFromDiagram, &QAction::triggered, this, &DiagramPage::deleteFromDiagram);
   connect(ui.actionDeleteFromModel, &QAction::triggered, this, &DiagramPage::deleteFromModel);
   connect(ui.actionEditProperties, &QAction::triggered, this, &DiagramPage::editElementProperties);
   connect(ui.actionEditShape, &QAction::triggered, this, &DiagramPage::editShapeProperties);
   
   _scene = new DiagramScene(_diagram, _contextMenu);
   connect(_scene, &DiagramScene::elementInserted, this, &DiagramPage::updateProject);

   ui.graphicsView->setBackgroundBrush(QPixmap(":/images/background2.png"));
   ui.graphicsView->setScene(_scene);
#ifdef _USE_OPENGL
   ui.graphicsView->setViewport(new QOpenGLWidget());
#endif
}

DiagramPage::~DiagramPage()
{
   delete _scene;
}

//---------------------------------------------------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------------------------------------------------

/** Gets the UmlDiagram object.*/
UmlDiagram* DiagramPage::diagram() const
{
   return _diagram;
}

/** Gets the DiagramScene object. */
DiagramScene* DiagramPage::scene() const
{
   return _scene;
}

/** 
 * Captures an image of the complete diagram scene (including all elements). 
 * 
 * The image can be stored as a file or put onto the system's clipboard for later use. Note that the class does not
 * take ownership of the QImage object returned - it needs to be deleted after use.
 * @returns A QImage object containing the image.
 */
QImage* DiagramPage::captureImage()
{
   QRectF source = _scene->itemsBoundingRect();
   source += QMarginsF(10.0, 10.0, 10.0, 10.0);
   
   QImage*  image = new QImage((int)source.width(), (int)source.height(), QImage::Format_ARGB32);
   QPainter painter(image);
   QBrush   brush(Qt::white);

   painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
   _scene->setBackgroundBrush(brush);
   _scene->render(&painter, QRectF(), source, Qt::KeepAspectRatio);
   return image;
}

//---------------------------------------------------------------------------------------------------------------------
// Slots
//---------------------------------------------------------------------------------------------------------------------

/**
 * Starts insert mode on the contained DiagramScene object.
 * 
 * This slot must be connected to the ToolBoxManager's buttonClicked signal. If called, it passes the class name to the
 * DiagramScene object and then sets its edit mode either to DiagramScene::InsertElement or DiagramScene::LinkElements,
 * depending on the identifier passed in, that is:
 * 
 * - if id < 100: DiagramScene::InsertElement
 * - otherwise: DiagramScene::LinkElements
 * 
 * The DiagramScene object then handles mouse events issued by the user to insert a new element or connect elements 
 * with a link. For further information see functions DiagramScene::setEditMode() and its mouse handling functions 
 * DiagramScene::mousePressEvent(), DiagramScene::mouseMoveEvent() and DiagramScene::mouseReleaseEvent().
 * @param id Identifier of the toolbox button that was selected by the user.
 * @param className Name of the class that shall be created and inserted into the diagram and the project tree.
 */
void DiagramPage::startInsert(int id, QString className)
{
   _scene->setClassName(className);
   _scene->setEditMode(id < 100 ? DiagramScene::InsertElement : DiagramScene::LinkElements);
}

/**
 * Updates the project.
 * 
 * This slot is connected with the elementInserted signal of the DiagramScene object. It emits a projectModified signal
 * to the main window, decorated with the model index of the UmlDiagram object assigned to this object. The main window
 * receives the signal and then updates the project tree model with the element inserted.
 * @param element UmlElement object inserted into the diagram.
 */
void DiagramPage::updateProject(UmlElement* element)
{
   // Issue further but decorated with the model index:
   emit projectModified(_index.parent(), element);
}

/**
 * Opens the properties dialog of the UmlElement object currently selected in the diagram.
 */
void DiagramPage::editElementProperties()
{
   auto items = _scene->selectedItems();
   if (!items.isEmpty())
   {
      // Note: QFrame has an enum named Shape, therefore use global namespace:
      auto* shape = dynamic_cast<::Shape*>(items[0]);
      Q_ASSERT(shape != nullptr);
      
      PropertiesDialog dialog(this, shape->element());
      dialog.exec();
   }
}

/**
 * Opens the properties dialog of the Shape object currently selected in the diagram.
 */
void DiagramPage::editShapeProperties()
{
}

/**
 * Deletes a shape from the diagram.
 */
void DiagramPage::deleteFromDiagram()
{
   auto items = _scene->selectedItems();
   if (!items.isEmpty())
   {
      foreach (QGraphicsItem* item, items)
      {
         auto shape = dynamic_cast<::Shape*>(item);
         Q_ASSERT(shape != nullptr);

         auto edges = shape->diaShape()->edges();
         foreach (DiaEdge* edge, edges)
         {
            auto victim = static_cast<QGraphicsItem*>(edge->itemData());
            _scene->removeItem(victim);
            delete victim;
         }
         _scene->removeItem(item);
         delete item;
      }
   }
}

/**
 * Deletes a shape as well as the UmlElement object associated with it from the project.
 */
void DiagramPage::deleteFromModel()
{
}
