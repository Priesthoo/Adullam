#ifndef CUSTOM_AIS_SHAPE_HXX
#define CUSTOM_AIS_SHAPE_HXX



#include <AIS_GraphicTool.hxx>
#include <AIS_InteractiveContext.hxx>
#include <BRepBndLib.hxx>
#include <BRepTools.hxx>
#include <BRepTools_ShapeSet.hxx>
#include <Graphic3d_AspectFillArea3d.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_Group.hxx>
#include<BRepBuilderAPI_Transform.hxx>
#include <Graphic3d_MaterialAspect.hxx>
#include <Graphic3d_Structure.hxx>
#include <Message.hxx>
#include <Message_Messenger.hxx>
#include <HLRBRep.hxx>
#include <OSD_Timer.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_Presentation.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <Prs3d_BndBox.hxx>
#include <StdPrs_ToolTriangulatedShape.hxx>
#include <Quantity_Color.hxx>
#include <Select3D_SensitiveBox.hxx>
#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>
#include <Standard_Type.hxx>
#include <StdPrs_HLRPolyShape.hxx>
#include <StdPrs_HLRShape.hxx>
#include <StdPrs_ShadedShape.hxx>
#include <StdPrs_WFShape.hxx>
#include <StdSelect.hxx>
#include <StdSelect_BRepSelectionTool.hxx>
#include <AIS_Shape.hxx>
#include<AIS_ColoredShape.hxx>
#include<TopExp_Explorer.hxx>
#include<TopAbs_ShapeEnum.hxx>
#include<TopTools_IndexedMapOfShape.hxx>
#include<BRepBuilderAPI_GTransform.hxx>
#include<TopExp.hxx>
#include<TopoDS.hxx>
#include<iostream>
#include<TopoDS.hxx>
#include<gp_GTrsf.hxx>
#include<InfoUtility.hpp>
using namespace INFO;
enum VISUAL_ASPECT{
VA_FACE,
VA_EDGE,
VA_VERTEX,
VA_NULLABLE
};
enum ERROR_TYPE{
  ET_SUCCESS,
  ET_FAILURE
};
class CustomAIS_Shape:public AIS_ColoredShape{

public:
size_t UniqueId=0;    
bool IsACopy=false;  
bool hasMaterial=false; //by default the object does not have any material
bool ColorIsSet=false;
Quantity_Color initialColor;
gp_Trsf initialTrsf; //compounded transformation
TopoDS_Shape trans_shape; //transformed shape used in construction of the selected or detected shape
TopTools_IndexedMapOfShape faceMap;
TopTools_IndexedMapOfShape edgeMap;
int highlightIndex=-1; //highlightIndex for face
int edgeHighlightIndex=-1;
ERROR_TYPE et;
CustomAIS_Shape(const TopoDS_Shape& theshape):AIS_ColoredShape(theshape){
  TopExp::MapShapes(Shape(),TopAbs_FACE,faceMap);
  TopExp::MapShapes(Shape(),TopAbs_EDGE,edgeMap);
  SetVisualAspect(Quantity_NOC_RED2);
  trans_shape=theshape;
}

bool AcceptDisplayMode(const Standard_Integer theMode) const override{
  return theMode>=0 && theMode<=3; 
}
void Compute(const Handle(PrsMgr_PresentationManager)& thePM, const Handle(Prs3d_Presentation)& thePrs,const Standard_Integer theMode) override{
      
       if(theMode==3){
        AIS_ColoredShape::Compute(thePM,thePrs,0);
        AIS_ColoredShape::Compute(thePM,thePrs,1);
        

       }
       else{
         AIS_ColoredShape::Compute(thePM,thePrs,theMode);
         std::cout<<theMode<<" is Chosen"<<std::endl;
        
       }
    
    thePrs->ReCompute();
    return;
}
void HighlightFace(const TopoDS_Face& face,const Quantity_Color& color){
  int index=FindFace(face);
  if(index==-1){
    LoadMessage(QString(""),QString("Could not find Face"));
    return;
  }
  highlightIndex=index;
  ShadeFace(index,color);
}
void UnhighlightFace(){
  if(highlightIndex==-1){
    LoadMessage(QString(""),QString("Highlight Index is minus"));
    return;
  }
  UnShadeFace(highlightIndex);

  return;
}

void HighlightEdge(const TopoDS_Edge& edge,const Quantity_Color& color){
   int index=FindEdge(edge);
  if(index==-1){
    LoadMessage(QString(""),QString("Could not find Edge"));
    return;
  }
  edgeHighlightIndex=index;
  ShadeEdge(index,color);
  
  
  
  return;
}
void UnhighlightEdge(){
   if(edgeHighlightIndex==-1){
    LoadMessage(QString(""),QString("Highlight Index is minus"));
    return;
  }
  UnShadeEdge(edgeHighlightIndex);
  return;
}


virtual AIS_KindOfInteractive Type() const Standard_OVERRIDE
  {
    return AIS_KindOfInteractive_Shape;
  }
  //you can set the color using diffuse component of MaterialAspect();
void SetVisualAspect(const Quantity_Color& color=Quantity_Color(),const VISUAL_ASPECT& aspect=VA_FACE){
   InitColor(color);
   return;
}
void SetMaterialAspect(const Graphic3d_MaterialAspect& mat){
  SetMaterial(mat);
  InitColor(mat.DiffuseColor()); //always set to diffuse color;
  return;
}
void setCustomColor(const TopoDS_Shape& shape,const Quantity_Color& color){
    SetCustomColor(shape,color);
    return;
}
void UnShadeEdge(const unsigned int& index){
    if(index-1==edgeMap.Extent()){
       UnsetCustomAspects(edgeMap(faceMap.Extent()));
       return;
     }
  if(index<1){
       return;
     }
     if(index>edgeMap.Extent()){
        return;
     }
  UnsetCustomAspects(edgeMap(index));
  return;
}
void UnShadeFace(const unsigned int& index){
  if(index-1==faceMap.Extent()){
       UnsetCustomAspects(faceMap(faceMap.Extent()));
       return;
     }
  if(index<1){
       return;
     }
     if(index>faceMap.Extent()){
        return;
     }
  UnsetCustomAspects(faceMap(index));
  return;
  
}
void ShadeFace(const unsigned int& index,const Quantity_Color& color){
     if(index-1==faceMap.Extent()){
       SetCustomColor(faceMap(faceMap.Extent()),color);
       return;
     }
     if(index<1){
       return;
     }
     if(index>faceMap.Extent()){
        return;
     }
     SetCustomColor(faceMap(index),color);
     return;
}
int FindFace(const TopoDS_Face& face){
   TopExp_Explorer exp;
   int i=1;
   bool isFound=false;
   for(exp.Init(Shape(),TopAbs_FACE);exp.More();exp.Next()){
     if(face.IsSame(TopoDS::Face(exp.Current()))){
        isFound=true;
        return i;
     }
     ++i;
   }
   if(isFound==false){
    return -1;
   }
}
int FindEdge(const TopoDS_Edge& edge){
   TopExp_Explorer exp;
   int i=1;
   bool isFound=false;
   for(exp.Init(Shape(),TopAbs_EDGE);exp.More();exp.Next()){
     if(edge.IsSame(TopoDS::Edge(exp.Current()))){
        isFound=true;
        return i;
     }
     ++i;
   }
   if(isFound==false){
    return -1;
   }
}




void ShadeEdge(const unsigned int& index,const Quantity_Color& color){
     if(index<1){
       return;
     }
     if(index>edgeMap.Extent()){
        return;
     }
     SetCustomColor(edgeMap(index),color);
     return;
}
int FaceCount() const{
  return faceMap.Extent();
}
int EdgeCount() const{
   return edgeMap.Extent();
}
TopoDS_Face GetFace(const int& index) const{
      return TopoDS::Face(faceMap(index));
}
TopoDS_Edge GetEdge(const int& index) const{
  return TopoDS::Edge(edgeMap(index));
}
void SetTransShape(const TopoDS_Shape& shape){ //for selection and detection
  trans_shape=shape;
  return;
}
void SetTransformedShape(const gp_Trsf& trsf){
  SetInitTransform(trsf);
  gp_GTrsf gtrans(trsf);
  BRepBuilderAPI_GTransform gst(Shape(),gtrans);
  if(gst.IsDone()){
    trans_shape=gst.Shape();
  }
  else{
    LoadMessage(QString("Failed Transformed"),QString("Failed To Transform the object"));
    return;
  }
  return;

}
TopoDS_Shape TransShape() const{
  return trans_shape;
}
//it is also applied to
void InitHighlightColor(const Quantity_Color& hi_color){
    SetColor(hi_color);

}
void UseColor(){
    SetColor(initialColor);
}
void SetInitShape(const TopoDS_Shape& shape){
   TopoDS_Shape sh=shape;
   sh.Location(initialTrsf);
   SetShape(sh);

}
void SetInitTransform(const gp_Trsf& trsf){
 initialTrsf=trsf;
 
 return;
 }
 gp_Trsf GetTransform() const{
     return initialTrsf;
}

void InitColor(const Quantity_Color& objectColor){
    initialColor=objectColor;
    SetColor(initialColor);
    return;
}

~CustomAIS_Shape(){
  return;
}

};















#endif