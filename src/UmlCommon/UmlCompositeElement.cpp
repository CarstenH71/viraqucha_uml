//---------------------------------------------------------------------------------------------------------------------
// UmlCompositeElement.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlCompositeElement.
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
#include "UmlCompositeElement.h"
#include "UmlLink.h"
#include "UmlProject.h"
#include "PropertyStrings.h"

#include <QJsonArray>
#include <QJsonObject>

/**
 * @class UmlCompositeElement
 * @brief The UmlCompositeElement class represents an UML element containing child elements.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * The UmlCompositeElement class is the base class for all composite memory objects in the data model. Together with 
 * its base class UmlElement, it forms the Composite Pattern. The class UmlCompositeElement has no equivalent in the 
 * UML specification; in principle, the modeling concept "Element" assumes the same task there.
 *
 * Objects of the class manage their child objects in a simple list of type QList. This list is not automatically 
 * sorted, e.g. when inserting or removing objects. However, it is possible to move objects in the list "up" or "down", 
 * i.e. functions are available with which the arrangement of the objects can be changed.
 *
 * Note: Although it is possible to create an object from this class, it is not recommended to do so. Since it is a
 * base class only you should better create objects from derived classes.
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct UmlCompositeElement::Data
{
   QList<UmlElementPtr> elements;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the UmlCompositeElement class with a new unique identifier.
 */
UmlCompositeElement::UmlCompositeElement()
: data(new Data())
{
}

/**
 * Initializes a new object of the UmlCompositeElement class with an identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new object with a new unique identifier, use constructor UmlCompositeElement() instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlCompositeElement::UmlCompositeElement(QUuid id)
: super(id)
, data(new Data())
{
}

UmlCompositeElement::~UmlCompositeElement()
{
   delete data;
}

/**
 * Gets a copy of the list of child elements owned by the composite element.
 */
QList<UmlElement*> UmlCompositeElement::elements() const
{
   QList<UmlElement*> list;
   for (auto elem : data->elements)
   {
      list.append(elem.pointee());
   }
   return list;
}

/** Gets a value indicating whether the list of elements is empty. */
bool UmlCompositeElement::empty() const
{
   return data->elements.empty();
}

/**
 * Appends a child element to the end of the list of elements of the composite.
 *
 * This function is used mainly by the serialization function. It should not be used by applications because it does
 * not constitute any sorting of elements in the list. Use function insert() instead.
 *
 * @param elem Element to be appended.
 */
void UmlCompositeElement::append(UmlElement* elem)
{
   if (elem != nullptr)
   {
      elem->setOwner(this);
      data->elements.append(UmlElementPtr(elem));
   }
}

/**
 * Inserts a child element at a specific position of the list of elements of the composite.
 *
 * Use this function for inserting elements from applications.
 * @param pos Insert position.
 */
void UmlCompositeElement::insert(int pos, UmlElement* elem)
{
   if (empty() || elem->isHidden())
   {
      append(elem);
      return;
   }

   // Count only non-hidden elements -> assure hidden elements are at the end of the list!
   int cnt = count(false); 
   if (pos > cnt) pos = cnt;
   elem->setOwner(this);
   data->elements.insert(pos, UmlElementPtr(elem));
}

/**
 * Removes a child element from the composite element.
 */
void UmlCompositeElement::remove(UmlElement* elem)
{
   if (elem != nullptr)
   {
      elem->setOwner(nullptr);
      bool test = data->elements.removeOne(UmlElementPtr(elem));
      Q_ASSERT(test == true);
   }
}

/**
 * Clears all (child) elements from the composite element.
 */
void UmlCompositeElement::clear()
{
   data->elements.clear();
}

/**
 * Moves an element up.
 */
void UmlCompositeElement::moveUp(UmlElement* elem)
{
   int index = indexOf(elem);
   if (index > 0)
   {
      data->elements.move(index, index - 1);
   }
}

/**
 * Moves an element down.
 */
void UmlCompositeElement::moveDown(UmlElement* elem)
{
   int index = indexOf(elem);
   if (index < count(false))
   {
      data->elements.move(index, index + 1);
   }
}

/**
 * Counts elements stored in the composite.
 *
 * @param hidden If false, hidden elements are *not* counted. Default is true.
 */
int UmlCompositeElement::count(bool hidden)
{
   if (hidden) return data->elements.count();
   
   int index = 0;
   while (index < data->elements.count() && !data->elements[index]->isHidden())
   {
      ++index;
   }

   return index;
}

/** 
 * Gets the index of an element in the list of elements of the composite. 
 *
 * @param elem Element to get the index of.
 * @return The index of the element or -1 if the element is not contained in the composite.
 */
int UmlCompositeElement::indexOf(UmlElement* elem)
{
   return data->elements.indexOf(UmlElementPtr(elem));
}

/**
 * Gets the element at a specified index or nullptr if the index is out of bounds or the list of elements is empty. 
 *
 * @param index Index of the element in the list of elements of the composite.
 */
UmlElement* UmlCompositeElement::at(int index)
{
   if (count() == 0) return nullptr;
   if (index < 0 || index >= count()) return nullptr;
   return data->elements.at(index).pointee();
}

/**
 * Disposes the composite element.
 *
 * This function is called by UmlProject::dispose() to reset all intrusive pointers owned by the element. Do not call
 * directly.
 */
void UmlCompositeElement::dispose(bool disposing)
{
   clear();
   super::dispose(disposing);
}

/**
 * Serializes properties of the UmlCompositeElement object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlCompositeElement::serialize(QJsonObject& json, bool read, bool flat, int version)
{
   QJsonArray array;

   super::serialize(json, read, flat, version);
   if (read)
   {
      if (json.contains(KPropElements))
      {
         array = json[KPropElements].toArray();
         for (int index = 0; index < array.size(); ++index)
         {
            // Get the identifier of the element:
            QUuid ident = QUuid(array[index].toString());

            // Get the element itself from the project...
            UmlElement* elem = nullptr;
            if (project()->find(ident, &elem))
            {
               // ... and add it to the list of elements:
               append(elem);
            }
         }
      }
   }
   else
   {
      if (!flat)
      {
         for (auto elem : data->elements)
         {
            array.append(QJsonValue(elem->identifier().toString()));
         }

         json[KPropElements] = array;
      }
   }
}
