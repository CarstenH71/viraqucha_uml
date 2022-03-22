//---------------------------------------------------------------------------------------------------------------------
// UmlDatatype.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlDatatype.
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
#include "UmlDatatype.h"
#include "../UmlCommon/UmlKeywords.h"

/**
 * @class UmlDatatype
 * @brief The UmlDatatype class stores data of a UML element of type DataType.
 * @since 0.1.0
 * @ingroup UmlClassifiers
 *
 * In UML a data type is a kind of classifier, with the difference that its instances are only identified by their 
 * values.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

UmlDatatype::UmlDatatype()
{
   setKeywords(KwdDataType);
}

UmlDatatype::UmlDatatype(QUuid id)
: super(id)
{
   setKeywords(KwdDataType);
}

UmlDatatype::~UmlDatatype()
{
}

QString UmlDatatype::className() const
{
   return staticMetaObject.className();
}
