#pragma once 
#include<NodeDelegateModel>
#include<AxisNodeData.hpp>
#include<memory>
#include<NodeInitializer.hpp>
#include<FloatNodeData.hpp>
#include<TransformNodeData.hpp>

using namespace QtNodes;
using namespace std;
const float _PI=3.141592654;
class RotationNode:public NodeDelegateModel,public NodeInitializer {
private:
std::weak_ptr<AxisNodeData> inputAxis;
std::weak_ptr<FloatNodeData>inputAngle;
gp_Ax2 axis;
float angle;
std::shared_ptr<TransformNodeData> outputTransform;
public:
RotationNode(){

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
    return tr("Transform_Rotation");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                    return AxisNodeData(1.0,0.0,0.0,1.0,0.0,0.0,QString("Axis Of Rotation")).type();
                case 1:
                   return  FloatNodeData(0.0,tr("Angle")).type();
                
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return TransformNodeData(tr("Output Transform")).type();
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

            inputAxis=std::dynamic_pointer_cast<AxisNodeData>(data);
            if(inputAxis.lock()){
              axis=inputAxis.lock()->Data();
            }
            
            
            break;
        }
        case 1:{
            inputAngle=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(inputAngle.lock()){
               angle=inputAngle.lock()->Data();
            }
           
           
            break;
        }
        
        
        default:
          break;
    }
    if(angle>=360.0f){
       angle=359.0;
    }
    if(angle<=-360.0f){
        angle=-359.0f;
    }
    if(!outputTransform){
        outputTransform=make_shared<TransformNodeData>(tr(""));
        gp_Trsf output;
        angle=(_PI*angle)/180.0f; //convert angle to randians
        output.SetRotation(axis.Axis(),angle);
        outputTransform->SetData(output);

    }
    else{
       gp_Trsf output;
        angle=(_PI*angle)/180.0f; //convert angle to randians
        output.SetRotation(axis.Axis(),angle);
        outputTransform->SetData(output);
 
    }
     emit dataUpdated(0);
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputTransform){
        return std::static_pointer_cast<NodeData>(outputTransform);
    }
   //if Output Shape is nullptr,set  dx,dy, and dz to default values
 
   std::shared_ptr<NodeData> outData;
   return static_pointer_cast<NodeData>(outData);

}
QWidget* embeddedWidget() override{return nullptr;}
};