#ifndef RGBCOLOR_NODE_HPP
#define RGBCOLOR_NODE_HPP
#include<ColorNodeData.hpp>
#include<FixedColorPane.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<FloatNodeData.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
class RGBColorNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<FloatNodeData> RedInput;
std::weak_ptr<FloatNodeData> GreenInput;
std::weak_ptr<FloatNodeData> BlueInput;

std::shared_ptr<ColorNodeData> outputData;
std::unique_ptr<FixedColorPane> colorPane;
float Red=0.0;
float Green=0.0;
float Blue=0.0;




public:
RGBColorNode(){

}
void SetData(const Quantity_Color& color){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::Out:{
            return 1 ;  //number of output node
        }
        case PortType::In:{
            return 3;
        }
        default:
           break;
    }
    return 0;
}
QString caption() const override{
    return tr("RGBColor Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return FloatNodeData(1.0,tr("Red")).type();
                case 1:
                   return FloatNodeData(1.0,tr("Green")).type();
                case 2:
                   return FloatNodeData(1.0,tr("Blue")).type();
            }
            break;
        }
        
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return ColorNodeData(tr("Output Color")).type();
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
        RedInput=dynamic_pointer_cast<FloatNodeData>(data);
        if(RedInput.lock()){
            Red=RedInput.lock()->Data();
            
        }
        break;
        }
        case 1:{
        GreenInput=dynamic_pointer_cast<FloatNodeData>(data);
        if(GreenInput.lock()){
            Green=GreenInput.lock()->Data();
            
        }
        break;
        }
        case 2:{
        BlueInput=dynamic_pointer_cast<FloatNodeData>(data);
        if(BlueInput.lock()){
            Blue=BlueInput.lock()->Data();
            
        }
        break;
        }
        default:
          break;

    }
    if(Red>1.0){
        Red=1.0f;
    }
    if(Green>1.0){
        Green=1.0f;
    }
    if(Blue>1.0f){
        Blue=1.0f;
    }
     if(colorPane){
        colorPane->SetColorFromOC(Quantity_Color(Red,Green,Blue,Quantity_TOC_RGB));
        
     }
     emit dataUpdated(0);
     return;
   
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
   if(outputData){
     outputData->SetData(Quantity_Color(Red,Green,Blue,Quantity_TOC_RGB));
     return static_pointer_cast<NodeData>(outputData);
   }
   outputData=make_shared<ColorNodeData>(tr(""));
    outputData->SetData(Quantity_Color(Red,Green,Blue,Quantity_TOC_RGB));
    
    return std::static_pointer_cast<NodeData>(outputData);
}

QWidget* embeddedWidget() override{ 
    if(!colorPane){
       colorPane=make_unique<FixedColorPane>();

    }
    return colorPane.get();
 }


};




#endif 