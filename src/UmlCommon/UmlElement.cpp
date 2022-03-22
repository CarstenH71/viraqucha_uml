//---------------------------------------------------------------------------------------------------------------------
// UmlElement.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlElement.
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
#include "UmlElement.h"
#include "UmlCompositeElement.h"
#include "UmlLink.h"
#include "UmlProject.h"
#include "PropertyStrings.h"

#include <QAtomicInteger>
#include <QDebug>

#include <QFile>

/**
 * @class UmlElement
 * @brief The UmlElement class is the abstract base class of all memory objects of the ViraquchaUML data model.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * The class UmlElement is the abstract base class for all linkable memory objects in the data model. It corresponds to
 * the modeling concept "Element" in the UML specification, but with the difference that it cannot be used directly for 
 * representation in diagrams. The class DiaShape and its derivatives take over this task instead.
 *
 * The class performs the following tasks in the data model:
 * 
 * 1. It allows the management of memory objects in a project. For this purpose, it provides a unique identifier and 
 *    a function to store its properties in a JSON file. To manage the lifetime of the memory object, it also provides 
 *    a reference counter that can be used together with an intrusive pointer that automatically deletes the memory 
 *    object if necessary.
 * 2. It implements the Composite Pattern together with the UmlCompositeElement class derived from it. With the help 
 *    of this object-oriented pattern, it is possible to arrange the memory objects hierarchically in a parent-child 
 *    like structure.
 * 3. It forms the basis for the mechanism for linking elements using connectors (links) and thus for the relationships
 *    described in the UML specification. For this purpose, the connectors are modelled by the UmlLink class, which is 
 *    also derived from UmlElement.
 *
 * UmlElement offers fundamental properties and operations, required for the administration in a project (see also 
 * class UmlProject). To keep the implementation of the class as lightweight as possible, it is not derived from class
 * QObject. Accordingly, it does not support the Signal-Slot mechanism. Instead, a different and simpler notification 
 * mechanism is used: If a class implements the IElementObserver interface, their objects can log on as observers to an
 * object of the UmlElement class. If the state of the UmlElement object changes (for example, if it is deleted), the 
 * objects logged on are informed via the interface and can trigger corresponding further actions.
 *
 * All UmlElement objects are stored and managed in an object of class UmlProject. The project to which an object of 
 * the class belongs to, can be queried using property project(). If this property returns nullptr, the object is not 
 * yet assigned to a project.
 */

#ifdef _DEBUG
 /// @cond
static QAtomicInteger<quint32> cleanCount = 0;

void assertClean()
{
   Q_ASSERT(cleanCount == 0);
}
/// @endcond
#endif

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlElement::Data
{
   Data(QUuid id)
   : identifier(id)
   , isDisposed(false)
   , owner(nullptr)
   , project(nullptr)
   , refCount(0)
   {}

   QUuid                    identifier;
   bool                     isDisposed;
   QString                  keywords;
   QList<UmlLinkPtr>        links;
   UmlCompositeElement*     owner;
   UmlProject*              project;
   QAtomicInteger<quint32>  refCount;
   QList<IElementObserver*> observers;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the UmlElement class with a new identifier.
 */
UmlElement::UmlElement()
: data(new Data(QUuid::createUuid()))
{
#ifdef _DEBUG
   ++cleanCount;
#endif
}

/**
 * Initializes a new object of the UmlElement class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new object with a new unique identifier, use constructor UmlElement() instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlElement::UmlElement(QUuid id)
: data(new Data(id))
{
#ifdef _DEBUG
   ++cleanCount;
#endif
}

UmlElement::~UmlElement()
{
   Q_ASSERT_X(data->isDisposed, "destructor", "UmlElement not disposed!");
   delete data;

#ifdef _DEBUG
   --cleanCount;
#endif
}

/**
 * @fn UmlElement::className() const
 * @brief Gets the class name of the UmlElement object.
 * 
 * This abstract function must be implemented in derived classes. Return staticMetaObject::className() here.
 */

/**
 * Gets the name of the JSON file of the UmlElement object on disk.
 */
QString UmlElement::elementFile() const
{
   return project()->elementsFolder() + "/" + identifier().toString() + ".json";
}

/**
 * Gets the identifier of the UmlElement object.
 *
 * The identifier is used to uniquely identify a memory object in the project (both in memory and as a file). It is 
 * either created automatically on creation of a new object or on loading the object from a file. In either case it
 * cannot (and must not!) be modified afterwards.
 */
QUuid UmlElement::identifier() const
{
   return data->identifier;
}

/**
 * Gets keywords associated with the UmlElement object.
 *
 * Note: All keywords supported by ViraquchaUML can be found in file UmlKeywords.h
 */
QString UmlElement::keywords() const
{
   return data->keywords;
}

/**
 * Sets keywords associated with the UmlElement object.
 */
void UmlElement::setKeywords(QString value)
{
   data->keywords = value;
}

/**
 * Gets a value indicating whether the UmlElement object is hidden.
 *
 * This is a GUI feature. It may be used to hide some objects (e.g. links) from a tree view.
 * @returns Always false.
 */
bool UmlElement::isHidden() const
{
   return false;
}

/** Gets a value indicating whether the UmlElement object is a link. */
 bool UmlElement::isLink() const
 {
    return false;
 }

/**
 * Gets a copy of the list of links attached to the UmlElement object.
 */
QList<UmlLink*> UmlElement::links() const
{
   QList<UmlLink*> list;
   for (auto link : data->links)
   {
      list.append(link.pointee());
   }

   return list;
}

/**
 * Gets a pointer to the UmlProject object to which the UmlElement object is assigned to.
 */
UmlProject* UmlElement::project() const
{
   return data->project;
}

/**
 * Sets a pointer to the UmlProject object to which the UmlElement object is assigned to.
 *
 * This is automatically done by the insert functions of UmlProject. Do not call directly, especially do not set 
 * nullptr since this will yield undefined behavior!
 */
void UmlElement::setProject(UmlProject* value)
{
   data->project = value;
}

/** Gets the list of observers connected with the UmlElement object. */
QList<IElementObserver*>& UmlElement::observers() const
{
   return data->observers;
}

/**
 * Gets the owner of the UmlElement object.
 *
 * Implements the Composite Pattern. The owner is always an object of class UmlCompositeElement.
 */
UmlCompositeElement* UmlElement::owner() const
{
   return data->owner;
}

/**
 * Sets the owner of the UmlElement object.
 *
 * Implements the Composite Pattern. The owner must always be an object of class UmlCompositeElement or one of its 
 * derivatives. Note that the owner is set automatically by the insert functions of class UmlCompositeElement, so
 * there is no need to modify it further.
 */
void UmlElement::setOwner(UmlCompositeElement* value)
{
   data->owner = value;
}

/**
 * Copies properties to another UmlElement object of same class name.
 *
 * @param other Other UmlElement object to be copied to
 */
void UmlElement::copyTo(UmlElement* other)
{
   if (other != nullptr && className() == other->className())
   {
      QJsonObject obj;
      serialize(obj, false, true, KFileVersion);
      other->serialize(obj, true, true, KFileVersion);
   }
}

/**
 * Copies serialized properties of the UmlElement object to a byte array.
 *
 * This function can be used e.g. to store the UmlElement object as a serialized string on the Clipboard.
 * @param array QByteArray object to receive serialized properties
 */
void UmlElement::copyTo(QByteArray& array)
{
   QJsonObject obj;
   serialize(obj, false, true, KFileVersion);

   QJsonDocument doc(obj);
   array = doc.toJson(QJsonDocument::Compact);
}

/**
 * Disposes the UmlElement object.
 *
 * This function resets intrusive pointers and releases system resources owned by the object. It must be called before
 * deleting the object.
 */
void UmlElement::dispose()
{
   dispose(true);
}

/**
 * Attaches a UmlLink object to the UmlElement object.
 *
 * @param link UmlLink object to be attached.
 */
void UmlElement::linkto(UmlLink* link)
{
   if (link != nullptr && !isLinkedTo(link))
   {
      data->links.append(UmlLinkPtr(link));
   }
}

/**
 * Detaches a UmlLink object from the UmlElement object.
 *
 * @param link UmlLink object to be detached.
 */
void UmlElement::unlink(UmlLink* link)
{
   if (link != nullptr && isLinkedTo(link))
   {
      data->links.removeOne(UmlLinkPtr(link));
   }
}

/**
 * Checks whether a UmlLink object is already attached to the UmlElement object.
 *
 * @param link UmlLink object to be checked. Must not be nullptr.
 * @returns True, if the UmlLink object is already attached; false otherwise.
 */
bool UmlElement::isLinkedTo(UmlLink* link)
{
   Q_ASSERT(link != nullptr);
   for (auto current : data->links)
   {
      if (current.pointee() == link) return true;
   }

   return false;
}

/**
 * Serializes properties of the UmlElement object to a QJsonObject.
 *
 * Calls protected function serialize(QJsonObject&, bool, bool, int).
 * @param json QJsonObject object to be used for serialization.
 * @param read If true: reads from the QJsonObject; otherwise writes to the QJsonObject.
 * @param version Version of the JSON file format.
 */
void UmlElement::serialize(QJsonObject& json, bool read, int version)
{
   serialize(json, read, false, version);
}

/**
 * Increases reference count.
 *
 * Needed by template class IntrusivePtr, do not call directly!
 */
void UmlElement::incRefCount()
{
   ++(data->refCount);
}

/**
 * Decreases reference count. Deletes the object if reference count is null.
 *
 * Needed by template class IntrusivePtr, do not call directly!
 */
void UmlElement::decRefCount()
{
   if (data->refCount > 0) --(data->refCount);
   if (data->refCount == 0)
   {
      delete this;
   }
}

/**  
 * Gets the reference count.
 *
 * Can be used e.g. for debugging to check whether the object is about to be deleted. 
 */
quint32 UmlElement::refCount() const
{
   return data->refCount;
}

/**
 * Gets a string representation of the UmlElement object.
 *
 * This base implementation returns a concatenation of the class name and the identifier of the object. It may be 
 * overridden in derived classes to return e.g. the name of the memory object or a signature.
 */
QString UmlElement::toString() const
{
   return className() + " {" + identifier().toString() + "}";
}

/**
 * Disposes the UmlElement object.
 *
 * This function resets intrusive pointers and releases system resources owned by the object. It should not be called
 * directly, call function dispose() without parameters instead.<br/>
 * If called with parameter disposing = true, it also sends a notification to all observers connected with the object 
 * to inform them that it is disposed.<br/>
 * Must be overridden in derived classes, if further files or system resources shall be disposed.
 * @param disposing If true: function was called from within UmlProject::dispose(); otherwise false.
 */
void UmlElement::dispose(bool disposing)
{
   if (disposing)
   {
      send(EventType::ObjectReleased);

      // Do a lazy remove of the element file:
      if (project() != nullptr)
      {
         project()->removeFile(elementFile());
      }
   }

   data->links.clear();
   data->observers.clear();
   data->isDisposed = true;
}

/**
 * Serializes properties of the UmlElement object to a QJsonObject.
 *
 * The base implementation of this function serializes the class name and the identity of the object only. This allows
 * the reconstruction of the memory object from class information if no project file is available and can be used e.g.
 * for copy-paste between different projects.
 * @param json QJsonObject object to be used for serialization.
 * @param read If true: reads from the QJsonObject; otherwise writes to the QJsonObject.
 * @param flat If true: serializes only properties, no sub elements.
 * @param version Version of the JSON file format.
 */
void UmlElement::serialize(QJsonObject& json, bool read, bool flat, int version)
{
   if (read)
   {
      // Class name cannot be read, it is constant - see meta object!
      data->keywords = json[KPropKeywords].toString();
   }
   else
   {
      json[KPropClass] = className();
      json[KPropKeywords] = data->keywords;
   }
}

/**
 * Sends an event to all connected observers.
 *
 * @param type Event type to be sent to the observers.
 */
void UmlElement::send(EventType type)
{
   for (IElementObserver* observer : data->observers)
   {
      observer->notify(this, type);
   }
}
