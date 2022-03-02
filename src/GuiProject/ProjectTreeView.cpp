//---------------------------------------------------------------------------------------------------------------------
// ProjectTreeView.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class ProjectTreeView.
// Compiles with: MSVC 15.2 (2017) or newer, GNU GCC 5.1 or newer
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This library is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
// * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
// * option) any later version.                                                                                      *
// *                                                                                                                 *
// * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
// * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
// * for more details.                                                                                               *
// *                                                                                                                 *
// * You should have received a copy of the GNU General Public License along with this library; if not, see          *
// * http://www.gnu.org/licenses/gpl                                                                                 *
// *                                                                                                                 *
// *******************************************************************************************************************
//
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#include "ProjectTreeView.h"
#include "ProjectTreeModel.h"

#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

/**
 * @class ProjectTreeView
 * @brief Implements the project tree view.
 * @since 0.1.0
 * @ingroup GuiProject
 *
 * The ProjectTreeView class implements the project tree view of ViraquchaUML. The project tree view visualizes the
 * UML project and all its UML elements in a tree and provides functions for editing and managing the UML elements.
 *
 * The ProjectTreeView class is created and initialized by the main window on startup of the program. See MainWindow
 * for additional information.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the ProjectTreeView class.
 * @param parent Parent widget
 */
ProjectTreeView::ProjectTreeView(QWidget* parent)
: super(parent)
{
}

ProjectTreeView::~ProjectTreeView()
{
}

//---------------------------------------------------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Handles mouse press events.
 *
 * This method is overriden to start a drag and drop operation.
 * @param event Mouse event to be handled
 */
void ProjectTreeView::mousePressEvent(QMouseEvent* event)
{
   if (event->button() == Qt::LeftButton)
   {
      _startPos = event->pos();
   }

   super::mousePressEvent(event);
}

/**
 * Handles mouse move events.
 *
 * This method is overridden to perform a drag and drop operation.
 * @param event Mouse event to be handled
 */
void ProjectTreeView::mouseMoveEvent(QMouseEvent* event)
{
   if (event->buttons() & Qt::LeftButton)
   {
      int dist = (event->pos() - _startPos).manhattanLength();
      if (dist >= QApplication::startDragDistance())
      {
         // Perform Drag
         auto* treemodel = dynamic_cast<ProjectTreeModel*>(model());
         auto* element = treemodel->getElement(currentIndex());
         if (element != nullptr)
         {
            auto* data = new QMimeData();
            data->setData("application/uuid", element->identifier().toByteArray());

            auto* drag = new QDrag(this);
            drag->setMimeData(data);
            //drag->setPixmap(QPixmap(":/images/dragdrop.png"));
            drag->exec(Qt::LinkAction);
         }
      }
   }

   super::mouseMoveEvent(event);
}
