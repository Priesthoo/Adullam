#ifndef FACE_NODE_HPP
#define FACE_NODE_HPP
#include<NodeDelegateModel>
#include<FaceNodeData.hpp>
#include<ParentShapeNodeData.hpp>
#include<NodeInitializer.hpp>
#include<iostream>
using namespace std;
class FaceNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<ParentShapeNodeData> inputData;
std::shared_ptr<FaceNodeData> outputData;
std::optional<std::reference_wrapper<ShapePair>> output;
bool IsAllAssigned=false;
public:
FaceNode(){

}
FaceNodeData* Output() const{
    return outputData.get();
}
TopoDS_Shape outputFace() const{
    if(!outputData){
        return TopoDS_Shape();
    }
        return outputData->Data().FaceShape();
    
}
 int GetId() const{
    if(outputData){
     (int)outputData->Data().Index()+1;  //to index a face,we start from 1
    }
    return -1;  //invalid index 
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
    return tr("Primitive Face");
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
              return FaceNodeData(tr("Output Face")).type();
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
                std::cout<<"Face Node Data On Enter"<<"/\n";
            }
            break;
        }

    }
    if(!output.has_value()){
        std::cout<<"Invalid Value"<<"\n";
        return;
    }
    if(outputData){
        std::cout<<"Face Count On Enter: "<<output.value().get().FaceCount()<<std::endl; 
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
           if(Output()->GetData().Index()<Output()->GetData().parent().FaceCount()){
               std::cout<<"Index To be removed:"<<Output()->GetData().Index()<<"\n";
               Output()->GetData().parent().GetFace(Output()->GetData().Index()).IsAssigned=false;
              
           }
          
        }
        if(!output.has_value()){
            std::cout<<"It doesn't have value()"<<"\n";
            return;
        }
        else{
            std::cout<<"It has Value"<<"\n";
        }
         if(output.value().get().FaceCount()==0){
            // no face at all
            std::cout<<"Face Count: "<<output.value().get().FaceCount()<<std::endl;
            return;
         }
        for(int i=0;i<output.value().get().FaceCount();i++){
           if(!output.value().get().GetFace(i).IsAssigned){
            output.value().get().GetFace(i).IsAssigned=true;
            outputData->SetData(output.value().get().GetFace(i));
            std::cout<<"Index:"<<i<<" is assigned"<<"\n";
            break;
           }
        }
        IsAllAssigned=true;
       }
    }
    else{
        if(!output.has_value()){
            std::cout<<"Nullptr"<<"\n";
            return;
        }
        else{
            std::cout<<"It has value"<<"\n";
        }
        outputData=make_shared<FaceNodeData>(tr(""));
        if(output.value().get().FaceCount()==0){
            return;
        }
        for(int i=0;i<output.value().get().FaceCount();i++){
           if(!output.value().get().GetFace(i).IsAssigned){
            output.value().get().GetFace(i).IsAssigned=true;
            outputData->SetData(output.value().get().GetFace(i));
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
~FaceNode(){
   
}


};











#endif