//---------------------------------------------------------------------------------------------------------------------
// SignatureTools.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of some helper functions used internally.
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
#include "SignatureTools.h"
#include "SignatureChars.h"
#include "IMultiplicityElement.h"

#include <QTextStream>

QChar toChar(VisibilityKind value)
{
   switch (value)
   {
   case VisibilityKind::Package:
      return ChTilde;
      break;
   case VisibilityKind::Private:
      return ChMinus;
      break;
   case VisibilityKind::Protected:
      return ChCross;
      break;;
   case VisibilityKind::Public:
      return ChPlus;
      break;
   case VisibilityKind::Undefined:
   default:
      break;
   }

   return QChar();
}

QString makeRange(quint32 lower, quint32 upper, bool brackets)
{
   QString result;
   
   if (lower != 1 || upper != 1)
   {
      QTextStream stream(&result);
      stream << ChSpace;
      if (brackets) stream << ChMultO;
      stream << dec;
      if (lower != upper) stream << lower << KRange;
      if (upper == KUnlimited)
      {
         stream << ChStar;
      }
      else
      {
         stream << upper;
      }
      if (brackets) stream << ChMultC;
      stream.flush();
   }

   return result;
}

QString makeAnnotation(QString kwd, QString sty)
{
   QString result;
   
   if (!kwd.isEmpty() || !sty.isEmpty())
   {
      QTextStream stream(&result);
      stream << ChGuilO;
      if (!kwd.isEmpty()) stream << kwd;
      if (!kwd.isEmpty() && !sty.isEmpty()) stream << ChComma << ChSpace;
      if (!sty.isEmpty()) stream << sty;
      stream << ChGuilC << ChSpace;
      stream.flush();
   }

   return result;
}
