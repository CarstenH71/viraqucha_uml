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
#include "Globals.h"

#include "UmlAttribute.h"
#include "UmlProject.h"

#include <QStringList>

/**
 * @class AttributeTab
 * @brief The AttributeTab class implements a tab for attribute properties.
 * @since 1.0
 * @ingroup GUI
 *
 * 
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
/**
 * Initializes a new instance of the AttributeTab class.
 *
 * @param parent Parent widget, i.e. an instance of class PropertiesDialog.
 * @param attr UmlAttribute instance to be edited by this tab.
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

bool AttributeTab::validateInput()
{
   return true;
}

/**
 * Applies all changes made to the attribute to the ViraquchaUML database. 
 *
 * This function is called by class PropertiesDialog if the user clicks on the Apply button of the dialog. It stores
 * all data in the UmlAttribute instance, after validating it. 
 * @returns false, if validation fails; otherwise true.
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
 * Updates the controls of the tab with data from the instance to be edited. 
 *
 * This method is called once on creation of the class.
 */
void AttributeTab::updateControls()
{
   ui.typeCombo->addItems(_attr->project()->primitiveTypes());
   ui.typeCombo->setCurrentText(_attr->type());

   ui.defaultEdit->setText(_attr->defaultValue());

   QStringList list;
   list << "None" << "Shared" << "Composite";
   ui.aggregationCombo->addItems(list);
   ui.aggregationCombo->setCurrentIndex((int)_attr->aggregation());

   // Flags:
   ui.isCompositeBox->setChecked(_attr->isComposite());
   ui.isDerivedBox->setChecked(_attr->isDerived());
   ui.isDerivedUnionBox->setChecked(_attr->isDerivedUnion());
   ui.isIDBox->setChecked(_attr->isID());
   ui.isStaticBox->setChecked(_attr->isStatic());
   ui.isReadonlyBox->setChecked(_attr->isReadOnly());
}
