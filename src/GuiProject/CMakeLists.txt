set(LIB_NAME GuiProject)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(${LIB_NAME} 
  STATIC
    ProjectTreeModel.cpp
    ProjectTreeView.cpp
    TreeIconProvider.cpp
)

target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)
target_compile_options(${LIB_NAME} PUBLIC -fPIC)

target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5/QtCore")
target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5")
