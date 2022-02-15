//---------------------------------------------------------------------------------------------------------------------
// ParameterTab.h
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class ParameterTab.
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

#include "ui_ParameterTab.h"
#include "IPropertiesTab.h"

#include <QStringList>
#include <QWidget>

class UmlOperation;
class PATableModel;
class ComboBoxDelegate;

class ParameterTab : public QWidget, public IPropertiesTab
{
   Q_OBJECT
   typedef QWidget super;
public: // Constructors
    ParameterTab(QWidget* parent, UmlOperation* oper);
    virtual ~ParameterTab();

public: // Methods
   bool validateInput() override;
   void applyChanges() override;

private slots:
   void addItem();
   void removeItems();
   void moveItemsUp();
   void moveItemsDown();
   void updateButtons(const QModelIndex& current, const QModelIndex& previous);

private: // Attributes
   Ui::ParameterTab  ui;
   UmlOperation*     _elem;
   PATableModel*     _model;
   ComboBoxDelegate* _directionsDelegate;
   ComboBoxDelegate* _effectsDelegate;
   ComboBoxDelegate* _multiDelegate;
   ComboBoxDelegate* _typesDelegate;
};
