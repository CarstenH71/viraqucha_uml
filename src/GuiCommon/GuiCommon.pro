#---------------------------------------------------------------------------------------------------------------------
# GuiCommon.pro
#
# Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
#
# Description: Qt project file for the GuiCommon static library.
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
TEMPLATE = lib
VERSION  = 1.0.0
TARGET   = GuiCommon
DESTDIR  = ../../bin

include (../UmlCommon/UmlCommon.pri)

CONFIG  += static
DEFINES += BUILD_STATIC

MOC_DIR     += ./moc
OBJECTS_DIR += ./obj
RCC_DIR     += ./moc

DISTFILES   += ./GuiCommon.pri

HEADERS += \
./MessageBox.h \
./MultiplicityUtils.h \
    Viraqucha.h

SOURCES += \ 
./MessageBox.cpp \
./MultiplicityUtils.cpp
