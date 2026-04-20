#ifndef TRANSLATION_GIZMO_HPP
#define TRANSLATION_GIZMO_HPP
#include<Gizmo.hpp>
#include<memory>
#include<AIS_InteractiveObject.hxx>
#include<Prs3d_ToolCylinder.hxx>

//The cylinders will be constructed with respect to the x,y,z axis
class Trans_Gizmo:public Gizmo,public AIS_InteractiveObject{
private:
   
public:
TopoDS_Shape TransAxis[3];  //This is for X,Y and Z axis

Trans_Gizmo(const gp_Pnt& point,Handle(AIS_InteractiveObject) attachedObject){
   
    UpdatePosition(point);
    type=GT_TRANSLATION;
   

}
//it is the same as SetPosition;
void UpdatePosition(const gp_Pnt& newposition){
    this->Position=newposition;
    return;
}
void UpdatePositionViaVector(const gp_Vec& vec){
   
    return;
}
virtual void Compute(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
                                       const Handle(Prs3d_Presentation)&         thePrs,
                                       const Standard_Integer theMode) override{
      
    if(theMode!=AIS_Shaded){
        return;
    }  

      return;                                        
                                       }

 virtual void ComputeSelection(const Handle(SelectMgr_Selection)& theSelection,
                                                const Standard_Integer theMode) override{
         return;
                                                }

};






#endif