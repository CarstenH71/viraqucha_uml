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

#include "UmlOperation.h"
#include "UmlProject.h"

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
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

bool OperationTab::validateInput()
{
   return true;
}

void OperationTab::applyChanges()
{
   _oper->setReturnType(ui.returnTypeCombo->currentText());
   _oper->setConcurrency((CallConcurrencyKind)ui.callConcurrencyCombo->currentIndex());
   _oper->isAbstract(ui.isAbstractBox->isChecked());
}

void OperationTab::updateControls()
{
   ui.returnTypeCombo->addItems(_oper->project()->primitiveTypes());
   ui.returnTypeCombo->setCurrentText(_oper->returnType());

   QStringList list;
   list << "Undefined" << "Concurrent" << "Guarded" << "Sequential";
   ui.callConcurrencyCombo->addItems(list);
   ui.callConcurrencyCombo->setCurrentIndex((int)_oper->concurrency());

   // Flags:
   ui.isAbstractBox->setChecked(_oper->isAbstract());
}
