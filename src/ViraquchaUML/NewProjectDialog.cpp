//---------------------------------------------------------------------------------------------------------------------
// NewProjectDialog.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class NewProjectDialog.
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
#include "NewProjectDialog.h"

#include "Globals.h"
#include "MessageBox.h"

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QRegularExpression>
#include <QSettings>

/**
 * @class NewProjectDialog
 * @brief Implements a dialog for creating new projects.
 * @since 1.0
 * @ingroup GUI
 *
 * The NewProjectDialog class implements a dialog providing users with controls for entering a name and a location
 * (path) for a new project. The dialog also checks name and location entered for validity and issues error messages
 * if they are not valid.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

NewProjectDialog::NewProjectDialog(QWidget* parent)
: super(parent)
, _selected(-1)
{
   ui.setupUi(this);
   connect(ui.browseButton, &QPushButton::clicked, this, &NewProjectDialog::browseClicked);
   readSettings();
   ui.nameEdit->setText(tr("NewUmlProject"));
}

NewProjectDialog::~NewProjectDialog()
{
}

/** Gets the name of the new project. */
QString NewProjectDialog::name() const
{
   return ui.nameEdit->text();
}

/** Gets the location (path) of the new project. */
QString NewProjectDialog::location() const
{
   return ui.locationEdit->currentText();
}

/** Checks file name and location for the new project and issues error messages if necessary. */
void NewProjectDialog::accept()
{
   if (checkName() && checkLocation())
   {
      while (_locations.count() > 10) { _locations.removeLast(); }
      _locations.append(ui.locationEdit->currentText());
      _locations.removeDuplicates();
      _locations.sort();
      _selected = _locations.indexOf(ui.locationEdit->currentText());
      writeSettings();

      setResult(QDialog::Accepted);
      super::accept();
   }
}

/** 
 * Checks the name entered for validity. 
 *
 * @returns True if the name is valid, otherwise false.
 */
bool NewProjectDialog::checkName()
{
   auto text = ui.nameEdit->text();
   if (text.isEmpty())
   {
      MessageBox::warning(
         this,
         tr("The project name is empty."),
         tr("Please enter a name for the new project."));
      return false;
   }
   
   if (text.indexOf(Viraqucha::KFileNamePattern) != -1)
   {
      MessageBox::warning(
         this,
         tr("The project name contains invalid characters."),
         tr("A project name must not contain any of the following characters: \n\\ / : * ? \" < > |.\nPlease re-enter the name."));
      return false;
   }

   return true;
}

/**
 * Checks the location entered for validity.
 *
 * @returns True if the location is valid and does exist, otherwise false.
 */
bool NewProjectDialog::checkLocation()
{
   auto text = ui.locationEdit->currentText();
   auto dir = QDir(text);
   if (text.isEmpty() || !dir.exists())
   {
      MessageBox::warning(
         this, 
         tr("The location is empty or does not exist."),
         tr("Please choose an existing location for the new project."));
      return false;
   }

   if (dir.exists(ui.nameEdit->text()))
   {
      MessageBox::warning(
         this,
         tr("Found another project with same name."),
         tr("There is already a project with same name in the location. Please choose another location or rename the project."));
      return false;
   }
   
   auto info = QFileInfo(text);
   if (!info.isWritable())
   {
      MessageBox::warning(
         this,
         tr("The location is write-protected."),
         tr("Please choose a location which is not write-protected for the new project."));
      return false;
   }

   return true;
}

/** Reads a list of recently used locations from the settings. */
void NewProjectDialog::readSettings()
{
   QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
   _locations = settings.value("lastLocations").toStringList();
   _selected = settings.value("selectedLocation").toInt();
   if (_locations.empty())
   {
      _locations.append(QDir::homePath());
      _selected = 0;
   }

   updateLocations();
}

/** Writes a list of recently used locations to the settings. */
void NewProjectDialog::writeSettings()
{
   QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
   settings.setValue("lastLocations", _locations);
   settings.setValue("selectedLocation", _selected);
}

/** Updates the combo box for locations. */
void NewProjectDialog::updateLocations()
{
   ui.locationEdit->clear();

   QListIterator<QString> iter(_locations);
   while (iter.hasNext())
   { 
      ui.locationEdit->addItem(iter.next());
   }

   ui.locationEdit->setCurrentIndex(_selected);
}

/** Opens a file dialog for selecting the location (path) for the new project. */
void NewProjectDialog::browseClicked()
{
   QString dir = QFileDialog::getExistingDirectory(
      this, 
      tr("Project Location"), 
      location(), 
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
   if (dir != "")
   {
      ui.locationEdit->setCurrentText(dir);
   }
}
