//---------------------------------------------------------------------------------------------------------------------
// ParameterDirectionKind.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of enum class ParameterDirectionKind.
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
 * @enum ParameterDirectionKind
 * @brief Denotes the parameter direction kind of a parameter of an operation.
 * @since 0.1.0
 * @ingroup UmlClassifiers
 */
enum class ParameterDirectionKind
{
   Undefined = 0, /**< Direction is undefined */
   In,            /**< Parameter goes in only (does not affect the caller) */
   InOut,         /**< Parameter goes in and out (affects the caller) */
   Out,           /**< Parameter goes out only (affects the caller) */
  Return          /**< Parameter is a return value */
};
