#pragma once 
#include<NodeDelegateModel>
#include<EdgeNodeData.hpp>
#include<ParentShapeNodeData.hpp>
#include<NodeInitializer.hpp>
#include<iostream>
using namespace std;
using namespace QtNodes;

class EdgeNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<ParentShapeNodeData> inputData;
std::shared_ptr<EdgeNodeData> outputData;
std::optional<std::reference_wrapper<ShapePair>> output;
bool IsAllAssigned=false;
public:
EdgeNode(){
    return;
}
EdgeNodeData* Output() const{
    return outputData.get();
}
TopoDS_Shape outputEdge() const{
     if(!outputData){
        return TopoDS_Shape();  //return an empty shape
     }
     return outputData->Data().EdgeShape();
}
ShapePair& GetOutputShape(){
    return output.value().get();
}
TopoDS_Shape outputShape() const{
    if(!outputData){
        return TopoDS_Shape();
    }
    return outputData->Data().parent().parentShape();
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  1;
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
    return tr("Primitive Edge");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
  switch(portType){
    case PortType::In:{
        switch(portIndex){
            case 0:
              return ParentShapeNodeData(tr("Input")).type();
        }
    }
    case PortType::Out:{
        switch(portIndex){
            case 0:
              return EdgeNodeData(tr("Output Edge")).type();
        }
    }
  }
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex){
    if(!data){
        return;
    }
    switch(portIndex){
        case 0:{
            inputData=std::dynamic_pointer_cast<ParentShapeNodeData>(data);
            //sometimes casting might fail,that is why we need to check
            
            if(inputData.lock()){
                output.emplace(inputData.lock()->GetOwnShape());
                std::cout<<"Edge Node Data On Enter"<<"/\n";

            }
            break;
        }

    }
    if(!output.has_value()){
        std::cout<<"Invalid Value"<<"\n";
        return;
    }
    if(outputData){
        std::cout<<"Edge Count On Enter: "<<output.value().get().EdgeCount()<<std::endl; 
       
       if(IsAllAssigned){
          return;
       }
       if(outputData->Data().parent().parentShape().IsSame(output.value().get().parentShape())){
          std::cout<<"Shape Is the same"<<"\n";
          std::cout<<"Index: "<<outputData->Data().Index()<<"\n";
          emit dataUpdated(0);
       }
       else{
        if(Output()){
            
            IsAllAssigned=false;
            if(Output()->GetData().Index()<Output()->GetData().parent().EdgeCount()){
               std::cout<<"Index To be removed:"<<Output()->GetData().Index()<<"\n";
               Output()->GetData().parent().GetEdge(Output()->GetData().Index()).IsAssigned=false;
              
           }
         }
         if(output.value().get().EdgeCount()==0){
            // no face at all
            std::cout<<"Edge Count: "<<output.value().get().EdgeCount()<<std::endl;
            return;
         }
        for(int i=0;i<output.value().get().EdgeCount();i++){
           if(!output.value().get().GetEdge(i).IsAssigned){
            output.value().get().GetEdge(i).IsAssigned=true;
            outputData->SetData(output.value().get().GetEdge(i));
            std::cout<<"Index:"<<i<<" is assigned"<<"\n";
            break;
           }
        }
        IsAllAssigned=true;
       }
    }
    else{
        
        outputData=make_shared<EdgeNodeData>(tr(""));
        if(output.value().get().EdgeCount()==0){
            return;
        }
        if(IsAllAssigned){
            return;
        }
        for(int i=0;i<output.value().get().EdgeCount();i++){
           if(!output.value().get().GetEdge(i).IsAssigned){
            output.value().get().GetEdge(i).IsAssigned=true;
            outputData->SetData(output.value().get().GetEdge(i));
            std::cout<<"Index:"<<i<<" is assigned"<<"\n";
            break;
           }
        }
        IsAllAssigned=true;
        emit dataUpdated(0);
        return;
    }
    emit dataUpdated(0);
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(outputData){
    return std::static_pointer_cast<NodeData>(outputData);
  }
  std::shared_ptr<NodeData> mptr;
  return mptr;
}

QWidget* embeddedWidget() override{return nullptr;}
~EdgeNode(){
   
}
};