set(EXE_NAME ViraquchaUML)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# add the executable:
add_executable(${EXE_NAME}
  AssociationShape.cpp
  AttributesTab.cpp
  AttributesTab.ui
  AttributeTab.cpp
  AttributeTab.ui
  ClassifierShape.cpp
  ClassifierTab.cpp
  ClassifierTab.ui
  ComboBoxDelegate.cpp
  CommandStack.cpp
  CommentShape.cpp
  CommentTab.cpp
  CommentTab.ui
  DependencyShape.cpp
  DiagramPage.cpp
  DiagramPage.ui
  DiagramScene.cpp
  EdgeShape.cpp
  GeneralizationShape.cpp
  GeneralTab.cpp
  GeneralTab.ui
  LinkShape.cpp
  main.cpp
  MainWindow.cpp
  MainWindow.ui
  MessageBox.cpp
  MoveCommand.cpp
  MultiplicityTab.cpp
  MultiplicityTab.ui
  MultiplicityUtils.cpp
  NewDiagramDialog.cpp
  NewDiagramDialog.ui
  NewProjectDialog.cpp
  NewProjectDialog.ui
  NodeShape.cpp
  OperationsTab.cpp
  OperationsTab.ui
  OperationTab.cpp
  OperationTab.ui
  ParameterTab.cpp
  ParameterTab.ui
  PrimitiveTypeShape.cpp
  ProjectTreeModel.cpp
  ProjectTreeView.cpp
  PropertiesDialog.cpp
  PropertiesDialog.ui
  RealizationShape.cpp
  Shape.cpp
  ShapeFactory.cpp
  StartPage.cpp
  StartPage.ui
  StringProvider.cpp
  TemplateBox.cpp
  TemplateParameterTab.cpp
  TemplateParameterTab.ui
  ToolBoxManager.cpp
  TreeIconProvider.cpp
  UndoCommand.cpp
  ViraquchaUML.qrc
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
)

target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/UmlCommon")
target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/UmlClassifiers")
target_include_directories(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/ViraquchaUML")

# tell cmake where to install the executable:
#install(TARGET ${EXE_NAME} DESTINATION bin)
