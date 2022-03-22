set(LIB_NAME UmlClassifiers)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(${LIB_NAME} 
  STATIC
    AssociationEnd.cpp
    UmlLiteral.cpp
    UmlAssociation.cpp
    UmlAttribute.cpp
    UmlClass.cpp
    UmlClassifier.cpp
    UmlClassifiers.cpp
    UmlComponent.cpp
    UmlDatatype.cpp
    UmlEnumeration.cpp
    UmlGeneralization.cpp
    UmlInterface.cpp
    UmlOperation.cpp
    UmlParameter.cpp
    UmlPort.cpp
    UmlPrimitiveType.cpp
    UmlRealization.cpp
    UmlSignal.cpp
)

target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)
target_compile_options(${LIB_NAME} PUBLIC -fPIC)

target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5/QtCore")
target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5")
target_include_directories(${LIB_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/UmlCommon")
