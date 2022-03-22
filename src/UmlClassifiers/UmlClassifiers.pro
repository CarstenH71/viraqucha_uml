#---------------------------------------------------------------------------------------------------------------------
# UmlClassifiers.pro
#
# Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
#
# Description: Qt project file for the UmlClassifiers shared library.
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

QT      -= gui
TEMPLATE = lib
VERSION  = 1.0.0
TARGET   = UmlClassifiers
DESTDIR  = ../../bin
CONFIG  += qt c++17

include (../UmlCommon/UmlCommon.pri)

win32 {
   CONFIG  += shared
   DEFINES += QT_DLL WIN64 UMLCLASSIFIERS_LIB
}
unix {
   CONFIG  += static
   DEFINES += BUILD_STATIC
}

MOC_DIR     += ./moc
OBJECTS_DIR += ./obj
UI_DIR      += ./moc
RCC_DIR     += ./moc

HEADERS += \
    AggregationKind.h \
    AssociationEnd.h \
    CallConcurrencyKind.h \
    IProperty.h \
    UmlLiteral.h \
    ParameterDirectionKind.h \
    ParameterEffectKind.h \
    PropertyStrings.h \
    UmlAssociation.h \
    UmlAttribute.h \
    UmlClass.h \
    UmlClassifier.h \
    umlclassifiers_global.h \
    UmlClassifiers.h \
    UmlComponent.h \
    UmlDatatype.h \
    UmlEnumeration.h \
    UmlGeneralization.h \
    UmlInterface.h \
    UmlOperation.h \
    UmlParameter.h \
    UmlPort.h \
    UmlPrimitiveType.h \
    UmlRealization.h \
    UmlSignal.h

SOURCES += \
    AssociationEnd.cpp \
    UmlLiteral.cpp \
    UmlAssociation.cpp \
    UmlAttribute.cpp \
    UmlClass.cpp \
    UmlClassifier.cpp \
    UmlClassifiers.cpp \
    UmlComponent.cpp \
    UmlDatatype.cpp \
    UmlEnumeration.cpp \
    UmlGeneralization.cpp \
    UmlInterface.cpp \
    UmlOperation.cpp \
    UmlParameter.cpp \
    UmlPort.cpp \
    UmlPrimitiveType.cpp \
    UmlRealization.cpp \
    UmlSignal.cpp

DISTFILES += \
    UmlClassifiers.pri
