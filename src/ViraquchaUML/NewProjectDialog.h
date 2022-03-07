//---------------------------------------------------------------------------------------------------------------------
// NewProjectDialog.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class NewProjectDialog.
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

#include <QtWidgets/QDialog>
#include "ui_NewProjectDialog.h"

#include <QStringList>

class NewProjectDialog : public QDialog
{
   ///@cond
   Q_OBJECT
   typedef QDialog super;
   ///@endcond
public: // Constructors
   NewProjectDialog(QWidget* parent = nullptr);
   virtual ~NewProjectDialog();

public: // Properties
   QString name() const;
   QString location() const;

public: // Methods
   void accept() override;

private:
   bool checkName();
   bool checkLocation();
   void readSettings();
   void writeSettings();
   void updateLocations();

private slots:
   void browseClicked();

private: // Attributes
   ///@cond
   Ui::NewProjectDialog ui;
   QStringList _locations;
   int         _selected;
   ///@endcond
};
