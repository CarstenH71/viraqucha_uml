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

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

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
 * Handles a mouse press event.
 *
 * This method is overriden to start a drag and drop operation.
 * @param event Mouse event.
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
 * Handles a mouse move event.
 *
 * This method is overridden to perform a drag and drop operation.
 * @param event Mouse event.
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
