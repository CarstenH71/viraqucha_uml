//---------------------------------------------------------------------------------------------------------------------
// UmlClassifier.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlClassifier.
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
#pragma once

#include "umlclassifiers_global.h"
#include "UmlAttribute.h"
#include "UmlOperation.h"
#include "UmlPort.h"

#include "../UmlCommon/UmlCompositeElement.h"
#include "../UmlCommon/ICompartmentProvider.h"
#include "../UmlCommon/INamedElement.h"
#include "../UmlCommon/IStereotypedElement.h"
#include "../UmlCommon/ITemplatableElement.h"

class UMLCLASSIFIERS_EXPORT UmlClassifier : public UmlCompositeElement,
   public ICompartmentProvider,
   public INamedElement,
   public IStereotypedElement,
   public ITemplatableElement
{
   Q_GADGET
   typedef UmlCompositeElement super;
public: // Constructors
   UmlClassifier();
   UmlClassifier(QUuid id);
   virtual ~UmlClassifier();

public: // Attributes
   QString name() const override;
   void setName(QString value) override;

   QString comment() const override;
   void setComment(QString value) override;

   VisibilityKind visibility() const override;
   void setVisibility(VisibilityKind value) override;

   QString stereotype() const override;
   void setStereotype(QString value) override;

   QString language() const;
   void setLanguage(QString value);

   QList<UmlAttribute*> attributes() const;
   QList<UmlOperation*> operations() const;

   QList<UmlTemplateBinding*> templateBindings() const override;
   QList<UmlTemplateParameter*> templateParameter() const override;
   bool isTemplated() const override;

   bool isAbstract() const;
   void isAbstract(bool value);

   bool isFinal() const;
   void isFinal(bool value);

   bool isLeaf() const;
   void isLeaf(bool value);

   QVector<Compartment*> compartments() override;

public: // Methods
   void clearAttributes();
   void clearOperations();

   void append(UmlTemplateParameter* par) override;
   void remove(UmlTemplateParameter* par) override;
   void clearTemplate() override;

   void update(int index, Compartment* comp) override;

   QString toString() const override;

protected:
   void dispose(bool disposing) override;
   void serialize(QJsonObject& json, bool read, bool flat, int version) override;

private: // Attributes
   /// @cond
   struct Data;
   Data* data;
   /// @endcond
};
