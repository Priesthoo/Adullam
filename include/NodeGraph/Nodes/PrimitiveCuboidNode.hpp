#pragma once 
#include<ShapeUtil.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<AxisNodeData.hpp>
#include<FloatNodeData.hpp>
#include<memory>
using namespace QtNodes;
using namespace Shape_Utility;
class PrimitiveCubeNode:public NodeDelegateModel,public NodeInitializer{
  private:
  std::weak_ptr<AxisNodeData> axis_input;
  std::weak_ptr<FloatNodeData> Input_data;
  std::shared_ptr<ShapeNodeData> output_shape;
  float InputValue=15.0f; //default value
   gp_Ax2 axis;
  public:
  PrimitiveCubeNode(){
       axis.SetDirection(gp_Dir(1.0,0.0,0.0));
  }
  TopoDS_Shape Shape() const{  //we didn't bother checking for null pointer
    if(output_shape.get()){
    return output_shape->Data();
    }
    return TopoDS_Shape();
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
    return tr("Primitive Cube");
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
                   return  FloatNodeData(0.0,tr("Input Value")).type();
                 
                
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("TopoShape")).type();
             }
        }
        
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_shape.get()){
         output_shape->SetData(DrawCube(InputValue,axis)); 
        return std::static_pointer_cast<NodeData>(output_shape);
    }
   //if Output Shape is nullptr,set  dx,dy, and dz to default values
   output_shape=std::make_shared<ShapeNodeData>(tr(""));
   output_shape->SetData(DrawCube(InputValue,axis));
   
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
            Input_data=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(Input_data.lock()){
            InputValue=Input_data.lock()->Data();
            }
            std::cout<<"Second Data set"<<std::endl;
            break;
        }
        
        
        default:
          break;
    }
    if(axis_input.lock().get() && Input_data.lock().get()){  //when all data is set
        if(output_shape.get()){
            output_shape->SetData(DrawCube(InputValue,axis));
              emit dataUpdated(0);
            std::cout<<"Output Shape"<<std::endl;
            return;
        }
        std::cout<<"All input values are set"<<std::endl;
        output_shape=std::make_shared<ShapeNodeData>(tr(""));
        output_shape->SetData(DrawCube(InputValue,axis));

        emit dataUpdated(0);
        return;
    }
    else{   //when all the data is not set
        if(output_shape.get()){
            output_shape->SetData(DrawCube(InputValue,axis));
           std::cout<<"It worked"<<std::endl;
             emit dataUpdated(0);
           return;
        }
        output_shape=std::make_shared<ShapeNodeData>(tr(""));
        std::cout<<"Shape Is Set"<<std::endl;
        output_shape->SetData(DrawCube(InputValue,axis));
        emit dataUpdated(0);
        return; 
    } 
    return;
}
QWidget* embeddedWidget() override{return nullptr;}

};