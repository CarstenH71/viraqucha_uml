//---------------------------------------------------------------------------------------------------------------------
// UndoCommand.cpp
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UndoCommand.
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
#include "UndoCommand.h"
#include "ISerializable.h"
#include "UmlElementFactory.h"

#include <QJsonDocument>
#include <QJsonObject>

/**
 * @class UndoCommand
 * @brief Base class for the undo commands of ViraquchaUML
 * @since 1.0
 * @ingroup GUI
 *
 * The UndoCommand class is the base class of the undo commands of ViraquchaUML. It extends QUndoCommand by properties
 * and functions for managing UmlElement objects.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Instantiates a new object of the UndoCommand class with a UmlElement and a UmlProject object.
 * @param element
 * @param project
 */
UndoCommand::UndoCommand(UmlElement* element, UmlProject* project)
: _element(element)
, _project(project)
{
   Q_ASSERT(_element != nullptr);
   Q_ASSERT(_project != nullptr);
   _className = _element->className();
   _elementId = _element->identifier();
   _neighborId = QUuid();
}

UndoCommand::~UndoCommand()
{}

/** Gets the element contained. */
UmlElement* UndoCommand::element() const
{
   return _element;
}

/** Gets the identifier of the element contained. */
QUuid UndoCommand::elementId() const
{
   return _elementId;
}

/**
 * Gets the identifier of a neighboring element.
 *
 * This property can be used for move commands, where it is important to know the neighoring elements of an element.
 */
QUuid UndoCommand::neighborId() const
{
   return _neighborId;
}

/** Sets the identifier of a neighboring element. */
void UndoCommand::setNeighborId(QUuid value)
{
   _neighborId = value;
}

/** Saves properties of the element to a byte array. */
void UndoCommand::saveProperties(QByteArray& array)
{
   if (_element == nullptr) return;
   QJsonObject json;
   _element->serialize(json, false, KFileVersion);
   QJsonDocument jdoc(json);
   array = jdoc.toJson(QJsonDocument::Compact);
}

/** Loads properties of the element from a byte array. */
void UndoCommand::loadProperties(QByteArray& array)
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
void UndoCommand::restoreElement()
{
   if (!_project->find(_elementId, &_element))
   {
      _element = UmlElementFactory::instance().build(_className, _elementId);
   }
}

/** Resets the element to nullptr. */
void UndoCommand::resetElement()
{
   _element = nullptr;
}
