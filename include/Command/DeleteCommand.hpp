#pragma once
#include<AIS_Shape.hxx>

#include<AIS_InteractiveContext.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<functional>
#include<QtGui/QUndoCommand>
//What makes up the delete command, 
//for undo:it will redisplay the deleted object
//for Redo: it will do the deletion, provided the object exists
class DeleteCommand:public QUndoCommand{
private:
Handle(CustomAIS_Shape) PreviousShape;
std::reference_wrapper<Handle(AIS_InteractiveContext)> ref_context;
int currentselectionmode=-1;
int currShadingMode=-1;
public:
DeleteCommand(const Handle(CustomAIS_Shape)& shape,Handle(AIS_InteractiveContext)& co,const int& selcode,const int& cshmode):ref_context{co}{
    PreviousShape=shape;
    
    currentselectionmode=selcode;
    currShadingMode=cshmode;
    
}
 void undo() override{
    
    if(!PreviousShape.IsNull()){
        if(!ref_context.get().IsNull()){
            if(ref_context.get()->IsDisplayed(PreviousShape)){
                ref_context.get()->Redisplay(PreviousShape,true);
                ref_context.get()->UpdateCurrentViewer();
                return;
            }
            else{
                ref_context.get()->Display(PreviousShape,currShadingMode,currentselectionmode,true);
                ref_context.get()->UpdateCurrentViewer();
                return;
            }
        }
    }
    
    return;
}
void redo() override{ //This is the redo action that involves 
    if(!PreviousShape.IsNull()){
       if(ref_context.get()->IsDisplayed(PreviousShape)){
        ref_context.get()->Remove(PreviousShape,true);
        ref_context.get()->UpdateCurrentViewer();  //context->view->Redraw();
       }
    }
    return;
}

};