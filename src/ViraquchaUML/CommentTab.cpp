//---------------------------------------------------------------------------------------------------------------------
// CommentTab.cpp
//
// Copyright (C) 2020 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of class CommentTab.
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
#include "CommentTab.h"
#include "UmlComment.h"

#include <QPlainTextEdit>

//---------------------------------------------------------------------------------------------------------------------
// Class implementation
//---------------------------------------------------------------------------------------------------------------------
CommentTab::CommentTab(QWidget* parent, UmlComment* comment)
: super(parent)
, _comment(comment)
{
   ui.setupUi(this);
   ui.textEdit->setPlainText(comment->body());
}

CommentTab::~CommentTab()
{
}

bool CommentTab::validateInput()
{
   return true;
}

void CommentTab::applyChanges()
{
   _comment->setBody(ui.textEdit->toPlainText());
}
