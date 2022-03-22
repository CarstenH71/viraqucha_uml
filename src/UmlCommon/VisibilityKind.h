//---------------------------------------------------------------------------------------------------------------------
// VisibilityKind.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of enum class VisibilityKind.
// Compiles with: MSVC 15.2 (2017) or newer, GNU GCC 5.1 or newer
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This library is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
// * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
// * option) any later version.                                                                                      *
// *                                                                                                                 *
// * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
// * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
// * for more details.                                                                                               *
// *                                                                                                                 *
// * You should have received a copy of the GNU General Public License along with this library; if not, see          *
// * http://www.gnu.org/licenses/gpl                                                                                 *
// *                                                                                                                 *
// *******************************************************************************************************************
//
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#pragma once

/**
 * @enum VisibilityKind
 * @brief Denotes the visibility kind of a named element in the UML model.
 * @since 0.1.0
 * @ingroup UmlCommon
 */
enum class VisibilityKind
{
   Undefined = 0, /**< Undefined visibility. */
   Public,        /**< The element is visible for all other elements even in other packages. */
   Protected,     /**< The element is only visible in its owner element and all elements derived from the owner. */
   Private,       /**< The element is only visible in its owner element. */
   Package        /**< The element is visible in its owner element and all other elements in the same package. */
};
