//---------------------------------------------------------------------------------------------------------------------
// main.cpp
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Implementation of function main.
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
#include "Viraqucha.h"
#include "MainWindow.h"

#include "UmlCommon.h"
#include "UmlClassifiers.h"

#include <QtWidgets/QApplication>
#include <QCommandLineParser>

/**
 * @defgroup ViraquchaUML
 * Implements the Graphical User Interface of ViraquchaUML.
 */

int main(int argc, char *argv[])
{
   Q_INIT_RESOURCE(GuiResources);

   QApplication app(argc, argv);
   QCoreApplication::setOrganizationName(Viraqucha::KOrgaName);
   QCoreApplication::setOrganizationDomain(Viraqucha::KOrgaDomain);
   QCoreApplication::setApplicationName(Viraqucha::KProgramName);
   QCoreApplication::setApplicationVersion(Viraqucha::KProgramVersion.toString());

   QCommandLineParser parser;
   parser.setApplicationDescription(QCoreApplication::applicationName());
   parser.addHelpOption();
   parser.addVersionOption();
   parser.addPositionalArgument("project", "The project to open.");
   parser.process(app);

   initCommon();
   initClassifiers();

   MainWindow win;  
   if (!parser.positionalArguments().isEmpty())
   {
      win.loadProject(parser.positionalArguments().first());
   }
   win.show();
   return app.exec();
}
