#ifndef SHAPE_ARRAY_NODE_HPP
#define SHAPE_ARRAY_NODE_HPP
#include<memory>
#include<ShapeNodeData.hpp>
#include<NodeInitializer.hpp>
#include<DataArrayNode.hpp>
#include<NodeDelegateModel>

#include<iostream>
using QtNodes::NodeDelegateModel;
using namespace std;
//Accepts two shapes and display them on the screen
class ShapeArrayNode:public NodeDelegateModel,public NodeInitializer{
private:
Q_OBJECT
std::weak_ptr<ShapeNodeData> InputShape_1;  //first input shape
std::weak_ptr<ShapeNodeData> InputShape_2;  //second input shape
std::shared_ptr<DataArrayNode<2,ShapeNodeData>> output_data;  //output shapes

public:
ShapeArrayNode(){
   
}

unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 2;
        }
        case PortType::Out:{
            return 1;
        }
        default:
        break;
    }
    return 0;
}
QString caption() const override{
    return tr("Shape Array");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                  return ShapeNodeData(tr("TopoShape")).type();
                case 1:
                  return ShapeNodeData(tr("TopoShape")).type();
            }
        }
        case PortType::Out:{
            switch(portIndex){
                case 0:                  //name        //name of type
                   return DataArrayNode<2,ShapeNodeData>(tr("Shape"),tr("ArrayOfShape")).type();
            }
        }
    }
}

//Inputs to the node
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data.get()){
        return;
    }
    if(!output_data.get()){
       output_data.reset(new DataArrayNode<2,ShapeNodeData>(tr(""),tr("")));
    }
    switch(portIndex){
     case 0:{
        InputShape_1=std::dynamic_pointer_cast<ShapeNodeData>(data);
        if(InputShape_1.lock().get()){
            output_data->SetValueAt(0,*InputShape_1.lock().get());
        }
          emit dataUpdated(0);
        break;
     }
     case 1:{
        InputShape_2=std::dynamic_pointer_cast<ShapeNodeData>(data);
        if(InputShape_2.lock().get()){
            output_data->SetValueAt(1,*InputShape_2.lock().get());
        }
        emit dataUpdated(0);
        break;
     }
    }
    return;
}

std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
        return std::static_pointer_cast<NodeData>(output_data);

    }
    output_data.reset(new DataArrayNode<2,ShapeNodeData>(tr(""),tr("")));
    return static_pointer_cast<NodeData>(output_data);  //it will surely cast to an Object of NodeData
}

QWidget* embeddedWidget() override {return nullptr;}

};










#endif