#pragma once
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<FaceNodeData.hpp>
#include<iostream>
using namespace QtNodes;
using namespace std;
class SinglyFaceNode:public NodeDelegateModel,public NodeInitializer{
private:
std::shared_ptr<FaceNodeData> output_data;
TopoDS_Face inputValue;
public:
SinglyFaceNode(){

}
void SetFace(const TopoDS_Face& face){
     inputValue=face;
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
    return tr("Single Face Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return FaceNodeData(QString("Output Face")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
        output_data->SetFaceData(inputValue);
        return std::static_pointer_cast<NodeData>(output_data);
    }
    output_data=std::make_shared<FaceNodeData>(tr(""));
    output_data->SetFaceData(inputValue);
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};















