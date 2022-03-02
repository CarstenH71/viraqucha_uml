#---------------------------------------------------------------------------------------------------------------------
# GuiUndoing.pro
#
# Copyright (C) 2022 Carsten Huber (Dipl.-Ing.)
#
# Description: Qt project file for the GuiUndoing static library.
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

TEMPLATE = lib
VERSION  = 0.2.0
TARGET   = GuiUndoing
DESTDIR  = ../../bin
CONFIG  += qt c++17 static
DEFINES += BUILD_STATIC

QT          += widgets
MOC_DIR     += ./moc
OBJECTS_DIR += ./obj
RCC_DIR     += ./moc

include (../GuiProject/GuiProject.pri)
include (../UmlCommon/UmlCommon.pri)
include (../UmlClassifiers/UmlClassifiers.pri)

DISTFILES   += ./GuiUndoing.pri

HEADERS += \
    GuiUndoing.h \
    CommandStack.h \
    InsertCommand.h \
    MoveCommand.h \
    RemoveCommand.h \
    UndoCommand.h

SOURCES += \ 
    CommandStack.cpp \
    InsertCommand.cpp \
    MoveCommand.cpp \
    RemoveCommand.cpp \
    UndoCommand.cpp
