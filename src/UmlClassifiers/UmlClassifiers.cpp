//---------------------------------------------------------------------------------------------------------------------
// UmlClassifiers.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of initialization routines needed for the DLL/shared library.
// Compiles with: MSVC 15.2 (2017) or newer, GNU GCC 5.1 or newer
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This library is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
// * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
// * option) any later version.                                                                                      *
// *                                                                                                                 *
// * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
// * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
// * for more details.                                                                                               *
// *                                                                                                                 *
// * You should have received a copy of the GNU General Public License along with this library; if not, see          *
// * http://www.gnu.org/licenses/gpl                                                                                 *
// *                                                                                                                 *
// *******************************************************************************************************************
//
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#include "UmlClassifiers.h"
#include "../UmlCommon/UmlElementFactory.h"

#include "AssociationEnd.h"

static bool isInitialized = false;

/**
 * @defgroup UmlClassifiers
 * Provides classes for the Classification of elements of a system.
 * 
 * UmlClassifiers contains the elements summarized in the UML specification in chapters 9 "Classification", 10 "Simple
 * Classifiers", and 11 "Structured Classifiers". Many of the classes defined here are reused and extended in the
 * following modules.
 */

///@cond
class UmlAssociationBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlAssociation(id); }
};

class UmlAggregationBuilder : public IElementBuilder
{
public:
   static QString className() { return QString(UmlAssociation::staticMetaObject.className()) + "::Aggregation"; }
   UmlElement* build(QUuid id) override 
   {
      auto* elem = new UmlAssociation(id);
      elem->sourceEnd().setAggregation(AggregationKind::Shared);
      return elem;
   }
};

class UmlCompositionBuilder : public IElementBuilder
{
public:
   static QString className() { return QString(UmlAssociation::staticMetaObject.className()) + "::Composition"; }
   UmlElement* build(QUuid id) override
   {
      auto* elem = new UmlAssociation(id);
      elem->sourceEnd().setAggregation(AggregationKind::Composite);
      return elem;
   }
};

class UmlAttributeBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlAttribute(id); }
};

class UmlClassBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlClass(id); }
};

class UmlComponentBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlComponent(id); }
};

class UmlDatatypeBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlDatatype(id); }
};

class UmlEnumerationBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlEnumeration(id); }
};

class UmlGeneralizationBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlGeneralization(id); }
};

class UmlInterfaceBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlInterface(id); }
};

class UmlOperationBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlOperation(id); }
};

class UmlPortBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlPort(id); }
};

class UmlPrimitiveTypeBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlPrimitiveType(id); }
};

class UmlRealizationBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlRealization(id); }
};

class UmlSignalBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlSignal(id); }
};
///@endcond

/**
 * Initializes the UmlClassifiers library.
 *
 * Call this function once to initialize the library and the factory method creating UmlElement instances.
 * @ingroup UmlClassifiers
 */
void initClassifiers()
{
   if (!isInitialized)
   {
      auto& factory = UmlElementFactory::instance();
      factory.subscribe(UmlAssociation::staticMetaObject.className(), new UmlAssociationBuilder());
      factory.subscribe(UmlAggregationBuilder::className(), new UmlAggregationBuilder());
      factory.subscribe(UmlCompositionBuilder::className(), new UmlCompositionBuilder());
      factory.subscribe(UmlAttribute::staticMetaObject.className(), new UmlAttributeBuilder());
      factory.subscribe(UmlClass::staticMetaObject.className(), new UmlClassBuilder());
      factory.subscribe(UmlDatatype::staticMetaObject.className(), new UmlDatatypeBuilder());
      factory.subscribe(UmlEnumeration::staticMetaObject.className(), new UmlEnumerationBuilder());
      factory.subscribe(UmlGeneralization::staticMetaObject.className(), new UmlGeneralizationBuilder());
      factory.subscribe(UmlInterface::staticMetaObject.className(), new UmlInterfaceBuilder());
      factory.subscribe(UmlOperation::staticMetaObject.className(), new UmlOperationBuilder());
      factory.subscribe(UmlPrimitiveType::staticMetaObject.className(), new UmlPrimitiveTypeBuilder());
      factory.subscribe(UmlRealization::staticMetaObject.className(), new UmlRealizationBuilder());
      factory.subscribe(UmlSignal::staticMetaObject.className(), new UmlSignalBuilder());
      factory.subscribe(UmlPort::staticMetaObject.className(), new UmlPortBuilder());
      factory.subscribe(UmlComponent::staticMetaObject.className(), new UmlComponentBuilder());
   }
}
