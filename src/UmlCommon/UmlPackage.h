//---------------------------------------------------------------------------------------------------------------------
// UmlPackage.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlPackage.
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
#include "UmlCompositeElement.h"

#include "ICompartmentProvider.h"
#include "IElementBuilder.h"
#include "INamedElement.h"
#include "ITemplatableElement.h"

#include <QString>
#include <QList>

class UmlDiagram;

class UMLCOMMON_EXPORT UmlPackage : public UmlCompositeElement,
   public ICompartmentProvider,
   public INamedElement,
   public ITemplatableElement
{
   ///@cond
   Q_GADGET
   typedef UmlCompositeElement super;
   ///@endcond
public: // Constructors
   UmlPackage();
   UmlPackage(QUuid id);
   virtual ~UmlPackage();

public: // Properties
   QString className() const override;

   QString name() const override;
   void setName(QString value) override;

   QString comment() const override;
   void setComment(QString value) override;

   VisibilityKind visibility() const override;
   void setVisibility(VisibilityKind value) override;

   QString uri() const;
   void setUri(QString value);

   QList<UmlTemplateBinding*> templateBindings() const override;
   QList<UmlTemplateParameter*> templateParameter() const override;
   bool isTemplated() const override;

public: // Methods
   void append(UmlTemplateParameter* par) override;
   void remove(UmlTemplateParameter* par) override;
   void clearTemplate() override;

   void serialize(QJsonObject& json, bool read, int version) override;

   QVector<Compartment*> compartments() override;
   void update(int index, Compartment* comp) override;

   QString toString() const override;

protected:
   void dispose(bool disposing) override;

private: // Attributes
   ///@cond
   struct Data;
   Data* data;
   ///@endcond
};
