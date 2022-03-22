//---------------------------------------------------------------------------------------------------------------------
// IProperty.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class IProperty.
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

#include "umlclassifiers_global.h"
#include "AggregationKind.h"

#include "../UmlCommon/INamedElement.h"
#include "../UmlCommon/IMultiplicityElement.h"
#include "../UmlCommon/IStereotypedElement.h"

/**
 * @class IProperty
 * @brief Inteface of a property in the UML model.
 * @since 0.1.0
 * @ingroup UmlClassifiers
 *
 * The IProperty class provides an interface for UML properties (attributes or association ends).
 */
class IProperty : public INamedElement, public IMultiplicityElement, public IStereotypedElement
{
public:
    virtual ~IProperty() {}

public:
    virtual AggregationKind aggregation() const = 0;
    virtual void setAggregation(AggregationKind value) = 0;

    virtual bool isComposite() const = 0;
    virtual void isComposite(bool value) = 0;
    
    virtual bool isDerived() const = 0;
    virtual void isDerived(bool value) = 0;

    virtual bool isDerivedUnion() const = 0;
    virtual void isDerivedUnion(bool value) = 0;

    virtual bool isID() const = 0;
    virtual void isID(bool value) = 0;

    // Feature
    virtual bool isStatic() const = 0;
    virtual void isStatic(bool value) = 0;
    
    // StructuralFeature
    virtual bool isReadOnly() const = 0;
    virtual void isReadOnly(bool value) = 0;

    // TypedElement
    virtual QString type() const = 0;
    virtual void setType(QString value) = 0;
};
