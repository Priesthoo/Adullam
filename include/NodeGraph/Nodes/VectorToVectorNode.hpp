#pragma once
#include<VectorDataNodeData.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<memory>
#include<iostream>

using namespace std;
using QtNodes::NodeDelegateModel;



class VectorToVectorNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<VectorDataNode<ShapeNodeData>> InputShape_1;
std::weak_ptr<VectorDataNode<ShapeNodeData>> InputShape_2;
std::shared_ptr<VectorDataNode<ShapeNodeData>> OutputShape;
bool AreFirstShapesAdded=false;
bool AreSecondShapesAdded=false;
bool AreBothShapesAdded=false;

public:
VectorToVectorNode(){

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 2;  //number of input node
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
    return tr("Vector To Vector(Shape)");
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
                case 1:
                  return VectorDataNode<ShapeNodeData>(tr("Vector"),tr("VectorOfShape")).type();
            }
        }
        case PortType::Out:{
            switch(portIndex){
                case 0:                  //name        //name of type
                   return VectorDataNode<ShapeNodeData>(tr("Vector"),tr("VectorOfShape")).type();


            }
        }
    }
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data.get()){
        return;
    }
    std::vector<ShapeNodeData> shapes1;
    std::vector<ShapeNodeData> shapes2;
   
    switch(portIndex){
        case 0:{
            InputShape_1=dynamic_pointer_cast<VectorDataNode<ShapeNodeData>>(data);
            if(InputShape_1.lock().get()){
               shapes1=InputShape_1.lock()->Data();  //copy the data instead of moving it
            }
            break;
        }
      case 1:{
           InputShape_2=dynamic_pointer_cast<VectorDataNode<ShapeNodeData>>(data);
            if(InputShape_2.lock().get()){
               shapes2=InputShape_2.lock()->Data();  //copy the data instead of moving it
            }
            break;
      }
        
    }
    if(!OutputShape.get()){
        OutputShape=std::make_shared<VectorDataNode<ShapeNodeData>>(tr(""),tr(""));
    }
    //it is possible for shape1 to have values while shape2 is empty
    if(!shapes1.empty() && shapes2.empty()){
        if(!AreFirstShapesAdded){
        if(shapes1.size()<=OutputShape->Capacity()){
            for(int i=0;i<shapes1.size();i++){
                OutputShape->Data().emplace_back(tr(""),shapes1.at(i).Data());
            }
            AreFirstShapesAdded=true;
        }
        else{
            size_t diffcap=OutputShape->Capacity()+(shapes1.size()-OutputShape->Capacity());
            OutputShape->Data().reserve(diffcap); //previous capacity+ diffcap
            for(int i=0;i<shapes1.size();i++){
                OutputShape->Data().emplace_back(tr(""),shapes1.at(i).Data());
            }
           AreFirstShapesAdded=true; 
        }
        }
        else{ //AreFirstShapesAdded=true;
           if(shapes1.size()<=OutputShape->Capacity()){
            for(int i=0;i<shapes1.size();i++){
                OutputShape->Data()[i]=shapes1.at(i); //overwriting the previous values
            }
        }
           else{
             size_t diffcap=OutputShape->Capacity()+(shapes1.size()-OutputShape->Capacity());
              OutputShape->Data().reserve(diffcap);
               size_t trackindex=0; //this is used to track the index movement
               size_t nbElement=OutputShape->Size();
               for(int i=0;i<shapes1.size();i++){

                if(trackindex>=nbElement){
                    OutputShape->Data().emplace_back(tr(""),shapes1.at(i).Data());
                }
                else{
                    OutputShape->Data()[i]=shapes1.at(i);
                    ++trackindex;
                }
               }
           }

    }
    return;

}
    if(!shapes2.empty() && shapes1.empty()){
        if(!AreSecondShapesAdded){
        if(shapes2.size()<=OutputShape->Capacity()){
            for(int i=0;i<shapes2.size();i++){
                OutputShape->Data().emplace_back(tr(""),shapes2.at(i).Data());
            }
            AreSecondShapesAdded=true;
        }
        else{
            size_t diffcap=OutputShape->Capacity()+(shapes2.size()-OutputShape->Capacity());
            OutputShape->Data().reserve(diffcap); //previous capacity+ diffcap
            for(int i=0;i<shapes2.size();i++){
                OutputShape->Data().emplace_back(tr(""),shapes2.at(i).Data());
            }
           AreSecondShapesAdded=true; 
        }
        }
        else{ //AreFirstShapesAdded=true;
           if(shapes2.size()<=OutputShape->Capacity()){
            for(int i=0;i<shapes2.size();i++){
                OutputShape->Data()[i]=shapes2.at(i); //overwriting the previous values
            }
        }
           else{
             size_t diffcap=OutputShape->Capacity()+(shapes2.size()-OutputShape->Capacity());
              OutputShape->Data().reserve(diffcap);
               size_t trackindex=0; //this is used to track the index movement
               size_t nbElement=OutputShape->Size();
               for(int i=0;i<shapes2.size();i++){

                 if(trackindex>=nbElement){
                    OutputShape->Data().emplace_back(tr(""),shapes2.at(i).Data());
                }
                else{
                    OutputShape->Data()[i]=shapes2.at(i);
                    ++trackindex;
                }
               }
           }

    }
    return;
    }

    if(!shapes1.empty() && !shapes2.empty()){
        if(!AreBothShapesAdded){
           size_t shapesize=shapes1.size()+shapes2.size();
           if(shapesize<=OutputShape->Capacity()){
              for(int i=0;i<shapes1.size();i++){
                OutputShape->Data().emplace_back(tr(""),shapes1.at(i).Data());
              }
              for(int i=0; i<shapes2.size();i++){
                OutputShape->Data().emplace_back(tr(""),shapes2.at(i).Data());
              }
              AreBothShapesAdded=true;
           }
            else{
              size_t diffcap=OutputShape->Capacity()+(shapesize-OutputShape->Capacity());
              OutputShape->Data().reserve(diffcap);
              for(int i=0;i<shapes1.size();i++){
                OutputShape->Data().emplace_back(tr(""),shapes1.at(i).Data());
              }
              for(int i=0; i<shapes2.size();i++){
                OutputShape->Data().emplace_back(tr(""),shapes2.at(i).Data());
              }
              AreBothShapesAdded=true;
        }
        } 
        else{
            size_t shapesize=shapes1.size()+shapes2.size();
            
           if(shapesize<=OutputShape->Capacity()){
            size_t indextrack=0;
              for(int i=0;i<shapes1.size();i++){
                OutputShape->Data()[i]=shapes1.at(i);
                ++indextrack;
              }
              for(int i=0; i<shapes2.size();i++){
                OutputShape->Data()[indextrack+i]=shapes2.at(i);
              }
        }
         else{
            size_t ind_tr=0;
            size_t diffcap=OutputShape->Capacity()+(shapesize-OutputShape->Capacity());
              OutputShape->Data().reserve(diffcap);
              size_t nbElement=shapes1.size();
              size_t trackindex=0;
            //for(int i=0;i<10;i++)
            for(int i=0;i<shapes1.size();i++){
                 if(trackindex>=nbElement){
                    OutputShape->Data().emplace_back(tr(""),shapes1.at(i).Data());
                    ++ind_tr;
                }
                else{
                    OutputShape->Data()[i]=shapes1.at(i);
                    ++trackindex;
                    ++ind_tr;
                }
               }
        /*
        For the second array, we have to create a deduction on how to insert the elements
         ind_tr=shapes1.size();
        
        
        */
            trackindex=0;
            nbElement=shapes2.size();
               for(int i=0;i<shapes2.size();i++){
                   if(trackindex>=nbElement){
                     OutputShape->Data().emplace_back(tr(""),shapes2.at(i).Data());
                   }
                   else{
                    OutputShape->Data()[ind_tr+i]=shapes2.at(i);
                    ++trackindex;
                   }                   
               }
         }
         return;
       
    }
}
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(OutputShape.get()){
        return static_pointer_cast<NodeData>(OutputShape);
    }
     std::shared_ptr<NodeData> OutData;
     return OutData; 
}
QWidget* embeddedWidget () override{
    return nullptr;
}
};






