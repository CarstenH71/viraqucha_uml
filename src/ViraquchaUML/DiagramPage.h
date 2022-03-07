//---------------------------------------------------------------------------------------------------------------------
// DiagramPage.h
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class DiagramPage.
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

#include "ui_DiagramPage.h"

#include <QFrame>
#include <QGraphicsScene>
#include <QImage>
#include <QMenu>
#include <QModelIndex>
#include <QPersistentModelIndex>

class UmlDiagram;
class UmlElement;
class DiagramScene;
class ToolBoxManager;

class DiagramPage : public QFrame
{
   ///@cond
   Q_OBJECT
   typedef QFrame super;
   ///@endcond
public: // Constructors
   DiagramPage(UmlDiagram* diagram, const QModelIndex& index, QWidget* parent = nullptr);
   virtual ~DiagramPage();

public: // Properties
   UmlDiagram* diagram() const;
   DiagramScene* scene() const;

public: // Methods
   QImage* captureImage();
   
signals: 
   void projectModified(const QModelIndex& index, UmlElement* element);

public slots:
   void startInsert(int id, QString className);
   void updateProject(UmlElement* element);

private slots:
   void editElementProperties();
   void editShapeProperties();
   void deleteFromDiagram();
   void deleteFromModel();
   
private: // Attributes
   ///@cond
   Ui::DiagramPage       ui;
   UmlDiagram*           _diagram;
   QPersistentModelIndex _index;
   DiagramScene*         _scene;
   QMenu*                _contextMenu;
   ///@endcond
};
