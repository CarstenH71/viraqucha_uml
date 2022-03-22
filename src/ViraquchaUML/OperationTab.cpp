//---------------------------------------------------------------------------------------------------------------------
// OperationTab.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class OperationTab.
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
#include "OperationTab.h"
#include "StringProvider.h"

#include "UmlOperation.h"
#include "UmlProject.h"

/**
 * @class OperationTab
 * @brief Provides a widget for editing a single operation of a UML classifier.
 * @since 0.1.0
 * @ingroup ViraquchaUML
 *
 * The OperationTab class provides controls for editing properties of a single operation of a UML classifier. It is
 * added to the properties dialog (see class PropertiesDialog) for every UML classifier instance in the ViraquchaUML
 * datamodel.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the OperationTab class.
 *
 * @param parent Parent widget
 * @param oper UmlOperation object to be edited
 */
OperationTab::OperationTab(QWidget* parent, UmlOperation* oper)
: super(parent)
, _oper(oper)
{
   ui.setupUi(this);
   updateControls();
}

OperationTab::~OperationTab()
{
}

/**
 * Validates user input.
 *
 * @returns True, if input is valid; false otherwise
 */
bool OperationTab::validateInput()
{
   return true;
}

/** Applies changes to the properties of the UmlOperation object. */
void OperationTab::applyChanges()
{
   _oper->setReturnType(ui.returnTypeCombo->currentText());
   _oper->setConcurrency((CallConcurrencyKind)ui.callConcurrencyCombo->currentIndex());
   _oper->isAbstract(ui.isAbstractBox->isChecked());
}

/** Updates controls in this widget. */
void OperationTab::updateControls()
{
   ui.returnTypeCombo->addItems(StringProvider::primitiveTypes());
   ui.returnTypeCombo->setCurrentText(_oper->returnType());

   ui.callConcurrencyCombo->addItems(StringProvider::callConcurrencies());
   ui.callConcurrencyCombo->setCurrentText(StringProvider::callConcurrencies()[(int)_oper->concurrency()]);
   ui.callConcurrencyCombo->setCurrentIndex((int)_oper->concurrency());

   ui.isAbstractBox->setChecked(_oper->isAbstract());
}
