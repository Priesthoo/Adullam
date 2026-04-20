#ifndef OUTPUT_NODE_HPP
#define OUTPUT_NODE_HPP
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<AIS_ShapeNodeData.hpp>
#include<NodeDescription.hpp>
#include<iostream>
#include<memory>
using QtNodes::NodeDelegateModel;
using namespace std;
//This Node will send an output signal to DrawingWidget
//This Node will have only one input, this input will be the outputted shape on the screen 
class OutputNode:public NodeDelegateModel,public NodeInitializer {
private:
Q_OBJECT
std::weak_ptr<AIS_ShapeNodeData> OutputAIS_Shape;


public:
OutputNode(){
   
}
unsigned int nPorts(PortType portType) const override{
    if(portType==PortType::In){
        return 1;
    }
    return 0;
}
QString caption() const override{
    return tr("OutputNode");
}
//This is the name of the 
QString name() const override{
    return tr("OutputNode");
}

NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    return AIS_ShapeNodeData(tr("Output")).type();
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
     if(!data.get()){
        return;
    }
    auto input=std::dynamic_pointer_cast<AIS_ShapeNodeData>(data);
   if(!input){
      return;
   }
    if(portIndex==0){
        OutputAIS_Shape=input;
        auto sh=OutputAIS_Shape.lock();
        emit OnSendAIS_Shape(sh->Data());
        std::cout<<"An Object Of AIS_Shape is Sent"<<"\n";
        return;
    }

    return;
}
virtual std::shared_ptr<NodeData> outData(PortIndex const port){
    std::shared_ptr<NodeData> ptr;
    return ptr;
}
//No embedded widget
QWidget* embeddedWidget() override{ return nullptr;}
signals:
void OnSendAIS_Shape(const Handle(CustomAIS_Shape)& shape);



};















#endif