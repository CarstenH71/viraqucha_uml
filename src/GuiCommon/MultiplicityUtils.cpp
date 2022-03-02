//---------------------------------------------------------------------------------------------------------------------
// MultiplicityUtils.cpp
//
// Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class MultiplicityUtils.
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
#include "MultiplicityUtils.h"
#include "IMultiplicityElement.h"

#include <QTextStream>

/**
 * @class MultiplicityUtils
 * @brief The MultiplicityUtils class provides utility functions for multiplicities.
 * @since 0.1.0
 * @ingroup GuiCommon
 */

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------

/**
 * Parses a given string and returns the lower and upper bound of a multiplicity.
 *
 * @param text
 * @param lower
 * @param upper
 */
bool MultiplicityUtils::tryParse(QString text, unsigned int& lower, unsigned int& upper)
{
   static QRegularExpression expr("^(\\d+\\.{2}(\\d+|\\*))$|^(\\d+)$|^(\\*)$");

   auto match = expr.match(text);
   if (match.hasMatch())
   {
      bool ok = false;

      auto range = match.captured(0);
      if (range == "*")
      {
         lower = 0;
         upper = KUnlimited;
      }
      else if (range.contains(".."))
      {
         auto result = range.split("..");
         lower = (result[0] == "*" ? KUnlimited : result[0].toUInt());
         upper = (result[1] == "*" ? KUnlimited : result[1].toUInt());
      }
      else
      {
         quint32 value = range.toUInt(&ok);
         lower = value;
         upper = value;
      }

      return true;
   }

   return false;
}

/**
 * Converts lower and upper value of a multiplicity to a string.
 *
 * @param lower
 * @param upper
 */
QString MultiplicityUtils::toString(unsigned int lower, unsigned int upper)
{
   QString result;
   QTextStream stream(&result);
   if (lower != upper) stream << lower << "..";
   if (upper == KUnlimited) stream << "*"; else stream << upper;
   stream.flush();
   return result;
}
