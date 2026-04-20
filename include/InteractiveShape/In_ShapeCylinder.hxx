#ifndef IN_SHAPE_CYLINDER_HPP
#define IN_SHAPE_CYLINDER_HPP
#include<BRepPrimAPI_MakeCylinder.hxx>
#include<TopoDS_Shape.hxx>
#include<AIS_Shape.hxx>

class In_ShapeCylinder{

private:
double radius=0.0;
double height=0.0;
Handle(AIS_Shape) Cylind_Shape;
TopoDS_Shape Cylinder;
gp_Ax2 axis;

public:
In_ShapeCylinder(const gp_Ax2& p_axis,const double& p_radius,const double& p_height){
  axis=p_axis;
  Cylinder=BRepPrimAPI_MakeCylinder(axis,p_radius,height).Shape();
  radius=p_radius;
  height=p_height;
  Cylind_Shape=new AIS_Shape(Cylinder);
}
AIS_Shape GetCylinder() const{
    return Cylind_Shape;
}
AIS_Shape& ChangeCylind(){
    return Cylind_Shape;
}
TopoDS_Shape GetCylind_Shape() const{
    return Cylinder;
}
TopoDS_Shape& ChangeCylind_Shape(){
    return Cylinder;
} 
double GetRadius() const{
    return radius;
}
double GetHeight() const{
    return height;
}
void SetHeight(const double& p_h){
    height=p_h;
    Cylinder=BRepPrimAPI_MakeCylinder(axis,radius,height).Shape();
    if(!Cylind_Shape.IsNull()){
        Cylind_Shape.Nullify();
    }
    Cylind_Shape=new AIS_Shape(Cylinder);
    return;
}
void SetRadius(const double& p_radius){
    radius=p_radius;
    Cylinder=BRepPrimAPI_MakeCylinder(axis,radius,height).Shape();
    if(!Cylind_Shape.IsNull()){
        Cylind_Shape.Nullify();
    }
    Cylind_Shape=new AIS_Shape(Cylinder);
    return;
}
};







#endif 