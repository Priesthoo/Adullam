#ifndef UNDO_TRANSFORM_HPP
#define UNDO_TRANSFORM_HPP
#include<functional>
#include<QtGui/QUndoCommand>
#include<gp_Trsf.hxx>
class UndoTransformCommand:public QUndoCommand{
private:
std::reference_wrapper<Handle(AIS_InteractiveContext)> ref_context;
Handle(CustomAIS_Shape) myShape;
gp_Trsf prev_trsf;
gp_Trsf curr_trsf;




public:
UndoTransformCommand(Handle(AIS_InteractiveContext)& co,const Handle(CustomAIS_Shape)& shape,const gp_Trsf& form_trsf,const gp_Trsf& c_trsf):ref_context{co}{
   myShape=shape;
   prev_trsf=form_trsf;
   curr_trsf=c_trsf;
}
void undo() override{
    if(!ref_context.get().IsNull()){
         if(myShape.IsNull()){
            return;
         }
         if(ref_context.get()->IsDisplayed(myShape)){
            myShape->SetLocalTransformation(prev_trsf);
            ref_context.get()->Redisplay(myShape,false);
            ref_context.get()->UpdateCurrentViewer();
         }
    }
    return;
}
void redo() override{
     if(!ref_context.get().IsNull()){
         if(myShape.IsNull()){
            return;
         }
         if(ref_context.get()->IsDisplayed(myShape)){
            myShape->SetLocalTransformation(curr_trsf);
            ref_context.get()->Redisplay(myShape,false);
            ref_context.get()->UpdateCurrentViewer();
         }
    }
    return;
}
};
















#endif