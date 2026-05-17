#pragma once
#include<NodeDelegateModel>
#include<AxisNodeData.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
class SinglyAxisNode:public NodeDelegateModel{
private:
gp_Ax2 outputDir;
std::shared_ptr<AxisNodeData> outputData;
public:
SinglyAxisNode(){
    return;
}
gp_Ax2 Dir() const{
    return outputDir;
}
void SetDir(const gp_Ax2& dir){
    outputDir=dir;
    if(outputData){
        outputData->SetData(outputDir);
    }
    else{
        outputData=make_shared<AxisNodeData>(tr(""));
        outputData->SetData(outputDir);
    }
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
    return tr("Singly Axis Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return AxisNodeData(tr("Output Direction")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        outputData->SetData(outputDir);
    }
    return std::static_pointer_cast<NodeData>(outputData);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};