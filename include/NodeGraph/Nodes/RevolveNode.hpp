#pragma once 

#include<NodeDelegateModel>
#include<AxisNodeData.hpp>
#include<ShapeUtil.hpp>
#include<FloatNodeData.hpp>
#include<memory>
#include<InfoUtility.hpp>
#include<ShapeNodeData.hpp>
using namespace std;
using namespace QtNodes;
const float C_PI=3.141592654;
using namespace Shape_Utility;

using namespace INFO;
class RevolveNode:public NodeDelegateModel{
 private:
 std::weak_ptr<ShapeNodeData> shape_input;
 std::weak_ptr<AxisNodeData> axis_input;
 std::weak_ptr<FloatNodeData> float_input;
 std::shared_ptr<ShapeNodeData> outputShape;
 QString Error;
 gp_Ax2 axis;
 TopoDS_Shape inputShape;
 double value=80.0f;
 public:
 RevolveNode(){
    axis.SetDirection(gp_Dir(1.0,0.0,0.0)); //by default,along the x-axis
    return;
 }
 unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 3;
        }
        case PortType::Out:{
            return 1;
        }
       
    }
 }
QString caption() const override{
    return tr("Revolve Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Input Shape")).type();
                case 1:
                    return AxisNodeData(1.0,0.0,0.0,1.0,0.0,0.0,QString("Input_Axis")).type();
                case 2:
                   return  FloatNodeData(0.0,tr("Angle")).type();
               
                
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
    if(!data.get()){ //analogous to data.ptr, such that ptr is a pointer
        return;
    }
    switch(portIndex){
        case 0:{
            shape_input=dynamic_pointer_cast<ShapeNodeData>(data);
            if(shape_input.lock()){
                inputShape=shape_input.lock()->Data();
            }
            break;
        }
        case 1:{
            axis_input=dynamic_pointer_cast<AxisNodeData>(data);
            if(axis_input.lock()){
                axis=axis_input.lock()->Data();
            }
            break;
        }
        case 2:{
            float_input=dynamic_pointer_cast<FloatNodeData>(data);
            if(float_input.lock()){
                value=float_input.lock()->Data();
                 if(value>=360.0f){
                     value=359.0;
                      }
                 if(value<=-360.0f){
                   value=-359.0f;
                  }
            }
            break;
        }
        
    }
    if(outputShape){
        
        value=(C_PI*value)/180.0f; //convert to radian
        TopoDS_Shape sh=Revolve(inputShape,axis,value,Error);
        if(sh.IsSame(TopoDS_Shape())){
            LoadMessage(tr("Shape Error"),tr("It is an Empty Shape"));
            return;
        }
        LoadMessage(tr("Shape Output"),Error);
        outputShape->SetData(sh);
    }
    else{
       outputShape=make_shared<ShapeNodeData>(tr(""));
       value=(C_PI*value)/180.0f; //convert to radian
        TopoDS_Shape sh=Revolve(inputShape,axis,value,Error);
        if(sh.IsSame(TopoDS_Shape())){
            LoadMessage(tr("Shape Error"),tr("It is an Empty Shape"));
            return;
        }
        LoadMessage(tr("Shape Output"),Error);
       outputShape->SetData(sh);
    }
    emit dataUpdated(0);
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(outputShape){
    return std::static_pointer_cast<NodeData>(outputShape);
  }
   outputShape=make_shared<ShapeNodeData>(tr(""));
  TopoDS_Shape sh=Revolve(inputShape,axis,value,Error);
    if(sh.IsSame(TopoDS_Shape())){
        LoadMessage(tr("Shape Error"),tr("It is an Empty Shape"));
        std::shared_ptr<NodeData> ptr;
        return ptr;
    }
        LoadMessage(tr("Shape Output"),Error);
       outputShape->SetData(sh);
  return std::static_pointer_cast<NodeData>(outputShape);
}

QWidget* embeddedWidget() override{return nullptr;}

 
};