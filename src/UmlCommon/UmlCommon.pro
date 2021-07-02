#---------------------------------------------------------------------------------------------------------------------
# UmlCommon.pro
#
# Copyright (C) 2019 Carsten Huber (Dipl.-Ing.)
#
# Description: Qt project file for the UmlCommon shared library.
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
TARGET   = UmlCommon
DESTDIR  = ../../bin
CONFIG  += qt c++17

win32 {
   CONFIG  += shared
   DEFINES += QT_DLL WIN64 UMLCOMMON_LIB
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
./AlignmentKind.h \
./Compartment.h \
./DiaEdge.h \
./DiagramKind.h \
./DiaNode.h \
./DiaShape.h \
./ErrorTools.h \
./EventType.h \
./FormatKind.h \
./ICompartmentProvider.h \
./IElementBuilder.h \
./IElementObserver.h \
./ILabelProvider.h \
./IMultiplicityElement.h \
./INamedElement.h \
./IntrusivePtr.h \
./ISerializable.h \
./IShapeObserver.h \
./IStereotypedElement.h \
./ITemplatableElement.h \
./Label.h \
./NameBuilder.h \
./PropertyStrings.h \
./RoutingKind.h \
./SignatureChars.h \
./SignatureTools.h \
./TextBox.h \
./UmlComment.h \
./umlcommon_globals.h \
./UmlCommon.h \
./UmlCompositeElement.h \
./UmlDependency.h \
./UmlDiagram.h \
./UmlElementFactory.h \
./UmlElement.h \
./UmlKeywords.h \
./UmlLink.h \
./UmlModel.h \
./UmlNesting.h \
./UmlPackage.h \
./UmlParameterSubstitution.h \
./UmlProject.h \
./UmlRoot.h \
./UmlTemplateBinding.h \
./UmlTemplateParameter.h \
./VisibilityKind.h

SOURCES +=  \
./Compartment.cpp \
./DiaEdge.cpp \
./DiaNode.cpp \
./DiaShape.cpp \
./ErrorTools.cpp \
./Label.cpp \
./NameBuilder.cpp \
./SignatureTools.cpp \
./TextBox.cpp \
./UmlComment.cpp \
./UmlCommon.cpp \
./UmlCompositeElement.cpp \
./UmlDependency.cpp \
./UmlDiagram.cpp \
./UmlElement.cpp \
./UmlElementFactory.cpp \
./UmlLink.cpp \
./UmlModel.cpp \
./UmlNesting.cpp \
./UmlPackage.cpp \
./UmlParameterSubstitution.cpp \
./UmlProject.cpp \
./UmlRoot.cpp \
./UmlTemplateBinding.cpp \
./UmlTemplateParameter.cpp

DISTFILES += \
./UmlCommon.pri


