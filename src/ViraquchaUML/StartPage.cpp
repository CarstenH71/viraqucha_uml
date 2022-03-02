//---------------------------------------------------------------------------------------------------------------------
// StartPage.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class StartPage.
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
#include "StartPage.h"
#include "MainWindow.h"

/**
 * @class StartPage
 * @brief Implements a start page for ViraquchaUML
 * @since 0.1.0
 * @ingroup ViraquchaUML
 * 
 * The start page is shown on start up and provides controls for opening existing projects, creating new projects or
 * accessing online help.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------
StartPage::StartPage(MainWindow* mainWin, QWidget* parent)
: super(parent)
, _mainWin(mainWin)
{
   setObjectName("StartPage");

   ui.setupUi(this);
   connect(ui.recentProjects, &QListWidget::itemDoubleClicked, this, &StartPage::openFromRecentProjects);
   connect(ui.openProject, &QPushButton::clicked, this, &StartPage::openUsingFileDialog);
   connect(ui.projectTemplates, &QListWidget::itemDoubleClicked, this, &StartPage::createFromTemplate);
   connect(ui.newProject, &QPushButton::clicked, this, &StartPage::createUsingNewDialog);
   
   updateRecentProjects();
}

StartPage::~StartPage()
{
}

//---------------------------------------------------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------------------------------------------------

void StartPage::openFromRecentProjects(QListWidgetItem* item)
{
   Q_ASSERT(item != nullptr);
   _mainWin->loadProject(item->text());
   updateRecentProjects();
}

void StartPage::openUsingFileDialog()
{
   _mainWin->openProject();
   updateRecentProjects();
}

void StartPage::createFromTemplate(QListWidgetItem* item)
{
   Q_ASSERT(item != nullptr);
   // TODO: Create templates...
}

void StartPage::createUsingNewDialog()
{
   _mainWin->newProject();
}

void StartPage::updateRecentProjects()
{
   ui.recentProjects->clear();
   ui.recentProjects->insertItems(0, _mainWin->mruList());
}
