//---------------------------------------------------------------------------------------------------------------------
// ProjectTreeView.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class ProjectTreeView.
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
#pragma once

#include <QPoint>
#include <QTreeView>

class ProjectTreeView : public QTreeView
{
   Q_OBJECT
   typedef QTreeView super;
public: // Constructors
   ProjectTreeView(QWidget* parent = nullptr);
   virtual ~ProjectTreeView();

public: // Methods
   void mousePressEvent(QMouseEvent* event) override;
   void mouseMoveEvent(QMouseEvent* event) override;

private: // Attributes
   QPoint _startPos;
};

