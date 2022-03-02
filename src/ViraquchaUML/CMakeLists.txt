set(EXE_NAME ViraquchaUML)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# add the executable:
add_executable(${EXE_NAME}
  AttributesTab.cpp
  AttributesTab.ui
  AttributeTab.cpp
  AttributeTab.ui
  ClassifierTab.cpp
  ClassifierTab.ui
  CommandStack.cpp
  CommentTab.cpp
  CommentTab.ui
  DiagramPage.cpp
  DiagramPage.ui
  GeneralTab.cpp
  GeneralTab.ui
  main.cpp
  MainWindow.cpp
  MainWindow.ui
  MoveCommand.cpp
  MultiplicityTab.cpp
  MultiplicityTab.ui
  NewDiagramDialog.cpp
  NewDiagramDialog.ui
  NewProjectDialog.cpp
  NewProjectDialog.ui
  OperationsTab.cpp
  OperationsTab.ui
  OperationTab.cpp
  OperationTab.ui
  ParameterTab.cpp
  ParameterTab.ui
  PropertiesDialog.cpp
  PropertiesDialog.ui
  StartPage.cpp
  StartPage.ui
  TemplateParameterTab.cpp
  TemplateParameterTab.ui
  ToolBoxManager.cpp
  UndoCommand.cpp
  ../GuiResources/GuiResources.qrc
)

# set compile and link properties:
target_compile_features(${EXE_NAME} PUBLIC cxx_std_17)
target_compile_options(${EXE_NAME} PUBLIC -fPIC)

target_link_libraries(${EXE_NAME} 
  PRIVATE 
    Qt5::Gui
    Qt5::Widgets
  PUBLIC
    UmlCommon
    UmlClassifiers
    GuiCommon
    GuiDiagram
    GuiProject
    GuiResources
)

target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/GuiCommon")
target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/GuiDiagram")
target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/GuiProject")
target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/GuiResources")
target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/UmlCommon")
target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/UmlClassifiers")
target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/ViraquchaUML")

# tell cmake where to install the executable:
#install(TARGET ${EXE_NAME} DESTINATION bin)
