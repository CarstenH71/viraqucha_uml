//---------------------------------------------------------------------------------------------------------------------
// UmlOperation.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlOperation.
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
#include "CallConcurrencyKind.h"
#include "UmlParameter.h"

#include "../UmlCommon/UmlElement.h"
#include "../UmlCommon/IElementBuilder.h"
#include "../UmlCommon/INamedElement.h"
#include "../UmlCommon/IMultiplicityElement.h"
#include "../UmlCommon/IStereotypedElement.h"
#include "../UmlCommon/ITemplatableElement.h"

class UMLCLASSIFIERS_EXPORT UmlOperation : public UmlElement,
   public INamedElement,
   public IMultiplicityElement,
   public ITemplatableElement
{
   ///@cond
   Q_GADGET
   typedef UmlElement super;
   ///@endcond
public: // Constructors
   UmlOperation();
   UmlOperation(QUuid id);
   virtual ~UmlOperation();

public: // Properties
   QString className() const override;

   QString name() const override;
   void setName(QString value) override;

   QString comment() const override;
   void setComment(QString value) override;

   VisibilityKind visibility() const override;
   void setVisibility(VisibilityKind value) override;

   bool isOrdered() const override;
   void isOrdered(bool value) override;

   bool isUnique() const override;
   void isUnique(bool value) override;

   quint32 lower() const override;
   void setLower(quint32 value) override;

   quint32 upper() const override;
   void setUpper(quint32 value) override;

   QList<UmlTemplateBinding*> templateBindings() const override;
   QList<UmlTemplateParameter*> templateParameter() const override;
   bool isTemplated() const override;

   CallConcurrencyKind concurrency() const;
   void setConcurrency(CallConcurrencyKind value);

   bool isAbstract() const;
   void isAbstract(bool value);

   QString initCode() const;
   void setInitCode(QString value);

   QString returnType() const;
   void setReturnType(QString value);

   QList<UmlParameter*> parameter() const;
   QString signature() const;
   QString toString() const override;

public: // Methods
   void copyTo(UmlElement* other) override;
   void append(UmlParameter* par);
   void remove(UmlParameter* par);

   UmlParameter* findParameter(QString name);
   void clearParameter();

   void append(UmlTemplateParameter* par) override;
   void remove(UmlTemplateParameter* par) override;
   void clearTemplate() override;

protected:
   void serialize(QJsonObject& json, bool read, bool flat, int version) override;

private: // Attributes
   ///@cond
   struct Data;
   Data* data;
   ///@endcond
};

typedef IntrusivePtr<UmlOperation> UmlOperationPtr;
