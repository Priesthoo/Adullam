cmake_minimum_required(VERSION 3.30)

project(Adullam VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build Type")
find_package(Qt6 COMPONENTS Widgets Core Gui)

add_executable(Adullam Adullam.cpp include/Dialogs/DrawLineDialog.cpp include/Widgets/TreeWidget.cpp include/Panes/ImagePane.cpp include/Widgets/ChildDrawWidget.cpp include/DockWidgets/SurfaceInfoWidget.cpp include/Panes/SurfaceInfoPane.cpp  include/DockWidgets/ObjectInfoWidget.cpp include/Widgets/TextButton.cpp  include/NodeGraph/Nodes/PrimitiveShapeNode.cpp include/NodeGraph/Nodes/BooleanNode.cpp include/NodeGraph/Nodes/MultipleOutputNode.cpp include/NodeGraph/Nodes/ShapeArrayNode.cpp include/Widgets/ColourCollectionWidget.cpp include/Widgets/DoubleLineEdit.cpp include/Panes/ColorPane.cpp include/NodeGraph/Nodes/FloatInputData.cpp include/NodeGraph/NodeGraphModel.cpp include/NodeGraph/AdullamNodeDelegateModel.cpp include/DockWidgets/SceneSettingDockWidget.cpp include/NodeGraph/AdullamNodeDelegateModel.cpp include/NodeGraph/DisplayedWidget.cpp include/DockWidgets/FloatNodeWidget.cpp include/Widgets/Section.cpp include/Widgets/CollaneWidget.cxx include/NodeGraph/Nodes/AxisNode.cpp include/NodeGraph/Nodes/PointVariableNode.cpp include/NodeGraph/Nodes/DirectionNode.cpp include/NodeGraph/Nodes/IntegerInputNode.cpp include/NodeGraph/Nodes/StringInputNode.cpp include/NodeGraph/Nodes/FloatInputData.cpp include/NodeGraph/Nodes/ConvertToAIS_ShapeNode.cpp  include/NodeGraph/Nodes/OutputNode.cpp include/NodeGraph/Nodes/AdditionNode.cpp include/Menu/ModelActionMenu.cpp include/Menu/FileActionMenu.cpp include/Widgets/NodeGraphWidget.cpp include/WindowFrame.cpp include/Widgets/TabWidget.cpp include/Widgets/DockWidget.cpp include/Widgets/TitleBarWidget.cpp include/Widgets/DrawingCentralWidget.cpp include/Widgets/MenuBar.cpp include/Widgets/NodeGraphWidget.cpp)

target_link_directories(Adullam PRIVATE lib)
target_compile_definitions(Adullam PUBLIC NODE_EDITOR_STATIC)
target_link_libraries(Adullam PUBLIC QtNodes Qt6Widgets Qt6Core Qt6Gui TKBO.dll TKBool.dll TKCAF.dll TKBRep.dll TKG2d.dll TKG3d.dll TKGeomAlgo.dll TKGeomBase.dll TKFeat.dll TKFillet.dll TKMesh.dll TKMath.dll TKMeshVS.dll TKPrim.dll TKOpenGl.dll TKRWMesh.dll TKService.dll TKShHealing.dll TKV3d.dll TKTopAlgo.dll TKMath.dll TKOffset.dll TKernel.dll)
target_include_directories(Adullam PUBLIC include include/Dialogs Utilities include/Drafting include/Widgets include/qtFolder include/qtFolder/QtCore include/qtFolder/QtWidgets include/qtFolder/QtGui include/AIS include/Aspect include/Graphics3D include/View3D include/WNT include/OpenGL include/Maths include/Kernel include/MeshVS include/Topology include/Geometry2D include/Geometry3D include/Primitive include/GeometryBase include/ModelAlgo include/ModelOrigin include/Topology include/SceneObjects include/TopologyAlgorithm include/QtNodes include/QtNodes/internal include/Menu include/NodeGraph/NodeData include/NodeGraph/Nodes include/NodeGraph include/InteractiveShape include/DockWidgets include/Command include/Panes include/FileHandling)
