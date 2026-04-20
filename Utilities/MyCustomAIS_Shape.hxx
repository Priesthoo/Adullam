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
#include<TopExp.hxx>
#include<TopoDS.hxx>
#include<iostream>
#include<TopoDS.hxx>

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
    if (myshape.IsNull() || (myshape.ShapeType() == TopAbs_COMPOUND && myshape.NbChildren() == 0))
        {
          return;
        }

      if(static_cast<int>(myshape.ShapeType())> 4){
          StdPrs_WFShape::Add(thePrs, myshape, myDrawer);
    }
    else{
         StdPrs_ToolTriangulatedShape::ClearOnOwnDeflectionChange(myshape, myDrawer, Standard_True);
      try
      {
        OCC_CATCH_SIGNALS
        StdPrs_WFShape::Add(thePrs, myshape, myDrawer);
        StdPrs_ShadedShape::Add(
              thePrs,
              myshape,
              myDrawer,
              myDrawer->ShadingAspect()->Aspect()->ToMapTexture()
                && !myDrawer->ShadingAspect()->Aspect()->TextureMap().IsNull(),
              myUVOrigin,
              myUVRepeat,
              myUVScale);
           AIS_ColoredShape::Compute(thePM,thePrs,theMode);  
             
      }
      catch (Standard_Failure const& anException)
      {
        Message::SendFail(
          TCollection_AsciiString(
            "Error: AIS_Shape::Compute() wireframe presentation builder has failed (")
          + anException.GetMessageString() + ")");
      }
       
       }
        

       }
       else{
         AIS_ColoredShape::Compute(thePM,thePrs,theMode);
         std::cout<<theMode<<" is Chosen"<<std::endl;
        
       }
    
    thePrs->ReCompute();
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
void UnShadeEdge(const unsigned int& index){
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
void SetTransShape(const gp_Trsf& trans){ //for selection and detection
  initialTrsf=trans;
  BRepBuilderAPI_Transform trans_f(Shape(),trans);
  if(trans_f.IsDone()){
     trans_shape=trans_f.Shape();
     et=ET_SUCCESS;
     return;
  }
  et=ET_FAILURE;
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
 initialTrsf=initialTrsf*trsf;
 
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