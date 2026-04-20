#pragma once 
#include<PointNodeData.hpp>
#include<NodeInitializer.hpp>
#include<TransformNodeData.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
class TranslateNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<PointNodeData> inputPoint;
std::shared_ptr<TransformNodeData> outputTransform;
gp_Pnt outputPoint;

public:
TranslateNode(){

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  1;
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
    return tr("Transform_Translate");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return  PointNodeData(tr("Position")).type();
                
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
            inputPoint=std::dynamic_pointer_cast<PointNodeData>(data);
            if(inputPoint.lock()){
               outputPoint=inputPoint.lock()->ToPnt();
            }
        break;
        }
        
        
        default:
          break;
    }
    
    if(!outputTransform){
        outputTransform=make_shared<TransformNodeData>(tr(""));
        gp_Trsf output;
       
        output.SetTranslation(gp_Pnt(0.0,0.0,0.0),outputPoint);
        outputTransform->SetData(output);

    }
    else{
       gp_Trsf output;
       
       output.SetTranslation(gp_Pnt(0.0,0.0,0.0),outputPoint);
        outputTransform->SetData(output);
 
    }
     emit dataUpdated(0);
    return;
}

std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputTransform){
        return std::static_pointer_cast<NodeData>(outputTransform);
    }
 
   std::shared_ptr<NodeData> outData;
   return static_pointer_cast<NodeData>(outData);

}
QWidget* embeddedWidget() override{return nullptr;}


};