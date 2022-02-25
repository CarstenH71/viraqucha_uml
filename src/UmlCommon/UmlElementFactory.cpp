//---------------------------------------------------------------------------------------------------------------------
// UmlElementFactory.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlElementFactory.
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
#include "UmlElementFactory.h"
#include <QMap>

/**
 * @class UmlElementFactory
 * @brief The UmlElementFactory class implements a factory building UmlElement objects from class names.
 * @since 1.0
 * @ingroup UmlCommon
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlElementFactory::Data
{
   QMap<QString, IElementBuilder*> builder;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
UmlElementFactory::UmlElementFactory()
: data(new Data())
{
}

UmlElementFactory::~UmlElementFactory()
{
   delete data;
}

/**
 * Gets the only instance of this class (singleton).
 */
UmlElementFactory& UmlElementFactory::instance()
{
   static UmlElementFactory factory;
   return factory;
}

/**
 * Gets a value indicating whether a builder of a given class name is subscribed to the factory.
 * @param className Concrete name of a class derived from UmlElement.
 * @returns true, if the factory contains a builder for the class name; false otherwise.
 */
bool UmlElementFactory::isSubscribed(QString className)
{
   return !className.isEmpty() && data->builder.contains(className);
}

/**
 * Gets the count of builder instances subscribed to this factory.
 */
uint UmlElementFactory::count() const
{
   return data->builder.size();
}

/**
 * Builds an instance of a derivation of an UmlElement class using its class name.
 *
 * The function returns a nullptr if no IElementBuilder instance is associated with the class name. You can check whether
 * the instance is subscribed to the factory by calling function isSubscribed() with the class name of the UmlElement
 * that should be built by the instance. Use function subscribe() to subscribe the instance to the factory.
 * @param className Concrete name of a class derived from UmlElement.
 * @param id Identifier that the newly created UmlElement object shall receive.
 * @returns A new UmlElement object for the class name or nullptr if the factory has no corresponding builder.
 */
UmlElement* UmlElementFactory::build(QString className, QUuid id)
{
   if (data->builder.contains(className))
   {
      return data->builder[className]->build(id);
   }

   return nullptr;
}

/**
 * Subscribes a new IElementBuilder instance with the factory.
 * 
 * The class name must not be empty and the builder must not be nullptr. Otherwise the function does nothing.
 * @param className Class name to be used for subscription. Must not be empty.
 * @param builder Pointer to the IElementBuilder instance which shall be subscribed. Must not be nullptr.
 */
void UmlElementFactory::subscribe(QString className, IElementBuilder* builder)
{
   if (builder != nullptr && !className.isEmpty())
   {
      data->builder.insert(className, builder);
   }
}
