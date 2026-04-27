#ifndef DRAWINGCENTRALWIDGET_HPP
#define DRAWINGCENTRALWIDGET_HPP
#include<QtWidgets/QWidget>
#include<QtGui/QPainter>
#include<QtGui/QPalette>
#include<GraphicsLine.hpp>
#include<QtCore/Qt>
#include<vector>
#include<AIS_InteractiveContext.hxx>
#include<Prs3d_DatumAspect.hxx>
#include<V3d_View.hxx>
#include<Graphic3d_GraphicDriver.hxx>
#include<OpenGl_GraphicDriver.hxx>
#include<Aspect_DisplayConnection.hxx>
#include<AIS_ViewCube.hxx>
#include<AIS_ViewController.hxx>
#include<QtGui/QMouseEvent>
#include<QtGui/QWheelEvent>
#include<QtGui/QResizeEvent>
#include<QtWidgets/QMenu>
#include<V3d_TypeOfOrientation.hxx>
#include<Prs3d_LineAspect.hxx>
#include<Aspect_TypeOfLine.hxx>
#include<IntCurvesFace_ShapeIntersector.hxx>
#include<GeomAPI_IntCS.hxx>
#include<TopoDS.hxx>
#include<Geom_Curve.hxx>
#include<ElCLib.hxx>
#include<QtGui/QundoStack>
#include<WNT_Window.hxx>
#include<BRepPrimAPI_MakeBox.hxx>
#include<TopoDS_Shape.hxx>
#include<AIS_Shape.hxx>
#include<gp_Ax3.hxx>
#include<gp_Dir.hxx>
#include<V3d_RectangularGrid.hxx>
#include<memory>
#include<QtGui/QAction>
#include<ViewDirection.hpp>
#include<CameraAnimator.hpp>
#include<Sceneobject.hpp>
#include<AIS_Plane.hxx>
#include<WorkingPlane.hpp>
#include<SceneObject.hpp>
#include<gp_Lin.hxx>
#include<QtCore/QString>
#include<ViewCube.hpp>
#include<TopExp_Explorer.hxx>
#include<AIS_AnimationCamera.hxx>
#include<GraphicsCircle.hpp>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<Geom_Circle.hxx>
#include<gp_Pln.hxx>
#include<GeomAPI.hxx>
#include<algorithm>
#include<BRepPrimAPI_MakeSphere.hxx>
#include<QtWidgets/QMenu>
#include<BRepPrimAPI_MakeCone.hxx>
#include<BRepPrimAPI_MakeCylinder.hxx>
#include<AllCommand.hpp>
#include<AIS_Manipulator.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<Graphic3d_Vec2.hxx>
#include<DeleteCommand.hpp>
#include<ShapeUtil.hpp>
#include<BRepBuilderAPI_Transform.hxx>
#include<BRepBuilderAPI_Copy.hxx>
#include<UndoTransformCommand.hpp>
#include<UndoCreationCommand.hpp>
#include<EventManager.hpp>
#include<NCollection_List.hxx>
#include<unordered_map>
#include<Point.hpp>
#include<SurfaceUtility.hpp>
#include<iostream>
#include<StdSelect_BRepOwner.hxx>
#include<ShadingTypeMap.hpp>
#include<AIS_Circle.hxx>
#include<AIS_Point.hxx >
#include<Geom_Point.hxx>
#include<Geom_CartesianPoint.hxx>
#include<TopoDS.hxx>
#include<gp_Vec.hxx>
#include<FaceMenu.hpp>
#include<EdgeMenu.hpp>
//This file will enter 10,000 LOC
//We have to create a dialog for viewport setting,Drawing widget is also a viewport
//On Object Creation,deletion,editing,Transform
using namespace Shape_Utility;
using namespace std;
using namespace SURFACE;
using namespace STM;
enum CHOOSE_MODE{
  CM_FACE,
  CM_EDGE,
  CM_NULL
};
enum SELECTED_STATE{
  SELECT,
  NULL_SELECT,
  EDGE_SELECT,
  FACE_SELECT
};
class DrawingCentralWidget:public QWidget{
private:
Q_OBJECT
public:
size_t QActionsNum;  //Number of QActions 
//For Drawing Cubes,basic primitives
bool DrawCube=false;
bool isDrawingCube=false;
bool DrawLine=false;
bool isDrawingLine=false;
bool DrawCircle=true;
bool isDrawingCircle=false;


bool canOrbit=false;
bool isPan=false; //it is panning
bool isPanningView=false;  //this is set when isPan is set
std::unique_ptr<QUndoStack> UndoStack;  //this will store all redo and undo commands of all operation and commands in this widget
bool m_KeepPreviousObject=false;  //PreviousShape Variable will be used to store object after the current object has been displayed,this will be useful to avoid redisplay
bool m_CanDisplayWireFrame=false;
bool m_CanDisplayShaded=false;
bool m_CanDisplayBoth=false;  //it can display both WireFrame and Shaded
bool canSetPlane=false;

bool canGatherPoints=false;   ///gather points using
Handle(Aspect_DisplayConnection) display;
Handle(OpenGl_GraphicDriver) driver;
Handle(V3d_View) view;
Handle(V3d_Viewer) Viewer;
Handle(AIS_InteractiveContext) context;
Handle(WNT_Window) Window;

bool isLightOn=false;
bool UseWindowSize=true;
bool isObjectTransformed=false;

 TopoDS_Shape SphereShape;
 TopoDS_Shape ConeShape;
 TopoDS_Shape CylShape;

QMenu* SelectedMenu=nullptr;
QAction* DeleteAction=nullptr;
QAction* SelectAction=nullptr;
QAction* EditAction=nullptr;
QAction* UndoAction=nullptr;
QAction* RedoAction=nullptr;
QAction* ScaleAction=nullptr;
QAction* RotateAction=nullptr;
QAction* TranslateAction=nullptr;
std::unique_ptr<QAction> ShapeTypeAction;
QAction* ShapePrsAction=nullptr;
std::unique_ptr<QAction> ConstructPointNodeAction;
std::unique_ptr<QAction> ConstructTransformNodeAction;
std::unique_ptr<QAction> ConstructShapeNodeAction;
std::unique_ptr<QAction> ShowObjectInfo;
std::unique_ptr<QAction> convertPointAction; //this converts the face point to nodes
std::unique_ptr<QAction> ShowEdgeInfo;
std::unique_ptr<FaceMenu> faceMenu;
std::unique_ptr<EdgeMenu> edgeMenu; 
bool IsShapePrsAdded=false;   //this is to keep track of whether shape presentation menu item has been added
 TopoDS_Face selFace;
 TopoDS_Edge selEdge;
QAction* LinePrsAction=nullptr;
bool IsLinePrsAdded=false;  //thus is to keep track of whether lineprsaction is added to SelectedMenu or not

TopoDS_Shape SelectedShape;
QMenu* DockMenus=nullptr;
QAction* showSettingAction=nullptr;
QAction* DrawCubeAction=nullptr;
QAction* DeleteObjectGizmoAction=nullptr;
std::unique_ptr<QAction> refreshAction;

gp_Ax3 currentUCS=gp::XOY();   //This is a plane unto which drawings will be performed
gp_Vec PreviousDirection;
Handle(Graphic3d_AspectMarker3d) GridAspect=new Graphic3d_AspectMarker3d(Aspect_TOM_RING1,Quantity_NOC_LIGHTSTEELBLUE,2);
bool ShowGrid=true;
bool ShowPlane=true;
bool ShowDrawingPlane=true;
bool IsSeen=false; //this is initialized when an object is found in Shapes;
bool IsSelectedColorUsed=false;
int CurrentSelMode=-1; //Current Selection Mode
int CurrentShadeMode=3;
int WindowHeight=0;  //This is for the binded window;
int WindowWidth=0;
Handle(AIS_Manipulator) ObjectGizmo;    //This is the object gizmo

Handle(ViewCube) viewcube=new ViewCube();
Handle(AIS_ViewCubeOwner) viewcubeowner=new AIS_ViewCubeOwner(viewcube,V3d_Xpos);
const double dpr=devicePixelRatioF();


Handle(CustomAIS_Shape) ChosenShape;   //This will be a template for all chosen shapes
Handle(CustomAIS_Shape) PreviousShape;

Handle(CustomAIS_Shape) surfaceWidgetShape;

Handle(CustomAIS_Shape) prevCurrentObject;
Handle(CustomAIS_Shape) currentObject;   //this is used when a node is clicked,it will store the object 
Quantity_Color currentObjectColor;


Handle(CustomAIS_Shape) emittedShape;  //this is to select subshapes of a shape
Handle(CustomAIS_Shape) prevEmittedShape;
Handle(CustomAIS_Shape)  currSelShape;
Handle(CustomAIS_Shape) currDetShape;
Quantity_Color currentShapeColor;
gp_Pnt2d lastpoint; 
gp_Pnt2d panlastpoint;   //this will store the pan 
bool LastPointIsSet=false;
WorkingPlane Plane;
float GridSize_X=0.0;
float GridSize_Y=0.0;
float Grid_Spacing=2.0f;

bool isScaleGizmoEnabled=false;
bool isTranslateGizmoEnabled=false;
bool isRotateGizmoEnabled=false;

 
EventManager evt_manager;
Handle(Prs3d_Drawer) detected_drawer;

Handle(Prs3d_Drawer) selected_drawer;
Handle(AIS_Point) pointMarker=new AIS_Point(new Geom_CartesianPoint(0.0,0.0,0.0));

double x_value=0.0;
double y_value=0.0;
double z_value=0.0;

double int_x=0.0; //intersection point
double int_y=0.0;
double int_z=0.0;
gp_Trsf PrevTrsf;
gp_Trsf CurrTrsf;
gp_Trsf SentTransform;  //this is the transform that is sent from drawing widget to nodegraph
size_t objectCount=0;
std::unordered_map<size_t,Handle(CustomAIS_Shape)> Shapes;
Graphic3d_MaterialAspect prevChosenMat;
size_t ChosenId=0;

unsigned int faceIndex=0; //invalid index
unsigned int edgeIndex=0;

Quantity_Color chosenFaceColor;
Quantity_Color chosenEdgeColor;
Quantity_Color chosenVertexColor;

CHOOSE_MODE chmode=CM_NULL; //to select and isolate a particular subshape in the scene for intersection
SELECTED_STATE st;
SELECTED_STATE st1;//for per face selection and per edge selection
TopoDS_Face surfaceWidgetFace;
public:
DrawingCentralWidget(QWidget* parent_widget):QWidget(parent_widget){
    std::cout<<"I am in Drawing CentralWidget"<<"\n";
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NativeWindow);
    setFocusPolicy(Qt::StrongFocus);
    setBackgroundRole(QPalette::NoRole);
    setMouseTracking(true);
     UndoStack.reset(new QUndoStack);  //Allocate memory for QUndoStack
    winId();
    show();
    Shapes.reserve(100);   //maximum shapes in the scene to prevent rehashing
    edgeMenu=std::make_unique<EdgeMenu>();
    faceMenu=std::make_unique<FaceMenu>();

    DeleteAction=new QAction(tr("Delete"),nullptr);
    SelectAction=new QAction(tr("Select"),nullptr); 
   
    UndoAction=UndoStack->createUndoAction(this,tr("&Undo"));

    RedoAction=UndoStack->createRedoAction(this,tr("&Redo"));
    UndoAction->setShortcut(Qt::CTRL|Qt::Key_S);
    RedoAction->setShortcut(Qt::CTRL|Qt::Key_K);

    pointMarker->SetColor(Quantity_NOC_PERU);
    pointMarker->SetMarker(Aspect_TOM_O);
    
    SelectedMenu=new QMenu;
    TranslateAction=new QAction(tr("Translate"),nullptr);
    TranslateAction->setCheckable(true);
    TranslateAction->setChecked(true);

    RotateAction=new QAction(tr("Rotate"),nullptr);
    RotateAction->setCheckable(true);
    RotateAction->setChecked(true);
    ShowEdgeInfo=make_unique<QAction>(tr("Show Edge Info"),nullptr);
    ScaleAction=new QAction(tr("Scale"),nullptr);
    ScaleAction->setCheckable(true);
    ScaleAction->setChecked(true);
    DeleteObjectGizmoAction=new QAction(tr("Destroy Gizmo"),nullptr);
    
    ShapePrsAction=new QAction(tr("Object Presentation"),nullptr);
    LinePrsAction=new QAction(tr("Line Presentation"),nullptr);
    ShapeTypeAction=std::make_unique<QAction>(tr("Show Shape Type"),nullptr);
    
    ConstructTransformNodeAction=std::make_unique<QAction>(tr("Convert To TransformNode"),nullptr);
     ConstructTransformNodeAction->setCheckable(true);
      ConstructPointNodeAction=std::make_unique<QAction>(tr("Convert To Point Node"));
 ConstructPointNodeAction->setCheckable(true);
    ConstructShapeNodeAction=std::make_unique<QAction>(tr("Convert To ShapeNode"),nullptr);
    ConstructShapeNodeAction->setCheckable(true);
    ShowObjectInfo=make_unique<QAction>(tr("Show Object Info"),nullptr);
    convertPointAction=make_unique<QAction>(tr("Convert Intersect Point To Node"),nullptr);
    convertPointAction->setCheckable(true);
    SelectedMenu->addAction(DeleteAction);
    SelectedMenu->addAction(SelectAction);
    SelectedMenu->addAction(UndoAction);
    SelectedMenu->addAction(RedoAction);
    SelectedMenu->addAction(ScaleAction);
    SelectedMenu->addAction(RotateAction);
    SelectedMenu->addAction(TranslateAction);
    SelectedMenu->addAction(DeleteObjectGizmoAction);
    SelectedMenu->addAction(ShapeTypeAction.get());
    SelectedMenu->addAction(ConstructPointNodeAction.get());
    SelectedMenu->addAction(ConstructTransformNodeAction.get());
    SelectedMenu->addAction(ConstructShapeNodeAction.get());
    SelectedMenu->addAction(ShowObjectInfo.get());
    
    DockMenus=new QMenu;
    showSettingAction=new QAction(tr("Show SceneSettings"),nullptr);  
    showSettingAction->setCheckable(true);
    DrawCubeAction=new QAction(tr("Draw Cube"),nullptr);
    DeleteObjectGizmoAction=new QAction(tr("Destroy Gizmo"),nullptr);
    refreshAction=std::make_unique<QAction>(tr("Refresh"),nullptr);
   
    DockMenus->addAction(showSettingAction);
    DockMenus->addAction(DrawCubeAction);
    DockMenus->addAction(UndoAction);
    DockMenus->addAction(RedoAction);
    DockMenus->addAction(ConstructPointNodeAction.get());
    DockMenus->addAction(convertPointAction.get());
    DockMenus->addAction(refreshAction.get());
 display=new Aspect_DisplayConnection();
 driver=new OpenGl_GraphicDriver(display);
 Viewer=new V3d_Viewer(driver);
 view =Viewer->CreateView();   //Create the view from the viewer
 //Now to generate an id that can embed Qt project  
 context=new AIS_InteractiveContext(Viewer);
 
 
 

 WId winid=winId();
Window=new WNT_Window((Aspect_Handle)winid);
 
 Viewer->SetLightOn();
 Viewer->SetDefaultLights();
 view->SetWindow(Window);
    Window->Map();
 view->SetBackgroundColor(Quantity_Color(0.18,0.18,0.18,Quantity_TOC_RGB));
   CreateWorldGrid();
view->MustBeResized();
 view->TriedronDisplay(Aspect_TOTP_RIGHT_UPPER,Quantity_NOC_SNOW,0.1,V3d_ZBUFFER);
 


 SphereShape=BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(0.0,0.0,50.0),gp_Dir(0.0,0.0,1.0)),50.0).Shape();
 ConeShape=BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(0.0,0.0,0.0),gp_Dir(1.0,0.0,0.0)),0.0,60.0,50.0).Shape();
 CylShape=BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0.0,0.0,50.0),gp_Dir(0.0,1.0,0.0)),50.0,80.0).Shape();
 
 Handle(CustomAIS_Shape) sphereShape=new CustomAIS_Shape(SphereShape);
 sphereShape->ShadeFace(1, Quantity_NOC_MEDIUMPURPLE1);
 sphereShape->SetVisualAspect(Quantity_NOC_STEELBLUE4);
  
  context->SetAutomaticHilight(true);
  OnChangeSelectionColor(Quantity_NOC_SNOW);
  OnChangeDetectedColor(Quantity_NOC_SEASHELL);
  OnChangeSubShapeSelectedColor(Quantity_NOC_STEELBLUE);
  OnChangeSubShapeDetectedColor( Quantity_NOC_WHEAT);
 context->Display(sphereShape,CurrentShadeMode,0,true);
 context->Display(new CustomAIS_Shape(ConeShape),CurrentShadeMode,0,true);
 context->Display(new CustomAIS_Shape(CylShape),CurrentShadeMode,0,true);

 context->Display(viewcube,true);

 
 

 connect(DeleteAction,&QAction::triggered,this,&DrawingCentralWidget::OnDeleteObject);
 connect(UndoAction,&QAction::triggered,this,&DrawingCentralWidget::UndoStackContent);
 connect(RedoAction,&QAction::triggered,this,&DrawingCentralWidget::RedoStackContent);
 connect(showSettingAction,&QAction::toggled,this,&DrawingCentralWidget::OnShowSceneSetting);
 connect(RotateAction,&QAction::toggled,this,&DrawingCentralWidget::EnableRotation);
 connect(ScaleAction,&QAction::toggled,this,&DrawingCentralWidget::EnableScaling);
 connect(TranslateAction,&QAction::toggled,this,&DrawingCentralWidget::EnableTranslation);
 connect(DeleteObjectGizmoAction,&QAction::triggered,this,&DrawingCentralWidget::OnDestroyObjectGizmo);
 connect(ShapePrsAction,&QAction::triggered,this,&DrawingCentralWidget::OnSendRenderShapePrs);
 connect(convertPointAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertToFacePoint);
 connect(refreshAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnRefreshView);
 connect(faceMenu->convertAction.get(),&QAction::toggled,this,DrawingCentralWidget::OnConvertToFaceNode);
}
Handle(ViewCube) viewCube() {
  return viewcube;
}

void OnGetEmitShape(const TopoDS_Shape& shape){
   if(context.IsNull()){
       emit QueryDebugMessage(tr("Context Cannot be Null"));
        return;
      }
      if(Shapes.empty()){
         return;
    }
    for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
        if(iter->second->Shape().IsSame(shape)){
           emittedShape=iter->second;
           std::cout<<"Face found"<<"\n";
           break;
        }
    }
  return;
}
//highlight an edge
void HighlightEdge(const TopoDS_Shape& edge){
   if(emittedShape.IsNull()){
     return;
  }
  if(edge.IsSame(TopoDS_Shape())){
    return;
  }
 
  
  
  return;
}

/*
void OnChangeSelectionAspect();
void OnChangeSubShapeSelectionAspect();
void OnChangeDynamicAspect();
void OnChangeSubShapeDynamicAspect();





*/
//highlight a face
void HighlightFace(const int& id){
  if(emittedShape.IsNull()){
     return;
  }
  if(prevEmittedShape.IsNull()){
    std::cout<<"Current Shaded Face Index "<<id<<"\n";
    emittedShape->ShadeFace(id,Quantity_NOC_ORANGE);
    faceIndex=id;
    prevEmittedShape=emittedShape;
    if(!context.IsNull()){
      context->Redisplay(emittedShape,true);
    }
    return;
  }
  if(prevEmittedShape==emittedShape){
    if(faceIndex==id){
       context->Redisplay(emittedShape,true);
       return;
    }
    else{
      emittedShape->UnShadeFace(faceIndex);
      context->Redisplay(emittedShape,false);
      faceIndex=id;
      emittedShape->ShadeFace(faceIndex,Quantity_NOC_ORANGE);
       context->Redisplay(emittedShape,true);
      return;
    }
    
  }
  if(prevEmittedShape!=emittedShape){
      prevEmittedShape->UnShadeFace(faceIndex);
       context->Redisplay(prevEmittedShape,true);
       emittedShape->ShadeFace(id,Quantity_NOC_ORANGE);
       faceIndex=id;
       prevEmittedShape=emittedShape;
       context->Redisplay(emittedShape,true);

  }
  
  
  return;
}

/*
Algorithm For Highlighting Subshapes
compare a sub part of shape with every object in the scene
we will check if the shape is either a vertex,edge,edge loop(Wire),Face,Shell,Solid Or CompoSolid...
we will then loop through the shapes in the scene,After Finding it, we will highlight the section
shape.IsSame(for every [either vertex,edge,wire loop,face,shell,solid, CompoSolid])

*/
void HighlightSubShapes(const TopoDS_Shape& shape){
     if(context.IsNull()){
       emit QueryDebugMessage(tr("Context Cannot be Null"));
        return;
      }
      if(Shapes.empty()){
         return;
         }
         cout<<"Shape Size:"<<Shapes.size()<<endl;
     
      for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
           currentObject=iter->second;
           if(currentObject.IsNull()){
             emit QueryDebugMessage(tr("No Successful Casting"));
             std::cout<<"Object Is Currently Null "<<std::endl;
             continue;
           }
          if(!prevCurrentObject.IsNull()){
            if(prevCurrentObject->Shape().IsSame(shape)){ //it is possible to refer to the same pointer Object
              currentObject->SetVisualAspect( Quantity_NOC_STEELBLUE);
              context->Redisplay(currentObject,true);
              std::cout<<"Previous Object is Equal to CurrentObject"<<std::endl;
              break;
            }
            else{
              if(currentObject->Shape().IsSame(shape)){
              prevCurrentObject->SetVisualAspect(currentObjectColor);
              context->Redisplay(prevCurrentObject,true);
              prevCurrentObject=currentObject;
              currentObject->Color(currentObjectColor);
              currentObject->SetVisualAspect( Quantity_NOC_STEELBLUE);
              context->Redisplay(currentObject,true);
              std::cout<<"Another Object when Previous Shape Is Null Is Currently Selected "<<std::endl;
              break;
              }
              else{
                std::cout<<"Continue Searching"<<std::endl;

                continue;
              }
              
              }
             
            }
           else{
          if(currentObject->Shape().IsSame(shape)){   //this algorithm is wrong
              prevCurrentObject=currentObject;
              currentObject->Color(currentObjectColor);
              currentObject->SetVisualAspect(Quantity_NOC_STEELBLUE);
              context->Redisplay(currentObject,true);
              std::cout<<"Object Is Currently Selected"<<std::endl;
              break;
            }
         }
         }
         return;
      }

 void OnDebugGizmo(const Handle(AIS_Manipulator)& manip){
  
  if(manip.IsNull()){
    std::cout<<"Gizmo is Empty"<<"\n";
    return;
  }
  gp_Trsf trsf=manip->Object()->LocalTransformation();
  gp_Pnt pos=manip->Position().Location();

  switch(trsf.Form()){
    case gp_Identity:{
     std::cout<<"Identity Matrix"<<"\n";
     break;
    }

   case gp_Rotation:{
    std::cout<<"Rotation Matrix"<<"\n";
     break;
    }

   case gp_Translation:{
   std::cout<<"Translational Matrix"<<"\n";
     break;
    }

    case gp_Scale:{
    std::cout<<"Scale Matrix"<<"\n";
     break;
    }

    case gp_CompoundTrsf:{
      std::cout<<"Compound Matrix"<<"\n";
     break; 
    }

  }
  std::cout<<"Gizmo Position_X:"<<pos.X()<<"\n";
  std::cout<<"Gizmo Position_Y:"<<pos.Y()<<"\n";
   std::cout<<"Gizmo Position_Z:"<<pos.Z()<<"\n";
  return;
 } 
  




void OnChangeSelectionColor(const Quantity_Color& color){
  if(context.IsNull()){
    emit QueryDebugMessage(tr("Context Cannot be Null"));
    return;
  }
  //For both vertex,edge and face......,This is called when ever a or face is selected
   Handle(Prs3d_Drawer)& dynColor=const_cast<Handle(Prs3d_Drawer)&>(context->SelectionStyle());
   auto& sh_aspect=const_cast<Handle(Prs3d_ShadingAspect)&>(dynColor->ShadingAspect());
   dynColor->SetColor(color);
   sh_aspect->SetColor(color);
 
   dynColor->SetShadingAspect(sh_aspect);
   context->SetSelectionStyle(dynColor);
     view->Redraw();
   return;
}

void OnChangeDetectedColor(const Quantity_Color& color){
  if(context.IsNull()){
    emit QueryDebugMessage(tr("Context Cannot be Null"));
    return;
  }
  //For both vertex,edge and face......,This is called when ever a or face is selected
   Handle(Prs3d_Drawer)& dynColor=const_cast<Handle(Prs3d_Drawer)&>(context->HighlightStyle(Prs3d_TypeOfHighlight_Dynamic));
   
   auto& sh_aspect=const_cast<Handle(Prs3d_ShadingAspect)&>(dynColor->ShadingAspect());
   dynColor->SetColor(color);
   sh_aspect->SetColor(color);
 
   dynColor->SetShadingAspect(sh_aspect);
   context->SetHighlightStyle(Prs3d_TypeOfHighlight_Dynamic,dynColor);
      view->Redraw();
  return;
}
void OnChangeSubShapeSelectedColor(const Quantity_Color& color){
  if(context.IsNull()){
    emit QueryDebugMessage(tr("Context Cannot be Null"));
    return;
  }
  //For both vertex,edge and face......,This is called when ever a or face is selected
   Handle(Prs3d_Drawer)& dynColor=const_cast<Handle(Prs3d_Drawer)&>(context->HighlightStyle(Prs3d_TypeOfHighlight_LocalSelected));
   dynColor->SetFaceBoundaryDraw(true);
   auto& sh_aspect=const_cast<Handle(Prs3d_ShadingAspect)&>(dynColor->ShadingAspect());
   
   dynColor->SetColor(color);
   sh_aspect->SetColor(color);
 
   dynColor->SetShadingAspect(sh_aspect);
   context->SetHighlightStyle(Prs3d_TypeOfHighlight_LocalSelected,dynColor);
   view->Redraw();
  return;
}
void OnChangeSubShapeDetectedColor(const Quantity_Color& color){
  if(context.IsNull()){
    emit QueryDebugMessage(tr("Context Cannot be Null"));
    return;
  }
  //For both vertex,edge and face......,This is called when ever a or face is selected
   Handle(Prs3d_Drawer)& dynColor=const_cast<Handle(Prs3d_Drawer)&>(context->HighlightStyle(Prs3d_TypeOfHighlight_LocalDynamic));
   dynColor->SetFaceBoundaryDraw(true);
   auto& sh_aspect=const_cast<Handle(Prs3d_ShadingAspect)&>(dynColor->ShadingAspect());
   
   dynColor->SetColor(color);
   sh_aspect->SetColor(color);
 
   dynColor->SetShadingAspect(sh_aspect);
   context->SetHighlightStyle(Prs3d_TypeOfHighlight_LocalDynamic,dynColor);
   view->Redraw();
  return;
}

Aspect_VKeyMouse ToQtMouseButton(const Qt::MouseButton& btn){
    switch(btn){
        case Qt::LeftButton:
            return Aspect_VKeyMouse_LeftButton;
        case Qt::RightButton:
            return Aspect_VKeyMouse_RightButton;
        case Qt::MiddleButton:
           return Aspect_VKeyMouse_MiddleButton;
        default:
          return Aspect_VKeyMouse_NONE;
    }
}
Aspect_VKeyFlags ToNativeModifiers(const Qt::KeyboardModifiers& mod){
   switch(mod){
    case Qt::NoModifier:
       return Aspect_VKeyFlags_NONE;
    case Qt::ShiftModifier:
      return Aspect_VKeyFlags_SHIFT;
    case Qt::ControlModifier:
      return Aspect_VKeyFlags_CTRL;
    case Qt::AltModifier:
      return Aspect_VKeyFlags_ALT;
    case Qt::MetaModifier:
      return Aspect_VKeyFlags_META;
   }
}

QPaintEngine* paintEngine() const override{
    return nullptr;
}
void SetUseWindowSize(const bool& value){
  UseWindowSize=value;
  return;
}
void HighlightSensitiveEntities(){
  switch(CurrentSelMode){
    case 6:
    case 5:
    case 4:
    case 3:
    case 2:
    case 1:
    case 0:
        {
      if(context->IsSelected(context->SelectedInteractive())){
      context->HilightSelected(true);
      context->SetToHilightSelected(true);
      context->UpdateSelected(true);
      emit QueryDebugMessage(tr("Object Is Currently Selected"));
      return;
      }
    }
    default:
      return;
  }
}
void DeactivateWorldGrid(){
  Viewer->DeactivateGrid();
  view->Redraw();
  return;
}
void CreateWorldGrid(){
  if(ShowGrid){
  if(Viewer.IsNull()){
     return;
    }
  if(!UseWindowSize){
      Viewer->SetGridEcho(GridAspect);
      Viewer->SetRectangularGridGraphicValues(GridSize_X,GridSize_Y,Grid_Spacing);
      Viewer->ActivateGrid(Aspect_GT_Rectangular,Aspect_GDM_Lines);
       Viewer->Redraw();
       return;
  }
  Viewer->SetGridEcho(GridAspect);
  int x=0,y=0;
  view->Window()->Size(x,y);
  Viewer->SetRectangularGridGraphicValues(x,y,Grid_Spacing);
  Viewer->ActivateGrid(Aspect_GT_Rectangular,Aspect_GDM_Lines);

  Viewer->Redraw();
  
  }
  return;
   
}
//it runs in an iteration,For One shape
void DisplayObject(const Handle(CustomAIS_Shape)& object){
  if(context.IsNull()){
    return;
  }
  if(object.IsNull()){
    if(!PreviousShape.IsNull()){
      if(context->IsDisplayed(PreviousShape)){
        context->Redisplay(PreviousShape,true);
      }
    }
    emit QueryDebugMessage(tr("Object is not created"));
    return;
  }
  else{
    if(!PreviousShape.IsNull()){
      if(PreviousShape->Shape().IsSame(object->Shape())){
          context->Redisplay(object,true);
           return;
      }
      else{
         if(context->IsDisplayed(PreviousShape)){
          context->Remove(PreviousShape,true);
          if(!Shapes.empty()){
            for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
              if(iter->second==PreviousShape){
                Shapes.erase(iter);
              }
            }
          }
         }
          
         context->Display(object,CurrentShadeMode,0,true);
         Shapes.insert(std::pair<size_t,Handle(CustomAIS_Shape)>(objectCount,object));

         PreviousShape=object;
         ++objectCount;
         return;
      }
    }
    else{
    if(context->IsDisplayed(object)){
      context->Redisplay(object,true);
      return;
    }
    else{
      context->Display(object,CurrentShadeMode,0,true);
       Shapes.insert(std::pair<size_t,Handle(CustomAIS_Shape)>(objectCount,object));

      PreviousShape=object; //To compare objects before display
       ++objectCount;
      return;
    }
    }
  }
   return;
}
  /*
  A shape will be redislpayed or display
  
  
  */
 void DisplayObjects(const std::vector<Handle(CustomAIS_Shape)>& shapes){
  if(shapes.empty()){
    return;
  }
  if(!Shapes.empty()){
    Shapes.clear();
    objectCount=0;  //reset the counter
    context->RemoveAll(true);

  }
   context->Display(viewcube,true);
  for(const auto& shape: shapes){
    if(shape.get()){
      if(context->IsDisplayed(shape)){
        context->Redisplay(shape,true);
      }
      else{
        context->Display(shape,CurrentShadeMode,0,true);
        Shapes.insert(std::pair<size_t,Handle(CustomAIS_Shape)>(objectCount,shape));
        ++objectCount;
      }
    }
  }

  return;
 }
  
   
  
 
  
 
gp_Lin GetProjectedRay(const int& mouseX,const int& mouseY){
  double pointx=0.0,pointy=0.0,pointz=0.0,rayx=0.0,rayy=0.0,rayz=0.0;
  if(view.IsNull()){
    return gp_Lin();
  }

  view->ConvertWithProj(mouseX,mouseY,pointx,pointy,pointz,rayx,rayy,rayz);
  gp_Pnt origin(pointx,pointy,pointy);
  gp_Dir raydirection(rayx,rayy,rayz);
  return gp_Lin(origin,raydirection);
}
gp_Pnt Get3dPointFrom2D(const int& x,const int y){
  double p_x,p_y,p_z;
   //view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);

   view->ConvertToGrid(x,y,p_x,p_y,p_z);
  return gp_Pnt(p_x,p_y,p_z);
}
//This design method can allow you to perform test with every surface in the scene.




void DisplayGizmoOnObject(Handle(AIS_InteractiveObject) shape){
   if(ObjectGizmo.IsNull()){
    ObjectGizmo=new AIS_Manipulator();
   }
   if(isTranslateGizmoEnabled){
     if(!ObjectGizmo.IsNull()){
          RemoveObjectGizmo();
          ObjectGizmo->Detach();
       
          EnableManipulatorPart(AIS_MM_Rotation,shape);
          EnableManipulatorPart(AIS_MM_Scaling,shape);
          if(ObjectGizmo->HasActiveMode()){
            ObjectGizmo->DeactivateCurrentMode();
          }
           ObjectGizmo->SetModeActivationOnDetection(false);
          ObjectGizmo->EnableMode(AIS_MM_Translation);
            emit QueryDebugMessage(tr("The Translation Gizmo Enabled"));
          return;
       
     }
   }
   else if(isRotateGizmoEnabled){
     if(!ObjectGizmo.IsNull()){
       RemoveObjectGizmo();
          ObjectGizmo->Detach();
       
          EnableManipulatorPart(AIS_MM_Translation,shape);
          EnableManipulatorPart(AIS_MM_Scaling,shape);
          if(ObjectGizmo->HasActiveMode()){
            ObjectGizmo->DeactivateCurrentMode();
          }
           ObjectGizmo->SetModeActivationOnDetection(false);
          ObjectGizmo->EnableMode(AIS_MM_Rotation);
            emit QueryDebugMessage(tr("The Rotation Gizmo Enabled"));
          return;
       
     }
   }
  else if(isScaleGizmoEnabled){
       if(!ObjectGizmo.IsNull()){
          RemoveObjectGizmo();
          ObjectGizmo->Detach();
       
          EnableManipulatorPart(AIS_MM_Translation,shape);
          EnableManipulatorPart(AIS_MM_Rotation,shape);
          if(ObjectGizmo->HasActiveMode()){
            ObjectGizmo->DeactivateCurrentMode();
          }
           ObjectGizmo->SetModeActivationOnDetection(false);
          ObjectGizmo->EnableMode(AIS_MM_Scaling);
            emit QueryDebugMessage(tr("The Scale Gizmo Enabled"));
          return;
       
     }
  }
  ObjectGizmo->SetModeActivationOnDetection(false);
   ObjectGizmo->Attach(shape);
   ObjectGizmo->SetZoomPersistence(true);
   
   if(!context.IsNull()){
    if(context->IsDisplayed(ObjectGizmo)){
        context->Redisplay(ObjectGizmo,true);
        return;
    }
   context->Display(ObjectGizmo,AIS_Shaded,0,false);
   view->Redraw();
   emit QueryDebugMessage(tr("New Gizmo Created"));

   }
   emit QueryDebugMessage(tr("No Initialized Context"));
  return;
}
void RemoveObjectGizmo(){
  context->Remove(ObjectGizmo,false);
  view->Redraw();
  return;
}

void EnableManipulatorPart(const AIS_ManipulatorMode& theMode,Handle(AIS_InteractiveObject) shape){
  if(!ObjectGizmo.IsNull()){
    if(ObjectGizmo->HasActiveMode()){
        ObjectGizmo->DeactivateCurrentMode();
    }
    if(ObjectGizmo->IsAttached()){
      ObjectGizmo->Detach();
     }
     ObjectGizmo->SetPart(theMode,false);
     
     //re attach it again
     ObjectGizmo->Attach(shape);
     if(context->IsDisplayed(ObjectGizmo)){
      context->Redisplay(ObjectGizmo,true);
     }
     else{
      context->Display(ObjectGizmo,AIS_Shaded,0,false);
      view->Redraw();
     }
    return;
  }
  
  ObjectGizmo=new AIS_Manipulator();
  ObjectGizmo->SetPart(theMode,false);
 
 
  ObjectGizmo->Attach(shape);
  if(!context.IsNull()){
   context->Display(ObjectGizmo,AIS_Shaded,0,false);
   view->Redraw();
   }
   return;
}
void OnClearView(){
  for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
      if(context->IsDisplayed(iter->second)){
         context->Remove(iter->second,false);
      }
  }
  if(!Shapes.empty()){
    Shapes.clear();
  }
  view->Redraw();
  return;
}
~DrawingCentralWidget(){
  if(SelectedMenu){
    delete SelectedMenu;
    SelectedMenu=nullptr;
  }
  if(DeleteAction){
    delete DeleteAction;
    DeleteAction=nullptr;
  }
  if(SelectAction){
    delete SelectAction;
    SelectAction=nullptr;
  }
  if(UndoAction){
    delete UndoAction;
    UndoAction=nullptr;
  }
  if(RedoAction){
    delete RedoAction;
    RedoAction=nullptr;
  }
  if(DockMenus){
    delete DockMenus;
    DockMenus=nullptr;
  }
  if(showSettingAction){
    delete showSettingAction;
    showSettingAction=nullptr;
  }
  if(DrawCubeAction){
    delete DrawCubeAction;
    DrawCubeAction=nullptr;
  }
  if(ScaleAction){
    delete ScaleAction;
    ScaleAction=nullptr;
  }
  if(RotateAction){
    delete RotateAction;
    RotateAction=nullptr;
  }
  if(TranslateAction){
    delete TranslateAction;
    TranslateAction=nullptr;
  }
  if(ShapePrsAction){
    delete ShapePrsAction;
    ShapePrsAction=nullptr;
  }
  if(LinePrsAction){
    delete LinePrsAction;
    LinePrsAction=nullptr;
  }
 
}  







protected:
//On Selecting Objects,we must have knowledge of the selection mode that was chosen
void mousePressEvent(QMouseEvent* event) override{
 if(event->button()==Qt::LeftButton){
    
    if(context->MoveTo(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view,false)==AIS_SOD_Nothing){
     

       
        /*
        we have to find the intersection of the ray and the surface in question
        using surfaceWidgetShape
        
        */
      
      if(!ChosenShape.IsNull()){
         
          IsSelectedColorUsed=false;
          SentTransform=gp_Trsf();
          ChosenShape.Nullify();
      }
       if(!ObjectGizmo.IsNull()){
      ObjectGizmo->Detach();
      RemoveObjectGizmo();
       ObjectGizmo.Nullify();
     
     emit OnDestroyMaterialProp();
     emit QueryDebugMessage(tr("No Object Is Chosen"));
     emit OnSetPreviousColor();
     return;
    }
   if(context->IsDisplayed(pointMarker)){
    context->Remove(pointMarker,true);
   }
   if(context->IsDisplayed(currSelShape)){
    currSelShape->UseColor();
    context->Remove(currSelShape,true);
   }
  
   st=NULL_SELECT;
   st1=NULL_SELECT;
   context->Deactivate();
   context->Activate(0);
      return;
    }
    else{
    context->SelectDetected();
    
    
    context->InitSelected();
    while(context->MoreSelected()){
      st=SELECT;
     if(CurrentSelMode==4){  //When currentSelMode is 4
       if(chmode==CM_FACE){
        Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        if(!owner){
           std::cout<<"Failed To Cast To an object of SelectMgr_EntityOwner"<<"\n";
          return;
        }
       Handle(StdSelect_BRepOwner) selectedEntity=Handle(StdSelect_BRepOwner)::DownCast(owner);
        if(!selectedEntity){
          std::cout<<"Failed To Cast To an object of StdSelect_BRepOwner"<<"\n";
          return;
        }
        
        if(selectedEntity->Shape().ShapeType()==TopAbs_FACE){
            selFace=TopoDS::Face(selectedEntity->Shape());
            if(selFace.IsNull()){
               std::cout<<"Failed To Cast To Face"<<"\n";
               return;
            }
           
          std::cout<<"It is a Face"<<"\n";
        }
        else{
            std::cout<<"It is not a Face"<<"\n";
            QString str= shapetypemap.at(selectedEntity->Shape().ShapeType());
           std::cout<<"Shape's Type :"<<str.toUtf8().toStdString()<<"\n ";

            return;
        }
        st1=FACE_SELECT;
        if(currSelShape){
         currSelShape->UseColor();
         context->Redisplay(currSelShape,false);
         context->Remove(currSelShape,false);
        }
        currSelShape=new CustomAIS_Shape(selFace);
        currSelShape->InitHighlightColor(Quantity_NOC_YELLOW2);
        currSelShape->SetZLayer(Graphic3d_ZLayerId_Top);
        context->Display(currSelShape,1,CurrentSelMode,true);
       gp_Pnt selectedPoint=context->MainSelector()->PickedPoint(1);
      
      if(IsWithinSurface(selFace,selectedPoint)){
        int_x=selectedPoint.X();
        int_y=selectedPoint.Y();
        int_z=selectedPoint.Z();
       std::cout<<"Surface Points: "<<int_x<<","<<int_y<<","<<int_z<<"\n";
      gp_Pnt centroid=GetSurfaceCentre(selFace);
      Handle(Geom_Point) geom_pnt=new Geom_CartesianPoint(centroid.X(),centroid.Y(),centroid.Z());
      pointMarker->SetComponent(geom_pnt);

      if(context->IsDisplayed(pointMarker)){
         context->Remove(pointMarker,true);
         context->Display(pointMarker,true); 
      }
      else{
      context->Display(pointMarker,true);
      }

      }
      else{
        std::cout<<"Does not lie within Surface"<<"\n";
      }


        //Get3dPointFrom2D
      
       }
       return;
    }
    if(CurrentSelMode==2){
      if(chmode==CM_EDGE){
         Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        if(!owner){
           std::cout<<"Failed To Cast To an object of SelectMgr_EntityOwner"<<"\n";
          return;
        }
       Handle(StdSelect_BRepOwner) selectedEntity=Handle(StdSelect_BRepOwner)::DownCast(owner);
       if(!selectedEntity){
        std::cout<<"Failed To Cast To an object of StdSelect_BRepOwner"<<"\n";
          return;
       }
       
       if(selectedEntity->Shape().ShapeType()==TopAbs_EDGE){
            selEdge=TopoDS::Edge(selectedEntity->Shape());
            if(selEdge.IsNull()){
               std::cout<<"Failed To Cast To an Edge"<<"\n";
               return;
            }
           
          std::cout<<"It is an Edge"<<"\n";
        }
        else{
          std::cout<<"It is not an edge"<<"\n";
            QString str= shapetypemap.at(selectedEntity->Shape().ShapeType());
           std::cout<<"Shape's Type :"<<str.toUtf8().toStdString()<<"\n ";

            return;
        }
        st1=EDGE_SELECT;
         gp_Pnt selectedPoint=context->MainSelector()->PickedPoint(1);
         int_x=selectedPoint.X();
         int_y=selectedPoint.Y();
         int_z=selectedPoint.Z();
          if(currSelShape){
         currSelShape->UseColor();
         context->Redisplay(currSelShape,false);
         context->Remove(currSelShape,true);
        }
          currSelShape=new CustomAIS_Shape(selEdge);
        currSelShape->SetColor(Quantity_NOC_YELLOW2);
        currSelShape->SetTransparency(0.6);
        currSelShape->SetWidth(2.0);
        currSelShape->SetZLayer(Graphic3d_ZLayerId_Top);
        context->Display(currSelShape,1,CurrentSelMode,true);
          std::cout<<"Edge  Points: "<<int_x<<","<<int_y<<","<<int_z<<"\n";
         return;
      }
    }
      if(!ChosenShape.IsNull()){
         ChosenShape->SetMaterial(prevChosenMat);
         IsSelectedColorUsed=false;
          
      }
    PrintSelection(CurrentSelMode);
   Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
    
   //For the manipulator On the screen
    Handle(AIS_Manipulator) chmanip=Handle(AIS_Manipulator)::DownCast(owner->Selectable());
    if(!chmanip.IsNull()){
    if(chmanip==ObjectGizmo){
     evt_manager.ProcessPressMouseButton(context,ObjectGizmo,view,Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr),static_cast<int>(std::lround(event->pos().y()*dpr)))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier));
     if(ObjectGizmo->HasActiveMode() && ObjectGizmo->IsAttached()){
      if(evt_manager.UpdateMousePosition(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false)){
        if(!ChosenShape.IsNull()){
          PrevTrsf=ChosenShape->LocalTransformation();
         IsSelectedColorUsed=true;
        }
        emit EmitShape(ChosenShape->Shape());  //Send the shape......
        if(!Shapes.empty()){
        for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
           if(iter->second->Shape().IsSame(ChosenShape->Shape())){
               ChosenId=iter->first;
               IsSeen=true;
               std::cout<<"Object is Seen"<<std::endl;
               break;
           }
        }
        }
        ObjectGizmo->StartTransform(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view);
        view->Redraw();
      }
     }
     isObjectTransformed=true;
     emit QueryDebugMessage(tr("Object wants to be moved"));
      return;
    }
    }
  
   Handle(AIS_InteractiveObject) object=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
     if(!object.IsNull()){
      QString str=QString(tr("Object is Selected"));
     
      DisplayGizmoOnObject(object); //
     
      emit QueryDebugMessage(str);
}    
     
     Handle(CustomAIS_Shape) OShape=Handle(CustomAIS_Shape)::DownCast(object);
    if(OShape.IsNull()){
     emit QueryDebugMessage(tr("Failed to cast to an Object of AIS_Shape"));
      return;
    }
    else{   //bug 
     
     //ChosenShape still points to the same object as owner->Selectable()
     ChosenShape=OShape;    //Single Selection for Object
      if(currSelShape){
         currSelShape->UseColor();
         context->Redisplay(currSelShape,false);
         context->Remove(currSelShape,false);
        }
     currSelShape=new CustomAIS_Shape(ChosenShape->TransShape());
        
        currSelShape->SetColor(Quantity_NOC_YELLOW2);
        currSelShape->SetTransparency(0.6);
        currSelShape->SetZLayer(Graphic3d_ZLayerId_Top);
        context->Display(currSelShape,1,CurrentSelMode,true);
     IsSelectedColorUsed=true;
     view->Redraw();
     emit QueryDebugMessage(tr("Assignment Successful"));
      return;
    }
    context->NextSelected();
    }
 }
}     
   
   
   

else if(event->button()==Qt::RightButton){
  if(st1==FACE_SELECT){
    faceMenu->exec(event->globalPosition().toPoint());
    return;
  }
 if(st1==EDGE_SELECT){
  edgeMenu->exec(event->globalPosition().toPoint());
  return;
 }
if(SelectedMenu!=nullptr){
    if(!ChosenShape.IsNull()){
      if(ConstructPointNodeAction->isChecked()){
       if(context->MoveTo(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view,false)==AIS_SOD_Nothing){
      if(CurrentSelMode==4){
       std::cout<<"Successfully Integrated"<<std::endl;
       emit OnSendConvertValue(Point(x_value,y_value,z_value));
       return;
  }
  double projX=0.0,projY=0.0,projZ=0.0;
  view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
    //Move it to node graph
   x_value=projX;
   y_value=projY;
   z_value=projZ;
   std::cout<<"Current X Value: "<<x_value<<std::endl;
   std::cout<<"Current Y Value: "<<y_value<<std::endl;
   std::cout<<"Current Z Value: "<<z_value<<std::endl;
   emit OnSendConvertValue(Point(x_value,y_value,z_value));
  return;
  }
      }
      if(ChosenShape->Shape().ShapeType()>=5 && ChosenShape->Shape().ShapeType()<=7){
        if(IsShapePrsAdded){
          SelectedMenu->removeAction(ShapePrsAction);
          SelectedMenu->removeAction(ShowObjectInfo.get());
          IsShapePrsAdded=false;
        }
        SelectedMenu->addAction(LinePrsAction);
        SelectedMenu->addAction(ShowEdgeInfo.get());
        IsLinePrsAdded=true;
      }

    else if(ChosenShape->Shape().ShapeType()>=0 && ChosenShape->Shape().ShapeType()<=4){
      if(IsLinePrsAdded){
         SelectedMenu->removeAction(LinePrsAction);
         SelectedMenu->removeAction(ShowEdgeInfo.get());
         IsLinePrsAdded=false;
      }
      SelectedMenu->addAction(ShapePrsAction);
      SelectedMenu->addAction(ShowObjectInfo.get());
      IsShapePrsAdded=true;
    }
    //After adding,render at a particular position
    SelectedMenu->exec(event->globalPosition().toPoint());
    
    return;
    }
}
if(DockMenus!=nullptr){
  if(ChosenShape.IsNull()){
    DockMenus->exec(event->globalPosition().toPoint());
  if(ConstructPointNodeAction->isChecked()){
  if(context->MoveTo(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view,false)==AIS_SOD_Nothing){
 
  double projX=0.0,projY=0.0,projZ=0.0;
  view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
    //Move it to node graph
   x_value=projX;
   y_value=projY;
   z_value=projZ;
   std::cout<<"Current X Value: "<<x_value<<std::endl;
   std::cout<<"Current Y Value: "<<y_value<<std::endl;
   std::cout<<"Current Z Value: "<<z_value<<std::endl;
   emit OnSendConvertValue(Point(x_value,y_value,z_value));
  return;
  }
  else{
    double projX=0.0,projY=0.0,projZ=0.0;
  view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
    //Move it to node graph
   x_value=projX;
   y_value=projY;
   z_value=projZ;
   std::cout<<"Current X Value: "<<x_value<<std::endl;
   std::cout<<"Current Y Value: "<<y_value<<std::endl;
   std::cout<<"Current Z Value: "<<z_value<<std::endl;
   emit OnSendConvertValue(Point(x_value,y_value,z_value));
   return; 
  }
}


    return;
  }
  
  }
  


}
return;
}





void mouseMoveEvent(QMouseEvent* event) override{
  if(!view.IsNull() && evt_manager.UpdateMousePosition(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false)){
      if(isObjectTransformed){
        if(!ChosenShape.IsNull()){
           if(context->IsDisplayed(currSelShape)){
            context->Redisplay(currSelShape,false);
           }
           context->Redisplay(ChosenShape,false);
        }
      ObjectGizmo->Transform(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().x()*dpr)),view);
      view->Redraw();
      emit QueryDebugMessage(tr("I am being Updated"));
      return;
      } 
  }
 
if(context->MoveTo(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view,false)==AIS_SOD_Nothing){
//Still Same as viewer->Grid->IsActive;
Viewer->SetGridEcho(true);
if(Viewer->Grid()->IsActive()){
    double projX=0.0,projY=0.0,projZ=0.0;
    view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
    Viewer->ShowGridEcho(view,Graphic3d_Vertex(projX,projY,projZ));
    view->RedrawImmediate();
  }
    if(context->IsDisplayed(currDetShape)){
      currDetShape->UseColor();
    context->Remove(currDetShape,false);
  }
  return;
 view->Redraw();
}
else{
   if(st==SELECT){
    return;
   }
 Handle(SelectMgr_EntityOwner) owner=context->DetectedOwner();
 if(owner.IsNull()){
  
  return;
 }
 Handle(StdSelect_BRepOwner) detEntity=Handle(StdSelect_BRepOwner)::DownCast(owner);
 if(!detEntity){
  return;
 }
 Handle(AIS_InteractiveObject) object=Handle(AIS_InteractiveObject)::DownCast(detEntity->Selectable()); //Parent of entity owner 
 if(!object){
  std::cout<<"Failed To cast to object of AIS_InteractiveObject"<<"\n";
  
 }
 else{
  std::cout<<"Casted Successfully,Object has parent shape"<<"\n";
 }
 Handle(CustomAIS_Shape) objshape=Handle(CustomAIS_Shape)::DownCast(object);
 TopoDS_Shape detShape=detEntity->Shape();
 if(detShape.IsNull()){
  return;
 }
 BRepBuilderAPI_Transform objTrans(detShape,objshape->GetTransform());
 if(objTrans.IsDone()){
    detShape=objTrans.Shape();
 }
 else{
    detShape=TopoDS_Shape(); 
    //Failed to transform the entity
    std::cout<<"Failed to transform Entity"<<"\n";
    return;
 } 
  
  if(currDetShape){
         currDetShape->UseColor();
         context->Redisplay(currDetShape,false);
        context->Remove(currDetShape,false);
        }
 
 currDetShape=new CustomAIS_Shape(detShape);
 currDetShape->SetWidth(2.0);
 currDetShape->SetTransparency(0.6);
 currDetShape->SetColor(Quantity_NOC_CYAN);
currDetShape->SetZLayer(Graphic3d_ZLayerId_Top);
 if(context){
  context->Display(currDetShape,1,CurrentSelMode,false);
 }

view->Redraw();
}

   
return;
}

void PrintSelection(const int& mode){
  switch(mode){
    case 0:{
      std::cout<<"A Shape Is Chosen"<<std::endl;
      break;
    }
   case 1:{
       std::cout<<"A Vertex Is Chosen"<<std::endl;
      break;
   }
   case 2:{
     std::cout<<"An Edge Is Chosen"<<std::endl;
      break; 
   }
   case 4:{
      std::cout<<"A Face Is Chosen"<<std::endl;
      break; 
   }
   case 5:{
     std::cout<<"A Shell Is Chosen"<<std::endl;
      break;
   }
   case 6:{
     std::cout<<"A Solid Is Chosen"<<std::endl;
      break;
   }
   default:{
     std::cout<<"A Default Mode"<<std::endl;
      return;
   }
  }
  return;
}


void mouseReleaseEvent(QMouseEvent* event) override{
  if(event->button()==Qt::LeftButton){
    if(isObjectTransformed){
     if(!ObjectGizmo.IsNull()){
       
       ObjectGizmo->StopTransform(true);
        OnDebugGizmo(ObjectGizmo);
        SentTransform=ObjectGizmo->Object()->LocalTransformation();
        
       emit QueryDebugMessage(tr("Transformation has been stopped,oops"));
}    
      if(!ChosenShape.IsNull()){
         gp_Trsf trsf=ObjectGizmo->Object()->LocalTransformation();
         auto vec=trsf.TranslationPart(); //of type gp_XYZ;
         trsf.SetTranslationPart(gp_Vec(vec.X(),vec.Y(),vec.Z()));
         CurrTrsf=ChosenShape->LocalTransformation();
         ChosenShape->SetTransShape(trsf); //this stores the transformed entity for selection and highlighting 
         
        
        
         
         if(IsSeen){
           Shapes[ChosenId]->SetTransShape(trsf);
           IsSeen=false;
           emit  EmitTransformedShape(ChosenShape->Shape()); 
         }
        if(context->IsDisplayed(currSelShape)){
          context->Remove(currSelShape,false);
        }

         UndoStack->push(new UndoTransformCommand(context,ChosenShape,PrevTrsf,CurrTrsf));
      }
      

      isObjectTransformed=false;
      view->Redraw();
      emit QueryDebugMessage(tr("Stop"));
      return;
    }
    else{
      emit QueryDebugMessage(tr("a boolean variable is not initialized"));
    }
  }

  if(event->button()==Qt::LeftButton && isPanningView){
    isPanningView=false;
    return;
  }

   return;
}


void resizeEvent(QResizeEvent* event) override{
    QWidget::resizeEvent(event);
    if(!view.IsNull()){
        if(UseWindowSize){
        view->MustBeResized();
          int x=0,y=0;
          view->Window()->Size(x,y);
          Viewer->SetRectangularGridGraphicValues(x,y,Grid_Spacing);
          WindowHeight=y;
          WindowWidth=x;
          view->Redraw();
        }
    }
        else{
          int x=0,y=0;
          view->Window()->Size(x,y);
          WindowHeight=y;
          WindowWidth=x;
           view->Redraw();
        }
       
    
    return;
}

void wheelEvent(QWheelEvent* event){
  auto value=event->angleDelta().y();
  
 double steps=value>0 ? 1.10 :-1.0;

  double factor=std::pow(1.1,steps);
  ZoomAtPosition(static_cast<int>(std::lround(event->position().x()*dpr)),static_cast<int>(std::lround((height()-event->position().y())*dpr)),factor);
   
   return;
}

//We can zoom at a point such that we use the view's camera's scale(view->camera()->scale()) and pan the view to still be at that position.
void ZoomAtPosition(const int& mouseX,const int& mouseY,const double& zoomfactor){
  if(zoomfactor<=0.0){
    return;
  }
  //Get the 3d point on the projection plane
  double x,y,z=0.0;
  view->Convert(mouseX,mouseY,x,y,z);
  Handle(Graphic3d_Camera) camera=view->Camera(); //we need to access the camera to access the scale
  const double scale=camera->Scale()/zoomfactor;
  UndoStack->push(new ZoomCommand(view,camera->Scale(),scale));
  camera->SetScale(scale);  //set the scale
  int newPX,newPY=0;

  view->Convert(x,y,z,newPX,newPY); //get the new position from the x,y,z on the projected plane
  int dx=mouseX-newPX;
  int dy=mouseY-newPY;
  if(dx!=0 || dy!=0){
    view->Pan(dx,dy); //Pan the view
    view->Redraw();
    return;
  }
  view->Redraw();
  return;
}


signals:
  void QueryDebugMessage(const QString& message);
  void OnOpenSceneSettings(bool truth);
  void OnRenderShapePrsWidget();
  void OnSendCubeEvent();
  void OnDestroyMaterialProp();
  void OnSetPreviousColor();
  void EmitShape(const TopoDS_Shape& shape);
  void EmitTransformedShape(const TopoDS_Shape& shape);
  void OnSendConvertValue(const Point& pt);
  void OnEmitBoolValue(bool value);
  void OnEmitFaceBool(bool value);
  void OnEmitFace(const TopoDS_Face& face);
public slots:
//This returns the top view
void SetDrawCircleAction(bool toggled){
    DrawCircle=true;
    return;
}
void OnDeleteObject(bool toggled){
  if(!ChosenShape.IsNull()){
    UndoStack->push(new DeleteCommand(ChosenShape,context,0,3));
    if(!Shapes.empty()){
    for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
       if(ChosenShape==iter->second){
        Shapes.erase(iter);
       }
    }
    }
    context->Remove(ChosenShape,true);
    if(!ObjectGizmo.IsNull()){
       RemoveObjectGizmo();
       ObjectGizmo.Nullify();
    }
    ChosenShape.Nullify();
    view->Redraw();

    return;
  }
  return;
}
void OnShowSceneSetting(bool truth){
  emit OnOpenSceneSettings(truth);
  return;
}
void UndoStackContent(){
  if(!UndoStack.get()){
    return;
  }
  UndoStack->undo();
  return;
}
void RedoStackContent(){
  if(!UndoStack.get()){
    return;
  }
  UndoStack->redo();
  return;
}
void OnSendDrawCubeFn(){
  emit OnSendCubeEvent();
  return;
}
void EnableRotation(bool isChecked){
    if(isChecked && ChosenShape.IsNull()){
     emit QueryDebugMessage(tr("No Object is Chosen,Please Select an object in Scene"));
     return;     
    }
    if(isChecked){
      if(ScaleAction->isChecked()){
        ScaleAction->setChecked(false);
      }
      if(TranslateAction->isChecked()){
        TranslateAction->setChecked(false);
      }
      EnableManipulatorPart(AIS_MM_Scaling,ChosenShape);
      EnableManipulatorPart(AIS_MM_Translation,ChosenShape); 
      isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=true;
      if(!ObjectGizmo.IsNull()){

          ObjectGizmo->EnableMode(AIS_MM_Rotation);
         emit QueryDebugMessage(tr("Rotation Gizmo Enabled"));
      }
      return;
    }
    else{
       if(ObjectGizmo.IsNull()){
        isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=false;
           return;
       }
       RemoveObjectGizmo();
       ObjectGizmo->Detach();
       ObjectGizmo->DeactivateCurrentMode();
       ObjectGizmo.Nullify();
    }
    return;
}
void EnableScaling(bool isChecked){
  if(isChecked && ChosenShape.IsNull()){
     emit QueryDebugMessage(tr("No Object is Chosen,Please Select an object in Scene"));
     return;     
    }
    if(isChecked){
      if(TranslateAction->isChecked()){
        TranslateAction->setChecked(false);
      }
      if(RotateAction->isChecked()){
        RotateAction->setChecked(false);
      }
      EnableManipulatorPart(AIS_MM_Rotation,ChosenShape);
       EnableManipulatorPart(AIS_MM_Translation,ChosenShape);
      isScaleGizmoEnabled=true;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=false;
      if(!ObjectGizmo.IsNull()){
          ObjectGizmo->EnableMode(AIS_MM_Scaling);
         emit QueryDebugMessage(tr("Scaling Gizmo Enabled"));
      }
      return;
    }
    else{
       if(ObjectGizmo.IsNull()){
        isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=false;
           return;
       }
       RemoveObjectGizmo();
       ObjectGizmo->Detach();
       ObjectGizmo->DeactivateCurrentMode();
       ObjectGizmo.Nullify();
    }
    return;
}
  void EnableTranslation(bool isChecked){
     if(isChecked && ChosenShape.IsNull()){
     emit QueryDebugMessage(tr("No Object is Chosen,Please Select an object in Scene"));
     return;     
    }
    if(isChecked){
      if(RotateAction->isChecked()){
        RotateAction->setChecked(false);

      }
      if(ScaleAction->isChecked()){
        ScaleAction->setChecked(false);
      }
      EnableManipulatorPart(AIS_MM_Rotation,ChosenShape);
      EnableManipulatorPart(AIS_MM_Scaling,ChosenShape);
      isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=true;
      isRotateGizmoEnabled=false;
      if(!ObjectGizmo.IsNull()){
          ObjectGizmo->EnableMode(AIS_MM_Translation);
         emit QueryDebugMessage(tr("Translation Gizmo Enabled"));
      }
      return;
    }
    else{
       if(ObjectGizmo.IsNull()){
        isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=false;
           return;
       }
       RemoveObjectGizmo();
       ObjectGizmo->Detach();
       ObjectGizmo->DeactivateCurrentMode();
       ObjectGizmo.Nullify();
    }
  return;
  }
void OnDestroyObjectGizmo(){
  if(ObjectGizmo.IsNull()){
    emit QueryDebugMessage(tr("Cannot Destroy An Empty Gizmo Object"));
    return;
  }
  RemoveObjectGizmo();
  if(ObjectGizmo->IsAttached()){
    ObjectGizmo->Detach();
  }
  if(ObjectGizmo->HasActiveMode()){
    ObjectGizmo->DeactivateCurrentMode();
  }
  ObjectGizmo.Nullify();
  return;
}
void OnSendRenderShapePrs(){
  emit OnRenderShapePrsWidget(); 
  return;
}
void OnConvertToFacePoint(bool value){
  if(value){
    emit OnEmitBoolValue(value);
    emit OnSendConvertValue(Point(int_x,int_y,int_z)); 
    return;
  }
  else{
    emit OnEmitBoolValue(value);
    }
  
  
  return;
}
void OnConvertToFaceNode(bool value){
  if(value){
   OnEmitFace(selFace);

} 
  else{
   OnEmitFaceBool(value);
  }

  return;
}
void OnRefreshView(){
  view->Redraw(); //cause a redraw;
  return;
}

};






#endif