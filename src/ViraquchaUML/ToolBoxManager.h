//---------------------------------------------------------------------------------------------------------------------
// ToolBoxManager.h
//
// Copyright (C) 2018 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of class ToolBoxManager.
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

#include <QBoxLayout>
#include <QButtonGroup>
#include <QIcon>
#include <QMap>
#include <QObject>
#include <QToolBox>
#include <QToolButton>

class ToolBoxManager final : public QObject
{
   ///@cond
   Q_OBJECT
   typedef QObject super;
   ///@endcond
public: // Constants
   const int KMaxColumns = 2;

public: // Constructors
    ToolBoxManager(QObject* parent, QToolBox* toolbox);
    virtual ~ToolBoxManager();

public: // Methods
   void addTab(QString name);
   void addButton(int id, QString name, QString className);
   void addButton(int id, QString name, QString className, QIcon icon);

signals:
   void buttonClicked(int id, QString className);

public slots:
   void resetButton();

private slots:
   void handleButton(int id);

private: // Attributes
   ///@cond
   QToolBox*          _toolbox;
   QButtonGroup*      _group;
   QMap<int, QString> _classes;
   QGridLayout*       _layout;
   int                _row, _col;
   ///@endcond
};
