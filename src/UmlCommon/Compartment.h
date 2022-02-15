//---------------------------------------------------------------------------------------------------------------------
// Compartment.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class Compartment.
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
#include "AlignmentKind.h"
#include "FormatKind.h"
#include "ISerializable.h"

#include <QVector>
using namespace Qt;

class TextBox;

class UMLCOMMON_EXPORT Compartment
{
public: // Constructors
   Compartment();
   virtual ~Compartment();

public: // Properties
   QString name() const;
   void setName(QString value);

   bool isHidden() const;
   void isHidden(bool value);

   quint64 flags() const;
   void setFlags(quint64 value);

   QVector<TextBox*> lines() const;

public: // Methods
   TextBox* addLine(QString text, bool bold = false, bool italic = false, bool underline = false, 
                    AlignmentFlag alignment = AlignmentFlag::AlignLeft);
   void append(TextBox* box);
   void remove(TextBox* box);
   void clear();

private: // Attributes
   ///@cond
   struct Data;
   Data* data;
   ///@endcond
};
