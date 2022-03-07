//---------------------------------------------------------------------------------------------------------------------
// MoveCommand.cpp
//
// Copyright (C) 2020 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class MoveCommand.
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
#include "MoveCommand.h"

/**
 * @class MoveCommand
 * @brief The MoveCommand class implements a move command for UmlElement objects.
 * @since 0.2.0
 * @ingroup GuiUndoing
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the MoveCommand class.
 * @param element
 * @param neighbor
 * @param model
 * @param down
 */
MoveCommand::MoveCommand(UmlElement* element, QUuid neighbor, ProjectTreeModel& model, bool down)
: super(element, model.getProject())
, _model(model)
, _down(down)
{
   setNeighborId(neighbor);
}

MoveCommand::~MoveCommand()
{
}

/** Moves the UmlElement object in the project model up or down. */
void MoveCommand::redo()
{
   if (_down)
   {
     _model.moveRow(_model.indexOf(element()), true);
   }
   else
   {
      _model.moveRow(_model.indexOf(element()), false);
   }
}

/** Moves the UmlElement object in the project model down or up. */
void MoveCommand::undo()
{
   if (_down)
   {
     _model.moveRow(_model.indexOf(element()), false);
   }
   else
   {
      _model.moveRow(_model.indexOf(element()), true);
   }
}
