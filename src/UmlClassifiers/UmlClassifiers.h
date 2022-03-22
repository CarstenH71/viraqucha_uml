//---------------------------------------------------------------------------------------------------------------------
// UmlClassifiers.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : General include file for DLL/Shared Library UmlClassifiers.
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

#include "umlclassifiers_global.h"

#include "UmlAssociation.h"
#include "UmlAttribute.h"
#include "UmlClassifier.h"
#include "UmlClass.h"
#include "UmlComponent.h"
#include "UmlDatatype.h"
#include "UmlGeneralization.h"
#include "UmlEnumeration.h"
#include "UmlInterface.h"
#include "UmlOperation.h"
#include "UmlParameter.h"
#include "UmlPort.h"
#include "UmlPrimitiveType.h"
#include "UmlRealization.h"
#include "UmlSignal.h"

/**
 * @defgroup UmlClassifiers
 * Provides classes for the Classification of elements of a system.
 *
 * UmlClassifiers contains the elements summarized in the UML specification in chapters 9 "Classification", 10 "Simple
 * Classifiers", and 11 "Structured Classifiers". Many of the classes defined here are reused and extended in the
 * following modules.
 *
 * TODO: Missing features are Collaborations and Receptions. Collaborations are of type Classifier, Receptions are of
 * type Feature (like an Operation, in fact they are a special kind of Operation called when a Class or Interface
 * receives a Signal). The corresponding classes (UmlCollaboration, UmlReception) need to be implemented.
 */

void UMLCLASSIFIERS_EXPORT initClassifiers();
