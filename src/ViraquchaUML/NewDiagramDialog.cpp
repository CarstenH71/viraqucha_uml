//---------------------------------------------------------------------------------------------------------------------
// NewDiagramDialog.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class NewDiagramDialog.
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
#include "NewDiagramDialog.h"
#include "StringProvider.h"

/**
 * @class NewDiagramDialog
 * @brief Implements a simple dialog which allows selection of a diagram type
 * @since 0.1.0
 * @ingroup ViraquchaUML
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the NewDiagramDialog class.
 *
 * @param parent Parent widget
 */
NewDiagramDialog::NewDiagramDialog(QWidget *parent)
: super(parent)
{
   ui.setupUi(this);
   ui.comboBox->addItems(StringProvider::diagramTypes());
}

NewDiagramDialog::~NewDiagramDialog()
{
}

/** Gets the diagram type selected by the user. */
DiagramKind NewDiagramDialog::kind() const
{
   return (DiagramKind)(ui.comboBox->currentIndex() + 1);
}
