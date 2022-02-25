//---------------------------------------------------------------------------------------------------------------------
// AttributeTab.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class AttributeTab.
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
#include "AttributeTab.h"
#include "StringProvider.h"

#include "UmlAttribute.h"
#include "UmlProject.h"

#include <QStringList>

/**
 * @class AttributeTab
 * @brief The AttributeTab class implements a widget for editing properties of a single UML attribute.
 * @since 1.0
 * @ingroup GUI
 * @see PropertiesDialog
 *
 * The AttributeTab class provides controls for editing attribute specific properties like type, default value,
 * aggregation kind and flags. It is added to the properties dialog, if the object to be edited is a UmlAttribute.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the AttributeTab class.
 *
 * @param parent Parent widget, i.e. an object of class PropertiesDialog.
 * @param attr UmlAttribute object to be edited by this tab.
 */
AttributeTab::AttributeTab(QWidget* parent, UmlAttribute* attr)
: super(parent)
, _attr(attr)
{
   ui.setupUi(this);
   updateControls();
}

AttributeTab::~AttributeTab()
{
}

/**
 * Validates user input.
 *
 * This function is unused and always returns true.
 * @returns Always true.
 */
bool AttributeTab::validateInput()
{
   return true;
}

/**
 * Applies changes to the properties of the UmlAttribute object.
 *
 * This function is called by class PropertiesDialog if the user clicks on the Apply button of the dialog and after
 * successfully calling function validateInput(). It writes modified data to the UmlAttribute object's properties.
 */
void AttributeTab::applyChanges()
{
   _attr->setType(ui.typeCombo->currentText());
   _attr->setDefaultValue(ui.defaultEdit->text());
   _attr->setAggregation((AggregationKind)ui.aggregationCombo->currentIndex());
   _attr->isComposite(ui.isCompositeBox->isChecked());
   _attr->isDerived(ui.isDerivedBox->isChecked());
   _attr->isDerivedUnion(ui.isDerivedUnionBox->isChecked());
   _attr->isID(ui.isIDBox->isChecked());
   _attr->isStatic(ui.isStaticBox->isChecked());
   _attr->isReadOnly(ui.isReadonlyBox->isChecked());
}

/** 
 * Updates the controls of the tab with data from the object to be edited.
 */
void AttributeTab::updateControls()
{
   ui.typeCombo->addItems(StringProvider::primitiveTypes());
   ui.typeCombo->setCurrentIndex(StringProvider::primitiveTypes().indexOf(_attr->type()));
   ui.typeCombo->setCurrentText(_attr->type());

   ui.defaultEdit->setText(_attr->defaultValue());

   ui.aggregationCombo->addItems(StringProvider::aggregations());
   ui.aggregationCombo->setCurrentIndex((int)_attr->aggregation());

   // Flags:
   ui.isCompositeBox->setChecked(_attr->isComposite());
   ui.isDerivedBox->setChecked(_attr->isDerived());
   ui.isDerivedUnionBox->setChecked(_attr->isDerivedUnion());
   ui.isIDBox->setChecked(_attr->isID());
   ui.isStaticBox->setChecked(_attr->isStatic());
   ui.isReadonlyBox->setChecked(_attr->isReadOnly());
}
