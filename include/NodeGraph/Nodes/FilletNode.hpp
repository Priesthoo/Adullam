#ifndef FILLET_HPP
#define FILLET_HPP
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<NodeInitializer.hpp>
#include<IntegerNodeData.hpp>
#include<FloatNodeData.hpp>
#include<BRepFilletAPI_MakeFillet.hxx>
#include<Standard_Failure.hxx>
#include<iostream>
#include<memory>
#include<ChFi3d_FilletShape.hxx>
using namespace std;
using namespace QtNodes;

class ClassOneFilletNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<ShapeNodeData> inputShape;
std::weak_ptr<FloatNodeData> inputValue;
std::weak_ptr<EdgeNodeData> inputEdge;
std::weak_ptr<TemplatedData<ChFi3d_FilletShape>> chData;
std::shared_ptr<ShapeNodeData> outputShape;
TopoDS_Shape Shape=TopoDS_Shape();
TopoDS_Edge Edge=TopoDS_Edge();
ChFi3d_FilletShape chType=ChFi3d_Rational;
float Value=1.0f;
bool portASet=false;
bool portBSet=false;
bool portCSet=false;
 
public:
ClassOneFilletNode(){
    return;
}
QString caption()const override{
    return tr("Fillet One Node");
}
virtual void SetToFalse() override{
portASet=false;
portBSet=false;
portCSet=false;
return;
}
QString name() const override{
    return caption();
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  4;
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
                     return FloatNodeData(tr("Radius")).type();
                case 2:
                    return EdgeNodeData(tr("Input Edge")).type();
                
                case 3:{
                    return TemplatedData<ChFi3d_FilletShape>(tr("Fillet Type"),tr("Fillet Type")).type();
                }
                
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
     std::cout<<"Shape Data is Set"<<"\n";
      portASet=true;
        Shape=inputShape.lock()->Data();
      }
      break;
    }
    case 1:{
        inputValue=std::dynamic_pointer_cast<FloatNodeData>(data);
        if(inputValue.lock()){
            std::cout<<"Value Data Is Set"<<"\n";
            portBSet=true;
            Value=inputValue.lock()->Data();
        }
        break;
    }
    case 2:{
        inputEdge=std::dynamic_pointer_cast<EdgeNodeData>(data);
        if(inputEdge.lock()){
            std::cout<<"Edge Data is Set"<<"\n";
            portCSet=true;
            Edge=inputEdge.lock()->edge();

        }
        break;
    }
    case 3:{
         chData=std::dynamic_pointer_cast<TemplatedData<ChFi3d_FilletShape>>(data);
         if(chData.lock()){
            
            chType=chData.lock()->Data();
         }
         break;
    }
    default:
      break;

  }
  if(outputShape){
    if(Shape.IsSame(TopoDS_Shape())){
      LoadMessage(tr(""),tr("The Input Parameter Shape of Chamfer One Node is empty"));
      return;
    }
   if(Edge.IsSame(TopoDS_Edge())){
    LoadMessage(tr(""),tr("The Input Edge is not  set"));
    return;
   }
    if(portASet==false){
        std::cout<<" Port A is not set"<<"\n";
        return;
    }
    if(portBSet==false){
        std::cout<<"Port B is not set"<<"\n";
        return;
    }
    if(portCSet==false){
        std::cout<<"Port C is not set"<<"\n";
        return;
    }
     BRepFilletAPI_MakeFillet filletMaker(Shape,chType);
    try{
    filletMaker.Add(Value,Edge);
    filletMaker.Build();
    }
    catch(const Standard_Failure& except ){
        std::cout<<"I am in exception handler"<<"\n";
      LoadMessage(tr(""),tr("Incomplete Build"));  
        return;
    }
    if(filletMaker.IsDone()){
        outputShape->SetData(filletMaker.Shape());
    }
    else{
        LoadMessage(tr(""),tr("Failed To Add Fillet To Shape"));
        return;
    }
  }
  else{
    outputShape=std::make_shared<ShapeNodeData>();
     if(Shape.IsSame(TopoDS_Shape())){
      LoadMessage(tr(""),tr("The Input Parameter Shape of Chamfer One Node is empty"));
      return;
    }
   if(Edge.IsSame(TopoDS_Edge())){
    LoadMessage(tr(""),tr("The Input Edge is not  set"));
    return;
   }
    if(portASet==false){
        std::cout<<" Port A is not set"<<"\n";
        return;
    }
    if(portBSet==false){
        std::cout<<"Port B is not set"<<"\n";
        return;
    }
    if(portCSet==false){
        std::cout<<"Port C is not set"<<"\n";
        return;
    }
     BRepFilletAPI_MakeFillet filletMaker(Shape,chType);
    try{
    filletMaker.Add(Value,Edge);
    filletMaker.Build();
    }
    catch(const Standard_Failure& except ){
        std::cout<<"I am in exception handler"<<"\n";
      LoadMessage(tr(""),tr("Incomplete Build"));  
        return;
    }
    if(filletMaker.IsDone()){
        outputShape->SetData(filletMaker.Shape());
    }
    else{
        LoadMessage(tr(""),tr("Failed To Add Fillet To Shape"));
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
class ClassTwoFilletNode;













#endif