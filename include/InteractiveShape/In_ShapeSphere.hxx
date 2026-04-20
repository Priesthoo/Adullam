#ifndef IN_SHAPE_SPHERE_HPP
#define IN_SHAPE_SPHERE_HPP
#include<BRepPrimAPI_MakeSphere.hxx>
#include<AIS_Shape.hxx>
#include<TopoDS_Shape.hxx>
class In_ShapeSphere{
  private:
  TopoDS_Shape Sphere;
  Handle(AIS_Shape) SphereShape;
  gp_Ax2 axis;
  double Radius=0.0;
  public:
  In_ShapeSphere(const gp_Ax2& p_axis,const double& p_radius){
    axis=p_axis;
    Radius=p_radius;
    Sphere=BRepPrimAPI_MakeSphere(axis,Radius).Shape();
    SphereShape=new AIS_Shape(Sphere);
  }
 void SetRadius(const double& p_radius){
  Radius=p_radius;
   Sphere=BRepPrimAPI_MakeSphere(axis,Radius).Shape();
   if(!SphereShape.IsNull()){
       SphereShape.Nullify();
   }
   SphereShape=new AIS_Shape(Sphere);
  return;
 }
 
};












#endif