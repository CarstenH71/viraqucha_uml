//---------------------------------------------------------------------------------------------------------------------
// MessageBox.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class MessageBox.
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
#include "MessageBox.h"
#include "Viraqucha.h"

/**
 * @class MessageBox
 * @brief Wrapper class for QMessageBox.
 * @since 0.1.0
 * @ingroup GuiCommon
 *
 * The MessageBox class provides static methods which show a message box like the static methods of QMessageBox. The
 * difference is that MessageBox allows setting of the informative text of a QMessageBox which makes the message boxes
 * nicer than the original QMessageBox methods.
 */

MessageBox::MessageBox()
{
}

MessageBox::~MessageBox()
{
}

int MessageBox::show(QWidget* parent, QString caption, QString text, QMessageBox::Icon icon,
                     QFlags<QMessageBox::StandardButton> buttons, QMessageBox::StandardButton defbtn)
{
   QMessageBox box(parent);
   box.setWindowTitle(Viraqucha::KProgramName);
   box.setText(caption);
   box.setInformativeText(text);
   box.setStandardButtons(buttons);
   box.setDefaultButton(defbtn);
   box.setIcon(icon);
   return box.exec();
}

void MessageBox::error(QWidget* parent, QString caption, QString text)
{
   show(parent, caption, text, QMessageBox::Critical, QMessageBox::Ok, QMessageBox::Ok);
}

void MessageBox::info(QWidget* parent, QString caption, QString text)
{
   show(parent, caption, text, QMessageBox::Information, QMessageBox::Ok, QMessageBox::Ok);
}

int MessageBox::question(QWidget* parent, QString caption, QString text,
                         QFlags<QMessageBox::StandardButton> buttons, QMessageBox::StandardButton defbtn)
{
   return show(parent, caption, text, QMessageBox::Question, buttons, defbtn);
}

void MessageBox::warning(QWidget* parent, QString caption, QString text)
{
   show(parent, caption, text, QMessageBox::Warning, QMessageBox::Ok, QMessageBox::Ok);
}

int MessageBox::warning(QWidget* parent, QString caption, QString text,
                        QFlags<QMessageBox::StandardButton> buttons, QMessageBox::StandardButton defbtn)
{
   return show(parent, caption, text, QMessageBox::Warning, buttons, defbtn);
}
