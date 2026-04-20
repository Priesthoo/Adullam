//Gizmo that will be displayed on the screen when an object is clicked
//This gizmo consist of three types
//we have the translational gizmo
//we have the rotational gizmo
//we have the scalar gizmo
//we just have to construct the gizmo on top of a gui element,it is going to be displayed on the gui element
//each gizmo consists of geometry(cone and cylinder) for translation,geometry(circular  discs) for rotation,cylinder+cube for scaling
//They will all respond to mouse inputs and emit events 
#ifndef GIZMO_HPP
#define GIZMO_HPP
#include<gp_Trsf.hxx>
#include<gp_Pnt.hxx>
#include<AIS_Shape.hxx>
#include<AIS_InteractiveContext.hxx>
#include<AIS_InteractiveObject.hxx>
#include<BRepPrimAPI_MakeSphere.hxx>
#include<AIS_Shape.hxx>
enum GIZMO_TYPE{
GT_TRANSLATION,
GT_ROTATION,
GT_SCALE,
GT_NO_GIZMO
};
enum AXIS{ //This is sent when a particular axis is chosen
AXIS_X,
AXIS_Y,
AXIS_Z
};
enum SURFACE_TYPE{
  CYLINDRICAL_SURFACE,
  CIRCULAR_SURFACE,
  PLANAR_SURFACE,
  BEIZER_SURFACE,
  BSPLINE_SURFACE
};
//This Gizmo will have a display function that will used to render the drawings of the gizmo,it will also respond to mouse inputs 
class Gizmo{
private:
//sz is used to either scale up the radius or the scale down the radius
TopoDS_Shape MakeSphere(const gp_Ax2& p_Axis,const double& p_radius,const size_t& sz){
   return BRepPrimAPI_MakeSphere(p_Axis,p_radius*sz).Shape();
}



public:
GIZMO_TYPE type=GT_NO_GIZMO;  //By Default,No gizmo is Drawn
gp_Pnt Position; //this will hold the origin of the coordinate axis
Handle(AIS_Shape) AttachedObject;
Gizmo(){
  
}
virtual void Display(){  //This will be used by the derived classes of Gizmo to render the represented geometry
    return;
}
virtual GIZMO_TYPE GizmoType() const{
    return type;
}
virtual void BuildGizmo(Handle(AIS_InteractiveContext)& context){
     
  return;
}
//It accepts mouse inputs and perform necessary actions to it..
virtual HandleMouseInput(){
  
  return;
}
};
#endif
