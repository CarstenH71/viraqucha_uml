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

/**
 * @class StringProvider
 * @brief Provides translatable strings and string lists for windows and dialogs.
 * @since 1.0
 * @ingroup GuiResources
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the StringProvider class.
 */
StringProvider::StringProvider()
{
   _aggregations << tr("None") << tr("Shared") << tr("Composite");
   _directions << "" << tr("in") << tr("out") << tr("inout") << tr("return");
   _effects << "" << tr("create") << tr("delete") << tr("read") << tr("update");
   _languages << "" << tr("Ada95") << tr("C++") << tr("C#") << tr("D") << tr("Delphi") << tr("Go") << tr("Java")
      << tr("Python") << tr("Smalltalk") << tr("Swift");
   _multiplicities << "0" << "1" << "*" << "0..1" << "1..*";
   _primitiveTypes << "" << tr("bool") << tr("char") << tr("double") << tr("float") << tr("int") << tr("long")
      << tr("short") << tr("string") << tr("uint") << tr("ulong") << tr("ushort") << tr("void");
   _stereotypes << "" << tr("Auxiliary") << tr("BuildComponent") << tr("Call") << tr("Create") << tr("Derive")
      << tr("Destroy") << tr("Document") << tr("Entity") << tr("Executable") << tr("File") << tr("Focus")
      << tr("Framework") << tr("Implement") << tr("ImplementationClass") << tr("Instantiate") << tr("Library")
      << tr("Metaclass") << tr("Metamodel") << tr("ModelLibrary") << tr("Pocess") << tr("Realization")
      << tr("Refine") << tr("Responsibility") << tr("Script") << tr("Send") << tr("Service") << tr("Source")
      << tr("Specification") << tr("Subsystem") << tr("SystemModel") << tr("Trace") << tr("Type") << tr("Utility");
   _visibilities << tr("public") << tr("protected") << tr("private") << tr("package");
}

StringProvider::~StringProvider()
{
}

/** Gets the only object of this class (singleton) */
StringProvider& StringProvider::instance()
{
   static StringProvider provider;
   return provider;
}

/** Gets the default multiplicity. */
QString StringProvider::defaultMultiplicity()
{
   return tr("1");
}

/** Gets the default primitive type. */
QString StringProvider::defaultPrimitiveType()
{
   return tr("int");
}

/** Gets the list of aggregations. */
QStringList& StringProvider::aggregations()
{
   return instance()._aggregations;
}

/** Gets the list of directions. */
QStringList& StringProvider::directions()
{
   return instance()._directions;
}

/** Gets the list of effects. */
QStringList& StringProvider::effects()
{
   return instance()._effects;
}

/** Gets the list of supported languages. */
QStringList& StringProvider::languages()
{
   return instance()._languages;
}

/** Gets the list of multiplicities. */
QStringList& StringProvider::multiplicities()
{
   return instance()._multiplicities;
}

/** Gets the list of primitive types. */
QStringList& StringProvider::primitiveTypes()
{
   return instance()._primitiveTypes;
}

/** Gets the list of stereotypes. */
QStringList& StringProvider::stereotypes()
{
   return instance()._stereotypes;
}

/** Gets the list of visibilities. */
QStringList& StringProvider::visibilities()
{
   return instance()._visibilities;
}
