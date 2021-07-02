//---------------------------------------------------------------------------------------------------------------------
// AttributesTab.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class AttributesTab.
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
#include "AttributesTab.h"

#include "UmlClassifier.h"

/**
 * @class AttributesTab
 * @brief Provides a widget for editing attributes of a UML classifier.
 * @since 1.0
 * @ingroup GUI
 *
 * The AttributesTab class provides a table widget and some buttons for editing attributes of an UML classifier. It
 * is added to the properties dialog (see class PropertiesDialog) for every UML classifier instance in the ViraquchaUML
 * datamodel.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
AttributesTab::AttributesTab(QWidget* parent, UmlClassifier* classifier)
: super(parent)
, _classifier(classifier)
{
   ui.setupUi(this);
}

AttributesTab::~AttributesTab()
{
}

bool AttributesTab::validateInput()
{
   return true;
}

void AttributesTab::applyChanges()
{
}
