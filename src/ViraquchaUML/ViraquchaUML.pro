#---------------------------------------------------------------------------------------------------------------------
# ViraquchaUML.pro
#
# Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
#
# Description: Qt project file for the ViraquchaUML executable.
#
# *******************************************************************************************************************
# *                                                                                                                 *
# * This file is part of ViraquchaUML.                                                                              *
# *                                                                                                                 *
# * ViraquchaUML is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
# * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
# * option) any later version.                                                                                      *
# *                                                                                                                 *
# * ViraquchaUML is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
# * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
# * for more details.                                                                                               *
# *                                                                                                                 *
# * You should have received a copy of the GNU General Public License along with ViraquchaUML; if not, see          *
# * http://www.gnu.org/licenses/gpl                                                                                 *
# *                                                                                                                 *
# *******************************************************************************************************************
#
# See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
#---------------------------------------------------------------------------------------------------------------------

TEMPLATE    = app
TARGET      = ViraquchaUML
DESTDIR     = ../../bin
CONFIG     += qt c++17
DEPENDPATH += .

QT          += widgets
MOC_DIR      = ./moc
OBJECTS_DIR  = ./obj
UI_DIR       = ./ui
RCC_DIR      = ./rcc
RESOURCES    = ../GuiResources/GuiResources.qrc

include (../GuiCommon/GuiCommon.pri)
include (../GuiDiagram/GuiDiagram.pri)
include (../GuiProject/GuiProject.pri)
include (../GuiResources/GuiResources.pri)
include (../UmlCommon/UmlCommon.pri)
include (../UmlClassifiers/UmlClassifiers.pri)

HEADERS += \
    AttributesTab.h \
    AttributeTab.h \
    ClassifierTab.h \
    CommentTab.h \
    DiagramPage.h \
    GeneralTab.h \
    InsertCommand.h \
    IPropertiesTab.h \
    MainWindow.h \
    MultiplicityTab.h \
    NewDiagramDialog.h \
    NewProjectDialog.h \
    OperationsTab.h \
    OperationTab.h \
    ParameterTab.h \
    PropertiesDialog.h \
    RemoveCommand.h \
    RenameCommand.h \
    StartPage.h \
    TemplateParameterTab.h \
    ToolBoxManager.h \
    UndoCommand.h \
    MoveCommand.h \
    CommandStack.h

FORMS += \
    AttributesTab.ui \
    AttributeTab.ui \
    ClassifierTab.ui \
    CommentTab.ui \
    DiagramPage.ui \
    GeneralTab.ui \
    MainWindow.ui \
    MultiplicityTab.ui \
    NewDiagramDialog.ui \
    NewProjectDialog.ui \
    OperationsTab.ui \
    OperationTab.ui \
    ParameterTab.ui \
    PropertiesDialog.ui \
    StartPage.ui \
    TemplateParameterTab.ui

SOURCES += \
    AttributesTab.cpp \
    AttributeTab.cpp \
    ClassifierTab.cpp \
    CommentTab.cpp \
    DiagramPage.cpp \
    GeneralTab.cpp \
    main.cpp \
    MainWindow.cpp \
    MultiplicityTab.cpp \
    NewDiagramDialog.cpp \
    NewProjectDialog.cpp \
    OperationsTab.cpp \
    OperationTab.cpp \
    ParameterTab.cpp \
    PropertiesDialog.cpp \
    StartPage.cpp \
    TemplateParameterTab.cpp \
    ToolBoxManager.cpp \
    UndoCommand.cpp \
    CommandStack.cpp \
    MoveCommand.cpp
