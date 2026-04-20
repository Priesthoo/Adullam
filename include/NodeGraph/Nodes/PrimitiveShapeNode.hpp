#pragma once
#include<ShapeNodeData.hpp >
#include<memory>
#include<BRepBuilderAPI_Transform.hxx>
#include<TransformNodeData.hpp>
#include<ParentShapeNodeData.hpp>
#include<NodeInitializer.hpp>
#include<MaterialNodeData.hpp>
#include<NodeDelegateModel>
#include<BooleanNodeData.hpp>
#include<ParentShape.hpp>
#include<iostream>
using namespace QtNodes;
using namespace std;

//this should contain ShouldSend Variable,ShouldKeep Variable, Transform Variable and etc;
class PrimitiveShapeNode:public NodeDelegateModel,public NodeInitializer{
private:
Q_OBJECT
weak_ptr<ShapeNodeData> input_data; //0-index
shared_ptr<ShapeNodeData> output_data;
std::shared_ptr<ParentShapeNodeData> output;  //for parent-child relationship in Parent
std::weak_ptr<MaterialNodeData> inputMaterial;
std::weak_ptr<BooleanNodeData> HasMaterial;  //ShouldKeep
gp_Trsf outTransform=gp_Trsf();

public:
TopoDS_Shape outputShape;
ShapePair shapepair;
bool hasMaterial=false;  //by default,there is no material set
bool ShouldSend=true;
PrimitiveShapeNode(){
   
}
TopoDS_Shape Shape() const{
    if(output_data.get()){
        return output_data->Data();
    }
    return TopoDS_Shape();
}
//This sets both the shape and the transform
void SetShape(const TopoDS_Shape& shape){
    if(shape.IsSame(TopoDS_Shape())){
         return;
    }
    if(output_data.get()){

        output_data->SetData(shape);
    }
    return;
}

gp_Trsf Transform() const{
    return outTransform;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  3;
        }
        case PortType::Out:{
            return 2;
        }
        default:
         break;
    }
    return 0;
}
QString caption() const override{
    return tr("Primitive Shape");
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
                   return BooleanNodeData(false,tr("Has Material")).type();
               case 2:{
                  return MaterialNodeData(tr("Material")).type();
               }
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("OutputShape")).type();
                case 1:
                  return ParentShapeNodeData(tr("Parent Shape")).type();
             }
        }
        
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
   switch(port){
    case 0:{
    if(output_data.get()){
        return static_pointer_cast<NodeData>(output_data);
    }
    output_data=std::make_shared<ShapeNodeData>();
    return static_pointer_cast<NodeData>(output_data);
   }
   break;
    case 1:{
        if(output){
             return static_pointer_cast<NodeData>(output);
        }
        std::shared_ptr<NodeData> mptr;
        return mptr;
    }
    break;
}
std::shared_ptr<NodeData> mptr;
    return static_pointer_cast<NodeData>(mptr);
}

void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data.get()){ //analogous to data.ptr, such that ptr is apointer
        return;
    }
    
   
    
    switch(portIndex){
        case 0:{

            input_data=std::dynamic_pointer_cast<ShapeNodeData>(data);
            if(input_data.lock().get()){
            outputShape=input_data.lock()->Data();
            std::cout<<"First Data set"<<std::endl;
        }
            break;
        }
        
        case 1:{
             HasMaterial=std::dynamic_pointer_cast<BooleanNodeData>(data);
           if(HasMaterial.lock()){
           hasMaterial=HasMaterial.lock()->Data();
           if(output_data){
            if(output_data->Data().ShapeType()>4){
                output_data->SetHasMaterialAspect(false);
            }
            else{
            output_data->SetHasMaterialAspect(hasMaterial);
            }
           }
           std::cout<<"Second Data set"<<std::endl;
           } 
            break;
        }
        case 2:{
           inputMaterial=std::dynamic_pointer_cast<MaterialNodeData>(data);
           if(inputMaterial.lock()){
            if(output_data){
                output_data->SetAspect(inputMaterial.lock()->Data());
                
            }
           }
           break;
        }
        
        default:
          break;
    }
    if(output_data){
        if(outputShape.IsSame(TopoDS_Shape())){
            return;
        }
        output_data->SetData(outputShape);
      emit dataUpdated(0);
    }
    else{

        output_data=make_shared<ShapeNodeData>();
        if(outputShape.IsSame(TopoDS_Shape())){
            return;
        }
        output_data->SetData(outputShape);
       emit dataUpdated(0);
    }

    if(output){
        if(!output->GetShape().has_value()){
            if(outputShape.IsSame(TopoDS_Shape())){
                return;
            }
           shapepair.SetShape(outputShape);
           output->SetShape(std::ref(shapepair));
           std::cout<<"Updated In SetInData()"<<"\n";
           emit dataUpdated(1);
        }
        else{
            if(!output->GetOwnShape().parentShape().IsSame(outputShape)){
                 output->GetOwnShape().SetShape(outputShape);
                 emit dataUpdated(1);
                 return;
            }
            emit dataUpdated(1);
        }
}
   else{
          output=make_shared<ParentShapeNodeData>(tr(""));  
           if(outputShape.IsSame(TopoDS_Shape())){
                return;
            }
             shapepair.SetShape(outputShape);
           output->SetShape(std::ref(shapepair));
           
           std::cout<<"Updated In Node"<<"\n";
           emit dataUpdated(1);
        }
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
signals:
void EmitShape(const TopoDS_Shape& shape);

};
