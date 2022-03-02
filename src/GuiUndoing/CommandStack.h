//---------------------------------------------------------------------------------------------------------------------
// CommandStack.h
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class CommandStack
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
#pragma once

#include "UndoCommand.h"

#include <QSharedPointer>
#include <QVector>

class CommandStack final
{
public:
   CommandStack();
   ~CommandStack();

public:
   void push(UndoCommand* cmd);

   void setObsolete(QUuid elementId);

   void redo();
   void undo();
   void redoOnce();
   void undoOnce();

   void clear();

public:
   ///@cond
   QVector<QSharedPointer<UndoCommand>> _stack;
   ///@endcond
};

