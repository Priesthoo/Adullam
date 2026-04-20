#pragma once 
#include<AxisNodeData.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<PointNodeData.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
//this requires direction,the other one doesn't
class NegatedPositionedDirXNode:public NodeDelegateModel,public NodeInitializer{
private:
std::shared_ptr<AxisNodeData> outputAxis;
std::weak_ptr<PointNodeData> inputPoint;
 gp_Dir axis=gp_Dir(-1.0,0.0,0.0);

public:
NegatedPositionedDirXNode(){
    outputAxis=make_shared<AxisNodeData>(tr(""));
    
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::Out:{
            return 1;
        }
        default:
           return 1;
    }
    return 0;
}
QString caption() const override{
    return tr("Negated Positioned Unit X Direction");  //
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                  return AxisNodeData(QString("output Axis")).type();
            }
        }
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return PointNodeData(tr("Position")).type();
            }
        }
        }
        
    
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
 if(!data){
    return;
 }
 if(portIndex==0){
    inputPoint=dynamic_pointer_cast<PointNodeData>(data);
    if(inputPoint.lock()){
        outputAxis->SetData(inputPoint.lock()->ToPnt(),axis);
        emit dataUpdated(0);
        return;
    }
 }
 return;
}

std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputAxis){
        return std::static_pointer_cast<NodeData>(outputAxis);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
QWidget* embeddedWidget() override{
    return nullptr;
}



};