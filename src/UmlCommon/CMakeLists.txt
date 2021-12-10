set(LIB_NAME UmlCommon)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(${LIB_NAME} 
  STATIC 
    Compartment.cpp
    DiaEdge.cpp
    DiaNode.cpp
    DiaShape.cpp
    ErrorTools.cpp
    Label.cpp
    NameBuilder.cpp
    SignatureTools.cpp
    TextBox.cpp
    UmlComment.cpp
    UmlCommon.cpp
    UmlCompositeElement.cpp
    UmlDependency.cpp
    UmlDiagram.cpp
    UmlElement.cpp
    UmlElementFactory.cpp
    UmlLink.cpp
    UmlModel.cpp
    UmlNesting.cpp
    UmlPackage.cpp
    UmlParameterSubstitution.cpp
    UmlProject.cpp
    UmlRoot.cpp
    UmlTemplateBinding.cpp
    UmlTemplateParameter.cpp
)

target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)
target_compile_options(${LIB_NAME} PUBLIC -fPIC)

target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5/QtCore")
target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5")
