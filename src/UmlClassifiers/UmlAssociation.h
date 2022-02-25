//---------------------------------------------------------------------------------------------------------------------
// UmlAssociation.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlAssociation.
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
#include "../UmlCommon/UmlLink.h"
#include "../UmlCommon/ILabelProvider.h"
#include "../UmlCommon/INamedElement.h"
#include "../UmlCommon/IStereotypedElement.h"

class AssociationEnd;

class UMLCLASSIFIERS_EXPORT UmlAssociation : public UmlLink,
   public ILabelProvider,
   public INamedElement,
   public IStereotypedElement
{
   ///@cond
   Q_GADGET
   typedef UmlLink super;
   ///@endcond
public: // Constructors
   UmlAssociation();
   UmlAssociation(QUuid id);
   virtual ~UmlAssociation();

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

   AssociationEnd& sourceEnd() const;
   AssociationEnd& targetEnd() const;

   bool isDerived() const;
   void isDerived(bool value);

   QVector<Label*> labels() override;

public: // Methods
   void update(int index, Label* label) override;

protected:
   void serialize(QJsonObject& json, bool read, bool flat, int version) override;

private: // Attributes
   ///@cond
   struct Data;
   Data* data;
   ///@endcond
};
