#ifndef IN_SHAPE_BOX_HPP
#deifne IN_SHAPE_BOX_HPP
#include<BRepPrimAPI_MakeBox.hxx>
#include<AIS_Shape.hxx>
#include<TopoDS_Shape.hxx>
//In_ means Interactive 
class In_ShapeBox{
  private:
  Handle(AIS_Shape) BoxShape;
  TopoDS_Shape Box;
  double Height=0.0;
  double Width=0.0;
  double Length=0.0;
  gp_Ax2 axis;
  public:
  In_ShapeBox(const gp_Ax2& p_axis,const double& p_height,const double& p_width,const double& p_length){
    Height=p_height;
    Width=p_width;
    Length=p_length;
    axis=p_axis;
    Box=BRepPrimAPI_MakeBox(axis,Height,Width,Length).Shape();
    BoxShape=new AIS_Shape(Box);
    return;
  }
  void SetHeight(const double& p_h){
    Height=p_h;
     Box=BRepPrimAPI_MakeBox(axis,Height,Width,Length).Shape();
    if(!BoxShape.IsNull()){
        BoxShape.Nullify();
    }
    BoxShape=new AIS_Shape(Box);
    return;
  }

  void SetWidth(const double& p_w){
    Width=p_w;
    Box=BRepPrimAPI_MakeBox(axis,Height,Width,Length).Shape();
    if(!BoxShape.IsNull()){
        BoxShape.Nullify();
    }
    BoxShape=new AIS_Shape(Box);
    return;
  }

  void SetLength(const double& p_l){
    Length=p_l;
     Box=BRepPrimAPI_MakeBox(axis,Height,Width,Length).Shape();
     if(!BoxShape.IsNull()){
       BoxShape.Nullify();
     }
     BoxShape=new AIS_Shape(Box);
     return;
  }
  double GetHeight() const{
    return Height;
  }
  double GetWidth() const{
    return Width;
  }
  double GetLength() const{
    return Length;
  }
};













#endif