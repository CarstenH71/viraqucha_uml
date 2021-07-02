//---------------------------------------------------------------------------------------------------------------------
// Compartment.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class Compartment.
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
#include "Compartment.h"
#include "TextBox.h"

/**
 * @class Compartment
 * @brief The Compartment class holds information about a compartment of a diagram node.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * Depending on the type of an UML element, a diagram node (DiaNode) can have up to 6 compartments. Compartments may
 * contain lines of text showing the properties of an UML element.
 */

 //---------------------------------------------------------------------------------------------------------------------
 // Internal struct hiding implementation details
 //---------------------------------------------------------------------------------------------------------------------
 /// @cond
struct Compartment::Data
{
   Data()
      : isHidden(false)
      , flags(0)
   {}

   QString           name;
   QVector<TextBox*> lines;
   bool              isHidden;
   quint64           flags;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Initializes a new instance of the Compartment class.
 */
Compartment::Compartment()
: data(new Data())
{
}

Compartment::~Compartment()
{
   clear();
   delete data;
}

/**
 * Gets the name of the compartment.
 */
QString Compartment::name() const
{
   return data->name;
}

/**
 * Sets the name of the compartment.
 */
void Compartment::setName(QString value)
{
   data->name = value;
}

/**
 * Gets a value indicating whether the whole compartment is hidden.
 */
bool Compartment::isHidden() const
{
   return data->isHidden;
}

/**
 * Sets a value indicating whether the whole compartment is hidden.
 */
void Compartment::isHidden(bool value)
{
   data->isHidden = value;
}

/**
 * Gets additional flags used for filtering visibility of lines in a compartment.
 *
 * The flags are used e.g. to store information about whether public, protected and private attributes or operations
 * of a UML class shall be hidden or not.
 */
quint64 Compartment::flags() const
{
   return data->flags;
}

/**
 * Sets additional flags used for filtering visibility of lines in a compartment.
 */
void Compartment::setFlags(quint64 value)
{
   data->flags = value;
}

/**
 * Gets the vector of lines (TextBox instances) of the compartment.
 */
QVector<TextBox*> Compartment::lines() const
{
   return QVector<TextBox*>(data->lines);
}

/**
 * Adds a new line (that is a TextBox instance) to the compartment.
 * 
 * @param text Text to be shown in the text box.
 * @param bold If true: text will be drawn <b>bold</b>.
 * @param italic If true: text will be drawn <i>italic</i>.
 * @param underline If true: text will be drawn underlined.
 * @param alignment Alignment of the text. See enum AlignmentFlag for further details.
 * @returns A new TextBox instance with properties set to the parameter values.
 */
TextBox* Compartment::addLine(QString text, bool bold, bool italic, bool underline, AlignmentFlag alignment)
{
   auto* box = new TextBox();
   box->setText(text);
   box->isBold(bold);
   box->isItalic(italic);
   box->isUnderline(underline);
   box->setAlignment(alignment);
   append(box);
   return box;
}

/**
 * Appends a TextBox instance to the compartment.
 */
void Compartment::append(TextBox* box)
{
   if (box != nullptr)
   {
      data->lines.append(box);
   }
}

/**
 * Removes a TextBox instance from the compartment.
 * 
 * @param box TextBox instance to be removed.
 */
void Compartment::remove(TextBox* box)
{
   if (box != nullptr)
   {
      int index = data->lines.indexOf(box);
      if (index > -1) data->lines.remove(index);
   }
}

/**
 * Clears the compartment, that is removes all TextBox instances from it.
 */
void Compartment::clear()
{
   int end = data->lines.size();
   for (int index = 0; index < end; ++index)
   {
      delete data->lines[index];
   }
   data->lines.clear();
}
