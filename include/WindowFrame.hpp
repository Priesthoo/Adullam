#ifndef WINDOW_FRAME_HPP
#define WINDOW_FRAME_HPP
//Window_Frame is a class that contains the titlebar,status bar,CentralWidget,Docked Widget,
//Central Widget is a widget that is also the main client area in which drawing(2D and 3D ),Text rendering are performed...
//For Drawings to be performed, we have to bind the drawing context to the Client drawing widget
#include<QtWidgets/QMainWindow>
#include<QtWidgets/QWidget>
#include"DockWidget.hpp"
#include"DrawingCentralWidget.hpp"
#include<TabWidget.hpp>
#include"MenuBar.hpp"
#include<QtGui/QAction>
#include<memory>
#include<QStatusBar>
#include<FileActionMenu.hpp>
#include<QtWidgets/QSplitter>
#include<ModelActionMenu.hpp>
#include<NodeGraphWidget.hpp>
#include<SceneSettingDockWidget.hpp>
#include<DrawCircleWidget.hpp>
#include<DrawCubeWidget.hpp>
#include<TreeWidget.hpp>
#include<DrawCubeDialog.hpp>
#include<ObjectPresentationWidget.hpp>
#include<BooleanWidget.hpp>
#include<ColourCollectionWidget.hpp>
#include<ObjectInfoWidget.hpp>
#include<SurfaceInfoWidget.hpp>
#include<QtWidgets/QFileDialog>
#include<EditorMenu.hpp>
#include<iostream>
using namespace Shape_Utility;
using namespace SURFACE;
class Window_Frame:public QMainWindow{
    Q_OBJECT  //Required for a class that has signals and slots, signals and slots are both functions,but signals are function declaration while slots are function definition
    std::unique_ptr<DockWidget> dockwidget_1;  //First dockwidget that will be placed at the right
    std::unique_ptr<DockWidget> dockwidget_2;   
    std::unique_ptr<DrawingCentralWidget> centralwidget_1;  //we named it 1,because we can have more than one central widget in the future
    std::unique_ptr<MenuBar> menubar;
    std::unique_ptr<QAction> FileAction;
    std::unique_ptr<QAction> ModelAction;
    std::unique_ptr<QAction> ModifyMenuAction;
    std::unique_ptr<QAction> EditorAction;  //this is not a synonym of view action
    std::unique_ptr<NodeGraphWidget> nodewidget;
    std::unique_ptr<QStatusBar> statusbar_1;
    
    std::unique_ptr<BooleanWidget> boolWidget;
    
    std::unique_ptr<SceneSettingWidget> sceneSettingWidget;    
    std::unique_ptr<FloatNodeWidget> fnodewidget;
    std::unique_ptr<DrawCubeWidget> dcubewidget;
    std::unique_ptr<ColorCollectionWidget> colorwidget; 
    std::unique_ptr<ColorCollectionWidget> colorwidget_1=std::make_unique<ColorCollectionWidget>(nullptr);
    std::unique_ptr<QSplitter> Splitter;
    ModelMenu* ModelActionMenu=nullptr;
    FileMenu* FileActionMenu=nullptr;
    QMenu* ModifyActionMenu=nullptr;
    QAction* ShowGridAction=nullptr;
    std::unique_ptr<EditorMenu> editorMenu;
    QPalette WindowFramePalette;
    std::unique_ptr<TabWidget> tabwidget;
    std::unique_ptr<TabWidget> tabwidget_1;  //This tabwidgets will be used to display Graphics View,it will contained by the splitter
    std::unique_ptr<TreeViewWidget> fileSystemWidget;
    std::unique_ptr<ObjectPresentationWidget> objprswidget;
    std::unique_ptr<ObjectInfoWidget> objinfowidget;  //this will show the properties of the object to display
    Handle(CustomAIS_Shape) shape=new CustomAIS_Shape(DrawCube(80));
    std::unique_ptr<SurfaceInfoWidget> surface_widget=std::make_unique<SurfaceInfoWidget>();
    SurfaceInfo sfaceinfo;
    float cubeSize=0.0f; //This variable is always set when we enabled an object DrawCubeWidget
    DrawCubeDialog* dcubedialog=nullptr;
    QString currentWorkingDirectory=QString();

  public:
  Window_Frame(QWidget* parent_widget);
  ~Window_Frame(){
    if(ModelActionMenu!=nullptr){
      delete ModelActionMenu;
      ModelActionMenu=nullptr;
    }
    if(FileActionMenu!=nullptr){
      delete FileActionMenu;
      FileActionMenu=nullptr;
    }
    if(ShowGridAction){
      delete ShowGridAction;
      ShowGridAction=nullptr;
    }
    if(ModifyActionMenu){
      delete ModifyActionMenu;
      ModifyActionMenu=nullptr;
    }
    if(dcubedialog){
      delete dcubedialog;
      dcubedialog=nullptr;
    }
  }
  
  signals:
  void ChangeCentralWidget(QWidget* widget); //This one is sent whem we want to change the current widget on view
  void GetOpenFileFromDialog(const QString& filepath);
  void OnSetNodeWidgetTripleValue(const Point& pnt);
  void OnSendShape(const TopoDS_Shape& shape);
  void OnSendTransform(const gp_Trsf& transform);
  void IsDone();
  void emitCurrentFolder(QString Folder);
  void emitCurrentFile(QString nCADFile);
  public slots:
  void OnSetToCurrentCentralWidget(QWidget* widget){
    return;
  }  //Get the sent widget and Set it to the current central widget...
 void OnSetDrawCircleBool(bool check){
    if(centralwidget_1.get()!=nullptr){
        //if centralwidget's pointer is not equal to nullptr
        centralwidget_1->DrawCircle=check;
        return;
    }
    return;
 }
 void OnClickOpenStepFileAction(bool toggled ){
   return;
 }
 void OnRenderAIS_Shape(const Handle(CustomAIS_Shape)& shape){
  if(centralwidget_1.get()){
    centralwidget_1->DisplayObject(shape);
    DisplayText(QString(tr("Object is Displayed Successfully")));
    return;
  }
  return;
 }
 void SetStatusTextFromDrawingWidget(const QString& str){
  if(statusBar()!=nullptr){
    statusBar()->showMessage(str,3000); //status should display message after 3000 millisecond (3secs)
  }
  return;
 }
 void OnDisplayWidgetFromGraphWidget(QWidget* widget){
  if(widget==nullptr){
    return;
  }
  std::cout<<"Hello I am in an EventHandler"<<std::endl;
  if(!dockwidget_1.get()){
      return;
  }
    dockwidget_1->SetWidget(widget);
   return;
 }
 void OnSetWireframeMode(bool canSetWireframe){
  if(canSetWireframe){
  if(centralwidget_1.get()){
    
    centralwidget_1->context->SetDisplayMode(AIS_WireFrame,true);
    centralwidget_1->CurrentShadeMode=AIS_WireFrame;
    centralwidget_1->view->Redraw();
    DisplayText(tr("I am currently using WireFrame Mode"));
    return;
  }
  }
  return;
 }
 void OnSetShadedMode(bool canSetShaded){
  if(canSetShaded){
  if(centralwidget_1.get()){
    
   
    centralwidget_1->context->SetDisplayMode(AIS_Shaded,true);
     centralwidget_1->CurrentShadeMode=AIS_Shaded;
    centralwidget_1->view->Redraw();
     DisplayText(tr("I am currently using Shaded Mode"));
    return;
  }
  }
  return;
 }
 void OnSetBothShadedAndWireFrame(bool check){
  if(check){
    if(centralwidget_1.get()){
      centralwidget_1->context->SetDisplayMode(3,true);
       centralwidget_1->CurrentShadeMode=3;
      centralwidget_1->view->Redraw();
       DisplayText(tr("I am currently using both WireFrame Mode and Shaded mode"));
      return;
    }
  }
  return;
 }
 void OnDrawBoundBox(bool check){
  if(check){
    if(centralwidget_1.get()){
      centralwidget_1->context->SetDisplayMode(2,true);
       centralwidget_1->CurrentShadeMode=2;
      centralwidget_1->view->Redraw();
       DisplayText(tr("Displaying Bound Box"));
      return;
    }
  }
  return;
 }
 void OnChooseWireFilter(bool ChooseWireFilter){
  if(ChooseWireFilter){
  if(centralwidget_1.get()){
    centralwidget_1->context->Deactivate();
    centralwidget_1->CurrentSelMode=3;
    centralwidget_1->context->Activate(3); // For Wire Selection
   
    centralwidget_1->view->Redraw();
    
     DisplayText(tr("Wire Selection Filter is Selected"));
  }
  return;
  }

  return;
 }

 void OnChooseVertexFilter(bool check){
  if(check){
    if(centralwidget_1.get()){
        centralwidget_1->context->Deactivate();
        centralwidget_1->CurrentSelMode=1; 
         
      centralwidget_1->context->Activate(1);  // For Vertex Selection
   
      centralwidget_1->view->Redraw();
       DisplayText(tr("Vertex Selection Filter is Selected"));
      return;
    }
    return;
  }
 }
void OnChooseEdgeFilter(bool check){
  if(check){
    if(centralwidget_1.get()){
        centralwidget_1->context->Deactivate();
        centralwidget_1->CurrentSelMode=2; 
      centralwidget_1->context->Activate(2);  //For Edge Selection
   
     centralwidget_1->view->Redraw();        
       DisplayText(tr("Edge Selection Filter is Selected"));
    }
    return;
  }
  return;
}
void OnChooseFaceFilter(bool check){
  if(check){
    if(centralwidget_1.get()){  //For Face Selection
        centralwidget_1->context->Deactivate();
       centralwidget_1->CurrentSelMode=4;  
      centralwidget_1->context->Activate(4);  //For Face Selection
   
      centralwidget_1->view->Redraw();  
       DisplayText(tr("Face Selection Filter is Selected"));
    }
    return;
  }
  return;
}
void OnChooseShapeFilter(bool check){
   if(check){
    if(centralwidget_1.get()){  //For Shape Selection
        centralwidget_1->context->Deactivate();
         centralwidget_1->CurrentSelMode=6;
      centralwidget_1->context->Activate(6);  //For Shape Selection
      centralwidget_1->view->Redraw();  
     DisplayText(tr("Shape Selection Filter is Selected"));
    return;
    }
  }
  return;
}
void OnCreateFnodeWidget(){
  if(nodewidget.get()){
    if(dockwidget_2.get()){
      if(dockwidget_2->GetScrolledWidget()){
        dockwidget_2->RemoveWidget();
      }
      if(nodewidget->receivedFloatNode){
         fnodewidget->SetValue(nodewidget->receivedFloatNode->GetData());
         dockwidget_2->SetWidget(fnodewidget.get());
         return;
      }
    }
  }
  return;
}
//This is called when we want to handle OnSendWidget() from NodeGraphWidget class

void OnSetAutoHilight(bool check){
  if(check){
    if(centralwidget_1.get()){
      centralwidget_1->context->SetAutoActivateSelection(check);
      return;
    }

  }
  else{
     centralwidget_1->context->SetAutoActivateSelection(false);
     return;
  }
  return;
}
void OnToggleShowGrid(bool value){
  if(value){
    centralwidget_1->CreateWorldGrid();
    return;
  }
  centralwidget_1->DeactivateWorldGrid();

  return;
}
void OnToggleUseWindowSize(bool value){
  if(!centralwidget_1.get()){
     DisplayText(tr("No Initialized Window"));
     return;
  }
  if(value){
    centralwidget_1->UseWindowSize=value;
    centralwidget_1->CreateWorldGrid();
    return;
  }
  else{
    centralwidget_1->UseWindowSize=value;
    centralwidget_1->CreateWorldGrid();
   
  }
  return;
}
void OnSetGridX(float value){
  if(sceneSettingWidget.get()){
    if(sceneSettingWidget->SetXEdit->isConverted){
       if(centralwidget_1.get()){
        centralwidget_1->GridSize_X=value;
        centralwidget_1->CreateWorldGrid();
        DisplayText(tr("Coversion Successful"));
        return;
      }
    }
    else{
    DisplayText(tr("Failed to convert "));
    return;
    }
  }
  return;
}
void OnSetGridY(float value){
  if(sceneSettingWidget.get()){
   if(centralwidget_1.get()){
    if(!sceneSettingWidget->SetYEdit->isConverted){
           DisplayText(tr("Failed to convert "));
           return;        
    }
        centralwidget_1->GridSize_Y=value;
        centralwidget_1->CreateWorldGrid();
        DisplayText(tr("Coversion Successful"));
        return;
      }
      
  }
  return;
}
void OnSetGridSpacing(float value){
   if(!sceneSettingWidget.get()){
       DisplayText(tr("Scene Widget is not Created"));
    return;
   }
   if(centralwidget_1.get()){
      if(!sceneSettingWidget->SpaceEdit->isConverted){
          DisplayText(tr("Failed to convert "));
           return;
      }
        centralwidget_1->Grid_Spacing=value;
        centralwidget_1->CreateWorldGrid();
         DisplayText(tr("Coversion Successful"));
        return;
      }
      
  return;
  
}
void DisplayText(const QString& text){
    statusBar()->showMessage(text);
    return;
  }
void OnDrawCubeHandler(bool isTriggered=false){
  dcubedialog=new DrawCubeDialog(this);
  dcubedialog->exec();
  return;
}
void OnSetCubeSize(const float& value){
  if(dcubewidget->input_valueSection->myValueEdit->isConverted){
      cubeSize=value;
      DisplayText(tr("Converted Successfully"));
  }
  else{
    DisplayText(tr("Failed to convert to an object of float"));
  }
  
  return;
}

void OnDrawCube(){
  TopoDS_Shape myshape=DrawCube(cubeSize);
  centralwidget_1->context->Display(new CustomAIS_Shape(myshape),3,0,true);
  return;
}
void OnShowSceneSettings(bool truth){
  if(!dockwidget_1.get()){
    DisplayText(tr("DockWidget is not created"));
    return;
  }
  if(truth){
     centralwidget_1->showSettingAction->setChecked(truth);
     if(sceneSettingWidget.get()){
      if(dockwidget_1->GetScrolledWidget()){
        dockwidget_1->RemoveWidget();
      }
      dockwidget_1->SetWidget(sceneSettingWidget.get());
      sceneSettingWidget->show();
      return;
     }
    
  }
  else{
    if(dockwidget_1->GetScrolledWidget()){
       dockwidget_1->RemoveWidget();
    }   //empty widget
  }
  return;
}
void OnDrawCubeInWorld(bool Checked){
  TopoDS_Shape sh=DrawCube(150);
  
  if(!nodewidget){
    return;
   }
  if(!centralwidget_1){
   return; 
  }
  nodewidget->NodeInputShape=sh;
  if(Checked==true){
    nodewidget->shapedraw=SP_SHAPE;
    return;
  }
  if(Checked==false){
    nodewidget->shapedraw=SP_NULL;
    return;
  }
  return;
}
void OnDrawSphere(bool Checked){
   TopoDS_Shape sh=DrawSphere(50);
  
  if(!nodewidget){
    return;
   }
  if(!centralwidget_1){
   return; 
  }
  nodewidget->NodeInputShape=sh;
  if(Checked==true){
    nodewidget->shapedraw=SP_SHAPE;
    return;
  }
  if(Checked==false){
    nodewidget->shapedraw=SP_NULL;
    return;
  }
  return;
}
void OnDrawCylinder(bool Checked){
   TopoDS_Shape sh=DrawCylinder(25,50);
  
 if(!nodewidget){
    return;
   }
  if(!centralwidget_1){
   return; 
  }
  nodewidget->NodeInputShape=sh;
  if(Checked==true){
    nodewidget->shapedraw=SP_SHAPE;
    return;
  }
  if(Checked==false){
    nodewidget->shapedraw=SP_NULL;
    return;
  }
  return;
}
void OnDrawCone(bool Checked){
    TopoDS_Shape sh=DrawCone(30,0.0,50.0);
     
   if(!nodewidget){
    return;
   }
  if(!centralwidget_1){
   return; 
  }
  nodewidget->NodeInputShape=sh;
  if(Checked==true){
    nodewidget->shapedraw=SP_SHAPE;
    return;
  }
  if(Checked==false){
    nodewidget->shapedraw=SP_NULL;
    return;
  }
  
  
   return;
}
void OnDrawTorus(bool Checked){
   TopoDS_Shape sh=DrawTorus(20,5);
  
   if(!nodewidget){
    return;
   }
  if(!centralwidget_1){
   return; 
  }
  nodewidget->NodeInputShape=sh;
  if(Checked==true){
    nodewidget->shapedraw=SP_SHAPE;
    return;
  }
  if(Checked==false){
    nodewidget->shapedraw=SP_NULL;
    return;
  }
  
  return;
}
void OnDrawCuboid(bool Checked){
  TopoDS_Shape sh=DrawCuboid(40,30,25);
 if(!nodewidget){
    return;
   }
  if(!centralwidget_1){
   return; 
  }
  nodewidget->NodeInputShape=sh;
  if(Checked==true){
    nodewidget->shapedraw=SP_SHAPE;
    return;
  }
  if(Checked==false){
    nodewidget->shapedraw=SP_NULL;
    return;
  }
  return;
  
}
void OnDrawShapePrsUI(){
  if(!centralwidget_1.get()){
     return;
  }
  if(!dockwidget_1.get()){
    return;
  }
  
  Handle(CustomAIS_Shape)& ref_shape=centralwidget_1->ChosenShape;
 
   if(!objprswidget.get()){
     DisplayText(tr("Failed to create the Object Presentation Widget"));
     return;
   }
    if(dockwidget_1->GetScrolledWidget()){
      dockwidget_1->RemoveWidget();  //remove the current widget....
    }

   dockwidget_1->SetWidget(objprswidget.get());
   if(centralwidget_1->IsSelectedColorUsed){
   objprswidget->propsection()->SetPropertiesFromSelectedShape(ref_shape,centralwidget_1->prevChosenMat.DiffuseColor());

   }
   else{
    objprswidget->propsection()->SetPropertiesFromSelectedShapeOnCondition(ref_shape);
   }
   objprswidget->show();
   return;
   
  
}
void OnBaseColorHandler(size_t idx){
  if(!colorwidget.get()){
     DisplayText(tr("Failed to create Colour Collection Widget"));
     return;
  }
  if(!objprswidget.get()){
      DisplayText(tr("Failed to create the Object Presentation Widget"));
     return;
  }
  if(!centralwidget_1.get()){
    return;
  }
  objprswidget->propsection()->SetPropertiesOnCondition(MATERIALCOLOR::MC_BASE);
  if(!dockwidget_2.get()){
     return;
  }
  if(dockwidget_2->GetScrolledWidget()){
    dockwidget_2->RemoveWidget();
  }
  dockwidget_2->SetWidget(colorwidget.get());
   colorwidget->show();
  return;
}

void OnSetObjectBaseColor(){
  if(!colorwidget.get()){
     DisplayText(tr("Failed to create Colour Collection Widget"));
     return;
  }
   
  objprswidget->propsection()->OnSetProperties(colorwidget->GetChosenColor());
  
  return;
}



void OnDisplayFloatNodeWidget(){
  if(!fnodewidget.get()){
      DisplayText(tr("Failed to create float node widget"));
        return;
  }
  if(!dockwidget_2.get()){
     return;
  }
  if(dockwidget_2->GetScrolledWidget()){
    dockwidget_2->RemoveWidget();
  }
  dockwidget_2->SetWidget(fnodewidget.get());
  fnodewidget->show();
  return;
}

void OnChooseBaseColor(){
  if(!centralwidget_1.get()){
    return;
  }
  if(!colorwidget.get()){
    return;
  }
  if(!objprswidget.get()){
    return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
    DisplayText(tr("There is no chosen shape,Please Select a shape"));
    return;
  }
  objprswidget->propsection()->OnSetProperties(colorwidget->GetChosenColor());
  objprswidget->propsection()->SetObjectBaseColor(centralwidget_1->context,centralwidget_1->ChosenShape);
 
  return;

}
void OnAmbientColorHandler(size_t ind){
   if(!colorwidget.get()){
     DisplayText(tr("Failed to create Colour Collection Widget"));
     return;
  }
  if(!objprswidget.get()){
      DisplayText(tr("Failed to create the Object Presentation Widget"));
     return;
  }
  if(!centralwidget_1.get()){
    return;
  }
   objprswidget->propsection()->SetPropertiesOnCondition( MATERIALCOLOR::MC_AMBIENT);
  if(!dockwidget_2.get()){
     return;
  }
  if(dockwidget_2->GetScrolledWidget()){
    dockwidget_2->RemoveWidget();
  }
   dockwidget_2->SetWidget(colorwidget.get());
  return;
}

void OnDiffuseColorHandler(size_t ind){
  if(!colorwidget.get()){
     DisplayText(tr("Failed to create Colour Collection Widget"));
     return;
  }
  if(!objprswidget.get()){
      DisplayText(tr("Failed to create the Object Presentation Widget"));
     return;
  }
  if(!centralwidget_1.get()){
    return;
  }
  objprswidget->propsection()->SetPropertiesOnCondition(MATERIALCOLOR::MC_DIFFUSE);
    if(!dockwidget_2.get()){
     return;
  }
  if(dockwidget_2->GetScrolledWidget()){
    dockwidget_2->RemoveWidget();
  }
    dockwidget_2->SetWidget(colorwidget.get());
  return;
}

void OnSpecularColorHandler(size_t ind){
   if(!colorwidget.get()){
     DisplayText(tr("Failed to create Colour Collection Widget"));
     return;
  }
  if(!objprswidget.get()){
      DisplayText(tr("Failed to create the Object Presentation Widget"));
     return;
  }
  if(!centralwidget_1.get()){
    return;
  }
   objprswidget->propsection()->SetPropertiesOnCondition(MATERIALCOLOR::MC_SPECULAR);
   if(!dockwidget_2.get()){
     return;
  }
  if(dockwidget_2->GetScrolledWidget()){
    dockwidget_2->RemoveWidget();
  }
  dockwidget_2->SetWidget(colorwidget.get());
  return;
}

void OnEmissiveColorHandler(size_t ind){
  if(!colorwidget.get()){
     DisplayText(tr("Failed to create Colour Collection Widget"));
     return;
  }
  if(!objprswidget.get()){
      DisplayText(tr("Failed to create the Object Presentation Widget"));
     return;
  }
  if(!centralwidget_1.get()){
    return;
  }
    objprswidget->propsection()->SetPropertiesOnCondition(MATERIALCOLOR::MC_EMISSIVE);
    if(!dockwidget_2.get()){
     return;
  }
  if(dockwidget_2->GetScrolledWidget()){
    dockwidget_2->RemoveWidget();
  }
  dockwidget_2->SetWidget(colorwidget.get());
  return;
} 

void OnChooseAmbientColor(){
   if(!centralwidget_1.get()){
    return;
  }
  if(!colorwidget.get()){
    return;
  }
  if(!objprswidget.get()){
    return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
    DisplayText(tr("There is no chosen shape,Please Select a shape"));
    return;
  }
  objprswidget->propsection()->OnSetProperties(colorwidget->GetChosenColor());
  objprswidget->propsection()->SetObjectAmbientColor(centralwidget_1->context,centralwidget_1->ChosenShape);
   centralwidget_1->prevChosenMat=objprswidget->propsection()->OutputMaterial();
   
   
   return;
}

void OnChooseDiffuseColor(){
  if(!centralwidget_1.get()){
    return;
  }
  if(!colorwidget.get()){
    return;
  }
  if(!objprswidget.get()){
    return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
    DisplayText(tr("There is no chosen shape,Please Select a shape"));
    return;
  }
  objprswidget->propsection()->OnSetProperties(colorwidget->GetChosenColor());
  objprswidget->propsection()->SetObjectDiffuseColor(centralwidget_1->context,centralwidget_1->ChosenShape);
   centralwidget_1->prevChosenMat=objprswidget->propsection()->OutputMaterial();
  return;
}

void OnChooseSpecularColor(){
  if(!centralwidget_1.get()){
    return;
  }
  if(!colorwidget.get()){
    return;
  }
  if(!objprswidget.get()){
    return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
    DisplayText(tr("There is no chosen shape,Please Select a shape"));
    return;
  }
  objprswidget->propsection()->OnSetProperties(colorwidget->GetChosenColor());
  objprswidget->propsection()->SetObjectSpecularColor(centralwidget_1->context,centralwidget_1->ChosenShape);
   centralwidget_1->prevChosenMat=objprswidget->propsection()->OutputMaterial();
  return;
}

void OnChooseEmissiveColor(){
  if(!centralwidget_1.get()){
    return;
  }
  if(!colorwidget.get()){
    return;
  }
  if(!objprswidget.get()){
    return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
    DisplayText(tr("There is no chosen shape,Please Select a shape"));
    return;
  }
  objprswidget->propsection()->OnSetProperties(colorwidget->GetChosenColor());
  objprswidget->propsection()->SetObjectEmissiveColor(centralwidget_1->context,centralwidget_1->ChosenShape);
   centralwidget_1->prevChosenMat=objprswidget->propsection()->OutputMaterial();
  return;
}

void OnSetObjectTransp(float value){
  if(value>=0.0000000000 && value<=1.0){
  if(!objprswidget->propsection()){
    DisplayText(tr("Material Property Section is not created,Try to create it"));
    return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
     DisplayText(tr("There is no chosen shape,Please Select a shape"));
    return;
  }
  objprswidget->propsection()->SetObjectTransparency(centralwidget_1->context,centralwidget_1->ChosenShape,value);
  }
  return;
}
void OnSetShadingType(const QString& value){
  if(!objprswidget->propsection()){
    DisplayText(tr("Material Property Section is not created,Try to create it"));
    return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
     DisplayText(tr("There is no chosen shape,Please Select a shape"));
    return;
  }
  objprswidget->propsection()->SetObjectShadingType(centralwidget_1->context,centralwidget_1->ChosenShape);
  return;
}
void DestroyMatPropWidget(){
  if(!dockwidget_1.get()){
      DisplayText(tr("The dockwidget is not created"));
      return;
  }
  if(!dockwidget_2.get()){
   DisplayText(tr("The dockwidget is not created"));
      return;
  }
  if(dockwidget_1->GetScrolledWidget()==objprswidget.get()){

      dockwidget_1->RemoveWidget();
  }
   if(dockwidget_2->GetScrolledWidget()==colorwidget.get()){
    dockwidget_2->RemoveWidget();
  }
  return;
}
void OnUpdateFloatNodeWidgetValue(const float& value){
  if(!dockwidget_2.get()){
     DisplayText(tr("DocWidget Is not Created"));
     return;
  }
  if(!fnodewidget.get()){
    DisplayText(tr("Float Node Widget Is not Created"));
     return;
  }
  if(dockwidget_2->GetScrolledWidget()==fnodewidget.get()){
    fnodewidget->SetValue(value);
    return;    
  }
  else{
     dockwidget_2->RemoveWidget();
     dockwidget_2->SetWidget(fnodewidget.get());
     fnodewidget->SetValue(value);
     return;
  }

  return;
}
void OnSetValueForFnodeWidget(float value){
   if(!nodewidget.get()){
    return;
   }
   if(!fnodewidget.get()){
     return;
   }
   if(nodewidget->receivedFloatNode){
        nodewidget->receivedFloatNode->SetFloatData(value);
        return;
   }
  
   return;
}
void OnDisplayObjects(const std::vector<Handle(CustomAIS_Shape)>& shapes){
  if(!centralwidget_1.get()){
     return;
  }
  centralwidget_1->DisplayObjects(shapes);  //move the shapes
  return;
}

void OnDestroyFloatNodeWidget(){
  if(!dockwidget_2.get()){
   DisplayText(tr("The dockwidget is not created"));
    return;
  }
  if(dockwidget_2->GetScrolledWidget()==fnodewidget.get()){
   std::cout<<"Shape Is the Same"<<std::endl;
     dockwidget_2->RemoveWidget();
       OnSetPreviousColor();
     return;
  }
   if(dockwidget_2->GetScrolledWidget()==boolWidget.get()){
    OnSetPreviousColor();
     dockwidget_2->RemoveWidget();
     return;
  }
  OnSetPreviousColor();
  return;
}

void OnSetRefractiveIndex(const float& value){
  if(!centralwidget_1.get()){
    return;
  }
  if(!objprswidget.get()){
    return;
  }
  if(!centralwidget_1->ChosenShape.IsNull() && !centralwidget_1->context.IsNull()){
     if(value>=1.0 && value<=5.0){
     objprswidget->propsection()->SetObjectRefractiveIndex(centralwidget_1->context,centralwidget_1->ChosenShape,value);
     }
  }
  return;
}
void CreateBoolWidget(){
  if(!boolWidget.get()){
     return;
  }
  if(!nodewidget.get()){
    return;
  }
   if(dockwidget_2->GetScrolledWidget()){
    dockwidget_2->RemoveWidget();
  }
  if(nodewidget->receivedBoolNode){
  boolWidget->SetChecked(nodewidget->receivedBoolNode->GetInputValue());
  }
  dockwidget_2->SetWidget(boolWidget.get());

  return;
}



void OnBoolHandler(bool value){
  if(!boolWidget.get()){  //if the internal pointer is not initializing 
    return;
  }
  if(!nodewidget.get()){
      return;
  }
  if(!nodewidget->receivedBoolNode){
    return;
  }
  nodewidget->receivedBoolNode->SetInputValue(value);
    return;
}


void OnHandleHighlightOfSubShape(const TopoDS_Shape& shape){
   if(!centralwidget_1.get()){
       return;
   }
   if(centralwidget_1->context.IsNull()){
       return;
   }
   centralwidget_1->HighlightSubShapes(shape);
   std::cout<<"Shape Currently Highlighted"<<std::endl;
   return;
}

void SetShapeTypeName(){
  if(!centralwidget_1.get()){
       return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
       return;
  }
  if(!sceneSettingWidget.get()){
    return;
  }
  sceneSettingWidget->STLabel()->setText(STM::shapetypemap.at(centralwidget_1->ChosenShape->Shape().ShapeType()));
}

void OnSetPreviousColor(){
  if(!centralwidget_1.get()){
       return;
  }
  if(centralwidget_1->currentObject.IsNull()){
       DisplayText(tr("No Object is Selected From the Node"));
       std::cout<<"Current Object Is Currently Null"<<std::endl;
       return;
  }
  if(centralwidget_1->context->IsDisplayed(centralwidget_1->currentObject)){
    centralwidget_1->currentObject->SetColor(centralwidget_1->currentObjectColor);
    
    centralwidget_1->context->Redisplay(centralwidget_1->currentObject,true);
     DisplayText(tr("Object  is Selected From the Node"));
     std::cout<<"Object Is Currently Changed"<<std::endl;
  }
   return;
}
void OnHandleEmittedShape(const TopoDS_Shape& shape){
  if(!centralwidget_1.get()){
    return;
  }
  if(!nodewidget.get()){
    return;
  }
  nodewidget->LoopModelAndFindShape(shape);
  return;
}
void OnHandleEmittedTrsfShape(const TopoDS_Shape& shape){
  if(!nodewidget.get()){
        return;
  }
  nodewidget->UpdateShape(shape);
  return;
}

void OnSpawnColorSelectionWidget(const int& index){
  if(!colorwidget_1.get()){
    return;
  }
  if(!dockwidget_2.get()){
    return;
  }
  if(dockwidget_2->GetScrolledWidget()){
    dockwidget_2->RemoveWidget();
  }
  dockwidget_2->SetWidget(colorwidget_1.get());

  return;
}
void OnSetSelectionColorFromColorWidget(){
  if(colorwidget_1.get()){
     if(centralwidget_1.get()){
     sceneSettingWidget->hilisection->FaceColorWidget()->SetColorFromOC(colorwidget_1->GetChosenColor()); 
      centralwidget_1->OnChangeSelectionColor(colorwidget_1->GetChosenColor());
      
     }
  }
  return;
}
//w3e bind it to ConstructPointNodeAction.....
void OnHandleConstructPointNode(bool Checked){
   //dummy Value
  if(Checked==false){
    nodewidget->CanDrawPointNode=Checked;
  }
  return;
}
void OnSetValuesForTriple(const Point& pnt){
  if(!nodewidget){
    return;
  }
  nodewidget->x=pnt.X();
  nodewidget->y=pnt.Y();
  nodewidget->z=pnt.Z();
  nodewidget->CanDrawPointNode=true;
  cout<<"gp_Pnt("<<pnt.X()<<","<<pnt.Y()<<","<<pnt.Z()<<")"<<std::endl;
  
  return;
}
void OnSetNodeTransformBool(bool Checked){
  if(!nodewidget){
    return;
  }
  if(!centralwidget_1){
     return;
  } 
  
  if(Checked==true){
    emit OnSendTransform(centralwidget_1->SentTransform);
    return;
  }
  if(Checked==false){
   nodewidget->rstate=RS_NULL;
   return;
  }
  return;
}
void OnHandleConvertToShapeNode(bool Checked){
  if(!centralwidget_1){
    return;
  }
if(!nodewidget){
     return; 
 }
 if(Checked==true){
  if(!centralwidget_1->ChosenShape.IsNull()){
    emit OnSendShape(centralwidget_1->ChosenShape->Shape());
    
}
  
 }
  if(Checked==false){
    nodewidget->shapedraw=SP_NULL;
  }
  return;
}
void OnHandleSentTransform(const gp_Trsf& trsf){
  if(!nodewidget){
    return;
  }
  nodewidget->NodeInputTransform=trsf;
  nodewidget->rstate=RS_TRANSFORM;

  return;
}
void OnHandleSentShape(const TopoDS_Shape& shape){
   if(!nodewidget){
    return;
  }
  if(!centralwidget_1){
    return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
    return;
  }
 

  BRepBuilderAPI_Copy copiedShape(shape);
  copiedShape.Perform(shape);
  if(copiedShape.IsDone()){
   nodewidget->NodeInputShape=copiedShape.Shape();
  nodewidget->shapedraw=SP_SHAPE;  
  }
  
  return;
}
void OnHandleEmittedParentShape(const TopoDS_Shape& shape){
  if(!centralwidget_1){
    return;
  }
  centralwidget_1->OnGetEmitShape(shape);
  return;
}
void OnHighlightFace(const int& id){
   if(!centralwidget_1){
    return;
  }
  centralwidget_1->HighlightFace(id);  //highlight face using Id;
  return;
}
void OnHighlightEdge(const TopoDS_Shape& edge){
   if(!centralwidget_1){
    return;
  }
  centralwidget_1->HighlightEdge(edge);
  return;
}
void OnHandleDestroyPrevObject(){
  if(!centralwidget_1){
    return;
  }
  if(!centralwidget_1->currentObject.IsNull()){
      centralwidget_1->currentObject->SetVisualAspect(centralwidget_1->currentObjectColor);
      centralwidget_1->context->Redisplay(centralwidget_1->currentObject,true);
      centralwidget_1->currentObject.Nullify();
  }
  return;
}
void OnShowObjectInfo(){
  
  if(!centralwidget_1){
     return;
  }
  if(centralwidget_1->ChosenShape){
  
  if(surface_widget){
    disconnect(surface_widget.get(),&SurfaceInfoWidget::EmitIndex,this,&Window_Frame::OnGetFaceIndex);
    surface_widget=std::make_unique<SurfaceInfoWidget>();
    connect(surface_widget.get(),&SurfaceInfoWidget::EmitIndex,this,&Window_Frame::OnGetFaceIndex);
  }
    if(dockwidget_1->GetScrolledWidget()){
      dockwidget_1->RemoveWidget();
    }
    surface_widget->SetCurrentShape(centralwidget_1->ChosenShape);

    surface_widget->SetSurfaceInfos(centralwidget_1->ChosenShape);
    dockwidget_1->SetWidget(surface_widget.get());
  }
     
  return;
}
void OnDisplayFaceInfo(int id){
  if(!centralwidget_1){
    return;
  }
  if(centralwidget_1->ChosenShape.IsNull()){
    return;
  }
  SURFACE::SurfaceInfo info;
  SURFACE::GetSurfaceInfo(centralwidget_1->ChosenShape->GetFace(id),info);
  surface_widget->SetSurfaceInfo(info,QString("Surface")+QString::number(id));
  if(dockwidget_2->GetScrolledWidget()){
    dockwidget_2->RemoveWidget();
  }
  dockwidget_2->SetWidget(surface_widget.get());
  return;
  
}
void OnGetFaceIndex(bool value){
  if(!centralwidget_1){
    return;
  }
  if(!sceneSettingWidget){
    return;
  }
 
  if(value){
  centralwidget_1->chmode=CM_FACE;
  std::cout<<"I am Currently in FaceIndex() method"<<std::endl;
  }
  else{
    centralwidget_1->chmode=CM_NULL;
  }
   
  return;
}
void OnGetEdgeId(bool value){
   if(!centralwidget_1){
    return;
  }
  if(!sceneSettingWidget){
    return;
  }
 
  if(value){
  centralwidget_1->chmode=CM_EDGE;
  
  }
  else{
    centralwidget_1->chmode=CM_NULL;
  }
   
  return;
}
void OnHandleFacePoint(bool value){
  OnHandleConstructPointNode(value);
  return;
}
void OnHandleFace(const TopoDS_Face& face){
  if(!centralwidget_1){
    return;
  }
  if(!nodewidget){
    return;
  }
  nodewidget->nodeInputFace=face;
  nodewidget->shapedraw=SP_FACE;
  return;
}
void OnHandleFaceBool(bool value){
  if(!nodewidget){
    return;
  }
  nodewidget->shapedraw=SP_NULL;
  return;
}
void OnOpenCurrentFolder(){
  QFileDialog dialog(this,tr("NodeCAD File Dialog"));
  dialog.setFileMode(QFileDialog::Directory);
  dialog.setViewMode(QFileDialog::Detail);

  if(dialog.exec()){
    currentWorkingDirectory=dialog.selectedFiles().first();
   emit emitCurrentFolder(currentWorkingDirectory);
    return;
  }
  return;
}
void onHandleEmittedFolder(QString Folder){
  if(fileSystemWidget){
    fileSystemWidget->SetRootPath(Folder);
    if(tabwidget_1->indexOf(fileSystemWidget.get())!=-1){ //that is,it is found
       tabwidget_1->setTabText(tabwidget_1->indexOf(fileSystemWidget.get()),Folder);
       return;
   }   
   else{
     fileSystemWidget->SetRootPath(Folder);
    tabwidget_1->addTab(fileSystemWidget.get(),Folder);
    return;
   }
  }
  
  return;
}
void onWriteFileToPath(const QString& str){
  
  if(currentWorkingDirectory==tr("")){
    OnOpenCurrentFolder();
    if(currentWorkingDirectory!=tr("")){
      QModelIndex index=fileSystemWidget->currentIndex();
      if(!index.isValid()){ 
      index=fileSystemWidget->Index(currentWorkingDirectory);
      }
      if(!fileSystemWidget->IsDir(index)){
           index=fileSystemWidget->Index(currentWorkingDirectory);
      }
      QString folderPath=fileSystemWidget->FilePath(index);
      QString fname=str;
      if(!fname.endsWith(tr(".nCAD"),Qt::CaseSensitive)){
         fname+=".nCAD";
      }
     
      QFile file(folderPath + "/"+fname);
      nodewidget->FileName=folderPath + "/" +fname;
      if(file.open(QIODevice::WriteOnly)){
        file.write(nodewidget->fileArray);
        file.close();
        fileSystemWidget->UpdateView(index);
        std::cout<<"Successfully Saved"<<endl;
        nodewidget->isFileSaved=true;
      }


  }
  }
  else{
     QModelIndex index=fileSystemWidget->currentIndex();
      if(!index.isValid()){ 
      index=fileSystemWidget->Index(currentWorkingDirectory);
      }
      if(!fileSystemWidget->IsDir(index)){
           index=fileSystemWidget->Index(currentWorkingDirectory);
      }
      QString folderPath=fileSystemWidget->FilePath(index);
      QString fname=str;
      if(!fname.endsWith(tr(".nCAD"),Qt::CaseSensitive)){
         fname+=".nCAD";
      }
     
      QFile file(folderPath + "/"+fname);
         nodewidget->FileName=folderPath + "/" +fname;
      if(file.open(QIODevice::WriteOnly)){
        file.write(nodewidget->fileArray);
        file.close();
        fileSystemWidget->UpdateView(index);
        std::cout<<"Successfully Saved"<<endl;
        nodewidget->isFileSaved=true;
      }
  }
  return;

}
void OnOpenFileDialogForFile(){
    QFileDialog dialog(this,tr("NodeCAD File Dialog"),QDir::currentPath(),tr("CAD Files (*.nCAD)"));
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if(dialog.exec()){
      emitCurrentFile(dialog.selectedFiles().first());
      return;
    }
    else{
      return;
    }
}
void OnOpenNCAD(const QString& str){
  if(str==tr("")){
    return;
  }
  if(!nodewidget){
    return;
  }
  if(!str.endsWith(tr(".nCAD"),Qt::CaseSensitive)){
     cout<<"FileName Does Not End with .nCAD,Find the File name that ends with .nCAD"<<"\n";
     return;
  }
  QFile file(str);
  nodewidget->FileName=str;
  if(file.open(QIODevice::ReadOnly)){
    auto bytearray=file.readAll();
    nodewidget->ClearScene();
    nodewidget->LoadScene(QJsonDocument::fromJson(bytearray).object());
     if(centralwidget_1){
     centralwidget_1->OnClearView();
     }
    std::cout<<"Successful Loading"<<"\n";
    nodewidget->isFiledSaved=true;
    file.close();
  }
  return;
}
void OnCloseFolder(){ //to close a folder
  if(currentWorkingDirectory==tr("")){
    cout<<"No current Working Directory"<<"\n";
    return;
  }
  if(!tabwidget_1){
      return;
  }
  if(tabwidget_1->indexOf(fileSystemWidget.get())!=-1){
    tabwidget_1->removeTab(tabwidget_1->indexOf(fileSystemWidget.get()));
    fileSystemWidget->SetRootPath(tr(""));
    currentWorkingDirectory=tr("");
    nodewidget->FileName=tr("");
  }
   return;
}
void OnRenameFolder(){
  fileSystemWidget->edit(fileSystemWidget->currentIndex());
  return;
}
void OnCreateFolder(){
  auto index=fileSystemWidget->currentIndex();
  if(!index.isValid()){
     bool Ok;
  auto FileName=QInputDialog::getText(nullptr,tr("NodeCAD Text Input Dialog"),tr("Folder Name:"),QLineEdit::Normal,tr(""),&Ok);
    if(!Ok && FileName.isEmpty()){
         return;
    }
   fileSystemWidget->MakeDir(QModelIndex(),FileName);
   return;
  }
  if(fileSystemWidget->IsDir(index)){
  bool Ok;
  auto FileName=QInputDialog::getText(nullptr,tr("NodeCAD Text Input Dialog"),tr("Folder Name:"),QLineEdit::Normal,tr(""),&Ok);
    if(!Ok && FileName.isEmpty()){
         return;
    }
   fileSystemWidget->MakeDir(index,FileName);
  }
  return;
}
void OnRenameFile(){
  fileSystemWidget->edit(fileSystemWidget->currentIndex());
  return;
}
};



#endif