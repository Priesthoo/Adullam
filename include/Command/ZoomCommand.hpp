#ifndef ZOOM_COMMAND_HPP
#define ZOOM_COMMAND_HPP
#include<QtGui/QUndoCommand>
#include<functional>
#include<V3d_View.hxx>
class ZoomCommand:public QUndoCommand{
private:

std::reference_wrapper<Handle(V3d_View)> ref_view;
float prevScale=0.0f;
float CurrScale=0.0f;
public:
ZoomCommand(Handle(V3d_View)& p_view,const float& p_prevscale,const float& p_CurrScale):ref_view{p_view}{
    
    prevScale=p_prevscale;
    CurrScale=p_CurrScale;
}
void undo() override{
    ref_view.get()->Camera()->SetScale(prevScale);
    return;
}
void redo() override{
    ref_view.get()->Camera()->SetScale(CurrScale);
    return;
}
};
















#endif