//---------------------------------------------------------------------------------------------------------------------
// ICompartmentProvider.h
//
// (c) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description: Declaration of interface ICompartmentProvider.
// Compiles with: 
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser       *
// * General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at  *
// * your option) any later version.                                                                                 *
// *                                                                                                                 *
// * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
// * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public      *
// * License for more details.                                                                                       *
// *                                                                                                                 *
// * You should have received a copy of the GNU Lesser General Public License along with this library; if not, write *
// * to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA                  *
// *                                                                                                                 *
// *******************************************************************************************************************
//
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#pragma once

#include <QVector>

class Compartment;

/**
 * @class ICompartmentProvider
 * @brief Interface for classes providing compartment information.
 * @since 0.1.0
 * @ingroup UmlCommon
 *
 * This interface must be implemented by classes that need to provide compartments for their shape.
 */
class ICompartmentProvider
{
public: // Constructors
    virtual ~ICompartmentProvider() {}

public: // Methods
   /** Gets the vector of Compartment objects provided. */
   virtual QVector<Compartment*> compartments() = 0;

   /** Updates a single Compartment object with text boxes. */
   virtual void update(int index, Compartment* comp) = 0; // TODO: remove index it is unused
};
