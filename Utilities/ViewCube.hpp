#ifndef VIEWCUBE_HPP
#define VIEWCUBE_HPP
//We have to include the viewing cube,and set the AutoStartAnimation to handle change in view, 
#include<AIS_ViewCube.hxx>
class ViewCube:public AIS_ViewCube{
 public:
 ViewCube():AIS_ViewCube(){
    SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers,Aspect_TOTP_LEFT_UPPER,Graphic3d_Vec2i(100,90)));
    SetAutoStartAnimation(true);
    SetFixedAnimationLoop(true);
 }
};





#endif