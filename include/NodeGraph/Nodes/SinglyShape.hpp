#pragma once
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>

#include<memory>
using namespace std;
using namespace QtNodes;

class SinglyShapeNode:public NodeDelegateModel,public NodeInitializer{
 private:
 TopoDS_Shape OutputValue;
 std::shared_ptr<ShapeNodeData> output_data;

 public:
 SinglyShapeNode(){

 } 
 void SetShapeData(const TopoDS_Shape& shape){
    OutputValue=shape;
    emit dataUpdated(0);
    return;
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
    return tr("Shape Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Output Shape")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
        output_data->SetData(OutputValue);
        return std::static_pointer_cast<NodeData>(output_data);
    }
   output_data=std::make_shared<ShapeNodeData>(tr(""));
    output_data->SetData(OutputValue);
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};
