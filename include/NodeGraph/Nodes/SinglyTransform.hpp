#pragma once
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<TransformNodeData.hpp>


#include<memory>
using namespace std;
using namespace QtNodes;
class SinglyTransformNode:public NodeDelegateModel,public NodeInitializer{
private:
gp_Trsf InputValue;
std::shared_ptr<TransformNodeData> output_data;
public:
SinglyTransformNode(){

}
void SetTransformData(const gp_Trsf& transform){
    InputValue=transform;
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
    return tr("Transform Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return TransformNodeData(tr("Output Transform")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
        output_data->SetData(InputValue);
        return std::static_pointer_cast<NodeData>(output_data);
    }
   output_data=std::make_shared<TransformNodeData>(tr(""));
    output_data->SetData(InputValue);
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};