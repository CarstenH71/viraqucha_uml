//---------------------------------------------------------------------------------------------------------------------
// UmlClassifier.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlClassifier.
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
#include "UmlClassifier.h"
#include "PropertyStrings.h"

#include "../UmlCommon/Compartment.h"
#include "../UmlCommon/PropertyStrings.h"
#include "../UmlCommon/SignatureChars.h"
#include "../UmlCommon/SignatureTools.h"
#include "../UmlCommon/TextBox.h"
#include "../UmlCommon/UmlTemplateBinding.h"
#include "../UmlCommon/UmlTemplateParameter.h"

#include <QJsonArray>
#include <QList>
#include <QString>
#include <QTextStream>

/**
 * @class UmlClassifier
 * @brief The UmlClassifier class is the base class of all classifier elements in the ViraquchaUML database.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 * UmlClassifier is the base class for all classes that store properties of UML Classifier elements in the database. It
 * also provides a default implementation of the ICompartmentProvider interface with four default compartments named
 * &quot;name&quot;, &quot;attributes&quot;, &quot;operations&quot; and &quot;receptions&quot;.
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct UmlClassifier::Data
{
   Data()
   : visibility(VisibilityKind::Public)
   , isAbstract(false)
   , isFinal(false)
   , isLeaf(false)
   {}

   QString                        name;
   QString                        comment;
   VisibilityKind                 visibility;
   QString                        stereotype;
   QList<UmlTemplateParameterPtr> templParams;
   bool                           isAbstract;
   bool                           isFinal;
   bool                           isLeaf;
   QString                        language;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlClassifier class.
 */
UmlClassifier::UmlClassifier()
: data(new Data())
{
}

/**
 * Initializes a new instance of the UmlClassifier class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlClassifier() instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlClassifier::UmlClassifier(QUuid id)
: super(id)
, data(new Data())
{
}

UmlClassifier::~UmlClassifier()
{
   delete data;
}

/** Gets the name of the classifier. */
QString UmlClassifier::name() const
{
   return data->name;
}

/** Sets the name of the classifier. */
void UmlClassifier::setName(QString value)
{
   data->name = value;
}

/** Gets the comment of the classifier. */
QString UmlClassifier::comment() const
{
   return data->comment;
}

/** Sets the comment of the classifier. */
void UmlClassifier::setComment(QString value)
{
   data->comment = value;
}

/** Gets the visibility of the classifier. */
VisibilityKind UmlClassifier::visibility() const
{
   return data->visibility;
}

/** Sets the visibility of the classifier. */
void UmlClassifier::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

/** Gets the stereotype of the classifier. */
QString UmlClassifier::stereotype() const
{
   return data->stereotype;
}

/** Sets the stereotype of the classifier. */
void UmlClassifier::setStereotype(QString value)
{
   data->stereotype = value;
}

/** Gets the programming language of the classifier. */
QString UmlClassifier::language() const
{
   return data->language;
}

/** Sets the programming language of the classifier. */
void UmlClassifier::setLanguage(QString value)
{
   data->language = value;
}

/** Gets a list of attributes of the classifier. */
QList<UmlAttribute*> UmlClassifier::attributes() const
{
   QList<UmlAttribute*> list;
   
   QList<UmlElement*> temp = elements();
   QListIterator<UmlElement*> iter(temp);
   while (iter.hasNext())
   {
      auto* obj = dynamic_cast<UmlAttribute*>(iter.next());
      if (obj != nullptr)
      {
         list.append(obj);
      }
   }

   return list;
}

/** Gets a list of operations of the classifier. */
QList<UmlOperation*> UmlClassifier::operations() const
{
   QList<UmlOperation*> list;

   QList<UmlElement*> temp = elements();
   QListIterator<UmlElement*> iter(temp);
   while (iter.hasNext())
   {
      auto* obj = dynamic_cast<UmlOperation*>(iter.next());
      if (obj != nullptr)
      {
         list.append(obj);
      }
   }

   return list;
}

/** Gets a list of template bindings of the classifier. */
QList<UmlTemplateBinding*> UmlClassifier::templateBindings() const
{
   QList<UmlTemplateBinding*> list;

   QList<UmlLink*> temp = links();
   QListIterator<UmlLink*> iter(temp);
   while (iter.hasNext())
   {
      auto* obj = dynamic_cast<UmlTemplateBinding*>(iter.next());
      if (obj != nullptr)
      {
         list.append(obj);
      }
   }

   return list;
}

/** Gets a list of template parameter of the classifier. */
QList<UmlTemplateParameter*> UmlClassifier::templateParameter() const
{
   QList<UmlTemplateParameter*> list;
   QListIterator<UmlTemplateParameterPtr> iter(data->templParams);
   while (iter.hasNext()) list.append(iter.next().pointee());
   return list;
}

/** Gets a value indicating whether the classifier is templated. */
bool UmlClassifier::isTemplated() const
{
   return data->templParams.size() != 0;
}

/** Gets a value indicating whether the classifier is abstract. */
bool UmlClassifier::isAbstract() const
{
   return data->isAbstract;
}

/** Sets a value indicating whether the classifier is abstract. */
void UmlClassifier::isAbstract(bool value)
{
   data->isAbstract = value;
}

/** Gets a value indicating whether the classifier is finally specified. */
bool UmlClassifier::isFinal() const
{
   return data->isFinal;
}

/** Sets a value indicating whether the classifier is finally specified. */
void UmlClassifier::isFinal(bool value)
{
   data->isFinal = value;
}

/** Gets a value indicating whether the classifier is a leaf. */
bool UmlClassifier::isLeaf() const
{
   return data->isLeaf;
}

/** Sets a value indicating whether the classifier is a leaf. */
void UmlClassifier::isLeaf(bool value)
{
   data->isLeaf = value;
}

/**
 * Initially creates the vector of compartments for this classifier.
 *
 * A classifier has at least 4 compartments: name, attributes, operations, receptions. On creation of the vector, only
 * name, attributes and operations compartments are visible. All other compartments are hidden.
 */
QVector<Compartment*> UmlClassifier::compartments()
{
   QVector<Compartment*> result(4);
   result[0] = new Compartment();
   result[0]->setName("name");
   result[1] = new Compartment();
   result[1]->setName("attributes");
   result[2] = new Compartment();
   result[2]->setName("operations");
   result[3] = new Compartment();
   result[3]->setName("receptions");
   result[3]->isHidden(true);
   for (int index = 0; index < result.length(); ++index)
   {
      update(index, result[index]);
   }

   return result;
}

/** Clears all attributes from the classifier. */
void UmlClassifier::clearAttributes()
{
   QList<UmlElement*> list = elements();
   QListIterator<UmlElement*> iter(list);
   while (iter.hasNext())
   {
      auto* elem = iter.next();
      if (elem->className() == UmlAttribute::staticMetaObject.className())
      {
         super::remove(elem);
      }
   }
}

/** Clears all operations from the classifier. */
void UmlClassifier::clearOperations()
{
   QList<UmlElement*> list = elements();
   QListIterator<UmlElement*> iter(list);
   while (iter.hasNext())
   {
      auto* elem = iter.next();
      if (elem->className() == UmlOperation::staticMetaObject.className())
      {
         super::remove(elem);
      }
   }
}

/** Appends a template parameter to the classifier. */
void UmlClassifier::append(UmlTemplateParameter* par)
{
   if (par != nullptr)
   {
      data->templParams.append(UmlTemplateParameterPtr(par));
   }
}

/** Removes a template parameter from the classifier. */
void UmlClassifier::remove(UmlTemplateParameter* par)
{
   if (par != nullptr)
   {
      data->templParams.removeOne(UmlTemplateParameterPtr(par));
   }
}

/** Clears all template parameter from the classifier. */
void UmlClassifier::clearTemplate()
{
   data->templParams.clear();
}

/**
 * Disposes the classifier.
 *
 * This function resets intrusive pointers and releases system resources owned by the object. It should not be called
 * directly, call function dispose() without parameters instead.
 */
void UmlClassifier::dispose(bool disposing)
{
   clearTemplate();
   super::dispose(disposing);
}

/**
 * Serializes properties of the UmlClassifier object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlClassifier::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
   if (read)
   {
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->visibility = (VisibilityKind)json[KPropVisibility].toInt();
      data->stereotype = json[KPropStereotype].toString();
      data->isAbstract = json[KPropIsAbstract].toBool();
      data->isFinal = json[KPropIsFinal].toBool();
      data->isLeaf = json[KPropIsLeaf].toBool();
      data->language = json[KPropLanguage].toString();

      // Template parameter:
      {
         auto array = json[KPropTemplParam].toArray();
         for (int index = 0; index < array.size(); ++index)
         {
            auto* par = new UmlTemplateParameter();
            auto  obj = array[index].toObject();
            par->serialize(obj, read, version);
            append(par);
         }
      }
   }
   else
   {
      json[KPropName] = data->name;
      json[KPropComment] = data->comment;
      json[KPropVisibility] = (int)data->visibility;
      json[KPropStereotype] = data->stereotype;
      json[KPropIsAbstract] = data->isAbstract;
      json[KPropIsFinal] = data->isFinal;
      json[KPropIsLeaf] = data->isLeaf;
      json[KPropLanguage] = data->language;

      // Template parameter:
      {
         QJsonArray array;
         QListIterator<UmlTemplateParameterPtr> iter(data->templParams);
         while (iter.hasNext())
         {
            QJsonObject obj;
            iter.next()->serialize(obj, read, version);
            array.append(obj);
         }
         json[KPropTemplParam] = array;
      }
   }
}

/** Returns a string representation of the classifier. */
QString UmlClassifier::toString() const
{
   return makeAnnotation(keywords(), stereotype()) + name();
}

/**
 * Updates a compartment by adding/modifying all text boxes.
 *
 * @param index Index of the compartment in the compartment vector returned by function compartments().
 * @param comp Pointer to the compartment to be updated.
 */
void UmlClassifier::update(int index, Compartment* comp)
{
   if (comp == nullptr) return;

   comp->clear();
   switch (index)
   {
   case 0: // Name compartment
   {
      QString ret = makeAnnotation(keywords(), stereotype());
      if (!ret.isEmpty())
      {
         comp->addLine(ret, false, false, false, AlignmentFlag::AlignCenter);
      }

      comp->addLine(name(), true, isAbstract(), false, AlignmentFlag::AlignCenter);
      break;
   }
   case 1: // Attributes compartment
   {
      auto list = attributes();
      auto iter = QListIterator<UmlAttribute*>(list);
      while (iter.hasNext())
      {
         comp->addLine(iter.next()->signature());
      }
      break;
   }
   case 2: // Operations compartment
   {
      auto list = operations();
      auto iter = QListIterator<UmlOperation*>(list);
      while (iter.hasNext())
      {
         auto oper = iter.next();
         comp->addLine(oper->signature(), false, oper->isAbstract());
      }
      break;
   }
   case 3: // Receptions compartment
   default:
      break;
   }
}
