#ifndef UNDO_CREATION_HPP
#define UNDO_CREATION_HPP
#include<QtGui/QUndoCommand>
#include<functional>
#include<MyCustomAIS_Shape.hxx>
#include<AIS_InteractiveContext.hxx>

// for every created shape,we can undo it's creation,just like deleting the shape
class UndoCreationCommand:public QUndoCommand{
private:
Handle(CustomAIS_Shape) DrawnShape;  //The drawn shape
std::reference_wrapper<Handle(AIS_InteractiveContext)> ref_context; //reference to the current context
public:
UndoCreationCommand(Handle(AIS_InteractiveContext)& co,const Handle(CustomAIS_Shape)& myshape):ref_context{co}{
DrawnShape=myshape;
}

void undo() override{
    if(ref_context.get().IsNull()){
        return;
    }
    if(DrawnShape.IsNull()){
        return;
    }
    if(ref_context.get()->IsDisplayed(DrawnShape)){
       ref_context.get()->Remove(DrawnShape,true);  //remove shape and update the view
       return;
    }
    return;
}
void redo() override{
     if(ref_context.get().IsNull()){
        return;
    }
    if(DrawnShape.IsNull()){
        return;
    }
    if(ref_context.get()->IsDisplayed(DrawnShape)){
        ref_context.get()->Redisplay(DrawnShape,true);
        return;
    }
}
};














#endif