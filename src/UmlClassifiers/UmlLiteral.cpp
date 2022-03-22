//---------------------------------------------------------------------------------------------------------------------
// UmlLiteral.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlLiteral.
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
#include "UmlLiteral.h"

/**
 * @class UmlLiteral
 * @brief Stores properties of a literal of an UML Enumeration
 * @since 0.1.0
 * @ingroup UmlClassifiers
 * 
 * Literals are part of an UML Enumeration. They consist of a number and a symbol (or name). Objects of the UmlLiteral
 * class can only be used with UmlEnumeration objects.
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlLiteral::Data
{
   Data()
   : number(0)
   {}

   int     number;
   QString symbol;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the Literal class.
 */
UmlLiteral::UmlLiteral()
: data(new Data())
{
}

/**
 * Initializes a new Literal object with a number and a symbol.
 * 
 * @param num Number of the Literal.
 * @param sym Symbol of the Literal.
 */
UmlLiteral::UmlLiteral(int num, QString sym)
: data(new Data())
{
   setNumber(num);
   setSymbol(sym);
}

UmlLiteral::~UmlLiteral()
{
   delete data;
}

/** Gets the number. */
int UmlLiteral::number() const
{
   return data->number;
}

/** Sets the number. */
void UmlLiteral::setNumber(int value)
{
   data->number = value;
}

/** Gets the symbol. */
QString UmlLiteral::symbol() const
{
   return data->symbol;
}

/** Sets the symbol. */
void UmlLiteral::setSymbol(QString value)
{
   data->symbol = value;
}
