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

QT      += widgets
TEMPLATE = app
TARGET   = ViraquchaUML
DESTDIR  = ../../bin
CONFIG  += qt c++17

include (../GuiCommon/GuiCommon.pri)
include (../GuiResources/GuiResources.pri)
include (../UmlCommon/UmlCommon.pri)
include (../UmlClassifiers/UmlClassifiers.pri)

DEPENDPATH  += .
MOC_DIR      = ./moc
OBJECTS_DIR  = ./obj
UI_DIR       = ./ui
RCC_DIR      = ./rcc
RESOURCES    = ../GuiResources/GuiResources.qrc

HEADERS += \
./AssociationShape.h \
./AttributesTab.h \
./AttributeTab.h \
./ClassifierShape.h \
./ClassifierTab.h \
./ComboBoxDelegate.h \
./CommentShape.h \
./CommentTab.h \
./DependencyShape.h \
./DiagramPage.h \
./DiagramScene.h \
./EdgeShape.h \
./GeneralizationShape.h \
./GeneralTab.h \
./InsertCommand.h \
./IPropertiesTab.h \
./IShapeBuilder.h \
./LinkShape.h \
./MainWindow.h \
./MultiplicityTab.h \
./NewDiagramDialog.h \
./NewProjectDialog.h \
./NodeShape.h \
./OperationsTab.h \
./OperationTab.h \
./ParameterTab.h \
./PrimitiveTypeShape.h \
./ProjectTreeModel.h \
./ProjectTreeView.h \
./PropertiesDialog.h \
./RealizationShape.h \
./RemoveCommand.h \
./RenameCommand.h \
./ShapeFactory.h \
./Shape.h \
./StartPage.h \
./TemplateBox.h \
./TemplateParameterTab.h \
./ToolBoxManager.h \
./TreeIconProvider.h \
./UndoCommand.h \
./MoveCommand.h \
./CommandStack.h

FORMS += \
./AttributesTab.ui \
./AttributeTab.ui \
./ClassifierTab.ui \
./CommentTab.ui \
./DiagramPage.ui \
./GeneralTab.ui \
./MainWindow.ui \
./MultiplicityTab.ui \
./NewDiagramDialog.ui \
./NewProjectDialog.ui \
./OperationsTab.ui \
./OperationTab.ui \
./ParameterTab.ui \
./PropertiesDialog.ui \
./StartPage.ui \
./TemplateParameterTab.ui

SOURCES += \
./AssociationShape.cpp \
./AttributesTab.cpp \
./AttributeTab.cpp \
./ClassifierShape.cpp \
./ClassifierTab.cpp \
./ComboBoxDelegate.cpp \
./CommentShape.cpp \
./CommentTab.cpp \
./DependencyShape.cpp \
./DiagramPage.cpp \
./DiagramScene.cpp \
./EdgeShape.cpp \
./GeneralizationShape.cpp \
./GeneralTab.cpp \
./LinkShape.cpp \
./main.cpp \
./MainWindow.cpp \
./MultiplicityTab.cpp \
./NewDiagramDialog.cpp \
./NewProjectDialog.cpp \
./NodeShape.cpp \
./OperationsTab.cpp \
./OperationTab.cpp \
./ParameterTab.cpp \
./PrimitiveTypeShape.cpp \
./ProjectTreeModel.cpp \
./ProjectTreeView.cpp \
./PropertiesDialog.cpp \
./RealizationShape.cpp \
./Shape.cpp \
./ShapeFactory.cpp \
./StartPage.cpp \
./TemplateBox.cpp \
./TemplateParameterTab.cpp \
./ToolBoxManager.cpp \
./TreeIconProvider.cpp \
./UndoCommand.cpp \
./CommandStack.cpp \
./MoveCommand.cpp
