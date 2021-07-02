//---------------------------------------------------------------------------------------------------------------------
// UmlOperation.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlOperation.
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
#include "UmlOperation.h"
#include "PropertyStrings.h"
#include "SignatureChars.h"
#include "SignatureTools.h"

#include "../UmlCommon/UmlTemplateBinding.h"
#include "../UmlCommon/UmlTemplateParameter.h"
#include "../UmlCommon/PropertyStrings.h"

#include <QJsonArray>
#include <QTextStream>

/**
 * @class UmlOperation
 * @brief The UmlOperation class stores information about an operation of a UML classifier.
 * @since 1.0
 * @ingroup UmlClassifiers
 *
 * In the ViraquchaUML datamodel an operation is defined as an element without child elements. Since it is an element, 
 * it can be referenced by other elements in the datamodel.
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct UmlOperation::Data
{
   Data()
   : visibility(VisibilityKind::Public)
   , isAbstract(false)
   , isOrdered(false)
   , isUnique(false)
   , lower(1)
   , upper(1)
   , concurrency(CallConcurrencyKind::Undefined)
   , isQuery(false)
   , isStatic(false)
   {}

   QString                        name;
   QString                        comment;
   VisibilityKind                 visibility;
   bool                           isAbstract;
   bool                           isOrdered;
   bool                           isUnique;
   quint32                        lower;
   quint32                        upper;
   CallConcurrencyKind            concurrency;
   bool                           isQuery;
   bool                           isStatic;
   QString                        initCode;
   QString                        returnType;
   QList<UmlParameterPtr>         parameter;
   QList<UmlTemplateParameterPtr> templParams;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the UmlDiagram class.
 */
UmlOperation::UmlOperation()
: data(new Data())
{
}

/**
 * Initializes a new instance of the UmlOperation class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new instance with a new unique identifier, use constructor UmlOperation() instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlOperation::UmlOperation(QUuid id)
: super(id)
, data(new Data())
{
}

UmlOperation::~UmlOperation()
{
   delete data;
}

QString UmlOperation::className() const
{
   return staticMetaObject.className();
}

/**
 * Gets the name of the operation.
 */
QString UmlOperation::name() const
{
   return data->name;
}

/**
 * Sets the name of the operation.
 */
void UmlOperation::setName(QString value)
{
   data->name = value;
}

/**
 * Gets the comment of the operation.
 */
QString UmlOperation::comment() const
{
   return data->comment;
}

/**
 * Sets the comment of the operation.
 */
void UmlOperation::setComment(QString value)
{
   data->comment = value;
}

/**
 * Gets the visibility of the operation.
 */
VisibilityKind UmlOperation::visibility() const
{
   return data->visibility;
}

/**
 * Sets the visibility of the operation.
 */
void UmlOperation::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

/**
 * Gets a value indicating whether the collection of values of the multiplicity element is unique.
 */
bool UmlOperation::isOrdered() const
{
   return data->isOrdered;
}

/**
 * Sets a value indicating whether the collection of values of the multiplicity element is unique.
 */
void UmlOperation::isOrdered(bool value)
{
   data->isOrdered = value;
}

/**
 * Gets a value indicating whether the collection of values of the multiplicity element is unique.
 *
 * Unique means that the collection does not contain any duplicate values.
 */
bool UmlOperation::isUnique() const
{
   return data->isUnique;
}

/**
 * Sets a value indicating whether the collection of values of the multiplicity element is unique.
 */
void UmlOperation::isUnique(bool value)
{
   data->isUnique = value;
}

/**
 * Gets the lower bound of the multiplicity of the operation.
 */
quint32 UmlOperation::lower() const
{
   return data->lower;
}

/**
 * Sets the lower bound of the multiplicity of the operation.
 */
void UmlOperation::setLower(quint32 value)
{
   data->lower = value;
}

/**
 * Gets the upper bound of the multiplicity of the operation.
 */
quint32 UmlOperation::upper() const
{
   return data->upper;
}

/**
 * Sets the upper bound of the multiplicity of the operation.
 */
void UmlOperation::setUpper(quint32 value)
{
   data->upper = value;
}

/**
 * Gets the list of template bindings.
 */
QList<UmlTemplateBinding*> UmlOperation::templateBindings() const
{
   QList<UmlLink*> temp = links();
   QList<UmlTemplateBinding*> result;

   QListIterator<UmlLink*> iter(temp);
   while (iter.hasNext())
   {
      auto* bind = dynamic_cast<UmlTemplateBinding*>(iter.next());
      if (bind != nullptr)
      {
         result.append(bind);
      }
   }

   return result;
}

/**
 * Gets the list of template parameters.
 */
QList<UmlTemplateParameter*> UmlOperation::templateParameter() const
{
   QList<UmlTemplateParameter*> list;
   QListIterator<UmlTemplateParameterPtr> iter(data->templParams);
   while (iter.hasNext()) list.append(iter.next().pointee());
   return list;
}

/**
 * Gets a value indicating whether the operation is templated.
 */
bool UmlOperation::isTemplated() const
{
   return data->templParams.size() != 0;
}

/**
 * Gets the concurrency kind of the operation.
 */
CallConcurrencyKind UmlOperation::concurrency() const
{
   return data->concurrency;
}

/**
 * Sets the concurrency kind of the operation.
 */
void UmlOperation::setConcurrency(CallConcurrencyKind value)
{
   data->concurrency = value;
}

/**
 * Gets a value indicating whether the operation is abstract.
 */
bool UmlOperation::isAbstract() const
{
   return data->isAbstract;
}

/**
 * Sets a value indicating whether the operation is abstract.
 */
void UmlOperation::isAbstract(bool value)
{
   data->isAbstract = value;
}

/**
 * Gets the initial code of the operation.
 */
QString UmlOperation::initCode() const
{
   return data->initCode;
}

/**
 * Sets the initial code of the operation.
 */
void UmlOperation::setInitCode(QString value)
{
   data->initCode = value;
}

/**
 * Gets the return type of the operation.
 */
QString UmlOperation::returnType() const
{
   return data->returnType;
}

/**
 * Sets the return type of the operation.
 */
void UmlOperation::setReturnType(QString value)
{
   data->returnType = value;
}

/**
 * Gets the list of parameters of the operation.
 */
QList<UmlParameter*> UmlOperation::parameter() const
{
   QList<UmlParameter*> list;
   QListIterator<UmlParameterPtr> iter(data->parameter);
   while (iter.hasNext()) list.append(iter.next().pointee());
   return list;
}

/**
 * Gets the signature of the operation.
 */
QString UmlOperation::signature() const
{
   QString result;
   QTextStream stream(&result);

   stream << toChar(visibility()) << ChSpace << name();
   if (isTemplated())
   {
      stream << ChLessr; //...TODO
   }
   stream << ChBrktO;

   bool first = true;
   auto iter = QListIterator<UmlParameterPtr>(data->parameter);
   while (iter.hasNext())
   {
      if (!first) stream << ChComma << ChSpace;
      first = false;

      stream << iter.next()->signature();
   }
   stream << ChBrktC << ChColon << ChSpace << returnType() << makeRange(lower(), upper());
   stream.flush();
   return result;
}

 QString UmlOperation::toString() const
 {
    return signature();
 }

/**
 * Appends a new parameter to the operation.
 */
void UmlOperation::append(UmlParameter* par)
{
   if (par != nullptr)
   {
      data->parameter.append(UmlParameterPtr(par));
   }
}

/**
 * Removes a parameter from the operation.
 */
void UmlOperation::remove(UmlParameter* par)
{
   if (par != nullptr)
   {
      data->parameter.removeOne(UmlParameterPtr(par));
   }
}

/**
 * Clears all parameter from the operation.
 */
void UmlOperation::clearParameter()
{
   data->parameter.clear();
}

/**
 * Appends a template parameter to the operation.
 * @param par UmlTemplateParameter instance to be added.
 */
void UmlOperation::append(UmlTemplateParameter* par)
{
   if (par != nullptr)
   {
      data->templParams.append(UmlTemplateParameterPtr(par));
   }
}

/**
 * Removes a template parameter from the operation.
 * @param par UmlTemplateParameter instance to be removed.
 */
void UmlOperation::remove(UmlTemplateParameter* par)
{
   if (par != nullptr)
   {
      data->templParams.removeOne(UmlTemplateParameterPtr(par));
   }
}

/**
 * Clears all template parameter from the operation.
 */
void UmlOperation::clearTemplate()
{
   data->templParams.clear();
}

/**
 * Disposes the operation.
 *
 * This function is called by UmlProject::dispose() to reset all intrusive pointers owned by the package. Do not call
 * it directly.
 */
void UmlOperation::dispose(bool disposing)
{
   clearParameter();
   clearTemplate();
   super::dispose(disposing);
}

/**
 * Serializes properties of the UmlOperation instance to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlOperation::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
   if (read)
   {
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->visibility = (VisibilityKind)json[KPropVisibility].toInt();
      data->isAbstract = json[KPropIsAbstract].toBool();
      data->isOrdered = json[KPropIsOrdered].toBool();
      data->isUnique = json[KPropIsUnique].toBool();
      data->lower = (quint32)json[KPropLower].toDouble();
      data->upper = (quint32)json[KPropUpper].toDouble();
      data->concurrency = (CallConcurrencyKind)json[KPropConcurrency].toInt();
      data->isQuery = json[KPropIsQuery].toBool();
      data->isStatic = json[KPropIsStatic].toBool();
      data->initCode = json[KPropInitCode].toString(); // TODO: Hier nur den Dateinamen ablegen, NICHT den Code!!
      data->returnType = json[KPropReturnType].toString();

      // Operation parameter:
      {
         auto array = json[KPropParameter].toArray();
         for (int index = 0; index < array.size(); ++index)
         {
            auto* par = new UmlParameter();
            auto  obj = array[index].toObject();
            par->serialize(obj, read, version);
            append(par);
         }
      }

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
      json[KPropIsAbstract] = data->isAbstract;
      json[KPropIsOrdered] = data->isOrdered;
      json[KPropIsUnique] = data->isUnique;
      json[KPropLower] = (double)data->lower;
      json[KPropUpper] = (double)data->upper;
      json[KPropConcurrency] = (int)data->concurrency;
      json[KPropIsQuery] = data->isQuery;
      json[KPropIsStatic] = data->isStatic;
      json[KPropInitCode] = data->initCode;  // TODO: Hier nur den Dateinamen ablegen, NICHT den Code!!
      json[KPropReturnType] = data->returnType;

      // Operation parameter:
      {
         QJsonArray array;
         QListIterator<UmlParameterPtr> iter(data->parameter);
         while (iter.hasNext())
         {
            QJsonObject obj;
            iter.next()->serialize(obj, read, version);
            array.append(obj);
         }
         json[KPropParameter] = array;
      }

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
