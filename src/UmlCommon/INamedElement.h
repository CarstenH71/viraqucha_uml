//---------------------------------------------------------------------------------------------------------------------
// INamedElement.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of interface INamedElement.
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
#include "VisibilityKind.h"

#include <QString>

/**
 * @class INamedElement
 * @brief Inteface of a named element in the ViraquchaUML datamodel.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * The pure abstract INamedElement class provides an interface for named elements in the ViraquchaUML datamodel. 
 * Named elements may be added to namespaces (like e.g. packages). 
 */
class INamedElement
{
public:
	virtual ~INamedElement() {}

public: // Properties
	virtual QString name() const = 0;
	virtual void setName(QString value) = 0;

	virtual QString comment() const = 0;
	virtual void setComment(QString value) = 0;

	virtual VisibilityKind visibility() const = 0;
	virtual void setVisibility(VisibilityKind value) = 0;
};
