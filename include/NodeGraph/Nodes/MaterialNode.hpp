#ifndef MATERIAL_NODE_HPP
#define MATERIAL_NODE_HPP
#include<MaterialNodeData.hpp>
#include<FloatNodeData.hpp>
#include<NodeDelegateModel>
#include<ColorNodeData.hpp>
#include<NodeInitializer.hpp>
//DiffuseColor,SpecularColor,Diffuse Color,
/*








*/
class MaterialNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<ColorNodeData> diffuseColor;
std::weak_ptr<ColorNodeData> specularColor;
std::weak_ptr<ColorNodeData> emissiveColor;
std::weak_ptr<ColorNodeData> ambientColor;
std::weak_ptr<FloatNodeData> refractValue;
std::weak_ptr<FloatNodeData> Transparency;
std::weak_ptr<FloatNodeData> shineValue;
std::shared_ptr<MaterialNodeData> outputMaterial;

public:
MaterialNode(){
  outputMaterial=std::make_shared<MaterialNodeData>(tr(""));

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  7;
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
    return tr("Material Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
     switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                return ColorNodeData(tr("Diffuse Color")).type(); 
                case 1:
                 return ColorNodeData(tr("Specular Color")).type(); 
                case 2:
                  return ColorNodeData(tr("Emissive Color")).type(); 
                case 3:
                  return ColorNodeData(tr("Ambient Color")).type(); 
                case 4:
                  return FloatNodeData(tr("Shine Coefficent")).type();
                case 5:
                   return FloatNodeData(tr("Transparency")).type(); 
                case 6:
                   return FloatNodeData(tr("Refractive Index")).type(); 
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                  return MaterialNodeData(tr("Output Material")).type();
             }
        }
        
    }
    
    
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
   if(outputMaterial){
     return static_pointer_cast<NodeData>(outputMaterial);
   }
   std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
  if(!data){
    return;
  }
  switch(portIndex){
    case 0:{
        diffuseColor=std::dynamic_pointer_cast<ColorNodeData>(data);
        if(diffuseColor.lock()){
          outputMaterial->SetDiffuse(diffuseColor.lock()->Data());

        }
        break;
    }
    case 1:{
        specularColor=std::dynamic_pointer_cast<ColorNodeData>(data);
        if(specularColor.lock()){
            outputMaterial->SetSpecular(specularColor.lock()->Data()); 
        }
        break;
    }
    case 2:{
        emissiveColor=std::dynamic_pointer_cast<ColorNodeData>(data);
        if(emissiveColor.lock()){
            outputMaterial->SetEmissive(emissiveColor.lock()->Data());

        }
        break;
    }
  case 3:{
      ambientColor=std::dynamic_pointer_cast<ColorNodeData>(data);
      if(ambientColor.lock()){
         outputMaterial->SetAmbient(ambientColor.lock()->Data());
      }
      break;
  }
  case 4:{
      shineValue=std::dynamic_pointer_cast<FloatNodeData>(data);
      if(shineValue.lock()){
        outputMaterial->SetShine(shineValue.lock()->Data());

      }
      break;
  }
 case 5:{
     Transparency=std::dynamic_pointer_cast<FloatNodeData>(data);
      if(Transparency.lock()){
        auto value=Transparency.lock()->Data();
        if(value>=0.0 && value<=1.0){
        outputMaterial->SetTransValue(Transparency.lock()->Data());
        }
      }
      break;
 }
 case 6:{
     refractValue=std::dynamic_pointer_cast<FloatNodeData>(data);
      if(refractValue.lock()){
        if(refractValue.lock()->Data()<=0.0){
             outputMaterial->SetRefractIndex(0.0);
        }
        else if(refractValue.lock()->Data()>0.0){
             outputMaterial->SetRefractIndex(1.0);
        }
        else{
        outputMaterial->SetRefractIndex(refractValue.lock()->Data());
        }
      }
      break;
 }
  }
  emit dataUpdated(0);
 return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};



















#endif