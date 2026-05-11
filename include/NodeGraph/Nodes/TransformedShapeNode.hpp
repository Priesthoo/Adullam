#pragma once
//it accepts a shape and a transform
#include<ShapeNodeData.hpp>
#include<memory>
#include<TransformNodeData.hpp>
#include<NodeInitializer.hpp>
using namespace std;
class TransformedShapeNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<ShapeNodeData> inputShape;
std::weak_ptr<TransformNodeData> inputTransform;
std::shared_ptr<ShapeNodeData> outputShape;
TopoDS_Shape shape;
  gp_Trsf trans;

public:
TransformedShapeNode(){

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
    return tr("Transformed Shape");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                    return ShapeNodeData(tr("InputShape")).type();
                case 1:
                   return TransformNodeData(tr("Transform")).type();
                
               
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("OutputShape")).type();
               
             }
        }
        
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
   if(outputShape){
    return static_pointer_cast<NodeData>(outputShape);
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
   inputShape=dynamic_pointer_cast<ShapeNodeData>(data);
   if(inputShape.lock()){
     shape=inputShape.lock()->Data();

   }
     break;
    }
  case 1:{
    inputTransform=dynamic_pointer_cast<TransformNodeData>(data);
    if(inputTransform.lock()){
        trans=inputTransform.lock()->Data();
    }
    break;
  }
 default:
    break;
  }
 if(outputShape){
    if(!shape.IsSame(TopoDS_Shape())){
    gp_GTrsf gtrans(trans);
    BRepBuilderAPI_GTransform transf(shape,gtrans);
    if(transf.IsDone()){
        outputShape->SetData(transf.Shape());
        emit dataUpdated(0);
      
    }
    }
 }
 else{
    outputShape=make_shared<ShapeNodeData>();
    if(!shape.IsSame(TopoDS_Shape())){
    gp_GTrsf gtrans(trans);
    BRepBuilderAPI_GTransform transf(shape,gtrans);
    
    if(transf.IsDone()){
        outputShape->SetData(transf.Shape());
        emit dataUpdated(0);

    }
    }
 }
  return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}

};