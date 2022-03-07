//---------------------------------------------------------------------------------------------------------------------
// MainWindow.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class MainWindow.
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

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include "UmlProject.h"
#include "ToolBoxManager.h"

#include <QListView>
#include <QProgressBar>
#include <QStringList>
#include <QToolBar>
#include <QTreeView>
#include <QUndoStack>

class ProjectTreeModel;
class StartPage;
class UmlDiagram;

class MainWindow : public QMainWindow
{
   /// @cond
   Q_OBJECT
   typedef QMainWindow super;
   /// @endcond
public: // Constructors
   MainWindow(QWidget* parent = nullptr);
   virtual ~MainWindow();

public: // Properties
   QString fileName() const;
   void setFileName(QString value);
   
   QStringList mruList() const;
   ProjectTreeModel* treeModel() const;

public: // Methods
   void loadProject(QString filename);

protected:
   void closeEvent(QCloseEvent* event) override;

private:
   void connectAppMenu();
   void connectProjectMenu();
   void connectEditMenu();
   void connectElementMenu();
   void connectDiagramMenu();
   void connectWindowsMenu();
   void connectContextMenus();
   
   void createToolBox();

   void writeSettings();
   void readSettings();
   bool maybeSave();
   void destroyProject();
   
   int findPageIndex(UmlDiagram* diagram) const;
   void updateMRUList(QString filename, bool prepend);

public slots:
   //  Menu "App":
   void help();
   void about();
   void preferences();

   // Menu "Project":
   void newProject();
   void openProject();
   bool saveProject();
   bool saveProjectAs();
   void closeProject();

   // Menu "Edit":
   void editUndo();
   void editRedo();
   void moveElementUp();
   void moveElementDown();
   void deleteElement();
   void expandElement();
   void collapseElement();
   void editProperties();

   // Menu "Element":
   void addDiagram();
   void addClass();
   void addInterface();
   void addDatatype();
   void addEnumeration();
   void addPrimitive();
   void addSignal();
   void addPackage();
   void addAttribute();
   void addOperation();

   // Menu "Diagram":
   void openDiagram();
   void closeDiagram(int index);
   void saveImageToClipboard();
   void saveImageToFile();

   // Menu "Tools":
   // Menu "Windows":
   void showStartPage();

   // Contex menus:
   void showTreeContextMenu(const QPoint& pos);

   // Updates
   void enableActions();
   void enableProjectActions();
   void enableEditActions();
   void enableElementActions();
   void enableDiagramActions();
   void updateModel(const QModelIndex& index, UmlElement* element);

private: // Attributes
   ///@cond
   Ui::MainWindowClass ui;
   UmlProject*     _project;
   QString         _fileName;
   QUndoStack      _undoStack;
   QProgressBar*   _progressBar;
   QStringList     _mruList;
   ToolBoxManager* _manager;
   StartPage*      _startPage;
   ///@endcond
};
