//---------------------------------------------------------------------------------------------------------------------
// UmlPackage.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class UmlPackage.
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
#include "UmlPackage.h"
#include "UmlDiagram.h"
#include "UmlLink.h"
#include "UmlTemplateBinding.h"
#include "UmlTemplateParameter.h"

#include "Compartment.h"
#include "PropertyStrings.h"
#include "TextBox.h"

#include <QJsonArray>

/**
 * @class UmlPackage
 * @brief The UmlPackage class models a UML package in the UML database.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * The UmlPackage class represents a package in the data model. In UML, packages are used to structure systems and 
 * organize modeling concepts. The UmlPackage class therefore corresponds to the "Package" modeling concept in the UML 
 * specification and performs the same tasks.
 *
 * Because objects of the UmlPackage class can have child objects, the class is derived from UmlCompositeElement. It 
 * also implements the interfaces INamedElement (with which it has a name, visibility in the system and a comment) and 
 * ITemplateableElement (which gives it the ability to serve as a template for further modeling concepts). 
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct UmlPackage::Data
{
   Data()
   : visibility(VisibilityKind::Public)
   {}

   QString                        name;
   QString                        comment;
   VisibilityKind                 visibility;
   QString                        uri;
   QList<UmlTemplateParameterPtr> templParams;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new object of the UmlPackage class with a new identifier.
 */
UmlPackage::UmlPackage()
: data(new Data())
{
}

/**
 * Initializes a new object of the UmlPackage class with an existing identifier.
 *
 * This constructor is used by serialization and the unit tests. It does not create a new identifier but uses the given
 * one. To create a new object with a new unique identifier, use the constructor without parameters instead.
 * @param id Identifier read from serialization or passed in by unit tests.
 */
UmlPackage::UmlPackage(QUuid id)
: super(id)
, data(new Data())
{
}

UmlPackage::~UmlPackage()
{
   delete data;
}

QString UmlPackage::className() const
{
   return staticMetaObject.className();
}

/**
 * Gets the name of the package.
 */
QString UmlPackage::name() const
{
   return data->name;
}

/**
 * Sets the name of the package.
 * @param value Name to be set.
 */
void UmlPackage::setName(QString value)
{
   data->name = value;
}

/**
 * Gets the comment of the package.
 */
QString UmlPackage::comment() const
{
   return data->comment;
}

/**
 * Sets the comment of the package.
 * @param value Comment to be set.
 */
void UmlPackage::setComment(QString value)
{
   data->comment = value;
}

/**
 * Gets the visibility of the package.
 */
VisibilityKind UmlPackage::visibility() const
{
   return data->visibility;
}

/**
 * Sets the visibility of the package.
 * @param value VisibilityKind to be set.
 */
void UmlPackage::setVisibility(VisibilityKind value)
{
   data->visibility = value;
}

/**
 * Gets the URI of the package.
 */
QString UmlPackage::uri() const
{
   return data->uri;
}

/**
 * Sets the URI of the package.
 * @param value URI to be set.
 */
void UmlPackage::setUri(QString value)
{
   data->uri = value;
}

/**
 * Gets a list of template bindings of the templated package.
 * @returns A list of UmlTemplateBinding objects.
 */
QList<UmlTemplateBinding*> UmlPackage::templateBindings() const
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
 * Gets a list of template parameter of the templated package.
 * @returns A list of UmlTemplateParameter objects.
 */
QList<UmlTemplateParameter*> UmlPackage::templateParameter() const
{
   QList<UmlTemplateParameter*> list;
   QListIterator<UmlTemplateParameterPtr> iter(data->templParams);
   while (iter.hasNext()) list.append(iter.next().pointee());
   return list;

}

/**
 * Gets a value indicating whether the package is templated or not.
 *
 * A package is templated if at least one template parameter for the package is defined.
 */
bool UmlPackage::isTemplated() const
{
   return data->templParams.size() != 0;
}

/**
 * Appends a template parameter to the package.
 * @param par UmlTemplateParameter object to be added.
 */
void UmlPackage::append(UmlTemplateParameter* par)
{
   if (par != nullptr)
   {
      data->templParams.append(UmlTemplateParameterPtr(par));
   }
}

/**
 * Removes a template parameter from the package.
 * @param par UmlTemplateParameter object to be removed.
 */
void UmlPackage::remove(UmlTemplateParameter* par)
{
   if (par != nullptr)
   {
      data->templParams.removeOne(UmlTemplateParameterPtr(par));
   }
}

/**
 * Clears all template parameter from the package.
 */
void UmlPackage::clearTemplate()
{
   data->templParams.clear();
}

/**
 * Disposes the package.
 *
 * This function is called by UmlProject::dispose() to reset all intrusive pointers owned by the package. Do not call
 * it directly.
 */
void UmlPackage::dispose(bool disposing)
{
   clearTemplate();
   super::dispose(disposing);
}

/**
 * Serializes properties of the UmlPackage object to a JSON file.
 *
 * @param json JSON object to be serialized to.
 * @param read True if reading, otherwise writing.
 * @param version File version number of the ViraquchaUML project.
 */
void UmlPackage::serialize(QJsonObject& json, bool read, int version)
{
   super::serialize(json, read, version);
   if (read)
   {
      data->name = json[KPropName].toString();
      data->comment = json[KPropComment].toString();
      data->visibility = (VisibilityKind)json[KPropVisibility].toInt();
      data->uri = json[KPropURI].toString();

      auto array = json[KPropTemplParam].toArray();
      for (int index = 0; index < array.size(); ++index)
      {
         auto* par = new UmlTemplateParameter();
         auto  obj = array[index].toObject();
         par->serialize(obj, read, version);
         append(par);
      }
   }
   else
   {
      json[KPropName] = data->name;
      json[KPropComment] = data->comment;
      json[KPropVisibility] = (double)data->visibility;
      json[KPropURI] = data->uri;

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

/**
 * Gets a vector of compartments needed for diagrams.
 */
QVector<Compartment*> UmlPackage::compartments()
{
   Compartment* com = new Compartment();
   com->setName("name");
   com->isHidden(false);
   com->addLine(name(), true, false, false, AlignmentFlag::AlignCenter);

   QVector<Compartment*> vec;
   vec.append(com);
   return vec;
}

/**
 * Updates the lines of a compartment.
 * @param comp Compartment to be updated.
 */
void UmlPackage::update(int index, Compartment* comp)
{
   Q_UNUSED(index);
   
   if (comp == nullptr) return;

   auto lns = comp->lines();
   if (comp->name() == "name" && lns.size() != 0)
   {
      lns[0]->setText(name());
   }
}

QString UmlPackage::toString() const
{
   return data->name;
}
