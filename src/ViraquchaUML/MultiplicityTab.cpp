//---------------------------------------------------------------------------------------------------------------------
// MultiplicityTab.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class MultiplicityTab.
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
#include "MultiplicityTab.h"
#include "Globals.h"
#include "StringProvider.h"

#include "IMultiplicityElement.h"
#include "MultiplicityUtils.h"

#include <QMessageBox>
#include <QStringList>
#include <QTextStream>

/**
 * @class MultiplicityTab
 * @brief The MultiplicityTab class implements a tab page for IMultiplicityElement instances.
 * @since 1.0
 * @ingroup GUI
 *
 * The MultiplicityTab allows editing of the multiplicity of an UML element, e.g. an attribute or an operation. It
 * provides a editable combo box for editing the multiplicity range as well as check boxes for setting properties 
 * isOrdered and isUnique of the multiplicity.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/** 
 * Initializes a new instance of the MultiplicityTab class.
 *
 * @param parent Parent widget (in this case a PropertiesDialog instance).
 * @param elem IMultiplicityElement instance to be edited.
 */
MultiplicityTab::MultiplicityTab(QWidget *parent, IMultiplicityElement* elem)
: super(parent)
, _elem(elem)
, _lower(1)
, _upper(1)
{
   Q_ASSERT(_elem);
   _lower = _elem->lower();
   _upper = _elem->upper();

   ui.setupUi(this);
   updateControls();
}

MultiplicityTab::~MultiplicityTab()
{
}

/** 
 * Validates user input.
 *
 * This function is called before changes are committed to the data model. It validates the multiplicity range entered
 * by the user using a regular expression and saves upper and lower value read from the range for later committing.
 * @returns true, if validation of the input was successful; otherwise false.
 */
bool MultiplicityTab::validateInput()
{
   auto range = ui.rangeCombo->currentText();
   if (MultiplicityUtils::tryParse(range, _lower, _upper))
   {
      if (_lower > _upper)
      {
         QString msg(tr("Lower value is greater than upper value."));
         QMessageBox::warning(this, Viraqucha::KProgramName, msg, QMessageBox::Ok);
         return false;
      }

      return true;
   }

   QString msg(tr("'%1' is not a valid range.\nA valid range may contain '0'-'9', '*' and '..' only.").arg(range));
   QMessageBox::warning(this, Viraqucha::KProgramName, msg, QMessageBox::Ok);
   return false;
}

/**
 * Applies changes to the ViraquchaUML data model.
 */
void MultiplicityTab::applyChanges()
{
   _elem->setLower(_lower);
   _elem->setUpper(_upper);
   _elem->isOrdered(ui.isOrderedBox->isChecked());
   _elem->isUnique(ui.isUniqueBox->isChecked());
}

/** 
 * Updates all controls of the tab control with data read from the ViraquchaUML data model.
 */
void MultiplicityTab::updateControls()
{
   auto range = MultiplicityUtils::toString(_lower, _upper);

   ui.rangeCombo->addItems(StringProvider::multiplicities());
   ui.rangeCombo->setCurrentIndex(StringProvider::multiplicities().indexOf(range));
   ui.rangeCombo->setCurrentText(range);

   ui.isOrderedBox->setChecked(_elem->isOrdered());
   ui.isUniqueBox->setChecked(_elem->isUnique());
}
