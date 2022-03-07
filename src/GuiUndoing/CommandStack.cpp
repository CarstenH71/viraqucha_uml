//---------------------------------------------------------------------------------------------------------------------
// CommandStack.cpp
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class CommandStack
// Compiles with: Compilers supporting C++17 (MSVC, GCC, CLang)
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
// See https://github.com/carstenhuber/viraqucha_uml for the latest version of ViraquchaUML.
//---------------------------------------------------------------------------------------------------------------------
#include "CommandStack.h"

/**
 * @class CommandStack
 * @brief The CommandStack class implements an undo stack that does not execute a command on push.
 * @since 0.2.0
 * @ingroup GuiUndoing
 *
 * The CommandStack class implements a special undo stack that unlike QUndoStack does not execute commands when pushed
 * onto it. This behavior is needed by the properties dialog of ViraquchaUML.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the CommandStack class.
 */
CommandStack::CommandStack()
{
}

CommandStack::~CommandStack()
{
}

/**
 * Pushes an UndoCommand object onto the stack without executing it.
 *
 * @param cmd UndoCommand to be pushed.
 */
void CommandStack::push(UndoCommand* cmd)
{
   _stack.append(QSharedPointer<UndoCommand>(cmd));
}

/**
 * Sets all UndoCommand objects with the given element ID obsolete.
 *
 * @param elementId
 */
void CommandStack::setObsolete(QUuid elementId)
{
   for (auto cmd : _stack)
   {
      if (cmd->elementId() == elementId || cmd->neighborId() == elementId)
      {
         cmd->setObsolete(true);
      }
   }
}

/** Redoes all commands on the stack that are not marked obsolete. */
void CommandStack::redo()
{
   for (int index = 0; index < _stack.count(); ++index)
   {
      auto cmd = _stack[index];
      if (!cmd->isObsolete())
      {
         cmd->redo();
      }
   }
}

/** Undoes all commands on the stack that are not marked obsolete. */
void CommandStack::undo()
{
   for (int index = _stack.count() - 1; index > 0; --index)
   {
      auto cmd = _stack[index];
      if (!cmd->isObsolete())
      {
         cmd->undo();
      }
   }
}

/** Redoes each command on the stack not marked obsolete once and deletes it. */
void CommandStack::redoOnce()
{
   while (!_stack.isEmpty())
   {
      auto cmd = _stack.takeFirst();
      if (!cmd->isObsolete())
      {
         cmd->redo();
      }
   }
}

/** Undoes each command on the stack not marked obsolete once and deletes it. */
void CommandStack::undoOnce()
{
   while (!_stack.isEmpty())
   {
      auto cmd = _stack.takeLast();
      if (!cmd->isObsolete())
      {
         cmd->undo();
      }
   }
}

/** Clears all command from the stack. */
void CommandStack::clear()
{
   _stack.clear();
}
