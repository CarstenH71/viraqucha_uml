//---------------------------------------------------------------------------------------------------------------------
// UmlDependency.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlDependency.
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

#include "umlcommon_globals.h"

#include "UmlLink.h"
#include "IElementBuilder.h"
#include "INamedElement.h"
#include "ILabelProvider.h"
#include "IStereotypedElement.h"

class UMLCOMMON_EXPORT UmlDependency : public UmlLink, 
   public ILabelProvider,
   public INamedElement,
   public IStereotypedElement
{
   Q_GADGET
   typedef UmlLink super;
public: // Constructors
   UmlDependency();
   UmlDependency(QUuid id);
   virtual ~UmlDependency();

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

   bool isDirected() const override;

   QVector<Label*> labels() override;

public: // Methods
   void serialize(QJsonObject& json, bool read, int version) override;
   void update(int index, Label* label) override;

private: // Attributes
   struct Data;
   Data* data;
};
