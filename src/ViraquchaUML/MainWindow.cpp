//---------------------------------------------------------------------------------------------------------------------
// MainWindow.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class MainWindow, the main window of the ViraquchaUML application.
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
#include "MainWindow.h"

#include "DiagramPage.h"
#include "DiagramScene.h"
#include "StartPage.h"
#include "MessageBox.h"
#include "NewDiagramDialog.h"
#include "NewProjectDialog.h"
#include "ProjectTreeModel.h"
#include "PropertiesDialog.h"
#include "Viraqucha.h"

#include "UmlDiagram.h"
#include "UmlClass.h"
#include "UmlModel.h"
#include "UmlRoot.h"

#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QScopedPointer>
#include <QSettings>

/**
 * @class MainWindow
 * @brief Implements the main window of ViraquchaUML
 * @since 0.1.0
 * @ingroup ViraquchaUML
 *
 * Like many modern software development tools, the main window of ViraquchaUML is divided into a set of docks and
 * widgets:
 * - the project tree dock on the left side of the window,
 * - the toolbox and properties dock on the right side of the window,
 * - the central widget where the diagrams are shown and
 * - an output dock (not yet implemented) at the bottom of the window.
 * 
 * The MainWindow class manages all these docks as well as the main menu and the status bar at the bottom of the
 * window. It also creates the main menu commands, the toolbox buttons and the project tree model.
 */

//---------------------------------------------------------------------------------------------------------------------
// Construction
//---------------------------------------------------------------------------------------------------------------------

/** 
 * Initializes a new object of the MainWindow class. 
 * 
 * @param parent Parent window of the main window.
 */
MainWindow::MainWindow(QWidget *parent)
: super(parent)
, _project(nullptr)
, _startPage(nullptr)
{
   ui.setupUi(this);

   _progressBar = new QProgressBar();
   _progressBar->setRange(0, 100);
   statusBar()->addPermanentWidget(_progressBar);

   readSettings();
   connectAppMenu();
   connectProjectMenu();
   connectEditMenu();
   connectElementMenu();
   connectDiagramMenu();
   connectWindowsMenu();
   connectContextMenus();

   createToolBox();
   connect(ui.centralWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeDiagram);
   enableActions();
}

MainWindow::~MainWindow()
{
   destroyProject();
   delete _manager;
   delete _progressBar;
}

//---------------------------------------------------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------------------------------------------------

/** Gets the name of the currently opened project file. */
QString MainWindow::fileName() const
{
   return _fileName;
}

/** Sets the name of the currently opened project file. */
void MainWindow::setFileName(QString value)
{
   _fileName = value;
   if (_fileName.isEmpty())
   {
      setWindowTitle(Viraqucha::KProgramName);
   }
   else
   {
      setWindowTitle(QString("%1[*] - %2").arg(_fileName).arg(Viraqucha::KProgramName));
   }
}

/** Gets the list of most recently used projects. */
QStringList MainWindow::mruList() const
{
   return _mruList;
}

/** Gets the ProjectTreeModel instance. */
ProjectTreeModel* MainWindow::treeModel() const
{
   return dynamic_cast<ProjectTreeModel*>(ui.projTreeView->model());
}

/** 
 * Loads a project. 
 *
 * This function is public to allow loading of project files from the command line. It creates a new UmlProject 
 * instance and then calls its load() function. If loading succeeds, it creates a new ProjectTreeModel object
 * and sets it to the project tree view. If loading fails, it shows an error message instead.
 * @param filename File name and path of the project to be loaded.
 */
void MainWindow::loadProject(QString filename)
{
   // Pre: File name must not be empty.
   if (filename.isEmpty()) return;
   // Pre: File must not be loaded already.
   if (!_fileName.isEmpty() && _fileName == filename) return;
   
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   destroyProject();
   _project = new UmlProject();

   _progressBar->reset();
   connect(_project, &UmlProject::updateProgress, _progressBar, &QProgressBar::setValue);

   bool success = _project->load(filename);
   QApplication::restoreOverrideCursor();
   
   if (success)
   {
      ui.projTreeView->setModel(new ProjectTreeModel(_project->root()));
      setFileName(filename);
      setWindowModified(false);
   }
   else
   {
      MessageBox::warning(this, Viraqucha::KProgramName, _project->errorString());
      
      _project->dispose();
      delete _project;
      _project = nullptr;
   }
   
   updateMRUList(filename, success);
   _progressBar->reset();
   enableActions();
}

/** Handles the close event of the base class. */
void MainWindow::closeEvent(QCloseEvent* event)
{
   if (maybeSave())
   {
      writeSettings();
      event->accept();
   }
   else
   {
      event->ignore();
   }
}

/** Connects the application menu with the main window. */
void MainWindow::connectAppMenu()
{
   connect(ui.actionAbout, &QAction::triggered, this, &MainWindow::about);
}

/** Connects the project menu with the main window command handlers. */
void MainWindow::connectProjectMenu()
{
   connect(ui.actionNew, &QAction::triggered, this, &MainWindow::newProject);
   connect(ui.actionOpen, &QAction::triggered, this, &MainWindow::openProject);
   connect(ui.actionClose, &QAction::triggered, this, &MainWindow::closeProject);
   connect(ui.actionSave, &QAction::triggered, this, &MainWindow::saveProject);
   connect(ui.actionSaveAs, &QAction::triggered, this, &MainWindow::saveProjectAs);
   connect(ui.menuProject, &QMenu::aboutToShow, this, &MainWindow::enableProjectActions);
}

/** Connects the edit menu with the main window command handlers. */
void MainWindow::connectEditMenu()
{
   connect(ui.actionUndo, &QAction::triggered, this, &MainWindow::editUndo);
   connect(ui.actionRedo, &QAction::triggered, this, &MainWindow::editRedo);
   connect(ui.actionMoveDown, &QAction::triggered, this, &MainWindow::moveElementDown);
   connect(ui.actionMoveUp, &QAction::triggered, this, &MainWindow::moveElementUp);
   connect(ui.actionDelete, &QAction::triggered, this, &MainWindow::deleteElement);
   connect(ui.actionProperties, &QAction::triggered, this, &MainWindow::editProperties);
   connect(ui.actionExpand, &QAction::triggered, this, &MainWindow::expandElement);
   connect(ui.actionCollapse, &QAction::triggered, this, &MainWindow::collapseElement);
   connect(ui.menuEdit, &QMenu::aboutToShow, this, &MainWindow::enableEditActions);
}

/** Connects the element menu with the main window command handlers. */
void MainWindow::connectElementMenu()
{
   connect(ui.actionAddDiagram, &QAction::triggered, this, &MainWindow::addDiagram);
   connect(ui.actionAddClass, &QAction::triggered, this, &MainWindow::addClass);
   connect(ui.actionAddInterface, &QAction::triggered, this, &MainWindow::addInterface);
   connect(ui.actionAddDatatype, &QAction::triggered, this, &MainWindow::addDatatype);
   connect(ui.actionAddEnumeration, &QAction::triggered, this, &MainWindow::addEnumeration);
   connect(ui.actionAddPrimitive, &QAction::triggered, this, &MainWindow::addPrimitive);
   connect(ui.actionAddSignal, &QAction::triggered, this, &MainWindow::addSignal);
   connect(ui.actionAddPackage, &QAction::triggered, this, &MainWindow::addPackage);
   connect(ui.actionAddAttribute, &QAction::triggered, this, &MainWindow::addAttribute);
   connect(ui.actionAddOperation, &QAction::triggered, this, &MainWindow::addOperation);
   connect(ui.menuElement, &QMenu::aboutToShow, this, &MainWindow::enableElementActions);
}

/** Connects the diagram menu with the main window command handlers. */
void MainWindow::connectDiagramMenu()
{
   connect(ui.actionOpenDiagram, &QAction::triggered, this, &MainWindow::openDiagram);
   connect(ui.actionSaveToClipboard, &QAction::triggered, this, &MainWindow::saveImageToClipboard);
   connect(ui.actionSaveToFile, &QAction::triggered, this, &MainWindow::saveImageToFile);
   connect(ui.menuDiagram, &QMenu::aboutToShow, this, &MainWindow::enableDiagramActions);
}

/** Connects the windows menu with the main window command handlers. */
void MainWindow::connectWindowsMenu()
{
   connect(ui.actionStartPage, &QAction::triggered, this, &MainWindow::showStartPage);
}

/** Connects the tree's context menu with the main window command handlers. */
void MainWindow::connectContextMenus()
{
   connect(ui.projTreeView, &QTreeView::customContextMenuRequested, this, &MainWindow::showTreeContextMenu);
}

/** 
 * Creates the tool box. 
 * 
 * The tool box - by default located at the right side of the main window - provides buttons creating new elements in
 * the diagrams of ViraquchaUML when clicked. This function is called by the constructor of the MainWindow class and
 * creates each of these buttons using the ToolBoxManager class.<br/>
 * Each button gets an identifier, a name and an icon: Identifier for node elements (i.e. Class, Package etc.) are in
 * the range [1..99] whereas identifier for edge elements (Links) are in the range [100..*]. Names must be marked as 
 * translatable (use tr()) and the icon must be located in the resource file of ViraquchaUML.
 */
void MainWindow::createToolBox()
{
   int id = 1;
   
   _manager = new ToolBoxManager(this, ui.toolBox);
   _manager->addTab(tr("General"));
   _manager->addButton(id++, tr("Comment"), "UmlComment");
   _manager->addButton(id++, tr("Package"), "UmlPackage");

   _manager->addTab(tr("Classifier"));
   _manager->addButton(id++, tr("Data Type"),"UmlDatatype");
   _manager->addButton(id++, tr("Class"), "UmlClass");
   _manager->addButton(id++, tr("Enumeration"), "UmlEnumeration");
   _manager->addButton(id++, tr("Interface"), "UmlInterface");
   _manager->addButton(id++, tr("Primitive"), "UmlPrimitiveType");
   _manager->addButton(id++, tr("Signal"), "UmlSignal");
   
   id = 100; // Identifier starting with 100 are reserved for links!
   _manager->addTab(tr("Relationship"));
   _manager->addButton(id++, tr("Abstraction"), "UmlDependency::Abstraction");
   _manager->addButton(id++, tr("Aggregation"), "UmlAssociation::Aggregation");
   _manager->addButton(id++, tr("Association"), "UmlAssociation");
   _manager->addButton(id++, tr("Composition"), "UmlAssociation::Composition");

   _manager->addButton(id++, tr("Dependency"), "UmlDependency");
   _manager->addButton(id++, tr("Generalization"), "UmlGeneralization");
   _manager->addButton(id++, tr("Link"), "UmlLink");
   _manager->addButton(id++, tr("Nesting"), "UmlNesting");
   _manager->addButton(id++, tr("Realization"), "UmlRealization");
   _manager->addButton(id++, tr("Template Binding"), "UmlTemplateBinding");

   _manager->addButton(id++, tr("Usage"), "UmlDependency::Usage");
}

/** 
 * Shows the start page of the program. 
 * 
 * The start page provides fast access to most recently used projects, project templates as well as the online help of
 * the program. It can be shown or hidden by menu command.
 */
void MainWindow::showStartPage()
{
   if (ui.actionStartPage->isChecked())
   {
      _startPage = new StartPage(this, ui.centralWidget);
      ui.centralWidget->insertTab(0, _startPage, tr("Start Page"));
   }
   else if (_startPage != nullptr)
   {
      ui.centralWidget->removeTab(ui.centralWidget->indexOf(_startPage));
      delete _startPage;
      _startPage = nullptr;
   }
}

/** Writes window positions and sizes to a settings file. */
void MainWindow::writeSettings()
{
   QSettings settings;
   settings.setValue("application/geometry", saveGeometry());
   settings.setValue("application/startPage", ui.actionStartPage->isChecked());
   settings.setValue("projects/recent", _mruList);
}

/** Reads window positions and sizes from a settings file. */
void MainWindow::readSettings()
{
   QSettings settings;
   
   // Restore geometry of the main window:
   const QByteArray geometry = settings.value("application/geometry", QByteArray()).toByteArray();
   if (geometry.isEmpty())
   {
      const QRect rect = QApplication::desktop()->availableGeometry(this);
      resize(rect.width() / 3, rect.height() / 2);
      move((rect.width() - width()) / 2, (rect.height() - height()) / 2);
   }
   else
   {
      restoreGeometry(geometry);
   }

   // Restore most recently used projects list:
   _mruList = settings.value("projects/recent").toStringList();

   // Restore start page if requested:
   ui.actionStartPage->setChecked(settings.value("application/startPage", true).toBool());
   showStartPage();   
}

/** 
 * Checks whether the project is modified and must be saved. 
 * @returns true, if the project is modified; false otherwise.
 */
bool MainWindow::maybeSave()
{
   if (_project == nullptr || !_project->isModified()) return true;
   
   auto result = QMessageBox::warning(
      this, 
      QCoreApplication::applicationName(), 
      tr("The project has been modified. Would you like to save the changes?"), 
      QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard);
   switch (result)
   {
      case QMessageBox::Save:
         return saveProject();
      case QMessageBox::Cancel:
         return false;
      default:
         break;
   }
   return true;
}

/** Destroys the project and removes all diagram tabs from the main window. */
void MainWindow::destroyProject()
{
   if (_project != nullptr)
   {
      ui.projTreeView->setModel(nullptr);
      setFileName("");
      
      // Close and delete all diagram tabs first:
      QList<QWidget*> tabs;
      for (int index = 0; index < ui.centralWidget->count(); ++index)
      {
         auto* tab = ui.centralWidget->widget(index);
         if (tab->objectName() == "DiagramPage") tabs.append(tab);
      }
      
      while (tabs.count() > 0)
      {
         ui.centralWidget->removeTab(ui.centralWidget->indexOf(tabs.first()));
         delete tabs.first();
         tabs.removeFirst();
      }

      // Now it is safe to delete the project itself:
      _project->dispose();
      delete _project;
      _project = nullptr;
   }
}

/** 
 * Finds the index of the DiagramPage keeping a given UmlDiagram object. 
 * 
 * @param diagram UmlDiagram object to be found.
 * @returns The index or -1 if nothing was found.
 */
int MainWindow::findPageIndex(UmlDiagram* diagram) const
{
   int count = ui.centralWidget->count();
   for (int index = 0; index < count; ++index)
   {
      auto* page = dynamic_cast<DiagramPage*>(ui.centralWidget->widget(index));
      if (page != nullptr && page->diagram() == diagram)
      {
         return index;
      }
   }
   
   return -1;
}

/** 
 * Updates the list of most recently used files. 
 * 
 * @param filename File name to be added to the list.
 * @param prepend True, if the file name shall be prepended to the list; otherwise false.
 */
void MainWindow::updateMRUList(QString filename, bool prepend)
{
   _mruList.removeAll(filename);
   if (prepend)
   {
      _mruList.prepend(filename);
   }
}

//---------------------------------------------------------------------------------------------------------------------
// Slots
//---------------------------------------------------------------------------------------------------------------------
/** Opens online help for the application. */
void MainWindow::help()
{}

/** Opens the application's About dialog. */
void MainWindow::about()
{
   QMessageBox::about(this, tr("About ViraquchaUML"), tr("ViraquchaUML is an open source UML tool written in C++ using Qt."));
}

/** Opens the preferences dialog. */
void MainWindow::preferences()
{}

/** Creates a new project using a default template. */
void MainWindow::newProject()
{
   QScopedPointer<NewProjectDialog> dialog(new NewProjectDialog(this));
   if (dialog->exec() == QDialog::Accepted)
   {
      destroyProject();

      _project = new UmlProject();
      _project->create(dialog->location(), dialog->name());
      setFileName(dialog->location() + "/" + dialog->name() + "/" + dialog->name() + ".uprj");
      
      auto* model = new UmlModel();
      model->setName(tr("System"));
      _project->insert(model);
      _project->root()->insert(0, model);

      auto* pkg = new UmlPackage();
      pkg->setName(tr("Classes"));
      _project->insert(pkg);
      model->insert(0, pkg);

      auto* dia = new UmlDiagram();
      dia->setName(tr("Classes"));
      _project->insert(dia);
      pkg->insert(0, dia);

      ui.projTreeView->setModel(new ProjectTreeModel(_project->root()));
      _project->isModified(true);
   }
}

/** Opens a file dialog and then loads the project selected in the dialog. */
void MainWindow::openProject()
{
   if (maybeSave()) 
   {
      loadProject(QFileDialog::getOpenFileName(
         this, 
         tr("Open Project"), 
         QString(), 
         tr("Project files (*.uprj);;All files (*.*)")));
   }
}

/** Saves the currently opened project. */
bool MainWindow::saveProject()
{
   if (_project != nullptr)
   {
      _project->save(_fileName);
      setWindowModified(false);
      updateMRUList(_fileName, true);
   }
   
   return true;
}

/** Saves the currently opened project under a new name to hard disk. */
bool MainWindow::saveProjectAs()
{
   return false;
}

/** Closes the currently opened project. */
void MainWindow::closeProject()
{
   if (maybeSave())
   {
      destroyProject();
      enableActions();
   }
}

/** Handles the Edit/Undo command. */
void MainWindow::editUndo()
{
   _undoStack.undo();
}

/** Handles the Edit/Redo command. */
void MainWindow::editRedo()
{
   _undoStack.redo();
}

/** Moves a selected element in the project tree up by one element. */
void MainWindow::moveElementUp()
{
   treeModel()->moveRow(ui.projTreeView->currentIndex(), false);
   setWindowModified(true);
}

/** Moves a selected element in the project tree down by one element. */
void MainWindow::moveElementDown()
{
   treeModel()->moveRow(ui.projTreeView->currentIndex(), true);
   setWindowModified(true);
}

/** Deletes a selected element from the data model. */
void MainWindow::deleteElement()
{
   auto index = ui.projTreeView->currentIndex();
   if (index.isValid())
   {
      auto* diagram = dynamic_cast<UmlDiagram*>(treeModel()->getElement(index));
      if (diagram != nullptr && diagram->isOpen())
      {
         closeDiagram(findPageIndex(diagram));
      }
      
      treeModel()->removeRow(index);
      setWindowModified(true);
   }
}

/** Expands a selected element in the project tree. */
void MainWindow::expandElement()
{
   ui.projTreeView->setExpanded(ui.projTreeView->currentIndex(), true);
}

/** Collapses a selected element in the project tree. */
void MainWindow::collapseElement()
{
   ui.projTreeView->setExpanded(ui.projTreeView->currentIndex(), false);
}

/** Opens the properties dialog for a selected element. */
void MainWindow::editProperties()
{
   auto index = ui.projTreeView->currentIndex();
   if (index.isValid())
   {
      QScopedPointer<PropertiesDialog> dialog(new PropertiesDialog(this, *treeModel(), treeModel()->getElement(index)));
      if (dialog->exec() == QDialog::Accepted)
      {
         _project->isModified(true);
         setWindowModified(true);
      }
   }
}

/** Adds a new Diagram element to the project tree model. */
void MainWindow::addDiagram()
{
   QScopedPointer<NewDiagramDialog> dialog(new NewDiagramDialog(this));
   if (dialog->exec() == QDialog::Accepted)
   {
      auto  index = ui.projTreeView->currentIndex();
      auto* model = dynamic_cast<ProjectTreeModel*>(ui.projTreeView->model());
      auto* owner = model->getComposite(index);
      Q_ASSERT(owner != nullptr);

      auto* diagram = dynamic_cast<UmlDiagram*>(_project->insertNew(UmlDiagram::staticMetaObject.className()));
      diagram->setKind(dialog->kind());

      NameBuilder builder(owner);
      builder.buildFor(diagram, tr("Diagram"));

      model->insertRow(index, diagram);
      setWindowModified(true);
   }
}

/** Adds a new Class element to the project tree model. */
void MainWindow::addClass()
{
   treeModel()->insertRow(ui.projTreeView->currentIndex(), UmlClass::staticMetaObject.className(), tr("Class"));
   setWindowModified(true);
}

/** Adds a new Interface element to the project tree model. */
void MainWindow::addInterface()
{
   treeModel()->insertRow(ui.projTreeView->currentIndex(), UmlInterface::staticMetaObject.className(), tr("Interface"));
   setWindowModified(true);
}

/** Adds a new Datatype element to the project tree model. */
void MainWindow::addDatatype()
{
   treeModel()->insertRow(ui.projTreeView->currentIndex(), UmlDatatype::staticMetaObject.className(), tr("DataType"));
   setWindowModified(true);
}

/** Adds a new Enumeration element to the project tree model. */
void MainWindow::addEnumeration()
{
   treeModel()->insertRow(ui.projTreeView->currentIndex(), UmlEnumeration::staticMetaObject.className(), tr("Enumeration"));
   setWindowModified(true);
}

/** Adds a new Primitive Type element to the project tree model. */
void MainWindow::addPrimitive()
{
   treeModel()->insertRow(ui.projTreeView->currentIndex(), UmlPrimitiveType::staticMetaObject.className(), tr("Primitive"));
   setWindowModified(true);
}

/** Adds a new Signal element to the project tree model. */
void MainWindow::addSignal()
{
   treeModel()->insertRow(ui.projTreeView->currentIndex(), UmlSignal::staticMetaObject.className(), tr("Signal"));
   setWindowModified(true);
}

/** Adds a new Package element to the project tree model. */
void MainWindow::addPackage()
{
   treeModel()->insertRow(ui.projTreeView->currentIndex(), UmlPackage::staticMetaObject.className(), tr("Package"));
   setWindowModified(true);
}

/** Adds a new Attribute element to the project tree model. */
void MainWindow::addAttribute()
{
   treeModel()->insertRow(ui.projTreeView->currentIndex(), UmlAttribute::staticMetaObject.className(), tr("attribute"));
   setWindowModified(true);
}

/** Adds a new Operation element to the project tree model. */
void MainWindow::addOperation()
{
   treeModel()->insertRow(ui.projTreeView->currentIndex(), UmlOperation::staticMetaObject.className(), tr("operation"));
   setWindowModified(true);
}

/** 
 * Opens a diagram view for a selected UmlDiagram element in the project tree. 
 *
 * If the diagram view already exists, it is selected instead of created a second time. The name of the tab is set to
 * the name of the UmlDiagram instance.
 */
void MainWindow::openDiagram()
{
   auto  modelIndex = ui.projTreeView->currentIndex();
   auto* diagram = dynamic_cast<UmlDiagram*>(treeModel()->getElement(modelIndex));
   if (diagram != nullptr)
   {
      int pageIndex = findPageIndex(diagram);
      if (pageIndex > -1)
      {
         ui.centralWidget->setCurrentIndex(pageIndex);
         return;
      }

      auto* page = new DiagramPage(diagram, modelIndex, ui.centralWidget);
      connect(_manager, &ToolBoxManager::buttonClicked, page, &DiagramPage::startInsert);
      connect(page, &DiagramPage::projectModified, this, &MainWindow::updateModel);
      connect(page->scene(), &DiagramScene::insertAborted, _manager, &ToolBoxManager::resetButton);

      ui.centralWidget->addTab(page, diagram->name());
      ui.centralWidget->setCurrentIndex(ui.centralWidget->count() - 1);
   }
}

/** 
 * Closes a diagram view and removes it from the central widget. 
 * 
 * @param index Index of the diagram view in the central widget.
 */
void MainWindow::closeDiagram(int index)
{
   if (index > -1)
   {
      auto* widget = ui.centralWidget->widget(index);
      if (widget->objectName() == "StartPage")
      {
         ui.actionStartPage->setChecked(false);
         showStartPage();
         return;
      }
      
      ui.centralWidget->removeTab(index);
      delete widget;
   }
}

/**
 * Saves an image of the current diagram to the clipboard.
 */
void MainWindow::saveImageToClipboard()
{
   auto* widget = ui.centralWidget->currentWidget();
   if (widget->objectName() == "DiagramPage")
   {
      auto* page = dynamic_cast<DiagramPage*>(widget);
      Q_ASSERT(page != nullptr);
      
      auto* image = page->captureImage();
      Q_ASSERT(image != nullptr);
      QGuiApplication::clipboard()->clear();
      QGuiApplication::clipboard()->setImage(*image);
      delete image;
      
      MessageBox::info(this, Viraqucha::KProgramName, tr("The image was saved to the clipboard."));
   }
}

/**
 * Saves an image of the current diagram to a file.
 */
void MainWindow::saveImageToFile()
{
   QStringList fileFilter = 
   { 
      "BMP - Windows Bitmap (.bmp)(*.bmp)",
      "JPG - Joint Photographic Experts Group (.jpg)(*.jpg)",
      "PNG - Portable Network Graphic (.png)(*.png)",
      "XBM - X11 Bitmap (.xbm)(*.xbm)"
   };

   auto* widget = ui.centralWidget->currentWidget();
   if (widget->objectName() == "DiagramPage")
   {
      auto* page = dynamic_cast<DiagramPage*>(widget);
      Q_ASSERT(page != nullptr);

      auto filename = QFileDialog::getSaveFileName(
         this, 
         tr("Save Image"), 
         QString(), 
         fileFilter.join(";;"));
      if (filename.isEmpty()) return;

      auto* image = page->captureImage();
      Q_ASSERT(image != nullptr);
      if (!image->save(filename))
      {
         MessageBox::error(this, Viraqucha::KProgramName, tr("The image could not be saved."));
      }
      
      delete image;
   }
}

/** Shows the context menu of the project tree view. */
void MainWindow::showTreeContextMenu(const QPoint& pos)
{
   if (_project != nullptr)
   {
      auto index = ui.projTreeView->currentIndex();
      if (index.isValid())
      {
         auto* elem = treeModel()->getElement(index);

         QMenu menu(ui.projTreeView);
         if (elem->className() == UmlDiagram::staticMetaObject.className())
         {
            menu.addAction(ui.actionOpenDiagram);
            menu.addSeparator();
         }
         menu.addAction(ui.actionCut);
         menu.addAction(ui.actionCopy);
         menu.addAction(ui.actionPaste);
         menu.addSeparator();
         menu.addAction(ui.actionMoveUp);
         menu.addAction(ui.actionMoveDown);
         menu.addSeparator();
         menu.addAction(ui.actionDelete);
         if (elem->className() == UmlModel::staticMetaObject.className())
         { 
            menu.addSeparator();
            menu.addAction(ui.actionAddPackage);
         }
         else if (elem->className() == UmlPackage::staticMetaObject.className())
         {
            menu.addSeparator();
            menu.addAction(ui.actionAddDiagram);
            QMenu& submenu = *menu.addMenu(tr("Add Element"));
            submenu.addAction(ui.actionAddClass);
            submenu.addAction(ui.actionAddDatatype);
            submenu.addAction(ui.actionAddEnumeration);
            submenu.addAction(ui.actionAddInterface);
            submenu.addAction(ui.actionAddPrimitive);
            submenu.addAction(ui.actionAddSignal);
            menu.addAction(ui.actionAddPackage);
         }
         else if (dynamic_cast<UmlClassifier*>(elem) != nullptr)
         {
            menu.addSeparator();
            menu.addAction(ui.actionAddDiagram);
            QMenu& submenu = *menu.addMenu(tr("Add Feature"));
            submenu.addAction(ui.actionAddAttribute);
            submenu.addAction(ui.actionAddOperation);
         }
         menu.addSeparator();
         menu.addAction(ui.actionProperties);

         enableDiagramActions();
         enableEditActions();
         enableElementActions();
         menu.exec(ui.projTreeView->mapToGlobal(pos));
      }
   }
}

/** Enables or disables all actions of the program. */
void MainWindow::enableActions()
{
   enableProjectActions();
   enableEditActions();
   enableElementActions();
   enableDiagramActions();
}

/** Enables or disables actions of the Projects menu. */
void MainWindow::enableProjectActions()
{
   bool hasProject = _project != nullptr;
   ui.actionSave->setEnabled(hasProject);
   ui.actionSaveAs->setEnabled(hasProject);
   ui.actionClose->setEnabled(hasProject);
   ui.actionExport->setEnabled(hasProject);
   ui.actionSettings->setEnabled(hasProject);
}

/** Enables or disables actions of the Edit menu. */
void MainWindow::enableEditActions()
{
   auto index = ui.projTreeView->currentIndex();
   if (index.isValid())
   {
      ui.actionCut->setEnabled(true);
      ui.actionCopy->setEnabled(true);
      ui.actionPaste->setEnabled(true);
      ui.actionDelete->setEnabled(true);
      ui.actionProperties->setEnabled(true);
   }
   else
   {
      ui.actionCut->setEnabled(false);
      ui.actionCopy->setEnabled(false);
      ui.actionPaste->setEnabled(false);
      ui.actionDelete->setEnabled(false);
      ui.actionProperties->setEnabled(false);
   }
}

/** Enables or disables actions of the Element menu. */
void MainWindow::enableElementActions()
{
   auto index = ui.projTreeView->currentIndex();
   if (index.isValid())
   {
      auto* elem = treeModel()->getElement(index);
      bool isClassifier = dynamic_cast<UmlClassifier*>(elem) != nullptr;
      bool isModel = elem->className() == UmlModel::staticMetaObject.className();
      bool isPackage = elem->className() == UmlPackage::staticMetaObject.className();

      ui.actionAddDiagram->setEnabled(isClassifier || isPackage);
      ui.actionAddClass->setEnabled(isPackage);
      ui.actionAddDatatype->setEnabled(isPackage);
      ui.actionAddEnumeration->setEnabled(isPackage);
      ui.actionAddInterface->setEnabled(isPackage);
      ui.actionAddPrimitive->setEnabled(isPackage);
      ui.actionAddSignal->setEnabled(isPackage);
      ui.actionAddAttribute->setEnabled(isClassifier);
      ui.actionAddOperation->setEnabled(isClassifier);
      ui.actionAddModel->setEnabled(true);
      ui.actionAddPackage->setEnabled(isModel || isPackage);
   }
   else
   {
      ui.actionAddDiagram->setEnabled(false);
      ui.actionAddClass->setEnabled(false);
      ui.actionAddDatatype->setEnabled(false);
      ui.actionAddEnumeration->setEnabled(false);
      ui.actionAddInterface->setEnabled(false);
      ui.actionAddPrimitive->setEnabled(false);
      ui.actionAddSignal->setEnabled(false);
      ui.actionAddAttribute->setEnabled(false);
      ui.actionAddOperation->setEnabled(false);
      ui.actionAddModel->setEnabled(false);
      ui.actionAddPackage->setEnabled(false);
   }
}

/** Enables or disables actions of the Diagram menu. */
void MainWindow::enableDiagramActions()
{
   auto index = ui.projTreeView->currentIndex();
   if (index.isValid())
   {
      auto* elem = treeModel()->getElement(index);
      bool isDiagram = elem->className() == UmlDiagram::staticMetaObject.className();
      ui.actionOpenDiagram->setEnabled(isDiagram);
      ui.actionAlign->setEnabled(isDiagram);
      ui.actionZoomIn->setEnabled(isDiagram);
      ui.actionZoomOut->setEnabled(isDiagram);
      ui.actionSaveToFile->setEnabled(isDiagram);
      ui.actionSaveToClipboard->setEnabled(isDiagram);
   }
   else
   {
      ui.actionOpenDiagram->setEnabled(false);
      ui.actionAlign->setEnabled(false);
      ui.actionZoomIn->setEnabled(false);
      ui.actionZoomOut->setEnabled(false);
      ui.actionSaveToFile->setEnabled(false);
      ui.actionSaveToClipboard->setEnabled(false);
   }
}

/** Updates the project tree model. */
void MainWindow::updateModel(const QModelIndex& index, UmlElement* element)
{
   if (index.isValid() && element != nullptr)
   {
      treeModel()->insertRow(index, element);
      _manager->resetButton();
      setWindowModified(true);
   }
}
