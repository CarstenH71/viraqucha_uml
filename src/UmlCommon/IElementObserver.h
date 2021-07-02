//---------------------------------------------------------------------------------------------------------------------
// IElementObserver.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class IElementObserver.
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

#include "EventType.h"

class UmlElement;

/**
 * @class IElementObserver
 * @brief Interface of an element observer.
 * @since 1.0
 * @ingroup UmlCommon
 * 
 * The IElementObserver interface is used by UmlElement objects to inform attached observer about their lifetime. See
 * class UmlElement for a description and UmlDiagram for an example of such an observer.
 */
class IElementObserver
{
public:
   virtual ~IElementObserver() {}

public:
   virtual void notify(UmlElement* sender, EventType type) = 0;
};

