//---------------------------------------------------------------------------------------------------------------------
// InsertCommand.h
//
// Copyright (C) 2020 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of template class InsertCommand.
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

#include "ProjectTreeModel.h"
#include "UndoCommand"

#include <QModelIndex>
#include <QPersistentModelIndex>

class InsertCommand : public UndoCommand<UmlElement>
{
   typedef UndoCommand<UmlElement> super;
public:
   InsertCommand(ProjectTreeModel* model, const QModelIndex& parent, UmlElement* element)
   : super(element)
   , _parent(parent)
   {}
   
   virtual ~InsertCommand()
   {}
   
public:
   void redo() { _model->insertRow(_parent, element()); } override;
   void undo() { _model->removeRow(_parent, element()); } override;
   
private:
   ProjectTreeModel*     _model;
   QPersistentModelIndex _parent;
};
