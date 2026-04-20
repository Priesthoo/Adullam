#pragma once
#include<NodeDelegateModel>
#include<memory>
#include<NodeInitializer.hpp>
#include<FloatNodeData.hpp> //for scale factor
#include<PointNodeData.hpp>
#include<TransformNodeData.hpp>  //for the output value

using namespace std;
using namespace QtNodes;
//advise scale and rotate in object space, then translate to world space....
class ScaleNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<FloatNodeData> inputScale;
std::weak_ptr<PointNodeData> inputPoint;
gp_Pnt outputPoint;
float ScaleFactor=1.0f;  //by default, we use 1.0f,

std::shared_ptr<TransformNodeData> outputTransform;
public:
ScaleNode(){

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
    return tr("Transform_Scale");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return  FloatNodeData(0.0,tr("Scale Factor")).type();
                case 1:
                   return PointNodeData(tr("Position")).type();
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
            inputScale=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(inputScale.lock()){
               ScaleFactor=inputScale.lock()->Data();
            }
        break;
        }
        case 1:{
            inputPoint=std::dynamic_pointer_cast<PointNodeData>(data);
            if(inputPoint.lock()){
                outputPoint=inputPoint.lock()->ToPnt();
            }
            break;
        }
        
        default:
          break;
    }
    if(ScaleFactor<=0.0f){
      ScaleFactor=0.1f;
    }
    if(!outputTransform){
        outputTransform=make_shared<TransformNodeData>(tr(""));
        gp_Trsf output;
       
        output.SetScale(outputPoint,ScaleFactor);
        outputTransform->SetData(output);

    }
    else{
       gp_Trsf output;
       
       output.SetScale(outputPoint,ScaleFactor);
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