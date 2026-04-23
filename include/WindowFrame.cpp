#include"WindowFrame.hpp"
#include<QtCore/Qt>
Window_Frame::Window_Frame(QWidget* parent_widget):QMainWindow(parent_widget){
  
     menubar.reset(new MenuBar(this));
     
     tabwidget.reset(new TabWidget(this));
     
     centralwidget_1.reset(new DrawingCentralWidget(tabwidget.get()));
      std::cout<<"I am after CentralWidget"<<std::endl;
     FileActionMenu=new FileMenu;
     ModelActionMenu=new ModelMenu;
     ModifyActionMenu=new QMenu;
     
     tabwidget->addTab(centralwidget_1.get(),tr("CAD View"));
     tabwidget->setTabsClosable(false);
     FileAction.reset(new QAction(tr("File"),menubar.get()));
     ModelAction.reset(new QAction(tr("Model"),menubar.get()));
     ModifyMenuAction.reset(new QAction(tr("Modify"),menubar.get()));
     dockwidget_1.reset(new DockWidget(this,tr("Item")));
     dockwidget_2.reset(new DockWidget(this,tr("")));
     setWindowTitle(tr("NodeCAD"));
     statusbar_1.reset(new QStatusBar(this));
     setStatusBar(statusbar_1.get());
     setMenuBar(menubar.get());
     Splitter.reset(new QSplitter(Qt::Vertical));
     boolWidget=std::make_unique<BooleanWidget>(false,tr("Input Value"),nullptr,tr("Boolean"));

     sceneSettingWidget.reset(new SceneSettingWidget);
     objprswidget.reset(new ObjectPresentationWidget(nullptr));
     FileAction->setMenu(FileActionMenu);
     ModelAction->setMenu(ModelActionMenu);
     menubar->addAction(FileAction.get());
     menubar->addAction(ModelAction.get());
     Splitter->addWidget(tabwidget.get());
     fileSystemWidget=std::make_unique<TreeViewWidget>(nullptr);

     tabwidget_1.reset(new TabWidget(Splitter.get()));
     tabwidget_1->setTabsClosable(false);
     tabwidget_1->setTabPosition(QTabWidget::North);
     nodewidget.reset(new NodeGraphWidget(tabwidget_1.get(),centralwidget_1->context));
     Splitter->addWidget(tabwidget_1.get());
     std::cout<<"I am in the constructor"<<std::endl;
     Splitter->setSizes({500,400});
     colorwidget.reset(new ColorCollectionWidget(nullptr));
     tabwidget_1->addTab(nodewidget.get(),tr("NodeGraph"));
     tabwidget_1->addTab(fileSystemWidget.get(),tr("File System"));
     fnodewidget.reset(new FloatNodeWidget(tr("Input"),0.0));
     surface_widget->SetSurfaceInfos(shape);

     setCentralWidget(Splitter.get());
     
     dockwidget_1->SetWidget(surface_widget.get());
     

     addDockWidget(Qt::RightDockWidgetArea,dockwidget_1.get());
     addDockWidget(Qt::RightDockWidgetArea,dockwidget_2.get());
     splitDockWidget(dockwidget_1.get(),dockwidget_2.get(),Qt::Vertical);
     
     //This is where we connect all the gui elements with their respective handlers
     connect(centralwidget_1.get(),&DrawingCentralWidget::QueryDebugMessage,this,&Window_Frame::SetStatusTextFromDrawingWidget);
     connect(nodewidget.get(),&NodeGraphWidget::OnSendAIS_ShapeToDrawingWidget,this,&Window_Frame::OnRenderAIS_Shape);
     

     connect(sceneSettingWidget->Wi_RadioButton,&QRadioButton::toggled,this,&Window_Frame::OnSetWireframeMode);
     connect(sceneSettingWidget->Sh_RadioButton,&QRadioButton::toggled,this,&Window_Frame::OnSetShadedMode);
     connect(sceneSettingWidget->Wi_ShRadioButton,&QRadioButton::toggled,this,&Window_Frame::OnSetBothShadedAndWireFrame);
     connect(sceneSettingWidget->VertexRadioButton,&QRadioButton::toggled,this,&Window_Frame::OnChooseVertexFilter);
     connect(sceneSettingWidget->EdgeRadioButton,&QRadioButton::toggled,this,&Window_Frame::OnChooseEdgeFilter);
     connect(sceneSettingWidget->WireRadioButton,&QRadioButton::toggled,this,&Window_Frame::OnChooseWireFilter);
     connect(sceneSettingWidget->FaceRadioButton,&QRadioButton::toggled,this,&Window_Frame::OnChooseFaceFilter);
     connect(sceneSettingWidget->ShapeRadioButton,&QRadioButton::toggled,this,&Window_Frame::OnChooseShapeFilter);
     connect(nodewidget.get(),&NodeGraphWidget::CreateFloatNodeWidget,this,&Window_Frame::OnCreateFnodeWidget);
     connect(sceneSettingWidget->ShowGridCheckBox,&QCheckBox::toggled,this,&Window_Frame::OnToggleShowGrid);
     connect(nodewidget.get(),&NodeGraphWidget::SendMessage,this,&Window_Frame::DisplayText);   
     connect(sceneSettingWidget->SetXEdit,&DoubleEdit::GetValue,this,&Window_Frame::OnSetGridX);
     connect(sceneSettingWidget->SetYEdit,&DoubleEdit::GetValue,this,&Window_Frame::OnSetGridY);
     connect(sceneSettingWidget->SpaceEdit,&DoubleEdit::GetValue,this,&Window_Frame::OnSetGridSpacing);
     connect(centralwidget_1.get(),&DrawingCentralWidget::OnOpenSceneSettings,this,&Window_Frame::OnShowSceneSettings);
     connect(sceneSettingWidget->boundboxr_button.get(),&QRadioButton::toggled,this,&Window_Frame::OnDrawBoundBox);
     connect(centralwidget_1->DrawCubeAction,&QAction::triggered,this,&Window_Frame::OnDrawCubeHandler);
     connect(centralwidget_1.get(),&DrawingCentralWidget::OnRenderShapePrsWidget,this,&Window_Frame::OnDrawShapePrsUI);
     connect(objprswidget->propsection()->baseColorPane(),&ColorPane::IsDoubleClicked,this,&Window_Frame::OnBaseColorHandler);
    
     connect(colorwidget.get(),&ColorCollectionWidget::GetSelectedColor,this,&Window_Frame::OnChooseBaseColor);

     connect(objprswidget->propsection()->ambientColorPane(),&ColorPane::IsDoubleClicked,this,&Window_Frame::OnAmbientColorHandler);
     connect(colorwidget.get(),&ColorCollectionWidget::GetSelectedColor,this,&Window_Frame::OnChooseAmbientColor);

     connect(objprswidget->propsection()->diffuseColorPane(),&ColorPane::IsDoubleClicked,this,&Window_Frame::OnDiffuseColorHandler);
     connect(colorwidget.get(),&ColorCollectionWidget::GetSelectedColor,this,&Window_Frame::OnChooseDiffuseColor);
     
     connect(objprswidget->propsection()->specularColorPane(),&ColorPane::IsDoubleClicked,this,&Window_Frame::OnSpecularColorHandler);
     connect(colorwidget.get(),&ColorCollectionWidget::GetSelectedColor,this,&Window_Frame::OnChooseSpecularColor);
     
     connect(objprswidget->propsection()->emissiveColorPane(),&ColorPane::IsDoubleClicked,this,&Window_Frame::OnEmissiveColorHandler); 
     connect(colorwidget.get(),&ColorCollectionWidget::GetSelectedColor,this,&Window_Frame::OnChooseEmissiveColor);
      

     connect(objprswidget->propsection()->transpEdit(),&DoubleEdit::GetValue,this,&Window_Frame::OnSetObjectTransp);
     connect(objprswidget->propsection()->ShaderTypeComboBox(),&QComboBox::currentTextChanged,this,&Window_Frame::OnSetShadingType);
     
     connect(objprswidget->propsection()->refractEdit(),&DoubleEdit::GetValue,this,&Window_Frame::OnSetRefractiveIndex);
     
     connect(centralwidget_1.get(),&DrawingCentralWidget::OnDestroyMaterialProp,this,&Window_Frame::DestroyMatPropWidget);
     connect(nodewidget.get(),&NodeGraphWidget::OnUpdateFloatInput,this,&Window_Frame::OnUpdateFloatNodeWidgetValue);
     connect(fnodewidget->ValueEdit(),&DoubleEdit::GetValue,this,&Window_Frame::OnSetValueForFnodeWidget);
     connect(nodewidget.get(),&NodeGraphWidget::OnMoveShapes,this,&Window_Frame::OnDisplayObjects);
     connect(nodewidget.get(),&NodeGraphWidget::DestroyFloatNodeWidget,this,&Window_Frame::OnDestroyFloatNodeWidget);
     connect(boolWidget->boolPane()->boolCheckBox(),&QCheckBox::toggled,this,&Window_Frame::OnBoolHandler);
     connect(nodewidget.get(),&NodeGraphWidget::OnCreateBoolWidget,this,&Window_Frame::CreateBoolWidget);
    connect(nodewidget.get(),&NodeGraphWidget::OnSendShape,this,&Window_Frame::OnHandleHighlightOfSubShape);
    connect(centralwidget_1->ShapeTypeAction.get(),&QAction::triggered,this,&Window_Frame::SetShapeTypeName);
    connect(centralwidget_1.get(),&DrawingCentralWidget::OnSetPreviousColor,this,&Window_Frame::OnSetPreviousColor);
    connect(centralwidget_1.get(),&DrawingCentralWidget::EmitShape,this,&Window_Frame::OnHandleEmittedShape);
    connect(centralwidget_1.get(),&DrawingCentralWidget::EmitTransformedShape,this,&Window_Frame::OnHandleEmittedTrsfShape);
    connect(sceneSettingWidget->hilisection->FaceColorWidget(),&ColorPane::IsDoubleClicked,this,&Window_Frame::OnSpawnColorSelectionWidget);
    connect(colorwidget_1.get(),&ColorCollectionWidget::GetSelectedColor,this,&Window_Frame::OnSetSelectionColorFromColorWidget);
    connect(centralwidget_1->ConstructPointNodeAction.get(),&QAction::toggled,this,&Window_Frame::OnHandleConstructPointNode);
    connect(centralwidget_1.get(),&DrawingCentralWidget::OnSendConvertValue,this,&Window_Frame::OnSetValuesForTriple);
    connect(centralwidget_1->ConstructTransformNodeAction.get(),&QAction::toggled,this,&Window_Frame::OnSetNodeTransformBool);
    connect(ModelActionMenu->CubeAction.get(),&QAction::toggled,this,&Window_Frame::OnDrawCubeInWorld);
    connect(ModelActionMenu->SphereAction.get(),&QAction::toggled,this,&Window_Frame::OnDrawSphere);
    connect(ModelActionMenu->CylinderAction.get(),&QAction::toggled,this,&Window_Frame::OnDrawCylinder);              
    connect(ModelActionMenu->CuboidAction.get(),&QAction::toggled,this,&Window_Frame::OnDrawCuboid);
    connect(ModelActionMenu->TorusAction.get(),&QAction::toggled,this,&Window_Frame::OnDrawTorus);
    connect(ModelActionMenu->ConeAction.get(),&QAction::toggled,this,&Window_Frame::OnDrawCone);
    connect(centralwidget_1->ConstructShapeNodeAction.get(),&QAction::toggled,this,&Window_Frame::OnHandleConvertToShapeNode);
    
    connect(this,&Window_Frame::OnSendTransform,this,&Window_Frame::OnHandleSentTransform);
    connect(this,&Window_Frame::OnSendShape,this,&Window_Frame::OnHandleSentShape);
    connect(nodewidget.get(),&NodeGraphWidget::EmitParentShape,this,&Window_Frame::OnHandleEmittedParentShape);
    connect(nodewidget.get(),&NodeGraphWidget::EmitFaceId,this,&Window_Frame::OnHighlightFace);
   connect(nodewidget.get(),&NodeGraphWidget::onDestroyPreviousObject,this,&Window_Frame::OnHandleDestroyPrevObject);
   connect(nodewidget.get(),&NodeGraphWidget::EmitEdge,this,&Window_Frame::OnHighlightEdge);
   connect(centralwidget_1->ShowObjectInfo.get(),&QAction::triggered,this,&Window_Frame::OnShowObjectInfo);
   connect(centralwidget_1.get(),&DrawingCentralWidget:: OnEmitBoolValue,this,&Window_Frame::OnHandleFacePoint);
   connect(sceneSettingWidget->highlightSection()->EditCheckBox(),&QCheckBox::toggled,this,&Window_Frame::OnGetFaceIndex);
   connect(sceneSettingWidget->highlightSection()->EdgeCheckBox(),&QCheckBox::toggled,this,&Window_Frame::OnGetEdgeId);
   connect(centralwidget_1.get(),&DrawingCentralWidget::OnEmitFace,this,&Window_Frame::OnHandleFace);
   connect(centralwidget_1.get(),&DrawingCentralWidget::OnEmitFaceBool,this,&Window_Frame::OnHandleFaceBool);
   connect(FileActionMenu->openFolderAction.get(),&QAction::triggered,this,&Window_Frame::OnOpenCurrentFolder);
   connect(this,&Window_Frame::emitCurrentFolder,this,&Window_Frame::onHandleEmittedFolder);
   connect(nodewidget.get(),&NodeGraphWidget::emitCurrentFile,this,&Window_Frame::onWriteFileToPath);
   

}

