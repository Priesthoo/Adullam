#ifndef PRIMITIVECUBENODE_HPP
#define PRIMITIVECUBENODE_HPP
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<FloatNodeData.hpp>
#include<DirectionNodeData.hpp>
#include<AxisNodeData.hpp>
#include<NodeDescription.hpp>
#include<BRepPrimAPI_MakeBox.hxx>
#include<memory>

#include<iostream>
//For a cube,there are different ways to construct a cube
using QtNodes::NodeDelegateModel;
using namespace std;
class PrimitiveCuboidNode:public NodeDelegateModel,public NodeInitializer{
private:

std::weak_ptr<AxisNodeData> axis_input;
std::weak_ptr<FloatNodeData> dx_input;
std::weak_ptr<FloatNodeData> dy_input;
std::weak_ptr<FloatNodeData> dz_input;


std::shared_ptr<ShapeNodeData> output_shape;
float _dx=25.0f;
float _dy=25.0f;
float _dz=25.0f;
 gp_Ax2 axis;
public:

PrimitiveCuboidNode(){
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
            return  4;
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
    return tr("Primitive Cuboid");
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
                   return  FloatNodeData(0.0,tr("dx")).type();
                case 2:
                   return FloatNodeData(0.0,tr("dy")).type();
                case 3:
                   return FloatNodeData(0.0,tr("dz")).type();
                
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
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_shape.get()){
        return std::static_pointer_cast<NodeData>(output_shape);
    }
   //if Output Shape is nullptr,set  dx,dy, and dz to default values
   output_shape=std::make_shared<ShapeNodeData>(tr(""));
   output_shape->SetData(BRepPrimAPI_MakeBox(axis,_dx,_dy,_dz).Shape());
   
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
            dx_input=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(dx_input.lock()){
               _dx=dx_input.lock()->Data();
            }
           
            std::cout<<"Second Data set"<<std::endl;
            break;
        }
        case 2:{
            dy_input=std::dynamic_pointer_cast<FloatNodeData>(data);
           if(dy_input.lock()){
           _dy=dy_input.lock()->Data();
           }
           std::cout<<"Third Data set"<<std::endl; 
           break; 
        }
        case 3:{
            dz_input=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(dz_input.lock()){
            _dz=dz_input.lock()->Data();
            }
             std::cout<<"Fourth Data set"<<std::endl;
            break;
        }
        
        default:
          break;
    }
    if(output_shape.get()){
        output_shape->SetData(BRepPrimAPI_MakeBox(axis,_dx,_dy,_dz).Shape());
    }
    else{
        output_shape=make_shared<ShapeNodeData>(tr(""));
        output_shape->SetData(BRepPrimAPI_MakeBox(axis,_dx,_dy,_dz).Shape());

    }
     emit dataUpdated(0);
    return;
}
QWidget* embeddedWidget() override{return nullptr;}

};







#endif