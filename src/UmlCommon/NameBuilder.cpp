//---------------------------------------------------------------------------------------------------------------------
// NameBuilder.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class NameBuilder.
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
#include "NameBuilder.h"
#include "INamedElement.h"

/**
 * @class NameBuilder
 * @brief Creates a unique name for an INamedElement object
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * The NameBuilder class creates a unique name for an INamedElement object stored in a UmlCompositeElement object.
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct NameBuilder::Data
{
   // A simple list should be fast enough. I do not expect any composite to have more than 10.000 elements!
   QStringList names;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the NameBuilder class with a string list containing names.
 *
 * @param names String list containing names
 */
NameBuilder::NameBuilder(QStringList& names)
: data(new Data())
{
   data->names = names;
}

/**
 * Initializes a new object of the NameBuilder class with a UmlCompositeElement object.
 *
 * The constructor creates a list of named elements found in the UmlCompositeElement object provided. The list is used
 * for searching equal names when creating the new name.
 * @param owner UmlCompositeElement object containing named elements (must not be nullptr)
 */
NameBuilder::NameBuilder(UmlCompositeElement* owner)
: data(new Data())
{
   Q_ASSERT(owner != nullptr);
   for (auto elem : owner->elements())
   {
      auto named = dynamic_cast<INamedElement*>(elem);
      if (named != nullptr && !data->names.contains(named->name()))
      {
         data->names.append(named->name());
      }
   }
}

NameBuilder::~NameBuilder()
{
   delete data;
}

/**
 * Builds a unique name for a named element.
 * 
 * The name is built by adding a postfix number to a base name (like &quot;Class1&quot;, where &quot;Class&quot; is the
 * base name). The postfix number starts at 1 and is increased by 1 until no other named element with the same name can
 * be found in the owner's list of elements.
 * Note that the named element must not be contained in the owner's list of elements, otherwise the function will never
 * return!
 * @param base Name base used to build the name
 * @returns A new unique name for the named element
 */
QString NameBuilder::build(QString base)
{
   int count = 1;
   QString form = QString("%1%2");
   QString name = form.arg(base).arg(count);
   while (data->names.contains(name))
   {
      ++count;
      name = form.arg(base).arg(count);
   }

   return name;
}
