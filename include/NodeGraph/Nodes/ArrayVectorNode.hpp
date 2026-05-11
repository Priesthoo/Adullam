#pragma once 
#include<DataArrayNode.hpp>
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<VectorDataNodeData.hpp>
#include<InfoUtility.hpp>
#include<memory>
using namespace INFO;
using namespace std;
using namespace QtNodes;
class ArrayVectorNode:public NodeDelegateModel{
private:
std::weak_ptr<VectorDataNode<ShapeNodeData>> shape_1;
std::weak_ptr<DataArrayNode<5,ShapeNodeData>> shape_2;
std::vector<ShapeNodeData> shapedata;
std::array<ShapeNodeData,5> shapearray;
std::shared_ptr<VectorDataNode<ShapeNodeData>> output_data;

public:
ArrayVectorNode(){

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  2;
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
    return tr("ArrayVector Of Shape Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:{
                    return VectorDataNode<ShapeNodeData>(tr("Input Shapes"),tr("VectorOfShape")).type();
                }
              case 1:{
                     return DataArrayNode<5,ShapeNodeData>(tr("Input Shapes"),tr("ArrayOfShape")).type();
              }
             

            }
        }
      case PortType::Out:{
            if(portIndex==0){
                return VectorDataNode<ShapeNodeData>(tr("Output Shapes"),tr("VectorOfShape")).type();

            }
        }
    
    }

}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
 if(!data){
    return;
 }
 switch(portIndex){
   case 0:{
    shape_1=dynamic_pointer_cast<VectorDataNode<ShapeNodeData>>(data);
    if(shape_1.lock()){
        if(!shapedata.empty()){
            shapedata.clear();
        }
        for(int i=0;i<shape_1.lock()->Size();i++){
            shapedata.emplace_back(tr(""),shape_1.lock()->GetValue(i).Data());
        }
    }
    break;
   }
   case 1:{
     shape_2=dynamic_pointer_cast<DataArrayNode<5,ShapeNodeData>>(data);
     if(shape_2.lock()){
        for(int i=0;i<shape_2.lock()->Size();i++){
            shapearray[i]=shape_2.lock()->GetValueAt(i);
        }
     }
     break;
   }
   }
   if(output_data){
     std::vector<ShapeNodeData> shapeVector;
     if(shapedata.empty()){
        LoadMessage(tr(""),tr("Array Of Shapes is Empty"));
        return;
     }
     for(int i=0;i<shapedata.size();i++){
        shapeVector.emplace_back(tr(""),shapedata.at(i).Data());

     }
     for(int i=0;i<shapearray.size();i++){
        shapeVector.emplace_back(tr(""),shapearray[i].Data());

     }
     output_data->SetData(shapeVector);
}
 else{
    output_data=std::make_shared<VectorDataNode<ShapeNodeData>>(tr(""),tr(""));
     std::vector<ShapeNodeData> shapeVector;
     if(shapedata.empty()){
        LoadMessage(tr(""),tr("Array Of Shapes is Empty"));
        return;
     }
     for(int i=0;i<shapedata.size();i++){
        shapeVector.emplace_back(tr(""),shapedata.at(i).Data());

     }
     for(int i=0;i<shapearray.size();i++){
        shapeVector.emplace_back(tr(""),shapearray[i].Data());

     }
     output_data->SetData(shapeVector);
 }
 emit dataUpdated(0);
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
      return static_pointer_cast<NodeData>(output_data);
      
    }
   std::shared_ptr<NodeData> mptr;
   return mptr;      
}
QWidget* embeddedWidget () override{
    return nullptr;
}
};