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

#include "ISerializable.h"
#include "UmlElement.h"
#include "UmlElementFactory.h"
#include "UmlProject.h"

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QUndoCommand>

class UndoCommand : public QUndoCommand
{
public:
   UndoCommand(UmlElement* element, UmlProject* project)
   : _element(element)
   , _project(project)
   {
      Q_ASSERT(_element != nullptr);
      Q_ASSERT(_project != nullptr);
      _className = _element->className();
      _elementId = _element->identifier();
   }

   virtual ~UndoCommand() {}

public:
   /** Gets the element contained in this command. */
   UmlElement* element() const { return _element; }

   QUuid elementId() const { return _elementId; }

protected:
   /** Saves properties of the element to a byte array. */
   void saveProperties(QByteArray& array)
   {
      if (_element == nullptr) return;
      QJsonObject json;
      _element->serialize(json, false, KFileVersion);
      QJsonDocument jdoc(json);
      array = jdoc.toJson(QJsonDocument::Compact);
   }

   /** Loads properties of the element from a byte array. */
   void loadProperties(QByteArray& array)
   {
      if (_element == nullptr) return;
      QJsonParseError error;
      auto doc = QJsonDocument::fromJson(array, &error);
      if (!doc.isNull())
      {
         auto obj = doc.object();
         _element->serialize(obj, true, KFileVersion);
      }
   }

   /** Restores the element. */
   void restoreElement()
   {
      if (!_project->find(_elementId, &_element))
      {
         _element = UmlElementFactory::instance().build(_className, _elementId);
      }
   }

   /** Resets the element to nullptr. */
   void resetElement()
   {
      _element = nullptr;
   }

private:
   UmlElement* _element;
   QUuid       _elementId;
   QString     _className;
   UmlProject* _project;
};

typedef QList<UndoCommand*> UndoCommandList;
int findElementId(UndoCommandList& list, QUuid id);
