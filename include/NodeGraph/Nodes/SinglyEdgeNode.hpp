#pragma once
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<EdgeNodeData.hpp>
#include<iostream>
using namespace QtNodes;
using namespace std;
class SinglyEdgeNode:public NodeDelegateModel,public NodeInitializer{
private:
std::shared_ptr<EdgeNodeData> output_data;
TopoDS_Edge inputValue;
int ParentIndex=-1;
int Index=-1;
public:
SinglyEdgeNode(){

}
void SetEdge(const TopoDS_Edge& edge){
     inputValue=edge;
     if(output_data){
        output_data->SetEdge(edge);
     }
     else{
        output_data=std::make_shared<EdgeNodeData>();
        output_data->SetEdge(edge);
     }
     emit dataUpdated(0);
     return;
}
void SetParentIndex(const int& p){
    ParentIndex=p;
    return;
}
int parentIndex() const{
    return ParentIndex;
}
void SetIndex(const int& p){
    Index=p;
    return;
}
int index() const{
    return Index;
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
    return tr("Single Edge Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return EdgeNodeData(QString("Output Edge")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
        
        return std::static_pointer_cast<NodeData>(output_data);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
    
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};
