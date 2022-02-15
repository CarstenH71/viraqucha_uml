//---------------------------------------------------------------------------------------------------------------------
// UmlLink.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlLink.
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
#include "UmlElement.h"
#include "IElementBuilder.h"
#include "IntrusivePtr.h"

class UMLCOMMON_EXPORT UmlLink : public UmlElement
{
   ///@cond
   Q_GADGET
   typedef UmlElement super;
   ///@endcond
public: // Constructors
   UmlLink();
   UmlLink(QUuid id);
   virtual ~UmlLink();

public: // Properties
   QString className() const override;

   UmlElement* source() const;
   void setSource(UmlElement* element);

   UmlElement* target() const;
   void setTarget(UmlElement* element);

   bool isHidden() const override;
   bool isLink() const override;

   virtual bool isDirected() const;
   virtual void swap();

public: // Methods
   void serialize(QJsonObject& json, bool read, int version) override;

protected:
   void dispose(bool disposing) override;

private: // Attributes
   ///@cond
   struct Data;
   Data* data;
   ///@endcond
};

typedef IntrusivePtr<UmlLink> UmlLinkPtr;
