#pragma once 
#include<NodeDelegateModel>
#include<memory>
#include<ShapeUtil.hpp>
#include<NodeInitializer.hpp>
/*




*/
using namespace std;
using namespace QtNodes;

class PrimitiveCylinderNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<AxisNodeData> axisInput;
std::weak_ptr<FloatNodeData> b_rInput;
std::weak_ptr<FloatNodeData> h_input;
float bottomRadius=3.0f; //default value;
float height=12.0f;// default height
gp_Ax2 axis;
std::shared_ptr<ShapeNodeData> outputShape;



public:
PrimitiveCylinderNode(){
    axis.SetDirection(gp_Dir(1.0,0.0,0.0));
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
    return 0;
}
QString caption() const override{
    return tr("Primitive Cylinder");
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
   if(!data){
    return;
   }
   //0: axis input.
   //1: height data.
   //2: radius data.
  switch(portIndex){
    case 0:{
        axisInput=std::dynamic_pointer_cast<AxisNodeData>(data);
        if(axisInput.lock()){
            axis=axisInput.lock()->Data();
        }
        break;
    }
    case 1:{
        h_input=std::dynamic_pointer_cast<FloatNodeData>(data);
        if(h_input.lock()){
            height=h_input.lock()->Data();
        }
        break;
    }
    case 2:{
        b_rInput=std::dynamic_pointer_cast<FloatNodeData>(data);
        if(b_rInput.lock()){
            bottomRadius=b_rInput.lock()->Data();
        }
        break;
    }
  default:
   break;
  }
   if(outputShape){
    outputShape->SetData(DrawCylinder(bottomRadius,height,axis));
    
   }
   else{
    outputShape=std::make_shared<ShapeNodeData>();
      outputShape->SetData(DrawCylinder(bottomRadius,height,axis));
   }
   emit dataUpdated(0);

return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
 if(outputShape){
    return std::static_pointer_cast<NodeData>(outputShape);
 }
 std::shared_ptr<NodeData> mptr;
 return mptr;
}
QWidget* embeddedWidget() override{return nullptr;}


};