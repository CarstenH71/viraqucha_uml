//---------------------------------------------------------------------------------------------------------------------
// ErrorTools.cpp
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of the helper functions for file errors.
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
#include "ErrorTools.h"

/**
 * Converts a QJsonParseError value to a nicely formatted string.
 *
 * @returns A formatted string.
 */
QString toString(QJsonParseError value)
{
   QString str;
   switch (value.error)
   {
   case QJsonParseError::NoError :
   default:
      break;
   case QJsonParseError::UnterminatedObject :
      str = "Unterminated object";
      break;
   case QJsonParseError::MissingNameSeparator :
      str = "Missing name separator";
      break;
   case QJsonParseError::UnterminatedArray :
      str = "Unterminated array";
      break;
   case QJsonParseError::MissingValueSeparator :
      str = "Missing value separator";
      break;
   case QJsonParseError::IllegalValue :
      str = "Illegal value";
      break;
   case QJsonParseError::TerminationByNumber :
      str = "Termination by number";
      break;
   case QJsonParseError::IllegalNumber :
      str = "Illegal number";
      break;
   case QJsonParseError::IllegalEscapeSequence :
      str = "Illegal espace sequence";
      break;
   case QJsonParseError::IllegalUTF8String :
      str = "Illegal UTF8 string";
      break;
   case QJsonParseError::UnterminatedString :
      str = "Unterminated string";
      break;
   case QJsonParseError::MissingObject :
      str = "Missing object";
      break;
   case QJsonParseError::DeepNesting :
      str = "Deep nesting";
      break;
   case QJsonParseError::DocumentTooLarge :
      str = "Document too large";
      break;
   case QJsonParseError::GarbageAtEnd :
      str = "Garbage at end";
      break;
   }

   return str + QString(" at offset %1").arg(value.offset);
}