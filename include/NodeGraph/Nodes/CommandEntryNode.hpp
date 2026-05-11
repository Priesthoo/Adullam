#pragma once 
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;

class CommandEntryShapeNode:public NodeDelegateModel{
 private:
 std::weak_ptr<ShapeNodeData>Inputdata;
 TopoDS_Shape shape=TopoDS_Shape();


 public:
 CommandEntryShapeNode(){

 }
 
 TopoDS_Shape Shape() const{
    return shape;
 }
 void SetShape(const TopoDS_Shape& sh){
    shape=sh;
    
    return;
 }
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 1;
        }
        case PortType::Out:{
            return 0;
        } 
       
    }
    return 0;
}
QString caption() const override{
    return tr("Cmd Entry Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Output Shape")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
   std::shared_ptr<NodeData> mptr;
   return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   if(portIndex==0){
    Inputdata=dynamic_pointer_cast<ShapeNodeData>(data);
    if(Inputdata.lock()){
        shape=Inputdata.lock()->Data();
    }
   }
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};