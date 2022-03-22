//---------------------------------------------------------------------------------------------------------------------
// StartPage.h
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class StartPage.
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

#include "ui_StartPage.h"

#include <QPixmap>
#include <QStringList>
#include <QWidget>

class MainWindow;

class StartPage : public QWidget
{
   ///@cond
   Q_OBJECT
   typedef QWidget super;
   ///@endcond
public:
    StartPage(MainWindow* mainWin, QWidget* parent = nullptr);
    virtual ~StartPage();

private slots:
   void openFromRecentProjects(QListWidgetItem* item);
   void openUsingFileDialog();
   void createFromTemplate(QListWidgetItem* item);
   void createUsingNewDialog();
   void openLinkInBrowser(const QString& link);
   
private:
   void updateRecentProjects();
   
private:
   ///@cond
    Ui::StartPage ui;
    MainWindow* _mainWin;
    ///@endcond
};
