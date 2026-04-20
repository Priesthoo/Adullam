//This will be used to display multiple objects in the scene..
#pragma once
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<MyCustomAIS_Shape.hxx>
#include<memory>
#include<VectorDataNodeData.hpp>
#include<ShapeNodeData.hpp>
using QtNodes::NodeDelegateModel;
using namespace std;
class MultipleOutputNode:public NodeDelegateModel,public NodeInitializer{
    private:
    Q_OBJECT
    std::weak_ptr<VectorDataNode<ShapeNodeData>> input_shape;
    public:
    MultipleOutputNode(){

    }
      unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 1;  
        }
    }
    return 0;
      }
   QString caption() const override{
    return tr("Multiple Output Node");
}
 QString name() const override{
    return caption();
} 
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return VectorDataNode<ShapeNodeData>(tr("Vector"),tr("VectorOfShape")).type();
            }
        }
    }
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data.get()){
        return;
    }
    input_shape=dynamic_pointer_cast<VectorDataNode<ShapeNodeData>>(data);
    if(input_shape.lock().get()){

    Handle(CustomAIS_Shape) customShape;

    std::vector<Handle(CustomAIS_Shape)> shapes{};
    shapes.reserve(input_shape.lock()->Size()+1); //to avoid reallocation
    for(int i=0;i<input_shape.lock()->Size();i++){
        customShape=new CustomAIS_Shape(input_shape.lock()->Data()[i].Data());
        if(input_shape.lock()->Data()[i].HasMaterial()){
            customShape->SetMaterialAspect(input_shape.lock()->Data()[i].aspect());
            customShape->SetColor(input_shape.lock()->Data()[i].aspect().DiffuseColor());
        }
        else{
            customShape->SetVisualAspect(input_shape.lock()->Data()[i].aspect().DiffuseColor());

        }

        shapes.push_back(customShape);
    }
    emit OnSendShapes(shapes);
    
    }
   return; 
}
std::shared_ptr<NodeData> outData(PortIndex const port){
    std::shared_ptr<NodeData> ptr;
    return ptr;
}

QWidget* embeddedWidget () override{
    return nullptr;
}
signals:
void OnSendShapes(const std::vector<Handle(CustomAIS_Shape)>& shapes);
};
