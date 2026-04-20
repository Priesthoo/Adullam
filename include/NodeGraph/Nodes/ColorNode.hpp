#ifndef COLOR_NODE_HPP
#define COLOR_NODE_HPP
//This will contain a widget that will display the chosen color,
#include<ColorNodeData.hpp>
#include<FixedColorPane.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<memory>
//better for visualization;
using namespace std;
using namespace QtNodes;
class ColorNode:public NodeDelegateModel,public NodeInitializer{
private:
std::shared_ptr<ColorNodeData> outputData;
std::weak_ptr<ColorNodeData> inputData;
std::unique_ptr<FixedColorPane> colorPane;
Quantity_Color outputColor;


public:
ColorNode(){

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::Out:{
            return 1;  //number of output node
        }
        case PortType::In:{
            return 1;
        }
        default:
           break;
    }
    return 0;
}
QString caption() const override{
    return tr("Color Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return ColorNodeData(tr("Input Color")).type();
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
   if(!data){
    return;
   }
   switch(portIndex){
    case 0:{
       inputData=dynamic_pointer_cast<ColorNodeData>(data);
       if(inputData.lock()){
        outputColor=inputData.lock()->Data();
        std::cout<<"Color Data is Set"<<"\n";
        if(colorPane){
        colorPane->SetColorFromOC(outputColor);
        std::cout<<"Color Data is Set in Pane"<<"\n";
        }
      emit dataUpdated(0);
       }
       break;
    }
   }
   return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        outputData->SetData(outputColor);
        return std::static_pointer_cast<NodeData>(outputData);
    }
    outputData=make_shared<ColorNodeData>(tr(""));
    outputData->SetData(outputColor);
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