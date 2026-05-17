#pragma once 
#include<NodeDelegateModel>
#include<NodeInitializer.hpp>
#include<BRepFilletAPI_MakeChamfer.hxx>
#include<Standard_Failure.hxx>
#include<FloatNodeData.hpp>
#include<ShapeNodeData.hpp>
#include<EdgeNodeData.hpp>
#include<InfoUtility.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace INFO;
class ClassOneChamferNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<ShapeNodeData> inputShape;
std::weak_ptr<FloatNodeData> inputValue;
std::weak_ptr<EdgeNodeData> inputEdge;
std::shared_ptr<ShapeNodeData> outputShape;
TopoDS_Shape Shape;
TopoDS_Edge Edge;
float Value=1.0f;
bool portASet=false;
bool portBSet=false;
bool portCSet=false;
public:
ClassOneChamferNode(){
    return;
}
virtual void SetToFalse() override{
  portASet=false;
  portBSet=false;
  portCSet=false;
  return;
}
QString caption()const override{
    return tr("Chamfer One Node");
}
QString name() const override{
    return caption();
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  3;
        }
        case PortType::Out:{
            return 1;
        }
        default:
         break;
    }
    return 0;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                    return ShapeNodeData(tr("Input Shape")).type();
                case 1:
                     return FloatNodeData(tr("Distance")).type();
                case 2:
                    return EdgeNodeData(tr("Input Edge")).type();
                
                
            }
        }
       case PortType::Out:{
             if(portIndex==0){
                return ShapeNodeData(tr("Output Shape")).type();
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
      inputShape=std::dynamic_pointer_cast<ShapeNodeData>(data);
      if(inputShape.lock()){
        portASet=true;
        Shape=inputShape.lock()->Data();
      }
      break;
    }
    case 1:{
        inputValue=std::dynamic_pointer_cast<FloatNodeData>(data);
        if(inputValue.lock()){
            portBSet=true;
            Value=inputValue.lock()->Data();
        }
        break;
    }
    case 2:{
        inputEdge=std::dynamic_pointer_cast<EdgeNodeData>(data);
        if(inputEdge.lock()){
            portCSet=true;
            Edge=inputEdge.lock()->edge();
        }
        break;
    }
    default:
      break;

  }
  if(outputShape){
    if(Shape.IsSame(TopoDS_Shape())){
      LoadMessage(tr(""),tr("The Input Parameter Shape or Input Parameter Edge of Chamfer One Node is empty"));
      return;
    }
    if(Edge.IsSame(TopoDS_Edge())){
        LoadMessage(tr(""),tr("The Input Edge Is Not Set"));
        return;
    }
   if(portASet==false){
        return;
   }
   if(portBSet==false){
     return;
   }
   if(portCSet==false){
    return;
   }
    BRepFilletAPI_MakeChamfer chamferMaker(Shape);
    try{
    chamferMaker.Add(Value,Edge);
    chamferMaker.Build();
    }
    catch(const Standard_Failure& failure){
        LoadMessage(tr(""),tr("Incomplete Build"));
        return;
    }
    if(chamferMaker.IsDone()){
        outputShape->SetData(chamferMaker.Shape());
    }
    else{
        LoadMessage(tr(""),tr("Failed To Add Chamfer To Shape"));
        return;
    }
  }
  else{
    outputShape=std::make_shared<ShapeNodeData>();
    if(Shape.IsSame(TopoDS_Shape())){
      LoadMessage(tr(""),tr("The Input Parameter Shape or Input Parameter Edge of Chamfer One Node is empty"));
      return;
    }
    if(Edge.IsSame(TopoDS_Edge())){
        LoadMessage(tr(""),tr("The Input Edge Is Not Set"));
        return;
    }
   if(portASet==false){
        return;
   }
   if(portBSet==false){
     return;
   }
   if(portCSet==false){
    return;
   }
    BRepFilletAPI_MakeChamfer chamferMaker(Shape);
    try{
    chamferMaker.Add(Value,Edge);
    chamferMaker.Build();
    }
    catch(const Standard_Failure& failure){
        LoadMessage(tr(""),tr("Incomplete Build"));
        return;
    }
    if(chamferMaker.IsDone()){
        outputShape->SetData(chamferMaker.Shape());
    }
     else{
        LoadMessage(tr(""),tr("Failed To Add Chamfer To Shape"));
        return;
    }
  }
  emit dataUpdated(0);
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputShape){
        return static_pointer_cast<NodeData>(outputShape);
    }
    shared_ptr<NodeData> mptr;
    return mptr;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};

class ClassTwoChamferNode;