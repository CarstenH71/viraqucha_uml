//---------------------------------------------------------------------------------------------------------------------
// IStereotypedElement.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of interface IStereotypedElement.
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
#include <QString>

/**
 * @class IStereotypedElement
 * @brief Inteface of a stereotyped element in the ViraquchaUML datamodel.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * The pure abstract IStereotypedElement class provides an interface for stereotyped elements in the ViraquchaUML datamodel.
 * In ViraquchaUML, a stereotype is a kind of keyword which can be specified by the user (in contrast to the UML keywords, 
 * which are fixed).
 */
class IStereotypedElement
{
public:
   virtual ~IStereotypedElement() {}

public: // Properties
   virtual QString stereotype() const = 0;
   virtual void setStereotype(QString value) = 0;
};
