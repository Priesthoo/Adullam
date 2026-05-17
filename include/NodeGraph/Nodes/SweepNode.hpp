#pragma once
#include<BRepOffsetAPI_MakePipeShell.hxx>
#include<ShapeNodeData.hpp>
#include<IntegerNodeData.hpp>
#include<memory>
#include<InfoUtility.hpp>
#include<NodeInitializer.hpp>
using namespace std;
using namespace QtNodes;
using namespace INFO;
//for surface construction
class ClassOneSurfaceSweepNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<WireNodeData> inputWire;
std::weak_ptr<TemplatedData<int>> inputBool;
std::weak_ptr<ShapeNodeData> inputShape;
std::shared_ptr<ShapeNodeData> outputShape;
TopoDS_Shape shape;
TopoDS_Wire wire;
int state=-1;
bool portASet=false;
bool portBSet=false;
bool portCSet=false;

void PrintError(const BRepBuilderAPI_PipeError& error){
    switch(error){
        case BRepBuilderAPI_PipeNotDone:{
            LoadMessage(tr(""),tr("An Error Occured When Building"));
            break;
        }
        case BRepBuilderAPI_PlaneNotIntersectGuide:{
            LoadMessage(tr(""),tr("Plane do not intersect with guide"));
            break;
        }
        case BRepBuilderAPI_ImpossibleContact:{
            LoadMessage(tr(""),tr("Contact are not possible"));
            break;
        }
    }
    return;
}
public:
ClassOneSurfaceSweepNode(){
    return;
}
QString caption() const override{
    return tr("Surface Sweep Node");
}virtual void SetToFalse() override{
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
                     return TemplatedData<int>(tr("Use Frenet"),tr("bool")).type();
                case 2:
                    return WireNodeData(tr("Input Wire")).type();
                
            
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
        inputShape=dynamic_pointer_cast<ShapeNodeData>(data);
        if(inputShape.lock()){
            portASet=true;
           shape=inputShape.lock()->Data(); 
        }
        break;
    }
    case 1:{
        inputBool=dynamic_pointer_cast<TemplatedData<int>>(data);
        if(inputBool.lock()){
            portBSet=true;
         state=inputBool.lock()->Data();
        }
        break;
    }
    case 2:{
        inputWire=dynamic_pointer_cast<WireNodeData>(data);
        if(inputWire.lock()){
            portCSet=true;
            wire=inputWire.lock()->Data();
        }
        break;
    }
  }
  if(outputShape){
    if(!portASet){
        return;
    }
    if(!portBSet){
        return;
    }
    if(!portCSet){
        return;
    }
    if(shape.IsSame(TopoDS_Shape())){
        return;
    }
    BRepOffsetAPI_MakePipeShell shellMaker(wire);
    if(state==1){
        shellMaker.SetMode(true);
    }
    else{
        shellMaker.SetMode(false);
    }
    
   
    try{
      shellMaker.Add(shape); //with contact=false and with correction=false...   
    shellMaker.Build();
    }
    catch(const Standard_Failure& failure){
        LoadMessage(tr(""),tr("Failed To Build"));
        return;
    }
    if(shellMaker.IsDone()){
        outputShape->SetData(shellMaker.Shape());
    }
    else{
        PrintError(shellMaker.GetStatus());

    }

  } 
  else{
    outputShape=std::make_shared<ShapeNodeData>(tr(""));
   if(!portASet){
        return;
    }
    if(!portBSet){
        return;
    }
    if(!portCSet){
        return;
    }
    if(shape.IsSame(TopoDS_Shape())){
        return;
    }
    BRepOffsetAPI_MakePipeShell shellMaker(wire);
    if(state==1){
        shellMaker.SetMode(true);
    }
    else{
        shellMaker.SetMode(false);
    }
    
    
    try{
    shellMaker.Add(shape); //with contact=false and with correction=false...
    shellMaker.Build();
    }
    catch(const Standard_Failure& failure){
        LoadMessage(tr(""),tr("Failed To Build"));
        return;
    }
    if(shellMaker.IsDone()){
        outputShape->SetData(shellMaker.Shape());
    }
    else{
        PrintError(shellMaker.GetStatus());

    }
  }
  
  emit dataUpdated(0);
  return;
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


class ClassOneSolidSweepNode:public NodeDelegateModel,public NodeInitializer{
std::weak_ptr<WireNodeData> inputWire;
std::weak_ptr<TemplatedData<int>> inputBool;
std::weak_ptr<ShapeNodeData> inputShape;
std::shared_ptr<ShapeNodeData> outputShape;
TopoDS_Shape shape;
TopoDS_Wire wire;
int state=-1;
bool portASet=false;
bool portBSet=false;
bool portCSet=false;
void PrintError(const BRepBuilderAPI_PipeError& error){
    switch(error){
        case BRepBuilderAPI_PipeNotDone:{
            LoadMessage(tr(""),tr("An Error Occured When Building"));
            break;
        }
        case BRepBuilderAPI_PlaneNotIntersectGuide:{
            LoadMessage(tr(""),tr("Plane do not intersect with guide"));
            break;
        }
        case BRepBuilderAPI_ImpossibleContact:{
            LoadMessage(tr(""),tr("Contact are not possible"));
            break;
        }
    }
    return;
}
public:
ClassOneSolidSweepNode(){
    return;
}
QString caption() const override{
    return tr("Solid Sweep Node");
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
                     return TemplatedData<int>(tr("Use Frenet"),tr("bool")).type();
                case 2:
                    return WireNodeData(tr("Input Wire")).type();
                
            
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
        inputShape=dynamic_pointer_cast<ShapeNodeData>(data);
        if(inputShape.lock()){
            portASet=true;
           shape=inputShape.lock()->Data(); 
        }
        break;
    }
    case 1:{
        inputBool=dynamic_pointer_cast<TemplatedData<int>>(data);
        if(inputBool.lock()){
            portBSet=true;
         state=inputBool.lock()->Data();
        }
        break;
    }
    case 2:{
        inputWire=dynamic_pointer_cast<WireNodeData>(data);
        if(inputWire.lock()){
            portCSet=true;
            wire=inputWire.lock()->Data();
        }
        break;
    }
  }
  if(outputShape){
   if(!portASet){
        return;
    }
    if(!portBSet){
        return;
    }
    if(!portCSet){
        return;
    }
    if(shape.IsSame(TopoDS_Shape())){
        return;
    }
    BRepOffsetAPI_MakePipeShell shellMaker(wire);
    if(state==1){
        shellMaker.SetMode(true);
    }
    else{
        shellMaker.SetMode(false);
    }
    
    shellMaker.Add(shape); //with contact=false and with correction=false...
    try{
    shellMaker.MakeSolid();
    shellMaker.Build();
    }
    catch(const Standard_Failure& failure){
        LoadMessage(tr(""),tr("Failed To Build"));
        return;
    }
    if(shellMaker.IsDone()){
        outputShape->SetData(shellMaker.Shape());
    }
    else{
        PrintError(shellMaker.GetStatus());

    }

  } 
  else{
    outputShape=std::make_shared<ShapeNodeData>(tr(""));
   if(!portASet){
        return;
    }
    if(!portBSet){
        return;
    }
    if(!portCSet){
        return;
    }
    if(shape.IsSame(TopoDS_Shape())){
        return;
    }
    BRepOffsetAPI_MakePipeShell shellMaker(wire);
    if(state==1){
        shellMaker.SetMode(true);
    }
    else{
        shellMaker.SetMode(false);
    }
    
    shellMaker.Add(shape); //with contact=false and with correction=false...
    try{
    shellMaker.MakeSolid();
    shellMaker.Build();
    }
    catch(const Standard_Failure& failure){
        LoadMessage(tr(""),tr("Failed To Build"));
        return;
    }
    if(shellMaker.IsDone()){
        outputShape->SetData(shellMaker.Shape());
    }
    else{
        PrintError(shellMaker.GetStatus());

    }
  }
  
  emit dataUpdated(0);
  return;
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






