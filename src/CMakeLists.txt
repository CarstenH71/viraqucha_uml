#------------------------------------------------------------------------------
# CMakeLists file for building ViraquchaUML              (C) 2021 Carsten Huber
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.16)

# set the project name and version:
project(ViraquchaUML VERSION 0.2.0 LANGUAGES CXX)

# specify C++ standard:
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify Qt features:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# setup output directories:
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)

# add sub directories containing libraries and the executable:
add_subdirectory(./GuiCommon GuiCommon)
add_subdirectory(./GuiDiagram GuiDiagram)
add_subdirectory(./GuiProject GuiProject)
add_subdirectory(./GuiResources GuiResources)
add_subdirectory(./UmlCommon UmlCommon)
add_subdirectory(./UmlClassifiers UmlClassifiers)
add_subdirectory(./ViraquchaUML ViraquchaUML)
