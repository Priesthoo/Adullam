#pragma once
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<FloatNodeData.hpp>
#include<AxisNodeData.hpp>
#include<memory>
#include<ShapeUtil.hpp>
#include<NodeInitializer.hpp>
using namespace std;
using namespace QtNodes;

class PrimitiveConeNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<AxisNodeData> axis_input;
std::weak_ptr<FloatNodeData> height_data;
std::weak_ptr<FloatNodeData> bottom_data;
std::weak_ptr<FloatNodeData> top_data;
std::shared_ptr<ShapeNodeData> output_shape;
gp_Ax2 axis;
float height=7.0;
float bottom=5.0;
float top=2.0;
public:
PrimitiveConeNode(){
     axis.SetDirection(gp_Dir(1.0,0.0,0.0));
}
 unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 4;
        }
        case PortType::Out:{
            return 1;
        }
       
    }
    return 0;
}
QString caption() const override{
    return tr("Primitive Cone");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                    return AxisNodeData(1.0,0.0,0.0,1.0,0.0,0.0,QString("Input_Axis")).type();
                case 1:
                   return  FloatNodeData(0.0,tr("Height")).type();
                case 2:
                   return FloatNodeData(0.0,tr("Bottom Radius")).type();
                case 3:
                   return FloatNodeData(0.0,tr("Top Radius")).type();
                
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
            
            std::cout<<"First Data set"<<std::endl;
            break;
        }
        case 1:{
            height_data=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(height_data.lock()){
            height=height_data.lock()->Data();
            }
            std::cout<<"Second Data set"<<std::endl;
            break;
        }
        case 2:{
            bottom_data=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(bottom_data.lock()){
            bottom=bottom_data.lock()->Data();
            }
            std::cout<<"Third Data set"<<std::endl;
            break;
        }
         case 3:{
            top_data=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(top_data.lock()){
            top=top_data.lock()->Data();
            }
            std::cout<<"Fourth Data set"<<std::endl;
            break;
        }
        default:
          break;
    }
    if(output_shape.get()){
        output_shape->SetData(DrawCone(bottom,top,height,axis));
    }
    else{
        output_shape=std::make_shared<ShapeNodeData>(tr(""));
        output_shape->SetData(DrawCone(bottom,top,height,axis));
    }
     emit dataUpdated(0);
    return;
}

std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_shape.get()){
        return std::static_pointer_cast<NodeData>(output_shape);
    }
   //if Output Shape is nullptr,set  dx,dy, and dz to default values
   output_shape=std::make_shared<ShapeNodeData>(tr(""));
   output_shape->SetData(DrawCone(bottom,top,height,axis));
   
   return static_pointer_cast<NodeData>(output_shape);

}

QWidget* embeddedWidget() override{return nullptr;}

};