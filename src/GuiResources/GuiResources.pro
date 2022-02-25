#---------------------------------------------------------------------------------------------------------------------
# GuiResources.pro
#
# Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
#
# Description: Qt project file for the GuiResources static library.
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
VERSION  = 1.0.0
TARGET   = GuiResources
DESTDIR  = ../../bin
 
CONFIG  += static
DEFINES += BUILD_STATIC

MOC_DIR     += ./moc
OBJECTS_DIR += ./obj
RCC_DIR     += ./moc

DISTFILES   += ./GuiResources.pri

HEADERS += \
    IconProvider.h \
    StringProvider.h

SOURCES += \
    IconProvider.cpp \
    StringProvider.cpp
