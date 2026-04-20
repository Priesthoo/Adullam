#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP
#include<AIS_ViewController.hxx>
#include<AIS_InteractiveContext.hxx>
#include<AIS_Manipulator.hxx>
#include<AIS_InteractiveObject.hxx>
#include<V3d_View.hxx>
#include<Aspect_VKeyFlags.hxx>
//manages the event from the input devices,rendering gui and instances of ais_shape
class EventManager:public AIS_ViewController{
public:
EventManager():AIS_ViewController(){

}
void ProcessPressMouseButton(Handle(AIS_InteractiveContext)& context,Handle(AIS_Manipulator)& manip,Handle(V3d_View)& view,const Graphic3d_Vec2i& CurrPoint,const Aspect_VKeyMouse& theButton,const Aspect_VKeyFlags& theModifiers){
    if(AIS_ViewController::PressMouseButton(CurrPoint,theButton,theModifiers,false)){
        AIS_ViewController::FlushViewEvents(context,view,true);
    }
    return;
}
void ProcessReleaseMouseButton(Handle(AIS_InteractiveContext)& context,Handle(AIS_Manipulator)& manip,Handle(V3d_View)& view,const Graphic3d_Vec2i& CurrPoint,const Aspect_VKeyMouse& theButton,const Aspect_VKeyFlags& theModifiers){
     
    return;
}


};










#endif