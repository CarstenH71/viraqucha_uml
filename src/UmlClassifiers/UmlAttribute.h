//---------------------------------------------------------------------------------------------------------------------
// UmlAttribute.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlAttribute.
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
#include "IProperty.h"

#include "../UmlCommon/UmlElement.h"
#include "../UmlCommon/IElementBuilder.h"

class UMLCLASSIFIERS_EXPORT UmlAttribute : public UmlElement, public IProperty
{
   Q_GADGET
   typedef UmlElement super;
public: // Constructors
   UmlAttribute();
   UmlAttribute(QUuid id);
   virtual ~UmlAttribute();

public: // Properties
   QString className() const override;

   QString name() const override;
   void setName(QString value) override;

   QString comment() const override;
   void setComment(QString value) override;

   VisibilityKind visibility() const override;
   void setVisibility(VisibilityKind value) override;

   QString stereotype() const override;
   void setStereotype(QString value) override;

   bool isOrdered() const override;
   void isOrdered(bool value) override;

   bool isUnique() const override;
   void isUnique(bool value) override;

   quint32 lower() const override;
   void setLower(quint32 value) override;

   quint32 upper() const override;
   void setUpper(quint32 value) override;

   AggregationKind aggregation() const override;
   void setAggregation(AggregationKind value) override;

   bool isComposite() const override;
   void isComposite(bool value) override;

   bool isDerived() const override;
   void isDerived(bool value) override;

   bool isDerivedUnion() const override;
   void isDerivedUnion(bool value) override;

   bool isID() const override;
   void isID(bool value) override;

   bool isStatic() const override;
   void isStatic(bool value) override;

   bool isReadOnly() const override;
   void isReadOnly(bool value) override;

   QString type() const override;
   void setType(QString value) override;

   QString defaultValue() const;
   void setDefaultValue(QString value);

   QString signature() const;
   QString toString() const override;

protected: // Methods
   void serialize(QJsonObject& json, bool read, bool flat, int version) override;

private: // Attributes
   struct Data;
   Data* data;
};

typedef IntrusivePtr<UmlAttribute> UmlAttributePtr;
