#pragma once 
#include<NodeDelegateModel>
#include<memory>
#include<WireNodeData.hpp>
using namespace std;
using namespace QtNodes;

class SinglyWireNode:public NodeDelegateModel{
private:
TopoDS_Wire wire;

std::shared_ptr<WireNodeData> output_data;


public:
SinglyWireNode(){
    return;
}
TopoDS_Wire Wire() const{
    return wire;
}
void SetWire(const TopoDS_Wire& wire_1){
  wire=wire_1;
  if(output_data){
    output_data->SetData(wire_1);
  }
  else{
    output_data=std::make_shared<WireNodeData>(tr(""));\
    output_data->SetData(wire_1);
  }
  emit dataUpdated(0);
}

unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 0;
        }
        case PortType::Out:{
            return 1;
        } 
       
    }
    return 0;
}
QString caption() const override{
    return tr("Wire Node");
}
QString name() const override{
    return caption();
}

NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return WireNodeData(tr("Output Wire")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data){
        output_data->SetData(wire);
    }
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};