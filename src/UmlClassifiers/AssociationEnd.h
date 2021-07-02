//---------------------------------------------------------------------------------------------------------------------
// AssociationEnd.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class AssociationEnd.
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

#include <QJsonObject>

class UmlAttribute;
class UmlProject;

class UMLCLASSIFIERS_EXPORT AssociationEnd : public IProperty
{
public: // Constructors
   AssociationEnd();
   virtual ~AssociationEnd();

public: // Properties
   virtual QString name() const override;
   virtual void setName(QString value) override;

   virtual QString comment() const override;
   virtual void setComment(QString value) override;

   virtual VisibilityKind visibility() const override;
   virtual void setVisibility(VisibilityKind value) override;

   virtual bool isOrdered() const override;
   virtual void isOrdered(bool value) override;

   virtual bool isUnique() const override;
   virtual void isUnique(bool value) override;

   virtual quint32 lower() const override;
   virtual void setLower(quint32 value) override;

   virtual quint32 upper() const override;
   virtual void setUpper(quint32 value) override;

   virtual QString stereotype() const override;
   virtual void setStereotype(QString value) override;

   virtual AggregationKind aggregation() const override;
   virtual void setAggregation(AggregationKind value) override;

   virtual bool isComposite() const override;
   virtual void isComposite(bool value) override;

   virtual bool isDerived() const override;
   virtual void isDerived(bool value) override;

   virtual bool isDerivedUnion() const override;
   virtual void isDerivedUnion(bool value) override;

   virtual bool isID() const override;
   virtual void isID(bool value) override;

   virtual bool isStatic() const override;
   virtual void isStatic(bool value) override;

   virtual bool isReadOnly() const override;
   virtual void isReadOnly(bool value) override;

   virtual QString type() const override;
   virtual void setType(QString value) override;

   UmlAttribute* attribute() const;
   void setAttribute(UmlAttribute* value);

   QList<UmlAttribute*> qualifiers() const;

public: // Methods
   void append(UmlAttribute* obj);
   void remove(UmlAttribute* obj);
   void clear();

   void serialize(QJsonObject& json, bool read, int version, UmlProject* project);

private: // Attributes
   struct Data;
   Data* data;
};

