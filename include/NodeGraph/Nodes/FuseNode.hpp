#ifndef FUSE_NODE_HPP
#define FUSE_NODE_HPP
#include<ShapeNodeData.hpp>
#include<NodeDelegateModel>
#include<iostream>
#include<BRepAlgoAPI_Fuse.hxx>
#include<NodeInitializer.hpp>
#include<memory>
using namespace QtNodes;
using namespace std;
class FuseNode:public NodeDelegateModel,public NodeInitializer{
  std::weak_ptr<ShapeNodeData> inputShape1; //first shape
  std::weak_ptr<ShapeNodeData> inputShape2;
  TopoDS_Shape outputShape;
  TopoDS_Shape shape1,shape2;
  std::shared_ptr<ShapeNodeData> shape;
  public:
  FuseNode(){

  }
  QString caption() const override{
    return tr("Fuse Node");
}
QString name() const override{
    return caption();
}
  unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  2;
        }
        case PortType::Out:{
            return 1;
        }
        default:
         break;
    }
    return 0;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:{
                    return ShapeNodeData(tr("First Shape")).type();
                case 1:
                     return ShapeNodeData(tr("Second Shape")).type();
                }
            }
        }
       case PortType::Out:{
          
            if(portIndex==0){
                return ShapeNodeData(tr("Output Shape")).type();
            }
       }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(shape){
        return static_pointer_cast<NodeData>(shape);
    }
    shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data.get()){
        return;
    }
    
    switch(portIndex){
        case 0:{
            inputShape1=std::dynamic_pointer_cast<ShapeNodeData>(data);
            if(inputShape1.lock()){
              shape1=inputShape1.lock()->Data();
              break;
            }
        }
       case 1:{
        inputShape2=std::dynamic_pointer_cast<ShapeNodeData>(data);
        if(inputShape2.lock()){
            shape2=inputShape2.lock()->Data();
        }
       }
    }
    if(!shape1.IsSame(TopoDS_Shape()) && !shape2.IsSame(TopoDS_Shape())){
        if(shape){
            BRepAlgoAPI_Fuse fuse(shape1,shape2);
            fuse.Build();
            if(fuse.IsDone()){
                shape->SetData(fuse.Shape());
                emit dataUpdated(0);
                return;
            }
            else{
                shape->SetData(TopoDS_Shape());
                emit dataUpdated(0);
                return;
            }
        }
        else{
            shape=make_shared<ShapeNodeData>(tr(""));
             BRepAlgoAPI_Fuse fuse(shape1,shape2);
            fuse.Build();
            if(fuse.IsDone()){
                shape->SetData(fuse.Shape());
                emit dataUpdated(0);
                return;
            }
            else{
                shape->SetData(TopoDS_Shape());
                emit dataUpdated(0);
                return;
            }
        }
    }
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};








#endif