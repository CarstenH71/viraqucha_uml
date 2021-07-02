# -----------------------------------------------------------------------------
# UnitTests project file for ViraquchaUML components           (C) 2017 C.Huber
# -----------------------------------------------------------------------------

TEMPLATE = app
TARGET   = UnitTests
DESTDIR  = ../../bin/tests
QT      += core
CONFIG  += qtestlib debug console

win32 {
  DEFINES += WIN64 QT_DLL QT_TESTLIB_LIB
}

include(../UmlCommon/UmlCommon.pri)
include(../UmlClassifiers/UmlClassifiers.pri)

DEPENDPATH  += .
MOC_DIR     += ./moc
OBJECTS_DIR += ./obj

HEADERS += ./TestProject.h
SOURCES += ./main.cpp \
./TestProject.cpp

