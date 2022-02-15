//---------------------------------------------------------------------------------------------------------------------
// StringProvider.cpp
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class StringProvider.
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
#include "StringProvider.h"

StringProvider::StringProvider()
{
   _directions << "" << tr("in") << tr("out") << tr("inout") << tr("return");
   _effects << "" << tr("create") << tr("delete") << tr("read") << tr("update");
   _multiplicities << "0" << "1" << "*" << "0..1" << "1..*";
   _primitiveTypes << "" << tr("bool") << tr("char") << tr("double") << tr("float") << tr("int") << tr("long")
      << tr("short") << tr("string") << tr("uint") << tr("ulong") << tr("ushort") << tr("void");
   _visibilities << tr("public") << tr("protected") << tr("private") << tr("package");
}

StringProvider::~StringProvider()
{
}

StringProvider& StringProvider::instance()
{
   static StringProvider provider;
   return provider;
}

QString StringProvider::defaultMultiplicity()
{
   return tr("1");
}

QString StringProvider::defaultPrimitiveType()
{
   return tr("int");
}

QStringList& StringProvider::directions()
{
   return instance()._directions;
}

QStringList& StringProvider::effects()
{
   return instance()._effects;
}

QStringList& StringProvider::multiplicities()
{
   return instance()._multiplicities;
}

QStringList& StringProvider::primitiveTypes()
{
   return instance()._primitiveTypes;
}

QStringList& StringProvider::visibilities()
{
   return instance()._visibilities;
}
