//---------------------------------------------------------------------------------------------------------------------
// RoutingKind.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of enum RoutingKind.
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

/**
 * @enum RoutingKind
 * @brief Denotes the Routing kind of a DiaEdge.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * This enumeration is not UML specific. It is used with class DiaEdge to specify the kind of routing to be done for
 * the edge.
 */
enum class RoutingKind
{
   Auto,   /**< Automatic routing (edge is routed by the program) */
   Custom, /**< Custom routing (edge is routed by the user) */
   Direct  /**< Direct routing (edge is drawn straight from one DiaShape to another). */
};
