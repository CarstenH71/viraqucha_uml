//---------------------------------------------------------------------------------------------------------------------
// StringProvider.cpp
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class StringProvider.
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

#include <QObject>
#include <QString>
#include <QStringList>

class StringProvider final : public QObject
{
   Q_OBJECT
private: // Constructors
   StringProvider();

public:
   /// @cond
   StringProvider(StringProvider const&) = delete;
   void operator=(StringProvider const&) = delete;
   /// @endcond
   virtual ~StringProvider();

private:
   static StringProvider& instance();

public: // Properties
   static QString defaultMultiplicity();
   static QString defaultPrimitiveType();

   static QStringList& aggregations();
   static QStringList& diagramTypes();
   static QStringList& directions();
   static QStringList& effects();
   static QStringList& languages();
   static QStringList& multiplicities();
   static QStringList& primitiveTypes();
   static QStringList& stereotypes();
   static QStringList& visibilities();

private: // Attributes
   /// @cond
   QStringList _aggregations;
   QStringList _diagramTypes;
   QStringList _directions;
   QStringList _effects;
   QStringList _languages;
   QStringList _multiplicities;
   QStringList _primitiveTypes;
   QStringList _stereotypes;
   QStringList _visibilities;
   /// @endcond
};
