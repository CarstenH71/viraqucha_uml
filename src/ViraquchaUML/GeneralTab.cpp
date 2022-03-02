//---------------------------------------------------------------------------------------------------------------------
// GeneralTab.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class GeneralTab.
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
#include "GeneralTab.h"
#include "StringProvider.h"

#include "UmlElement.h"
#include "UmlProject.h"
#include "INamedElement.h"
#include "IStereotypedElement.h"

#include <QStringList>

/**
 * @class GeneralTab
 * @brief The GeneralTab class implements a widget for editing general properties of a single UML element.
 * @since 1.0
 * @ingroup GUI
 * @see PropertiesDialog
 *
 * The GeneralTab class provides controls for editing the name, comment and visibility of an UmlElement object, if it
 * implements INamedElement. If the UmlElement object implements IStereotypedElement as well, it also provides a
 * control for editing the stereotype of the object. It is added to the properties dialog for objects of derivations
 * of class UmlElement implementing interfaces INamedElement and IStereotypedElement.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the GeneralTab class.
 *
 * @param parent Parent widget.
 * @param elem UmlElement object to be edited.
 */
GeneralTab::GeneralTab(QWidget* parent, UmlElement* elem)
: super(parent)
, _element(elem)
, _named(dynamic_cast<INamedElement*>(elem))
, _stereotyped(dynamic_cast<IStereotypedElement*>(elem))
{
   // Element to be edited must be at least a named element!
   Q_ASSERT(_named != nullptr);

   ui.setupUi(this);
   if (_stereotyped == nullptr)
   {
      ui.stereoLabel->setVisible(false);
      ui.stereoCombo->setVisible(false);
   }

   updateControls();
}

GeneralTab::~GeneralTab()
{
}

/**
 * Validates user input.
 *
 * Always returns true, since no validation is necessary.
 * @returns Always true
 */
bool GeneralTab::validateInput()
{
   return true;
}

/**
 * Applies changes to the properties of the UmlElement object.
 */
void GeneralTab::applyChanges()
{
   _named->setName(ui.nameEdit->text());
   _named->setComment(ui.commentEdit->toPlainText());
   _named->setVisibility((VisibilityKind)(ui.visibCombo->currentIndex() + 1));
   if (_stereotyped != nullptr)
   {
      _stereotyped->setStereotype(ui.stereoCombo->currentText());
   }
}

/**
 * Updates controls of the widget by reading properties from the UmlElement object.
 */
void GeneralTab::updateControls()
{
   ui.nameEdit->setText(_named->name());
   ui.commentEdit->setPlainText(_named->comment());

   ui.visibCombo->addItems(StringProvider::visibilities());
   ui.visibCombo->setCurrentIndex((int)_named->visibility() - 1);

   if (_stereotyped != nullptr)
   {
      ui.stereoCombo->addItems(StringProvider::stereotypes());
      ui.stereoCombo->setCurrentIndex(StringProvider::stereotypes().indexOf(_stereotyped->stereotype()));
      ui.stereoCombo->setCurrentText(_stereotyped->stereotype());
   }
}
