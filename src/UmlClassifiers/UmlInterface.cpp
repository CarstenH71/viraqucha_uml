//---------------------------------------------------------------------------------------------------------------------
// UmlInterface.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlInterface.
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
#include "UmlInterface.h"
#include "../UmlCommon/UmlKeywords.h"

/**
 * @class UmlInterface
 * @brief The UmlInterface class stores properties of a UML Interface element.
 * @since 0.1.0
 * @ingroup UmlClassifiers
 *
 * This class extends its base class by further properties specific to UML Interface elements
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlInterface class.
 */ 
UmlInterface::UmlInterface()
{
   setKeywords(KwdInterface);
}

/** 
 * Initializes a new instance of the UmlInterface class with an identifier. 
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlClassifier() instead.
 * @param id Identifier.
 */
UmlInterface::UmlInterface(QUuid id)
: super(id)
{
   setKeywords(KwdInterface);
}

UmlInterface::~UmlInterface()
{
}

/** Gets the class name. */
QString UmlInterface::className() const
{
   return staticMetaObject.className();
}
