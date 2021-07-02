//---------------------------------------------------------------------------------------------------------------------
// MultiplicityTab.h
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class MultiplicityTab.
// Compiles with: MSVC 15.2 (2017) or newer, GNU GCC 5.1 or newer
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
// * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
// * option) any later version.                                                                                      *
// *                                                                                                                 *
// * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
// * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
// * for more details.                                                                                               *
// *                                                                                                                 *
// * You should have received a copy of the GNU General Public License along with this library; if not, see          *
// * http://www.gnu.org/licenses/gpl                                                                                 *
// *                                                                                                                 *
// *******************************************************************************************************************
//
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#pragma once

#include "ui_MultiplicityTab.h"
#include "IPropertiesTab.h"

#include <QRegularExpression>
#include <QWidget>

class IMultiplicityElement;

class MultiplicityTab : public QWidget, public IPropertiesTab
{
   Q_OBJECT
   typedef QWidget super;
public: // Constructors
   MultiplicityTab(QWidget *parent, IMultiplicityElement* elem);
   virtual ~MultiplicityTab();

public: // Methods
   bool validateInput() override;
   void applyChanges() override;

private:
   void updateControls();

private: // Attributes
   Ui::MultiplicityTab   ui;
   IMultiplicityElement* _elem;
   quint32               _lower;
   quint32               _upper;
};
