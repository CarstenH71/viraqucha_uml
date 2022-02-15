//---------------------------------------------------------------------------------------------------------------------
// PropertiesDialog.h
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class PropertiesDialog.
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

#include "ui_PropertiesDialog.h"
#include "UmlCommon.h"
#include "UmlClassifiers.h"

#include <QDialog>
#include <QVector>

class IPropertiesTab;
class ProjectTreeModel;

class PropertiesDialog : public QDialog
{
   Q_OBJECT
   typedef QDialog super;
public: // Constructors
   PropertiesDialog(QWidget* parent, ProjectTreeModel& model, UmlElement* elem);
   virtual ~PropertiesDialog();

public slots:
   void accept() override;

private: // Methods
   void createTabsFor(UmlAttribute* elem);
   void createTabsFor(UmlDatatype* elem);
   void createTabsFor(UmlDiagram* elem);
   void createTabsFor(UmlClass* elem);
   void createTabsFor(UmlEnumeration* elem);
   void createTabsFor(UmlInterface* elem);
   void createTabsFor(UmlOperation* elem);
   void createTabsFor(UmlPackage* elem);

   void addTab(QWidget* tab, const QString& title);
   void showHelp();

private: // Attributes
   Ui::PropertiesDialog ui;
   QVector<IPropertiesTab*> _tabs;
   UmlElement*              _elem;
   ProjectTreeModel&        _model;
};
