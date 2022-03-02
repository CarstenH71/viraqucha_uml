set(LIB_NAME GuiUndoing)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(${LIB_NAME} 
  STATIC
    CommandStack.cpp
    EditCommand.cpp
    InsertCommand.cpp
    MoveCommand.cpp
    RemoveCommand.cpp
    UndoCommand.cpp
)

target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)
target_compile_options(${LIB_NAME} PUBLIC -fPIC)

target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5/QtCore")
target_include_directories(${LIB_NAME} PUBLIC "/usr/include/x86_64-linux-gnu/qt5")
