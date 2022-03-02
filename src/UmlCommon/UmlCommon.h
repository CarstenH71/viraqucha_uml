//---------------------------------------------------------------------------------------------------------------------
// UmlCommon.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : General include file for DLL/Shared Library UmlCommon
// Compiles with: MSVC 15.2 (2017) or newer (developed), GNU GCC 5.1 or newer (untested)
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

#include "Compartment.h"
#include "DiaNode.h"
#include "DiaEdge.h"
#include "Label.h"

#include "UmlComment.h"
#include "UmlCompositeElement.h"
#include "UmlDependency.h"
#include "UmlDiagram.h"
#include "UmlElement.h"
#include "UmlElementFactory.h"
#include "UmlKeywords.h"
#include "UmlLink.h"
#include "UmlModel.h"
#include "UmlNesting.h"
#include "UmlPackage.h"
#include "UmlParameterSubstitution.h"
#include "UmlProject.h"
#include "UmlRoot.h"
#include "UmlTemplateBinding.h"
#include "UmlTemplateParameter.h"

#include "NameBuilder.h"

/**
 * @defgroup UmlCommon
 * Provides the infrastructure of the ViraquchaUML data model.
 *
 * UmlCommon provides classes implementing the infrastructure for the remaining modules of the ViraquchaUML data model.
 * This includes the required base classes, as well as some general derivatives thereof, and the project management (in
 * particular the serialization of the data). The module also contains the elements summarized in the UML specification
 * in chapter 7, "Common Structure" and chapter 12, "Packages".
 */

void UMLCOMMON_EXPORT initCommon();
