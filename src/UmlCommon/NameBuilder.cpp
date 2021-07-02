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

#include <QList>
#include <QListIterator>
#include <QMap>

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct NameBuilder::Data
{
   QMap<QString, INamedElement*> names;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

NameBuilder::NameBuilder(UmlCompositeElement* owner)
: data(new Data())
{
   Q_ASSERT(owner != nullptr);
   
   QListIterator<UmlElement*> iter(owner->elements());
   while (iter.hasNext())
   {
      auto elem = dynamic_cast<INamedElement*>(iter.next());
      if (elem != nullptr && !data->names.contains(elem->name()))
      {
         data->names.insert(elem->name(), elem);
      }
   }
}

NameBuilder::~NameBuilder()
{
   delete data;
}

/**
 * Builds a name for a given named element.
 * 
 * The name is built by adding a postfix number to a base name. The postfix number is automatically increased as long
 * as the owner of the named element contains another named element with the same name. Note that the named element
 * must not be contained in the owner's list of elements!
 *
 * @param elem Named element receiving the new name.
 * @param base Name base used to build the name (e.g."Class").
 * @returns A new unique name for the named element.
 */
QString NameBuilder::buildFor(INamedElement* elem, QString base)
{
   if (elem == nullptr) return QString();
   
   int cnt = 0;
   QString name = QString("%1%2").arg(base).arg(cnt);
   while (data->names.contains(name))
   {
      ++cnt;
      name = QString("%1%2").arg(base).arg(cnt);
   }

   elem->setName(name);
   return name;
}
