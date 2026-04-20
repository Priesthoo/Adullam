#pragma once 
#include<TransformNodeData.hpp>
#include<NodeInitializer.hpp>
#include<BRepBuilderAPI_Transform.hxx>
#include<ShapeUtil.hpp>
#include<memory>


using namespace std;
using namespace QtNodes;
using namespace Shape_Utility;
class CombinedTransformNode:public NodeDelegateModel,public NodeInitializer{
private:
weak_ptr<TransformNodeData> inputData_1;
weak_ptr<TransformNodeData> inputData_2;
weak_ptr<TransformNodeData> inputData_3;

gp_Trsf outputTransform;
TopoDS_Shape transShape=DrawCube(10);  //dummy shape to store transform
shared_ptr<TransformNodeData> outputData;
public:
CombinedTransformNode(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 3;
        }
        case PortType::Out:{
            return 1;
        }
        default:
        break;

    }
    
    
    
    
    return 0;  //by default
}
QString caption() const override{
    return tr("CombinedTransform");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                 return TransformNodeData(tr("Input Transform(1)")).type();
                case 1:
                 return TransformNodeData(tr("Input Transform(2)")).type();
                case 2:
                    return TransformNodeData(tr("Input Transform(3)")).type();
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return TransformNodeData(tr("Output Transform")).type();
             }
        }
    }
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
if(!data){
    return;
}
gp_Trsf input_1,input_2,input_3;
switch(portIndex){
    case 0:{
        inputData_1=dynamic_pointer_cast<TransformNodeData>(data);
        if(inputData_1.lock()){
        input_1=inputData_1.lock()->Data();
        }
        break;
    }
    case 1:{
        inputData_2=dynamic_pointer_cast<TransformNodeData>(data);
        if(inputData_2.lock()){
            input_2=inputData_2.lock()->Data();
        }

        break;
    }
   case 2:{
        inputData_3=dynamic_pointer_cast<TransformNodeData>(data);
        if(inputData_3.lock()){
            input_2=inputData_3.lock()->Data();
        }
        
        break;
    }
}
//the order of multiplication:perform input_1,input_2,input_3:input_3*input_2*input_1;

if(!outputData){
  outputData=make_shared<TransformNodeData>(tr(""));
  BRepBuilderAPI_Transform trans(input_1);
  trans.Perform(transShape);
  if(trans.IsDone()){
    BRepBuilderAPI_Transform trans_1(input_2);
    trans_1.Perform(trans.Shape());
    if(trans_1.IsDone()){
        BRepBuilderAPI_Transform trans_2(input_3);
        trans_2.Perform(trans_1.Shape());
        if(trans_2.IsDone()){
            outputTransform=trans_2.Shape().Location().Transformation();
        }
    }
  }
 
  outputData->SetData(outputTransform);
}
else{
    BRepBuilderAPI_Transform trans(input_1);
  trans.Perform(transShape);
  if(trans.IsDone()){
    BRepBuilderAPI_Transform trans_1(input_2);
    trans_1.Perform(trans.Shape());
    if(trans_1.IsDone()){
        BRepBuilderAPI_Transform trans_2(input_3);
        trans_2.Perform(trans_1.Shape());
        if(trans_2.IsDone()){
            outputTransform=trans_2.Shape().Location().Transformation();
        }
    }
  }
    outputData->SetData(outputTransform);
}

emit dataUpdated(0);

return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        return std::static_pointer_cast<NodeData>(outputData);
    }
 
   std::shared_ptr<NodeData> outData;
   return static_pointer_cast<NodeData>(outData);

}
QWidget* embeddedWidget() override{return nullptr;}
};