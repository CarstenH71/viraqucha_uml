//---------------------------------------------------------------------------------------------------------------------
// ITemplatableElement.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of interface ITemplatableElement.
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
#include <QList>

class UmlTemplateBinding;
class UmlTemplateParameter;

/**
 * @class ITemplatableElement
 * @brief Inteface of a templatable element in the UML model.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * The ITemplatableElement interface provides a data contract for templatable elements in the ViraquchaUML datamodel.
 */
class ITemplatableElement
{
public: // Constructors
   virtual ~ITemplatableElement() {}

public: // Properties
   virtual QList<UmlTemplateBinding*> templateBindings() const = 0;
   virtual QList<UmlTemplateParameter*> templateParameter() const = 0;
   virtual bool isTemplated() const = 0;

public: // Methods
   virtual void append(UmlTemplateParameter* par) = 0;
   virtual void remove(UmlTemplateParameter* par) = 0;
   virtual void clearTemplate() = 0;
};
