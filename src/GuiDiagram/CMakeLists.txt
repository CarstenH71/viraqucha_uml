set(LIB_NAME GuiDiagram)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(${LIB_NAME} 
  STATIC
    AssociationShape.cpp
    ClassifierShape.cpp
    CommentShape.cpp
    DependencyShape.cpp
    DiagramScene.cpp
    EdgeShape.cpp
    GeneralizationShape.cpp
    LinkShape.cpp
    NodeShape.cpp
    PrimitiveTypeShape.cpp
    RealizationShape.cpp
    Shape.cpp
    ShapeFactory.cpp
    TemplateBox.cpp
)

target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)
target_compile_options(${LIB_NAME} PUBLIC -fPIC)

target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5/QtCore")
target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5")
