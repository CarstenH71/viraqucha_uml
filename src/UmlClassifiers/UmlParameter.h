//---------------------------------------------------------------------------------------------------------------------
// UmlParameter.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class UmlParameter.
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
#include "ParameterDirectionKind.h"
#include "ParameterEffectKind.h"

#include "../UmlCommon/IntrusivePtr.h"
#include "../UmlCommon/INamedElement.h"
#include "../UmlCommon/IMultiplicityElement.h"
#include "../UmlCommon/ISerializable.h"

class UMLCLASSIFIERS_EXPORT UmlParameter : public IMultiplicityElement, public ISerializable
{
public: // Constructors
   UmlParameter();
   virtual ~UmlParameter();

public: // Properties
   QString name() const;
   void setName(QString value);

   QString comment() const;
   void setComment(QString value);

   QString defaultValue() const;
   void setDefaultValue(QString value);

   ParameterDirectionKind direction() const;
   void setDirection(ParameterDirectionKind value);

   ParameterEffectKind effect() const;
   void setEffect(ParameterEffectKind value);

   bool isException() const;
   void isException(bool value);

   bool isStream() const;
   void isStream(bool value);

   QString type() const;
   void setType(QString value);

   bool isOrdered() const override;
   void isOrdered(bool value) override;

   bool isUnique() const override;
   void isUnique(bool value) override;

   quint32 lower() const override;
   void setLower(quint32 value) override;

   quint32 upper() const override;
   void setUpper(quint32 value) override;

   QString signature() const;

public: // Methods
   void serialize(QJsonObject& json, bool read, int version) override;

   void incRefCount();
   void decRefCount();
   quint32 refCount() const;

public: // Attributes
   ///@cond
   struct Data;
   Data* data;
   ///@endcond
};

typedef IntrusivePtr<UmlParameter> UmlParameterPtr;
