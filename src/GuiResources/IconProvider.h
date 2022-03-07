//---------------------------------------------------------------------------------------------------------------------
// IconProvider.h
//
// Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class IconProvider.
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

#include <QIcon>
#include <QVector>

enum class IconSize
{
   Small,
   Medium,
   Big
};

class IconProvider final
{
private: // Constructors
   IconProvider();

public:
   /// @cond
   IconProvider(IconProvider const&) = delete;
   void operator=(IconProvider const&) = delete;
   /// @endcond
   virtual ~IconProvider();

private: // Methods
   static IconProvider& instance();
   int indexOf(QString name) const;
   QString resourceAt(int index, IconSize size) const;

public:
   static QIcon getIcon(QString name, IconSize size = IconSize::Small);
   static QPixmap getPixmap(QString name, IconSize size = IconSize::Small);

private: // Attributes
   ///@cond
   struct Item;
   QVector<Item*> _items;
   ///@endcond
};
