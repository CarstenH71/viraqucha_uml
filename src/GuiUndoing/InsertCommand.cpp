//---------------------------------------------------------------------------------------------------------------------
// InsertCommand.cpp
//
// Copyright (C) 2020 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class InsertCommand.
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
#include "InsertCommand.h"
#include "ProjectTreeModel.h"

/**
 * @class InsertCommand
 * @brief The InsertCommand class implements an insert command for UmlElement objects.
 * @since 0.2.0
 * @ingroup GuiUndoing
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the InsertCommand class.
 * @param element
 * @param model
 * @param parent
 */
InsertCommand::InsertCommand(UmlElement* element, ProjectTreeModel& model, const QModelIndex& parent)
: super(element, model.getProject())
, _model(model)
, _parent(parent)
{}
   
InsertCommand::~InsertCommand()
{}

/** Inserts the UmlElement object into the project model. */
void InsertCommand::redo()
{
   _model.insertRow(_parent, element());
}

/** Removes the UmlElement object from the project model. */
void InsertCommand::undo()
{
   _model.removeRow(_parent, element());
}
