//---------------------------------------------------------------------------------------------------------------------
// UndoCommand.h
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
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

#include "UmlElement.h"
#include "UmlProject.h"

#include <QByteArray>
#include <QString>
#include <QUndoCommand>

class UndoCommand : public QUndoCommand
{
   ///@cond
   typedef QUndoCommand super;
   ///@endcond
public:
   UndoCommand(UmlElement* element, UmlProject* project);
   virtual ~UndoCommand();

public:
   UmlElement* element() const;

   QUuid elementId() const;
   QUuid neighborId() const;
   void setNeighborId(QUuid value);

protected:
   void saveProperties(QByteArray& array);
   void loadProperties(QByteArray& array);
   void restoreElement();
   void resetElement();

private:
   ///@cond
   UmlElement* _element;
   QUuid       _elementId;
   QUuid       _neighborId;
   QString     _className;
   UmlProject* _project;
   ///@endcond
};
