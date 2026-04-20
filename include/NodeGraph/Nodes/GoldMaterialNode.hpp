#pragma once
#include<MaterialNodeData.hpp>
#include<NodeDelegateModel>
#include<NodeInitializer.hpp>
#include<memory>
using namespace QtNodes;
using namespace std;
class GoldMaterialNode:public NodeDelegateModel,public NodeInitializer{
   private:
   std::shared_ptr<MaterialNodeData> outputMaterial;

   public:
   GoldMaterialNode(){
    outputMaterial=make_shared<MaterialNodeData>(tr(""));
    outputMaterial->SetAmbient(Quantity_Color(0.24725,0.1995,0.0745,Quantity_TOC_sRGB));
    outputMaterial->SetDiffuse(Quantity_Color(0.75164,0.60648,0.22648,Quantity_TOC_sRGB));
    outputMaterial->SetSpecular(Quantity_Color(0.628281,0.555802,0.366065,Quantity_TOC_sRGB));
    outputMaterial->SetShine(0.4);
   }
  unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 0;
        }
        case PortType::Out:{
            return 1;
        }
       
    }
    return 0;
}
 QString caption() const override{
    return tr("Gold Material Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return MaterialNodeData(tr("Output")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(outputMaterial){
    return static_pointer_cast<NodeData>(outputMaterial);
  }
  shared_ptr<NodeData> mptr;
  return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};