#ifndef CONVERT_TO_AIS_SHAPE_NODE_HPP
#define CONVERT_TO_AIS_SHAPE_NODE_HPP
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<AIS_ShapeNodeData.hpp>
#include<ShapeNodeData.hpp>
#include<NodeDescription.hpp>

#include<memory>
#include<iostream>
using QtNodes::NodeDelegateModel;
using namespace std;
class ConvertToAIS_ShapeNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<ShapeNodeData> m_inputdata;
std::shared_ptr<AIS_ShapeNodeData> m_outdata;
Handle(CustomAIS_Shape) outputShape;

public:
ConvertToAIS_ShapeNode(){

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 1;
        }
        case PortType::Out:{
            return 1;
        }
        default:
          return 0;
    }
    return 0;
}
QString caption() const override{
    return tr("ConvertToAIS_ShapeNode");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
            case 0:
              return ShapeNodeData(tr("TopoShape")).type();
        }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:
              return AIS_ShapeNodeData(tr("AIS_Shape")).type();
        }
        }
        default:
          break;
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(m_outdata.get()){
        m_outdata->SetData(outputShape);
      return std::static_pointer_cast<NodeData>(m_outdata);
}
   m_outdata=std::make_shared<AIS_ShapeNodeData>(tr("AIS_Shape"));
     m_outdata->SetData(outputShape);
    return std::static_pointer_cast<NodeData>(m_outdata);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    //Since we have only one input
    if(!data.get()){ //data.ptr;
       return;
    }
    auto input=std::dynamic_pointer_cast<ShapeNodeData>(data);

    if(portIndex==0){
        m_inputdata=input;
        m_outdata=std::make_shared<AIS_ShapeNodeData>(tr("AIS_Shape"));
        if(m_inputdata.lock()){
        outputShape=new CustomAIS_Shape(m_inputdata.lock()->Data());
        if(m_inputdata.lock()->HasMaterial()){
            outputShape->SetMaterialAspect(m_inputdata.lock()->aspect());
            outputShape->SetColor(m_inputdata.lock()->aspect().DiffuseColor());  //same as SetVisualAspect
        }
        else{
            outputShape->SetVisualAspect(m_inputdata.lock()->aspect().DiffuseColor()); //we use the diffuse 
        }
        }     
        emit dataUpdated(0);                                                              
    }
    return;
}
QWidget* embeddedWidget() override{ return nullptr;}

};

 







#endif 