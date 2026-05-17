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
#include<TransientPolygon.hpp>
#include<EdgeMenu.hpp>
#include<QtWidgets/QMessageBox>
#include<PolygonMenu.hpp>
#include<TransientBeizerCurve.hpp>
#include<TransientBSplineCurve.hpp>
#include<Standard_DomainError.hxx>
#include<GeomAPI_PointsToBSpline.hxx>
#include<AIS_Axis.hxx>
#include<Geom_Axis1Placement.hxx>
#include<EdgeUtility.hpp>
#include<DrawLineDialog.hpp>
//This file will enter 10,000 LOC
//We have to create a dialog for viewport setting,Drawing widget is also a viewport
//On Object Creation,deletion,editing,Transform
using namespace Shape_Utility;
using namespace std;
using namespace SURFACE;
using namespace STM;
using namespace EDGE;
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
enum DRAWCURVE{
DC_NULL,
DC_LINE,
DC_CIRCLE,
DC_SPLINE,
DC_BEZIER,
DC_ARC
};
enum GP_STATE{
 GPS_GATHER,
 GPS_BEZIER,
 GPS_BSPLINE,
 GPS_POINT,
 GPS_NULL
};
enum ContextMenu{
CE_NULL, //by default,show scene menu
CE_EDGE,
CE_FACE,
CE_SHAPE,
CE_POINT,
CE_AXIS
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
std::unique_ptr<DrawLineDialog> drawLineDialog;
std::unique_ptr<QAction> ConstructPointNodeAction;
std::unique_ptr<QAction> ConstructTransformNodeAction;
std::unique_ptr<QAction> ConstructShapeNodeAction;
std::unique_ptr<QAction> ShowObjectInfo;
std::unique_ptr<QAction> convertPointAction; //this converts the face point to nodes
std::unique_ptr<QAction> ShowEdgeInfo;
std::unique_ptr<QAction> GatherPointAction; //
std::unique_ptr<QAction> GatherCurveAction;
std::unique_ptr<QAction> GatherBSplineAction;
std::unique_ptr<QAction> FindAction;
std::unique_ptr<QAction> shouldSetAction=std::make_unique<QAction>(tr("Should Set"),nullptr);
std::unique_ptr<QAction> CheckShapeIdAction=std::make_unique<QAction>(tr("Shape Id"),nullptr);
std::unique_ptr<QAction> deleteAxisObject=std::make_unique<QAction>(tr("Delete"));
std::unique_ptr<QAction> faceNormalAction=std::make_unique<QAction>(tr("Assume Face Centre Normal"));
std::unique_ptr<QAction> convertFacePointAction=std::make_unique<QAction>(tr("Convert To Point Node"));
std::unique_ptr<QAction> drawAction=std::make_unique<QAction>(tr("Draw Line"));

std::unique_ptr<FaceMenu> faceMenu;
std::unique_ptr<EdgeMenu> edgeMenu; 
std::unique_ptr<PolygonMenu> polyMenu;
std::unique_ptr<DrawLineMenu> drawLineMenu=std::make_unique<DrawLineMenu>();
std::unique_ptr<PointMenu> pointMenu=std::make_unique<PointMenu>();
std::unique_ptr<QAction> convertPoint=std::make_unique<QAction>(tr("Convert To Point Node"));
std::unique_ptr<QAction> copyScaleAction=std::make_unique<QAction>(tr("Copy Scale"),nullptr);
std::unique_ptr<QAction> copyRotationAction=std::make_unique<QAction>(tr("Copy Rotation"),nullptr);
std::unique_ptr<QAction> copyTranslationAction=std::make_unique<QAction>(tr("Copy Translation"),nullptr);
std::unique_ptr<TransientPolygon> transPolygon;
std::unique_ptr<TransientBezierCurve> transCurve;
std::unique_ptr<TransientBSplineCurve> bspCurve;
std::unique_ptr<BezierMenu> bMenu;
std::unique_ptr<BSplineMenu> spMenu;
std::unique_ptr<AxisMenu> axisMenu;
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
ContextMenu cm=CE_NULL;
DRAWCURVE dc=DC_NULL;
Handle(Graphic3d_AspectMarker3d) GridAspect=new Graphic3d_AspectMarker3d(Aspect_TOM_RING1,Quantity_NOC_LIGHTSTEELBLUE,2);
bool ShowGrid=true;
bool ShowPlane=true;
bool ShowDrawingPlane=true;
bool IsSeen=false; //this is initialized when an object is found in Shapes;
bool IsSelectedColorUsed=false;
int CurrentSelMode=-1; //Current Selection Mode
int PrevSelMode=-1; //previous selection mode before current selection mode...
int CurrentShadeMode=3;
int WindowHeight=0;  //This is for the binded window;
int WindowWidth=0;
int ShapeId=-1; //invalid index
Handle(AIS_Manipulator) ObjectGizmo;    //This is the object gizmo

Handle(ViewCube) viewcube=new ViewCube();
Handle(AIS_ViewCubeOwner) viewcubeowner=new AIS_ViewCubeOwner(viewcube,V3d_Xpos);
const double dpr=devicePixelRatioF();


Handle(CustomAIS_Shape) ChosenShape;   //This will be a template for all chosen shapes
Handle(CustomAIS_Shape) PreviousShape;
Handle(CustomAIS_Shape) selShape;
Handle(CustomAIS_Shape) surfaceWidgetShape;

Handle(CustomAIS_Shape) prevCurrentObject;
Handle(CustomAIS_Shape) currentObject;   //this is used when a node is clicked,it will store the object 
Handle(AIS_Axis) AxisObject;
Quantity_Color currentObjectColor;


Handle(CustomAIS_Shape) emittedShape;  //this is to select subshapes of a shape
Handle(CustomAIS_Shape) prevEmittedShape;
Handle(CustomAIS_Shape)  currSelShape;
Handle(CustomAIS_Shape) currDetShape;
Quantity_Color currentShapeColor;
gp_Pnt2d lastpoint; 
gp_Pnt2d panlastpoint;   //this will store the pan 
gp_Pnt selFacePoint;
gp_Pnt LineStartPoint;
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
gp_Dir chosenDir;
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
std::unordered_map<size_t,Handle(AIS_InteractiveObject)> DraftShapes; //for every 2d shapes that will be rendered in the scene...
Graphic3d_MaterialAspect prevChosenMat;
size_t ChosenId=0;

int faceIndex=-1; //invalid index
int edgeIndex=-1;
int ParentIndex=-1;
TopoDS_Wire selWire;
Quantity_Color chosenFaceColor;
Quantity_Color chosenEdgeColor;
Quantity_Color chosenVertexColor;

CHOOSE_MODE chmode=CM_NULL; //to select and isolate a particular subshape in the scene for intersection
SELECTED_STATE st;
SELECTED_STATE st1;//for per face selection and per edge selection
TopoDS_Face surfaceWidgetFace;
TopoDS_Face convertedEdgeFace;
TopoDS_Shape SentShape=TopoDS_Shape();
TopoDS_Shape selFaceShape=TopoDS_Shape();
int mainIndex=-1;
int subMainIndex=-1;
int SentShapeId=-1;
GP_STATE gpsstate=GPS_NULL;
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
    convertPoint->setCheckable(true);
    drawLineDialog=std::make_unique<DrawLineDialog>(nullptr);
    
    Shapes.reserve(100);   //maximum shapes in the scene to prevent rehashing
    edgeMenu=std::make_unique<EdgeMenu>();
    faceMenu=std::make_unique<FaceMenu>();
    faceMenu->addAction(faceNormalAction.get());
    convertFacePointAction->setCheckable(true);
    faceMenu->addAction(convertFacePointAction.get());
    bMenu=std::make_unique<BezierMenu>();
    spMenu=std::make_unique<BSplineMenu>();
    axisMenu=std::make_unique<AxisMenu>();
    axisMenu->addAction(deleteAxisObject.get());
    AxisObject=new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0.0,0.0,0.0),gp_Dir(0.0,1.0,0.0)));
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
    copyScaleAction->setCheckable(true);
    copyTranslationAction->setCheckable(true);
    copyRotationAction->setCheckable(true);
    GatherPointAction=std::make_unique<QAction>(tr("Gather Point"),nullptr);
    GatherPointAction->setCheckable(true);
    FindAction=std::make_unique<QAction>(tr("Find In NodeGraph"));
    DeleteAction=new QAction(tr("Delete"),nullptr);
    
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
    SelectedMenu->addAction(FindAction.get());
    SelectedMenu->addAction(copyScaleAction.get());
    SelectedMenu->addAction(copyRotationAction.get());
    SelectedMenu->addAction(copyTranslationAction.get());
    SelectedMenu->addAction(CheckShapeIdAction.get());
    shouldSetAction->setCheckable(true);
   polyMenu=std::make_unique<PolygonMenu>();
    pointMenu->addAction(convertPoint.get());

    DockMenus=new QMenu;
    drawAction->setCheckable(true);
    showSettingAction=new QAction(tr("Show SceneSettings"),nullptr);  
    showSettingAction->setCheckable(true);
    DrawCubeAction=new QAction(tr("Draw Cube"),nullptr);
    DeleteObjectGizmoAction=new QAction(tr("Destroy Gizmo"),nullptr);
    refreshAction=std::make_unique<QAction>(tr("Refresh"),nullptr);
    GatherCurveAction=std::make_unique<QAction>(tr("Gather Bezier Points"),nullptr);
    GatherCurveAction->setCheckable(true);
    GatherBSplineAction=make_unique<QAction>(tr("Gather BSPline Points"),nullptr);
    GatherBSplineAction->setCheckable(true);
    DockMenus->addAction(showSettingAction);
    DockMenus->addAction(UndoAction);
    DockMenus->addAction(RedoAction);
    DockMenus->addAction(ConstructPointNodeAction.get());
    DockMenus->addAction(convertPointAction.get());
    DockMenus->addAction(refreshAction.get());
    DockMenus->addAction(drawAction.get());
    DockMenus->addAction(GatherPointAction.get());
    DockMenus->addAction(GatherCurveAction.get());
    DockMenus->addAction(GatherBSplineAction.get());
    DockMenus->addAction(shouldSetAction.get());
    
 display=new Aspect_DisplayConnection();
 driver=new OpenGl_GraphicDriver(display);
 Viewer=new V3d_Viewer(driver);
 view =Viewer->CreateView();   //Create the view from the viewer
 //Now to generate an id that can embed Qt project  
 context=new AIS_InteractiveContext(Viewer);
 
 transPolygon=std::make_unique <TransientPolygon>(std::ref(context));
 
 transCurve=make_unique<TransientBezierCurve>(std::ref(context));
 bspCurve=make_unique<TransientBSplineCurve>(std::ref(context));
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
 evt_manager.SetAllowZooming(false);
 evt_manager.SetAllowPanning(false);
 evt_manager.SetAllowRotation(false);


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
 connect(faceMenu->convertAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertToFaceNode);
 connect(faceMenu->searchAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleFaceSent);
 connect(edgeMenu->convertToFaceAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertEdgeToFace);
 connect(polyMenu->deleteAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDeletePoints);
 connect(polyMenu->removeLastAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnRemoveLastOne);
 connect(polyMenu->convertToBSpline.get(),&QAction::triggered,this,&DrawingCentralWidget::OnConvertToBSpline);
 connect(GatherPointAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGatherPoint);
 connect(GatherCurveAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGatherBezier);
 connect(bMenu->deleteAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDeleteBezier);
 connect(spMenu->IsPeriodicAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandlePeriodic);
 connect(GatherBSplineAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGatherBSpline);
 connect(spMenu->deleteAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDeleteBSplinePoint);
 connect(FindAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleSent);
 connect(CheckShapeIdAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnKnowId);
 connect(convertPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnSendPointValues);
 connect(pointMenu->DeleteAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDestroyMarker);
 connect(edgeMenu->convertToWireAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnSendWire);
 connect(edgeMenu->convertAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertToEdge);
 connect(copyTranslationAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSentTranslateTransform);
 connect(copyRotationAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSentRotateTransform);
 connect(copyScaleAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSentScaleTransform);
 connect(faceMenu->assumeFaceNormal.get(),&QAction::triggered,this,&DrawingCentralWidget::OnAssumeFaceNormal);
 connect(axisMenu->convertToAxisNode.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleOriginAxis);
 connect(axisMenu->convertToPositionedAxis.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandlePositionedAxis);
 connect(deleteAxisObject.get(),&QAction::triggered,this,&DrawingCentralWidget::OnRemoveAxisObject);
 connect(faceNormalAction.get(),&QAction::triggered,this,&DrawingCentralWidget::AssumeFaceCenterNormal);
 connect(convertFacePointAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGetFacePoint);
 connect(edgeMenu->showInfoAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnGetEdgeInfo);
 connect(drawAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleDrawLine);
 connect(drawLineMenu->drawLineAction.get(),&QAction::triggered,this,&DrawingCentralWidget::InitializeDrawDialog);
 connect(drawLineMenu->stopLineAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnStopDrawingLine);
 connect(drawLineDialog.get(),&DrawLineDialog::OnEmitDone,this,&DrawingCentralWidget::OnHandleDone);
}

void OnHighlight(Handle(CustomAIS_Shape)& cshape,const TopoDS_Shape& selshape,const int& mode){
  if(!cshape){
     return;
  }
  if(selshape.IsSame(TopoDS_Shape()) && mode!=0){
     return;
  }
  switch(mode){
    case 0:{
      
      break;
    }
    case 2:{
      cshape->HighlightEdge(TopoDS::Edge(selshape), Quantity_NOC_BURLYWOOD);
      break;
    }
    case 4:{
      cshape->HighlightFace(TopoDS::Face(selshape), Quantity_NOC_BURLYWOOD);
      break;
    }
  }
}   
void UnHighlight(Handle(CustomAIS_Shape)& cshape,const int& mode){
   switch(mode){
    case 0:{
      
      break;
    }
    case 2:{
      cshape->UnhighlightEdge();
      break;
    }
    case 4:{
      cshape->UnhighlightFace();
      break;
    }
  }
}










void LoadInfo(const QString& info,const QString& title){
  auto ret=QMessageBox::information(nullptr,title,info);

  return;
}
void OnHandleWireError(const BRepBuilderAPI_WireError& error,int& success){
  switch(error){
    case BRepBuilderAPI_WireDone:{
      LoadInfo(tr("Loop is successfully Created"),tr("Wire Info"));
      success=1;
      break;
    }
    case BRepBuilderAPI_EmptyWire:{
      LoadInfo(tr("Empty Wire was Formed"),tr("Wire Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_DisconnectedWire:{
      LoadInfo(tr("The Wire is not Fully Connected"),tr("Wire Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_NonManifoldWire:{
      LoadInfo(tr("A Non Manifold Wire was created"),tr("Wire Error"));
      success=-1;
      break;
    }
  }
  return;
}
void OnHandleFaceError(const BRepBuilderAPI_FaceError& error,int& success){
    switch(error){
    case BRepBuilderAPI_FaceDone:{
      LoadInfo(tr("Face Is Successfully Constructed"),tr("Face Info"));
      success=1;
      break;
    }
    case BRepBuilderAPI_NoFace:{
      LoadInfo(tr("No Face Is Created"),tr("Face Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_NotPlanar:{
      LoadInfo(tr("The Face Formed Is Not Planar"),tr("Face Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_CurveProjectionFailed:{
      LoadInfo(tr("Curve Projection Failed"),tr("Face Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_ParametersOutOfRange:{
      LoadInfo(tr("The Parameters Supplied to limit the surface are out of bounds"),tr("Face Error"));
      success=-1;
      break;
    }
    default:{
     LoadInfo(tr("Don't Know"),tr("Face Error"));
    }
    }
    return;
}
void FindSubShapeIndex(const Handle(CustomAIS_Shape)& cshape,const int& mode){
  //0 for edge,
  //1 for face
  //2 for the shape

  switch(mode){
    case 0:{
      edgeIndex=cshape->FindEdge(selEdge);
      break;
    }
    case 1:{
      faceIndex=cshape->FindFace(selFace);
      subMainIndex=faceIndex;
      break;
    }
    default:
     break;
  }
  return;
}
void ConvertEdgeToWire(){
  if(selEdge.IsNull()){
    return;
  }
  int success;
  BRepBuilderAPI_MakeWire wireBuilder(selEdge);
  OnHandleWireError(wireBuilder.Error(),success);
  if(success==-1){
    LoadInfo(tr("Failed"),tr("Wire Error"));
    return;
  }
  selWire=wireBuilder.Wire();
  return;
}
void ConvertEdgeToFace(){
  if(selEdge.IsNull()){
    return;
  }
  int success;
  BRepBuilderAPI_MakeWire wireBuilder(selEdge);
  OnHandleWireError(wireBuilder.Error(),success);
  if(success==-1){
    LoadInfo(tr("Failed"),tr("Wire Error"));
    return;
  }
  TopoDS_Wire wire=wireBuilder.Wire();
  BRepBuilderAPI_MakeFace faceBuilder(wire);
  OnHandleFaceError(faceBuilder.Error(),success);
  if(!faceBuilder.IsDone()){
    LoadInfo(tr("Failed To Build Face"),tr("Face Error"));
    return;
  }
  convertedEdgeFace=faceBuilder.Face();
  return;
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
     if(!Shapes.empty()){
      Shapes.clear();
       objectCount=0;
} 
   objectCount=0;
   context->RemoveAll(false);
   context->Display(viewcube,false);
   context->Display(object,CurrentShadeMode,CurrentSelMode,false);
   Shapes.insert(std::pair<size_t,Handle(CustomAIS_Shape)>(objectCount,object));
   ++objectCount;
   view->Redraw();
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
    for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
      context->Remove(iter->second,false);
    }
    Shapes.clear();
   
  
}
   
  objectCount=0;
   if(context->IsDisplayed(viewcube)){
    context->Redisplay(viewcube,false);
   }
  for(const auto& shape: shapes){
        context->Display(shape,CurrentShadeMode,CurrentSelMode,false);
        Shapes.insert(std::pair<size_t,Handle(CustomAIS_Shape)>(objectCount,shape));
        ++objectCount;
      
  }
  view->Redraw();

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
//this searches for an object that matches the chosen object,and store  it's ID
void OnSearch(const Handle(CustomAIS_Shape)& shape){
  bool isFound=false;
  for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
           if(iter->second==shape){
               ShapeId=iter->first;
               LoadMessage(tr("Shape Found Message"),tr("Shape Found"));
               isFound=true;
               break;
           }
        }
      if(isFound==false){
      LoadMessage(tr("Shape Not Found Error"),tr("Shape Not Found"));
       }
    
    return;
}
void MatrixInspector(const gp_Trsf& mat){
  std::cout<<"Matrix Form: "<<mat.Form()<<"\n";

  std::cout<<"Scale Factor: "<<mat.ScaleFactor()<<"\n";
  std::cout<<"Rotational Aspect:"<<"\n";
  gp_Mat rotMat=mat.GetRotation().GetMatrix();
  for(int i=1;i<=3;i++){
    for(int j=1;j<=3;j++){
    std::cout<<rotMat(i,j)<<" ";
  }
  cout<<"\n";
  }
  gp_XYZ transPart=mat.TranslationPart();
  cout<<"X: "<<transPart.X()<<" "<<"Y: "<<transPart.Y()<<" "<<"Z: "<<transPart.Z()<<"\n";
 return;
}
void OnHighlight(const int id){
if(id==-1){
  LoadMessage(tr("Negative Id"),tr("Cannot access shape using negative id"));
   return;
}
if(Shapes.find(id)==Shapes.end()){
  LoadMessage(tr("Invalid Id"),tr("Cannot Find Shape with this specific Id"));
  return;
}
  if(currSelShape){
         currSelShape->UseColor();
         context->Redisplay(currSelShape,false);
         context->Remove(currSelShape,false);
        }
      
       currSelShape=new CustomAIS_Shape(Shapes.at(id)->TransShape());
       if(!currSelShape){
        LoadMessage(tr("Current Selected Shape Error"),tr("No Current Selected Object"));
        return;
       }
        
        currSelShape->SetColor(Quantity_NOC_YELLOW2);
        currSelShape->SetTransparency(0.6);
        currSelShape->SetZLayer(Graphic3d_ZLayerId_Top);
        context->Display(currSelShape,1,CurrentSelMode,true);
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


void FlushViewEvent(){ //flush all the view events
  evt_manager.FlushViewEvents(context,view,true);
  return;
}




protected:
//On Selecting Objects,we must have knowledge of the selection mode that was chosen
void mousePressEvent(QMouseEvent* event) override{
 if(evt_manager.UpdateMouseButtons(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false)){
   

 
 if(event->button()==Qt::LeftButton){
    
    if(context->MoveTo(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view,false)==AIS_SOD_Nothing){
     

       
        /*
        we have to find the intersection of the ray and the surface in question
        using surfaceWidgetShape
        
        */
       if(dc==DC_LINE){
        double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
        LineStartPoint=gp_Pnt(projX,projY,projZ);
        return;
       }
      if(gpsstate==GPS_BSPLINE){
        LoadMessage(tr("B Spline Status"),tr("Spline In Progress"));
         double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
         bspCurve->AddBSplinePoles(gp_Pnt(projX,projY,projZ));
         FlushViewEvent();
         return;
      }
      if(gpsstate==GPS_BEZIER){
         double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
         transCurve->AddBezierPoles(gp_Pnt(projX,projY,projZ));
         transCurve->BuildShape();
         FlushViewEvent();
         return;
      }
      if(gpsstate==GPS_GATHER){
        double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);

        transPolygon->AddPoint(gp_Pnt(projX,projY,projZ));
        transPolygon->BuildShape();
        FlushViewEvent();
        return;
      }
      
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
        
       }
     UnHighlight(selShape,PrevSelMode);
     if(context->IsDisplayed(selShape)){
         context->Redisplay(selShape,true);
     }
     PrevSelMode=-1;
   if(context->IsDisplayed(pointMarker)){
    context->Remove(pointMarker,true);
   }
   if(context->IsDisplayed(currSelShape)){
    currSelShape->UseColor();
    context->Remove(currSelShape,true);
   }
  
   st=NULL_SELECT;
   st1=NULL_SELECT;
   cm=CE_NULL;
   context->Activate(viewcube,0);
   FlushViewEvent();
      return;
    }
    else{
    context->SelectDetected();
    
    
    context->InitSelected();
    while(context->MoreSelected()){
     
     if(CurrentSelMode==4){  //When currentSelMode is 4
       
        UnHighlight(selShape,PrevSelMode);
         if(selShape){
         if(context->IsDisplayed(selShape)){
          context->Redisplay(selShape,true);
         }
         }
        Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        Handle(AIS_InteractiveObject) obShape=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
        if(!obShape){
          cout<<"Failed To Cast"<<"\n";
        } 
        selShape=Handle(CustomAIS_Shape)::DownCast(obShape);
        
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
           selFaceShape=selectedEntity->Shape();
          std::cout<<"It is a Face"<<"\n";
        }
        else{
            std::cout<<"It is not a Face"<<"\n";
            QString str= shapetypemap.at(selectedEntity->Shape().ShapeType());
           std::cout<<"Shape's Type :"<<str.toUtf8().toStdString()<<"\n ";

            return;
        }
        st1=FACE_SELECT;
       
       gp_Pnt selectedPoint=context->MainSelector()->PickedPoint(1);
       selFacePoint=selectedPoint;
      
        int_x=selectedPoint.X();
        int_y=selectedPoint.Y();
        int_z=selectedPoint.Z();
       std::cout<<"Surface Points: "<<int_x<<","<<int_y<<","<<int_z<<"\n";
      gp_Pnt centroid=GetSurfaceCentre(selFace);
      if(!pointMarker){
        pointMarker=new AIS_Point(new Geom_CartesianPoint(0.0,0.0,0.0));
        pointMarker->SetColor(Quantity_NOC_PERU);
        pointMarker->SetMarker(Aspect_TOM_O);
      }
      Handle(Geom_Point) geom_pnt=new Geom_CartesianPoint(centroid.X(),centroid.Y(),centroid.Z());
      pointMarker->SetComponent(geom_pnt);
      x_value=centroid.X();
      y_value=centroid.Y();
      z_value=centroid.Z();
      if(context->IsDisplayed(pointMarker)){
         context->Remove(pointMarker,true);
         context->Display(pointMarker,true); 
      }
      else{
      context->Display(pointMarker,true);
      }
      OnHighlight(selShape,selFaceShape,CurrentSelMode);
       if(selShape){
         if(context->IsDisplayed(selShape)){
          context->Redisplay(selShape,true);
         }
         }
      PrevSelMode=CurrentSelMode;
      
    


        //Get3dPointFrom2D
      
       
       FlushViewEvent();
       return;

    }
    if(CurrentSelMode==2){ //for edge
         
         UnHighlight(selShape,PrevSelMode);
          if(selShape){
         if(context->IsDisplayed(selShape)){
          context->Redisplay(selShape,true);
         }
         }
         Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        if(!owner){
           std::cout<<"Failed To Cast To an object of SelectMgr_EntityOwner"<<"\n";
          return;
        }
         Handle(AIS_InteractiveObject) obShape=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
        if(!obShape){
          cout<<"Failed To Cast"<<"\n";
        } 
        selShape=Handle(CustomAIS_Shape)::DownCast(obShape);
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
        selFaceShape=selectedEntity->Shape();
        st1=EDGE_SELECT;
         gp_Pnt selectedPoint=context->MainSelector()->PickedPoint(1);
         int_x=selectedPoint.X();
         int_y=selectedPoint.Y();
         int_z=selectedPoint.Z();
          PrevSelMode=CurrentSelMode;
        OnHighlight(selShape,selFaceShape,CurrentSelMode); 
         if(selShape){
         if(context->IsDisplayed(selShape)){
          context->Redisplay(selShape,true);
         }
         }
         FlushViewEvent();
         return;
      
    }
      
    PrintSelection(CurrentSelMode);
   Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
   Handle(AIS_Axis) axisObject=Handle(AIS_Axis)::DownCast(owner->Selectable());
   if(axisObject){
    if(axisObject==AxisObject){
      cm=CE_AXIS;
      return;
    }
   }
   Handle(AIS_Point) pmaker=Handle(AIS_Point)::DownCast(owner->Selectable());
   if(pmaker){
    if(pmaker==pointMarker){
      cm=CE_POINT;
      return;
    }
   }
   Handle(AIS_Manipulator) chmanip=Handle(AIS_Manipulator)::DownCast(owner->Selectable());
   if(chmanip){
     if(chmanip==ObjectGizmo){
       if(ObjectGizmo->HasActiveMode()){
        evt_manager.UpdateMousePosition(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false);
        std::cout<<"Before Transform"<<"\n";
        try{
        ObjectGizmo->StartTransform(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view);
        }
        catch(const Standard_DomainError& error){
        LoadMessage(tr(""),tr("Invalid Index,Choose a part close the sphere to perform translation"));
        return;
        }
        std::cout<<"After Transform"<<"\n";
        view->Invalidate(); //force the redraw;
        isObjectTransformed=true;
        return;
       }
     }
   }
   //For the manipulator On the screen
  
    
  
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
      
     cm=CE_SHAPE;
     IsSelectedColorUsed=true;
     view->Redraw();
     emit QueryDebugMessage(tr("Assignment Successful"));
      FlushViewEvent();
      return;
    }
    context->NextSelected();
    }
 }
}     

   
   

else if(event->button()==Qt::RightButton){
  if(dc==DC_LINE){
    drawLineMenu->exec(event->globalPosition().toPoint());
    return;
  }
   if(cm==CE_AXIS){
     axisMenu->exec(event->globalPosition().toPoint());
     return;
   }
   if(cm==CE_POINT){
     pointMenu->exec(event->globalPosition().toPoint());
     return;
   }
  if(gpsstate==GPS_BSPLINE){
    spMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(gpsstate==GPS_BEZIER){
    bMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(gpsstate==GPS_GATHER){
   polyMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(st1==FACE_SELECT){
    faceMenu->exec(event->globalPosition().toPoint());
    return;
  }
 if(st1==EDGE_SELECT){
  edgeMenu->exec(event->globalPosition().toPoint());
  return;
 }

if(cm==CE_SHAPE){
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
if(cm==CE_NULL){
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
}





void mouseMoveEvent(QMouseEvent* event) override{
  if(!view.IsNull() && evt_manager.UpdateMousePosition(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false)){
    if(isObjectTransformed && ObjectGizmo->HasActiveMode()){
      ObjectGizmo->Transform(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view);
      context->Redisplay(ObjectGizmo->Object(),true);
      view->Invalidate(); //force the redraw of the scene...
      return;
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


}
}
   

void ComputeTransform(const TopoDS_Shape& prevShape,const TopoDS_Shape& currShape,gp_Trsf& outMat){
   cout<<"PrevShape's Transform:"<<"\n";
  MatrixInspector(prevShape.Location().Transformation());
  cout<<"CurrShape's Transform:"<<"\n";
  MatrixInspector(prevShape.Location().Transformation());
  
  if(currShape.Location().IsIdentity()){
     LoadMessage(tr("Identity Transform"),tr("The Current Transform is an identity matrix"));
     return;
  }
 
  TopLoc_Location prevLoc=currShape.Location();
  TopLoc_Location prevInvLoc=prevLoc.Inverted();
  TopLoc_Location currLoc=currShape.Location();
  auto currTrans=currLoc.Multiplied(prevInvLoc);
  outMat=currTrans.Transformation();
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
    if(evt_manager.UpdateMouseButtons(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false)){
     if(event->button()==Qt::LeftButton){
      if(isObjectTransformed && ObjectGizmo->HasActiveMode()){
        ObjectGizmo->StopTransform();
        view->Invalidate();
        SentTransform=ObjectGizmo->Object()->LocalTransformation();
        SentTransform.SetScaleFactor(ObjectGizmo->Object()->LocalTransformation().ScaleFactor());
        isObjectTransformed=false;
        OnDebugGizmo(ObjectGizmo);
        cout<<"\n";
        MatrixInspector(ObjectGizmo->Object()->LocalTransformation());
        
        Handle(CustomAIS_Shape) chosenShape=Handle(CustomAIS_Shape)::DownCast(ObjectGizmo->Object());
        if(chosenShape){
          chosenShape->SetTransformedShape(SentTransform);
        }
       return;
      }
     }
    
    return;
    }
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
  void OnEmitEdgeBool(bool value);
  void OnEmitFace(const TopoDS_Face& face);
  void OnEmitEdge(const TopoDS_Edge& edge);
  void OnEmitWire(const TopoDS_Wire& wire); //On Send Wire.
  void OnEmitSent();
  void OnSentFalseValue();
  void EmitAxis(const gp_Ax2& axis);
  void OnSendScaleTransform(const gp_Trsf& scaletransform);
  void OnEmitIndicies(const int a,const int b);
  void OnEmitPointCollections(const NCollection_Array1<gp_Pnt>& pnts);
  void OnEmitEdgeInfo(const EdgeInfo& edgeinfo);
  void OnEmitSurfaceInfo(const SurfaceInfo& surfaceinfo);
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
    context->Remove(ChosenShape,false);
    if(context->IsDisplayed(currSelShape)){
      context->Remove(currSelShape,false);
    }
    if(context->IsDisplayed(currDetShape)){
      context->Remove(currDetShape,false);
    }
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
//on convert Face Centre to point node
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

void OnConvertEdgeToFace(bool value){
  if(value){
    ConvertEdgeToFace();
    if(!convertedEdgeFace.IsNull()){
      emit OnEmitFace(convertedEdgeFace);
    }
  }
  else{
    emit OnEmitFaceBool(value);
  }
  return;
}

void OnGatherPoint(bool value){
    if(value){
      gpsstate=GPS_GATHER;
      
    }
    return;
}
void OnGatherBezier(bool value){
    if(value){
      gpsstate=GPS_BEZIER;
      
    }
    return;
}
void OnDeleteBezier(){
  if(!transCurve->Polygon()->Points().empty()){
    transCurve->Polygon()->Clear();
    transCurve->Polygon()->OnDestroy();
    transCurve->OnDestroy();
    gpsstate=GPS_NULL;
    GatherCurveAction->setChecked(false);
  }
}
void OnDeletePoints(){
   if(!transPolygon->Points().empty()){
    transPolygon->Clear();
    transPolygon->OnDestroy();
    gpsstate=GPS_NULL;
    GatherPointAction->setChecked(false);
   }
  
  return;
}
void OnRemoveLastOne(){
  if(!transPolygon->Points().empty()){
     transPolygon->RemoveLastPoint();
  }
  return;
}
void OnRefreshView(){
  view->Redraw(); //cause a redraw;
  return;
}
void OnHandlePeriodic(bool Value){
  bspCurve->SetIsPeriodic(Value);
  return;
}
void OnGatherBSpline(bool value){
   if(value){
     gpsstate= GPS_BSPLINE;
   }
   return;
}
void OnDeleteBSplinePoint(){
  if(!bspCurve->Polygon()->Points().empty()){
    bspCurve->Polygon()->Clear();
    bspCurve->Polygon()->OnDestroy();
    bspCurve->OnDestroy();
    gpsstate=GPS_NULL;
    GatherBSplineAction->setChecked(false);
  }
  return;
}
void OnHandleSent(){
  if(!ChosenShape){
  LoadMessage(tr("Chosen Shape Message"),tr("No Shape Selected"));
  return;
  }
  for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
    if(iter->second==ChosenShape){
      SentShapeId=iter->first;
      SentShape=iter->second->Shape();
      LoadMessage(tr("Shape Found"),tr("Shape And Id Found"));
      emit OnEmitSent();
      break;
    }
  }
  return;
}
void OnKnowId(){
  bool isFound=false;
  for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
           if(iter->second==ChosenShape){
               ShapeId=iter->first;
               LoadMessage(tr("ID Found"),QString("Current Id")+QString::number(iter->first));
               isFound=true;
               break;
           }
        }
      if(isFound==false){
      LoadMessage(tr("ID message"),tr("ID not found"));

       }
    return;
}
void OnSendPointValues(const bool value){
  if(value){
    emit OnSendConvertValue(Point(x_value,y_value,z_value));
  }
  else{
    emit OnSentFalseValue();
  }
}
void OnDestroyMarker(){
if(context->IsDisplayed(pointMarker)){
  context->Remove(pointMarker,true);

}
   if(pointMarker){
   pointMarker.Nullify();
   }
   return;
}
void OnSendWire(bool value){
  if(value){
    emit OnEmitWire(selWire);
    return;
  }
  else{
   emit OnEmitFaceBool(value);
  }
  return;
}
void OnConvertToFaceNode(bool value){
  if(value){
  if(selShape){
    OnSearch(selShape);
    FindSubShapeIndex(selShape,1);
    ParentIndex=ShapeId;

    emit OnEmitFace(selFace);
    return;
  }
   emit OnEmitFace(selFace);

} 
  else{
  emit OnEmitFaceBool(value);
  }

  return;
}
void OnConvertToEdge(bool value){
  if(value){
    if(selShape){
        OnSearch(selShape);
    FindSubShapeIndex(selShape,0); //search for edge index
    ParentIndex=ShapeId;
    emit OnEmitEdge(selEdge);
    return;
    }
    emit OnEmitEdge(selEdge);
  }
  else{
    emit OnEmitEdgeBool(value);
  }
  return;
}
//p for parent index and c for child index
void OnShadeFaceWithIndex(const int& p,const int&c){
  if(p==-1 || c==-1){
     LoadMessage(tr(""),tr("It is either the parent index or the child index is negative"));
     return;
  }
  if(Shapes.find(p)==Shapes.end()){
     LoadMessage(tr(""),tr("Object with this index does not exist"));
     return;
  }
  selShape=Shapes.at(p);
  if(!selShape){
    LoadMessage(tr(""),tr("Failed On Assigning a copy of an object of CustomAIS_Shape"));
    return;
  }
  selFaceShape=selShape->GetFace(c);
  PrevSelMode=4;
  selShape->ShadeFace(c, Quantity_NOC_CHARTREUSE2);
  if(context->IsDisplayed(selShape)){
    context->Redisplay(selShape,true);
  }
  return;
}
void UnShadeFaceWithIndex(const int& p,const int& c){
  if(p==-1 || c==-1){
     LoadMessage(tr(""),tr("It is either the parent index or the child index is negative"));
     return;
  }
  if(Shapes.find(p)==Shapes.end()){
     LoadMessage(tr(""),tr("Object with this index does not exist"));
     return;
  }
  selShape=Shapes.at(p);
  if(!selShape){
    LoadMessage(tr(""),tr("Failed On Assigning a copy of an object of CustomAIS_Shape"));
    return;
  }
  
  PrevSelMode=-1;
  selShape->UnShadeFace(c);
  if(context->IsDisplayed(selShape)){
    context->Redisplay(selShape,true);
  }
  return;
}
void OnConvertToBSpline(){
  if(transPolygon){
    GeomAPI_PointsToBSpline geomSpline(transPolygon->To_Array_One());
    if(geomSpline.IsDone()){
       BRepBuilderAPI_MakeEdge edge(geomSpline.Curve());
       if(edge.IsDone()){
        Handle(CustomAIS_Shape) shape=new CustomAIS_Shape(edge.Edge());
        if(shape){
           context->Display(shape,true);
           Shapes.insert(std::pair<size_t,Handle(CustomAIS_Shape)>(objectCount,shape));
           ++objectCount;
           context->Remove(transPolygon->DisplayedShape(),true);
        }
       }
       return;
    }
    else{
    LoadMessage(tr(""),tr("Failed To Convert To BSpline"));
    return;
    }
    
  }
  return;
}
void OnHandleFaceSent(){
  if(!selShape){
    LoadMessage(tr(""),tr("No Parent Shape own this selected entity"));
    return;
  }
  //mainIndex helps us to locate the main's shape  
   OnSearch(selShape);
    FindSubShapeIndex(selShape,1);
    mainIndex=ShapeId;
   emit  OnEmitIndicies(mainIndex,subMainIndex);
  return;
}

void OnHandleSentScaleTransform(bool value){
  if(value){
    gp_Trsf scaleTrans;
    scaleTrans.SetScale(gp_Pnt(0.0,0.0,0.0),SentTransform.ScaleFactor());
    MatrixInspector(scaleTrans);
    emit OnSendScaleTransform(scaleTrans);
    
  }
  else{
     emit OnEmitFaceBool(value);
  }
  return;
}
void OnHandleSentRotateTransform(bool value){
  if(value){
   gp_Trsf rotateTrans;
   rotateTrans.SetRotationPart(SentTransform.GetRotation());
   MatrixInspector(rotateTrans);
    emit OnSendScaleTransform(rotateTrans);

  }
  else{
    emit OnEmitFaceBool(value);
  }
  return;
}
void OnHandleSentTranslateTransform(bool value){
  if(value){
    gp_Trsf translate;
    translate.SetTranslationPart(SentTransform.TranslationPart());
     MatrixInspector(translate);
    emit OnSendScaleTransform(translate);
  }
  else{
     emit OnEmitFaceBool(value);
  }
  return;
}
//this assumes the face normal on the face
void OnAssumeFaceNormal(){
  if(selFace.IsNull()){
     LoadMessage(tr(""),tr("No Selected Face"));
     return;
  }
  gp_Dir chDir=SURFACE::GetFaceNormal(selFace,selFacePoint);
  chosenDir=chDir;
  if(!AxisObject){
    AxisObject=new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0.0,0.0,0.0),gp_Dir(0.0,1.0,0.0)));
  }
  AxisObject->SetAxis1Placement(new Geom_Axis1Placement(selFacePoint,chDir));
  if(context->IsDisplayed(AxisObject)){
    context->Redisplay(AxisObject,true);
  
  }
  else{
    context->Display(AxisObject,true);
  }
  
  return;
}
void OnHandlePositionedAxis(bool value){
 if(value){
  EmitAxis(gp_Ax2(selFacePoint,chosenDir));
 }
 else{
   emit OnEmitFaceBool(value);
 }
 return;
}
void OnHandleOriginAxis(bool value){
   if(value){
  EmitAxis(gp_Ax2(gp_Pnt(0.0,0.0,0.0),chosenDir));
 }
 else{
   emit OnEmitFaceBool(value);
 }
  return;
}
void OnRemoveAxisObject(){
  if(AxisObject){
        if(context->IsDisplayed(AxisObject)){
          context->Remove(AxisObject,true);
          view->Redraw();
        }

      }
      return;
}
void AssumeFaceCenterNormal(){
  if(selFace.IsNull()){
    return;
  }
  gp_Dir chDir=SURFACE::GetFaceNormal(selFace,SURFACE::GetSurfaceCentre(selFace));
  chosenDir=chDir;
  selFacePoint=SURFACE::GetSurfaceCentre(selFace);
  if(!AxisObject){
    AxisObject=new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0.0,0.0,0.0),gp_Dir(0.0,1.0,0.0)));
  }
  AxisObject->SetAxis1Placement(new Geom_Axis1Placement(SURFACE::GetSurfaceCentre(selFace),chDir));
  if(context->IsDisplayed(AxisObject)){
    context->Redisplay(AxisObject,true);
  
  }
  else{
    context->Display(AxisObject,true);
  }
  return;
}
//selFacePoint
void OnGetFacePoint(bool value){
if(value){
    emit OnEmitBoolValue(value);
    emit OnSendConvertValue(Point(selFacePoint.X(),selFacePoint.Y(),selFacePoint.Z())); 
    return;
  }
  else{
    emit OnEmitBoolValue(value);
    }
  return;
}
void OnGetFaceInfo(){
  if(selFace.IsNull()){
    LoadMessage(tr(""),tr("No face is selected"));
    return;
  }
  SurfaceInfo info;
  GetSurfaceInfo(selFace,info);
  emit OnEmitSurfaceInfo(info);
  return;
}
void OnGetEdgeInfo(){
  if(selEdge.IsNull()){
    LoadMessage(tr(""),tr("No edge is selected"));
    return;
  }
  EdgeInfo info;
  GetEdgeInfo(selEdge,info);
  emit OnEmitEdgeInfo(info);
  return;
}
void OnHandleDrawLine(bool value){
  if(value){
    dc=DC_LINE;
    LoadMessage(tr(""),tr("Click a point before clicking on start drawing menu option"));
    drawLineMenu->stopLineAction->setChecked(false);
  }
  return;
}
void OnStopDrawingLine(bool value){
  if(value){
    dc=DC_NULL;
    drawAction->setChecked(false);
  }
}
void InitializeDrawDialog(){
  if(drawLineDialog){
    drawLineDialog->SetPointOfRotation(LineStartPoint);
    drawLineDialog->exec();
  }
  return;
}

void OnHandleDone(){
  if(!drawLineDialog){
     LoadMessage(tr(""),tr("DrawLineDialog failed to be created"));
     return;
  }
  const float pie=3.14159265;
  gp_Ax1 axis=drawLineDialog->Axis();
  float ang=drawLineDialog->Angle();
  gp_Dir dir=drawLineDialog->Direction();
  float val=drawLineDialog->Length();
  if(ang>=0.1 && ang<=0.999999999){
    LoadMessage(tr(""),tr("Angle is not greater or equal to 1.0"));
    return;
  }
  if(val==0.000){
    LoadMessage(tr(""),tr("No Length is set"));
    return;
  }
  float convertedAngle=ang*(pie/180.0f);
  dir.Rotate(axis,convertedAngle);
  TopoDS_Edge edge=TopoDS_Edge();
  Handle(Geom_Line) line=new Geom_Line(LineStartPoint,dir);
  BRepBuilderAPI_MakeEdge edgeMaker;
  edgeMaker.Init(line,0,val);
  if(edgeMaker.IsDone()){
    edge=edgeMaker.Edge();
  }
  else{
    LoadMessage(tr(""),tr("Failed To Create Line"));
    return;
  }
  Handle(CustomAIS_Shape) lineShape=new CustomAIS_Shape(edge);
  context->Display(lineShape,false);
  view->Redraw();
  return;
}
};






#endif