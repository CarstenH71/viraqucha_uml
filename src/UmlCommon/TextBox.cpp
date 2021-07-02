//---------------------------------------------------------------------------------------------------------------------
// TextBox.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class TextBox.
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
#include "TextBox.h"

/**
 * @class TextBox
 * @brief Provides a text box for compartments or labels of links.
 * @since 1.0
 * @ingroup Common
 *
 * The TextBox class holds the text and information about the format and the alignment of the text in the text box.
 */

//---------------------------------------------------------------------------------------------------------------------
// Internal struct hiding implementation details
//---------------------------------------------------------------------------------------------------------------------
/// @cond
struct TextBox::Data
{
   Data()
   : bold(false)
   , italic(false)
   , underline(false)
   , alignment(AlignmentFlag::AlignLeft)
   {}

   QString       text;
   bool          bold;
   bool          italic;
   bool          underline;
   AlignmentFlag alignment;
};
/// @endcond

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
TextBox::TextBox()
: data(new Data())
{
}

TextBox::~TextBox()
{
   delete data;
}

/**
 * @brief Gets the text in the text box.
 */
QString TextBox::text() const
{
   return data->text;
}

/**
 * @brief Sets the text in the text box.
 */
void TextBox::setText(QString value)
{
   data->text = value;
}

bool TextBox::isBold() const
{
   return data->bold;
}

void TextBox::isBold(bool value)
{
   data->bold = value;
}

bool TextBox::isItalic() const
{
   return data->italic;
}

void TextBox::isItalic(bool value)
{
   data->italic = value;
}

bool TextBox::isUnderline() const
{
   return data->underline;
}

void TextBox::isUnderline(bool value)
{
   data->underline = value;
}

/**
 * @brief Gets the alignment of the text in the text box.
 */
AlignmentFlag TextBox::alignment() const
{
   return data->alignment;
}

/**
 * @brief Sets the alignment of the text in the text box.
 */
void TextBox::setAlignment(AlignmentFlag value)
{
   data->alignment = value;
}
