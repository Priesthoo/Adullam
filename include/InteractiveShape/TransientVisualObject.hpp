#pragma once 
//This will objects that will be controlled via mouse inputs,menu's item
#include<AIS_InteractiveContext.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<functional>

class TransientVisualObject{
 private:
 std::reference_wrapper<Handle(AIS_InteractiveContext)> context; //context for display
 Handle(CustomAIS_Shape) displayedShape; //shapes to be displayed
 

public:
TransientVisualObject(Handle(AIS_InteractiveContext)* ctxptr=nullptr):context{*ctxptr}{
 return;
}
TransientVisualObject(Handle(AIS_InteractiveContext)& con):context{con}{
   

}
virtual void BuildShape(){
    return;
}
Handle(AIS_InteractiveContext)& Context(){
    return context.get();
}

bool CheckDisplayStatus(const Handle(CustomAIS_Shape)& sh){
    if(Context()->IsDisplayed(sh)){
        return true;
    }
    return false;
}
void OnUpdate(){
    Context()->UpdateCurrentViewer();
}
void OnDestroy(){
    if(displayedShape){
        displayedShape.Nullify();
    }
    return;
}
void SetDisplayedShape(const Handle(CustomAIS_Shape)& shape){
    displayedShape=shape;
}
void DisplayShape(){
   if(Context().IsNull()){
    return;
   }
   if(Context()->IsDisplayed(displayedShape)){
    Context()->Redisplay(displayedShape,true);
    return;
   }
   //current shade mode, current selection mode
   Context()->Display(displayedShape,0,0,true);
   
   return;
}
void RemoveShape(){
  if(Context()->IsDisplayed(displayedShape)){
      Context()->Remove(displayedShape,true);
  }
  return;
}

Handle(CustomAIS_Shape) DisplayedShape() const{
    return displayedShape;
}
void SetShape(const TopoDS_Shape& sh){
    displayedShape->SetShape(sh);
    return;
}
virtual ~TransientVisualObject(){}
};