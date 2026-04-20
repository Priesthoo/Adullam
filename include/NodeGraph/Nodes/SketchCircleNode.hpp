#pragma once
#include<NodeDelegateModel>
#include<ShapeUtil.hpp>
#include<NodeInitializer.hpp>
#include<AxisNodeData.hpp>
#include<FloatNodeData.hpp>
#include<ShapeNodeData.hpp>
#include<memory>
using namespace Shape_Utility;
using namespace QtNodes;
using namespace std;

class SketchCircleNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<AxisNodeData> axis_input;
std::weak_ptr<FloatNodeData> float_data;
std::shared_ptr<ShapeNodeData> output_shape;
gp_Ax2 axis;
float rinput;

public:
SketchCircleNode(){
   axis.SetDirection(gp_Dir(1.0,0.0,0.0)); //drawn on the y and z plane
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
    return tr("Sketch Circle Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return  AxisNodeData(tr("Input Axis")).type();
                 case 1:
                   return  FloatNodeData(tr("Radius")).type();
                
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
          axis_input=std::dynamic_pointer_cast<AxisNodeData>(data);
            if(axis_input.lock()){
            axis=axis_input.lock()->Data();
            }
            break;
        }
        case 1:{
            float_data=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(float_data.lock()){
            rinput=float_data.lock()->Data();
            }
            std::cout<<"Second Data set"<<std::endl;
            break;
        }
       
        default:
          break;
    }
    if(rinput<0.0){
        rinput=1.0;
    }
    if(output_shape.get()){
        output_shape->SetData(DrawCircle(axis,rinput));
    }
    else{
        output_shape=std::make_shared<ShapeNodeData>(tr(""));
          output_shape->SetData(DrawCircle(axis,rinput));
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

















