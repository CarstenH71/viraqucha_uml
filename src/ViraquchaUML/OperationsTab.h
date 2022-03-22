//---------------------------------------------------------------------------------------------------------------------
// OperationsTab.h
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class OperationsTab.
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

#include "ui_OperationsTab.h"
#include "CommandStack.h"
#include "IPropertiesTab.h"
#include "UndoCommand.h"

#include <QList>
#include <QSharedPointer>
#include <QWidget>

class ComboBoxDelegate;
class ProjectTreeModel;
class OPTableModel;
class UmlClassifier;

class OperationsTab : public QWidget, public IPropertiesTab
{
   ///@cond
   Q_OBJECT
   typedef QWidget super;
   ///@endcond
public: // Constructors
   OperationsTab(QWidget* parent, UmlClassifier* classifier, ProjectTreeModel& project);
   virtual ~OperationsTab();

public: // Methods
   bool validateInput() override;
   void applyChanges() override;

private slots:
   void addItem();
   void editItem();
   void removeItems();
   void moveItemUp();
   void moveItemDown();
   void updateButtons(const QModelIndex& current, const QModelIndex& previous);

private: // Attributes
   ///@cond
   Ui::OperationsTab ui;
   UmlClassifier* _classifier;
   ProjectTreeModel& _project;
   OPTableModel*     _model;
   CommandStack      _commands;
   ComboBoxDelegate* _returnTypeDelegate;
   ComboBoxDelegate* _visibilityDelegate;
   ///@endcond
};
