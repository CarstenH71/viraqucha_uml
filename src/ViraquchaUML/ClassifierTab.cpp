//---------------------------------------------------------------------------------------------------------------------
// ClassifierTab.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class ClassifierTab.
// Compiles with: MSVC 15.2 (2017) or newer, GNU GCC 5.1 or newer
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This library is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
// * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
// * option) any later version.                                                                                      *
// *                                                                                                                 *
// * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
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
#include "ClassifierTab.h"
#include "StringProvider.h"
#include "UmlClassifier.h"
#include "UmlClass.h"

#include <QStringList>

/**
 * @class ClassifierTab
 * @brief The ClassifierTab class implements a widget for editing UML classifier.
 * @since 0.1.0
 * @ingroup ViraquchaUML
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the ClassifierTab class.
 *
 * @param parent Parent widget
 * @param elem UmlClassifier object to be edited
 */
ClassifierTab::ClassifierTab(QWidget* parent, UmlClassifier* elem)
: super(parent)
, _element(elem)
{
   ui.setupUi(this);
   updateControls();
}

ClassifierTab::~ClassifierTab()
{
}

/**
 * Validates user input.
 *
 * Always returns true, since no validation is necessary.
 * @returns Always true
 */
bool ClassifierTab::validateInput()
{
   return true;
}

/**
 * Applies changes to the properties of the UmlClassifier object.
 */
void ClassifierTab::applyChanges()
{
   _element->setLanguage(ui.languageCombo->currentText());
   _element->isAbstract(ui.isAbstractBox->isChecked());
   if (_element->className() == UmlClass::staticMetaObject.className())
   {
      dynamic_cast<UmlClass*>(_element)->isActive(ui.isActiveBox->isChecked());
   }
   _element->isFinal(ui.isFinalBox->isChecked());
   _element->isLeaf(ui.isLeafBox->isChecked());
}

/**
 * Updates the controls of this widget.
 */
void ClassifierTab::updateControls()
{
   ui.languageCombo->addItems(StringProvider::languages());
   ui.languageCombo->setCurrentIndex(StringProvider::languages().indexOf(_element->language()));
   ui.languageCombo->setCurrentText(_element->language());

   ui.isAbstractBox->setChecked(_element->isAbstract());
   if (_element->className() == UmlClass::staticMetaObject.className())
   {
      ui.isActiveBox->setVisible(true);
      ui.isActiveBox->setChecked(dynamic_cast<UmlClass*>(_element)->isActive());
   }
   else
   {
      ui.isActiveBox->setVisible(false);
   }
 
   ui.isFinalBox->setChecked(_element->isFinal());
   ui.isLeafBox->setChecked(_element->isLeaf());
}
