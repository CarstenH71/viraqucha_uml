//---------------------------------------------------------------------------------------------------------------------
// UmlCommon.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Initialization routines for UmlCommon.
// Compiles with: MSVC 15.2 (2017) or newer (developed), GNU GCC 5.1 or newer (untested)
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

#include "UmlCommon.h"

bool isInitialized = false;

/**
 * @defgroup UmlCommon 
 * Provides the infrastructure of the ViraquchaUML data model.
 * 
 * UmlCommon provides classes implementing the infrastructure for the remaining modules of the ViraquchaUML data model. 
 * This includes the required base classes, as well as some general derivatives thereof, and the project management (in 
 * particular the serialization of the data). The module also contains the elements summarized in the UML specification 
 * in chapter 7, "Common Structure" and chapter 12, "Packages".
 */

///@cond
class UmlDependencyBuilder : public IElementBuilder
{
public:
   static QString className() { return QString(UmlDependency::staticMetaObject.className()); }
   UmlElement* build(QUuid id) override { return new UmlDependency(id); }
};

class UmlDiagramBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlDiagram(id); }
};

class UmlUsageBuilder : public IElementBuilder
{
public:
   static QString className() { return QString(UmlDependency::staticMetaObject.className()) + "::Usage"; }
   UmlElement* build(QUuid id) override
   {
      auto* elem = new UmlDependency(id);
      elem->setKeywords(KwdUse);
      return elem;
   }
};

class UmlAbstractionBuilder : public IElementBuilder
{
public:
   static QString className() { return QString(UmlDependency::staticMetaObject.className()) + "::Abstraction"; }
   UmlElement* build(QUuid id) override
   {
      auto* elem = new UmlDependency(id);
      elem->setKeywords(KwdAbstraction);
      return elem;
   }
};

class UmlCommentBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlComment(id); }
};

class UmlLinkBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlLink(id); }
};

class UmlModelBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlModel(id); }
};

class UmlNestingBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlNesting(id); }
};

class UmlPackageBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlPackage(id); }
};

class UmlTemplateBindingBuilder : public IElementBuilder
{
public:
   UmlElement* build(QUuid id) override { return new UmlTemplateBinding(id); }
};
///@endcond

/**
 * Initializes the UmlCommon library.
 * 
 * Call this function once to initialize the library and the factory method creating UmlElement instances.
 * @ingroup UmlCommon
 */
void initCommon()
{
   if (!isInitialized)
   {
      auto& factory = UmlElementFactory::instance();
      factory.subscribe(UmlAbstractionBuilder::className(), new UmlAbstractionBuilder());
      factory.subscribe(UmlComment::staticMetaObject.className(), new UmlCommentBuilder());
      factory.subscribe(UmlDependencyBuilder::className(), new UmlDependencyBuilder());
      factory.subscribe(UmlDiagram::staticMetaObject.className(), new UmlDiagramBuilder());
      factory.subscribe(UmlModel::staticMetaObject.className(), new UmlModelBuilder());
      factory.subscribe(UmlNesting::staticMetaObject.className(), new UmlNestingBuilder());
      factory.subscribe(UmlLink::staticMetaObject.className(), new UmlLinkBuilder());
      factory.subscribe(UmlPackage::staticMetaObject.className(), new UmlPackageBuilder());
      factory.subscribe(UmlTemplateBinding::staticMetaObject.className(), new UmlTemplateBindingBuilder());
      factory.subscribe(UmlUsageBuilder::className(), new UmlUsageBuilder());
      isInitialized = true;
   }
}
