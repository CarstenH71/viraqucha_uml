//---------------------------------------------------------------------------------------------------------------------
// UmlSignal.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class name.
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
#include "UmlSignal.h"
#include "../UmlCommon/UmlKeywords.h"

/**
 * @class UmlSignal
 * @brief The UmlSignal class stores properties of a UML Signal element.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 * This class extends its base class by further properties specific to UML Signal elements.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlSignal class.
 *
 * Sets keyword &quot;signal&quot; automatically.
 */
UmlSignal::UmlSignal()
{
   setKeywords(KwdSignal);
}

/**
 * Initializes a new instance of the UmlSignal class with a given identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlSignal() instead. Sets keyword 
 * &quot;signal&quot; automatically.
 *
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlSignal::UmlSignal(QUuid id)
: super(id)
{
   setKeywords(KwdSignal);
}

UmlSignal::~UmlSignal()
{
}

/** Gets the class name. */
QString UmlSignal::className() const
{
   return staticMetaObject.className();
}
