//---------------------------------------------------------------------------------------------------------------------
// UmlCompositeElement.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlCompositeElement.
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

class UMLCOMMON_EXPORT UmlCompositeElement : public UmlElement
{
   /// @cond
   typedef UmlElement super;
   /// @endcond
public: // Constructors
   UmlCompositeElement();
   UmlCompositeElement(QUuid id);
   virtual ~UmlCompositeElement();

public: // Properties
   QList<UmlElement*> elements() const;
   bool empty() const;

public: // Methods
   virtual void append(UmlElement* elem);
   virtual void insert(int pos, UmlElement* elem);
   virtual void remove(UmlElement* elem);
   virtual void clear();
   
   virtual void moveUp(UmlElement* elem);
   virtual void moveDown(UmlElement* elem);
   
   int count(bool hidden = true);
   int indexOf(UmlElement* elem);
   UmlElement* at(int index);

   void serialize(QJsonObject& json, bool read, int version) override;

protected:
   void dispose(bool disposing) override;

private: // Attributes
   /// @cond
   struct Data;
   Data* data;
   /// @endcond
};
