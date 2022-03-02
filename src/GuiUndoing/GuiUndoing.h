//---------------------------------------------------------------------------------------------------------------------
// GuiUndoing.h
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
//
// Description  : Include file of the GuiUndoing library.
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
#pragma once

#include "CommandStack.h"
#include "EditCommand.h"
#include "InsertCommand.h"
#include "MoveCommand.h"
#include "RemoveCommand.h"
#include "UndoCommand.h"

/**
 * @defgroup GuiUndoing
 * @brief Classes for the Undo/Redo functionality of ViraquchaUML
 *
 * The GuiUndoing module provides classes for the Undo/Redo functionality of ViraquchaUML.
 */
