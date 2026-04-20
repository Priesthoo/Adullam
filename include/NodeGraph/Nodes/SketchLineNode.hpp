#pragma once
#include<NodeDelegateModel>
#include<PointNodeData.hpp>
#include<ShapeUtil.hpp>
#include<NodeInitializer.hpp>
#include<ShapeNodeData.hpp>
#include<memory>
using namespace Shape_Utility;
using namespace QtNodes;
using namespace std;
class SketchLineNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<PointNodeData> first_data;
std::weak_ptr<PointNodeData> second_data;
std::shared_ptr<ShapeNodeData> output_shape;
gp_Pnt pnt1;
gp_Pnt pnt2;

public:
SketchLineNode(){

}
 unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 2;
        }
        case PortType::Out:{
            return 1;
        }
       
    }
    return 0;
 }
 QString caption() const override{
    return tr("SketchLine Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return  PointNodeData(tr("Start Point")).type();
                 case 1:
                   return  PointNodeData(tr("End Point")).type();
                
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("Output Shape")).type();
             }
        }
        
    }
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data.get()){ //analogous to data.ptr, such that ptr is apointer
        return;
    }
    
   
   
    switch(portIndex){
        case 0:{
          first_data=std::dynamic_pointer_cast<PointNodeData>(data);
            if(first_data.lock()){
            pnt1=first_data.lock()->ToPnt();
            }
            break;
        }
        case 1:{
            second_data=std::dynamic_pointer_cast<PointNodeData>(data);
            if(second_data.lock()){
            pnt2=second_data.lock()->ToPnt();
            }
            std::cout<<"Second Data set"<<std::endl;
            break;
        }
       
        default:
          break;
    }
    if(output_shape.get()){
        output_shape->SetData(DrawLine(pnt1,pnt2));
    }
    else{
        output_shape=std::make_shared<ShapeNodeData>(tr(""));
         output_shape->SetData(DrawLine(pnt1,pnt2));
    }
     emit dataUpdated(0);
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_shape.get()){
        return std::static_pointer_cast<NodeData>(output_shape);
    }
  std::shared_ptr<NodeData> m_ptr;
  return m_ptr;
}
QWidget* embeddedWidget() override{return nullptr;}
};















