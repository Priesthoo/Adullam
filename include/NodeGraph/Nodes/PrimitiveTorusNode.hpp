#pragma once
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<FloatNodeData.hpp>
#include<AxisNodeData.hpp>
#include<memory>
#include<ShapeUtil.hpp>

using namespace std;
using namespace QtNodes;



class PrimitiveTorusNode:public NodeDelegateModel,public NodeInitializer{
private:
weak_ptr<AxisNodeData> axis_input;
weak_ptr<FloatNodeData> r1_input;
weak_ptr<FloatNodeData> r2_input;
std::shared_ptr<ShapeNodeData> output_shape;
gp_Ax2 axis;
float radius_1=1.0f;
float radius_2=1.0f;


public:
PrimitiveTorusNode(){
    axis.SetDirection(gp_Dir(1.0,0.0,0.0));
    return;
}

unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  3;
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
    return tr("Primitive Torus");
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
                   return  FloatNodeData(0.0,tr("R1")).type();
                case 2:
                    return  FloatNodeData(0.0,tr("R2")).type();
                
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("OutputShape")).type();
             }
        }
        
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_shape.get()){
         output_shape->SetData(DrawTorus(radius_1,radius_2,axis)); 
        return std::static_pointer_cast<NodeData>(output_shape);
    }
   //if Output Shape is nullptr,set  dx,dy, and dz to default values
   output_shape=std::make_shared<ShapeNodeData>(tr(""));
   output_shape->SetData(DrawTorus(radius_1,radius_2,axis));
   
   return static_pointer_cast<NodeData>(output_shape);

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
            r1_input=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(r1_input.lock()){
            radius_1=r1_input.lock()->Data();
            }
            std::cout<<"Second Data set"<<std::endl;
            break;
        }
        case 2:{
            r2_input=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(r2_input.lock()){
            radius_2=r2_input.lock()->Data();
            }
            std::cout<<"Third Data set"<<std::endl;
            break;
        }

        
        default:
          break;
    }

    if(output_shape.get()){
            output_shape->SetData(DrawTorus(radius_1,radius_2,axis));
            emit dataUpdated(0);
        }
        else{
            output_shape=make_shared<ShapeNodeData>(tr(""));
             output_shape->SetData(DrawTorus(radius_1,radius_2,axis));
             emit dataUpdated(0);
        }
    return;
}
QWidget* embeddedWidget() override{return nullptr;}


};