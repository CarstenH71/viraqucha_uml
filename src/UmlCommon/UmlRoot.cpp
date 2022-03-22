//---------------------------------------------------------------------------------------------------------------------
// UmlRoot.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlRoot.
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
#include "UmlRoot.h"
#include "UmlModel.h"

/**
 * @class UmlRoot
 * @brief The UmlRoot class represents the root object of the hirarchical structure of objects in the data model.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * The UmlRoot class serves as the root object for the hierarchical structure of the UmlElement objects in the data
 * model. When a new UmlProject object is created, a single object of this class is also automatically created, whereby 
 * the same identifier is always used (see file UmlProject.cpp). Therefore, you should never create an object of this
 * class or try to insert it into an UmlProject object (it will not work).
 *
 * The class has no properties other than those of the base class UmlCompositeElement. However, it overwrites the 
 * functions for inserting and removing UmlElement objects so that they only accept objects of the UmlModel class.
 *
 * The class UmlRoot has no equivalent in the UML specification.
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
/** 
 * Initializes a new instance of the UmlRoot class.
 */
UmlRoot::UmlRoot()
{
}

/**
 * Initializes a new instance of the UmlRoot class with a given identifier.
 */
UmlRoot::UmlRoot(QUuid id)
: super(id)
{
}

UmlRoot::~UmlRoot()
{
}

/** Gets the class name "UmlRoot" of the object. */
QString UmlRoot::className() const
{
   return staticMetaObject.className();
}

/**
 * Appends an UmlElement object to the root object.
 *
 * This overridden method asserts if the object is not of class UmlModel.
 * @param elem UmlElement object to be added.
 */
void UmlRoot::append(UmlElement* elem)
{
   Q_ASSERT(dynamic_cast<UmlModel*>(elem) != nullptr);
   super::append(elem);
}

/**
 * Inserts an UmlElement object into the root object.
 *
 * This overridden method asserts if the element is not of class UmlModel.
 * @param elem UmlElement object to be added.
 */
void UmlRoot::insert(int pos, UmlElement* elem)
{
   Q_ASSERT(dynamic_cast<UmlModel*>(elem) != nullptr);
   super::insert(pos, elem);
}

/**
 * Removes an UmlElement object from the root object.
 *
 * This overridden method asserts if the element is not of class UmlModel.
 * @param elem UmlElement object to be added.
 */
void UmlRoot::remove(UmlElement* elem)
{
   Q_ASSERT(dynamic_cast<UmlModel*>(elem) != nullptr);
   super::remove(elem);
}
