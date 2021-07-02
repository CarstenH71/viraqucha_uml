//---------------------------------------------------------------------------------------------------------------------
// SignatureChars.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of characters and strings needed for creating attribute or operation signatures.
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

#include <QChar>
#include <QString>

const QChar ChPlus   = '+';
const QChar ChMinus  = '-';
const QChar ChTilde  = '~';
const QChar ChCross  = '#';
const QChar ChSlash  = '/';
const QChar ChColon  = ':';
const QChar ChComma  = ',';
const QChar ChSpace  = ' ';
const QChar ChBrktO  = '(';
const QChar ChBrktC  = ')';
const QChar ChMultO  = '[';
const QChar ChMultC  = ']';
const QChar ChSqrbO  = '{';
const QChar ChSqrbC  = '}';
const QChar ChLessr  = '<';
const QChar ChGreat  = '>';
const QChar ChEqual  = '=';
const QChar ChStar   = '*';
const QChar ChGuilO  = QChar(0x00AB); // Opening guillemet "<<"
const QChar ChGuilC  = QChar(0x00BB); // Closing guillemet ">>"
const QString KRange = "..";
