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
class TenSizedArrayNode:public NodeDelegateModel{
private:
std::weak_ptr<DataArrayNode<5,ShapeNodeData>> shape_1;
std::array<ShapeNodeData,5> outputArray_1;
std::array<ShapeNodeData,5> outputArray_2;
std::shared_ptr<VectorDataNode<ShapeNodeData>> output_data;
public:
TenSizedArrayNode(){

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
    return tr("Ten Sized Shape Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:{
                    return DataArrayNode<5,ShapeNodeData>(tr("Input Shapes"),tr("ArrayOfShape")).type();
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
        shape_1=dynamic_pointer_cast<DataArrayNode<5,ShapeNodeData>>(data);
        if(shape_1.lock()){
            for(int i=0;i<shape_1.lock()->Size();i++){
                outputArray_1[i]=shape_1.lock()->GetValueAt(i);
            }
        }
        break;
    }
    case 1:{
        shape_1=dynamic_pointer_cast<DataArrayNode<5,ShapeNodeData>>(data);
        if(shape_1.lock()){
            for(int i=0;i<shape_1.lock()->Size();i++){
                outputArray_2[i]=shape_1.lock()->GetValueAt(i);
            }
        }
        break;
    }
 }
 if(output_data){
    std::vector<ShapeNodeData>shapeArray;
    shapeArray.resize(10);
    if(!outputArray_1.empty()&& outputArray_2.empty()){
     for(int i=0;i<outputArray_1.size();i++){
        shapeArray.emplace_back(tr(""),outputArray_1.at(i).Data());
     }
     for(int i=0;outputArray_2.size();i++){
        shapeArray.emplace_back(tr(""),outputArray_2.at(i).Data());
     }
    }
    if(shapeArray.empty()){
        LoadMessage(tr(""),tr("Shape Array is Empty"));
        return;
    }
    output_data->SetData(shapeArray);
 }
 else{
    output_data=std::make_shared<VectorDataNode<ShapeNodeData>>(tr(""),tr(""));
    std::vector<ShapeNodeData>shapeArray;
    shapeArray.resize(10);
    if(!outputArray_1.empty()&& outputArray_2.empty()){
     for(int i=0;i<outputArray_1.size();i++){
        shapeArray.emplace_back(tr(""),outputArray_1.at(i).Data());
     }
     for(int i=0;outputArray_2.size();i++){
        shapeArray.emplace_back(tr(""),outputArray_2.at(i).Data());
     }
    }
    if(shapeArray.empty()){
        LoadMessage(tr(""),tr("Shape Array is Empty"));
        return;
    }
    output_data->SetData(shapeArray);
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