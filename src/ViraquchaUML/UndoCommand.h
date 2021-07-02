//---------------------------------------------------------------------------------------------------------------------
// UndoCommand.h
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of template class UndoCommand.
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

#include "IntrusivePtr.h"
#include <QUndoCommand>

template<class T> class UndoCommand : public QUndoCommand
{
public:
   UndoCommand(T* element) : _element(element) {}
   virtual ~UndoCommand() {}

public:
   T* element() const { return _element.pointee(); }

private:
   IntrusivePtr<T> _element;
};

template<class T, class V> class UndoCommandWithValue : public UndoCommand<T>
{
   typedef UndoCommand<T> super;
public:
   UndoCommandWithValue(T* element, V oldval, V newval)
   : super(element)
   , _oldValue(oldval)
   , _newValue(newval)
   {}
   
   virtual ~UndoCommandWithValue()
   {}

public:
   V oldValue() const { return _oldValue; }
   V newValue() const { return _newValue; }

private:
   V _oldValue;
   V _newValue;
};
