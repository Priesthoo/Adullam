#pragma once 
#include<VectorDataNodeData.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<DataArrayNode.hpp>
#include<ShapeNodeData.hpp>

#include<memory>
#include<iostream>
using namespace std;
using namespace QtNodes;
//2 to 5
class SingleArrayToVectorNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<DataArrayNode<2 ,ShapeNodeData>> InputShape_1;
std::shared_ptr<VectorDataNode<ShapeNodeData>> output_shape;
std::array<TopoDS_Shape,2> shape1;
bool AreElementsAdded=false;




public:
SingleArrayToVectorNode(){

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 1;  //number of input node
        }
        case PortType::Out:{
            return 1;
        }
        default:
           return 0;
    }
    return 0;
}
QString caption() const override{
    return tr("Single Array To Vector (Shape)");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                  return DataArrayNode<2,ShapeNodeData>(tr("Array"),tr("ArrayOfShape")).type();
            }
        }
        case PortType::Out:{
            switch(portIndex){
                case 0:                  //name        //name of type
                   return VectorDataNode<ShapeNodeData>(tr("Vector"),tr("VectorOfShape")).type();


            }
        }
    }
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data.get()){
      return;
    }
    switch(portIndex){
        case 0:{
             InputShape_1=std::dynamic_pointer_cast< DataArrayNode<2,ShapeNodeData>>(data);
             if(InputShape_1.lock().get()){
             shape1[0]=InputShape_1.lock()->Data()[0].Data();  //move the elements instead of copying elements
              shape1[1]=InputShape_1.lock()->Data()[1].Data();
             break;
             }
             break;
        }
    }
    if(!output_shape){
    output_shape=std::make_shared<VectorDataNode<ShapeNodeData>>(tr(""),tr(""),shape1.size()+1);
    }
    if(output_shape.get()){
       if(!AreElementsAdded){
       for(int i=0;i<shape1.size();i++){
            output_shape->Data().emplace_back(tr(""),shape1.at(i));
         }
           
         AreElementsAdded=true;
       }
       else{
        output_shape->Data()[0].SetData(shape1.at(0));
        output_shape->Data()[1].SetData(shape1.at(1));
        
       }
    }
    emit dataUpdated(0);
    //try to implement an algorithm to remove duplicates......
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_shape.get()){
      return static_pointer_cast<NodeData>(output_shape);

    }
      output_shape=std::make_shared<VectorDataNode<ShapeNodeData>>(tr(""),tr(""),shape1.size()+1); 
     if(!AreElementsAdded){
       for(int i=0;i<shape1.size();i++){
            output_shape->Data().emplace_back(tr(""),shape1.at(i));
         }
         AreElementsAdded=true;
       }

   
    return static_pointer_cast<NodeData>(output_shape);
}


QWidget* embeddedWidget () override{
    return nullptr;
}
};