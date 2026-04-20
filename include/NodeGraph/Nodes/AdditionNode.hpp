#ifndef ADDITION_NODE_HPP
#define ADDITION_NODE_HPP
#include<NodeDelegateModel>
#include<Compute.hpp>
#include<FloatNodeData.hpp>
#include<memory>
//we have to use std::weak_ptr<NodeData> to avoid cyclic pointer.
using QtNodes::NodeDelegateModel;
using namespace std;
class AdditionNode:public NodeDelegateModel,public Compute{
private:
Q_OBJECT
std::shared_ptr<FloatNodeData> input_data_1;
std::shared_ptr<FloatNodeData> input_data_2;
std::shared_ptr<FloatNodeData> output_data_3;



public:
AdditionNode(){

}
unsigned int nPorts(PortType portType) const override{
  switch(portType){
   case PortType::In:{
        return 2;
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
    return tr("AdditionNode");
}
QString name() const override{
    return tr("AdditionNode");
}
 NodeDataType dataType(PortType portType, PortIndex portIndex) const override{
     switch(portType){
        case PortType::In:{
         switch(portIndex){
               case 0:
                  return FloatNodeData(0.0,tr("InputData")).type();
               case 1:
                   return FloatNodeData(0.0,tr("InputData")).type();
               
}  
        }
         case PortType::Out:{
             switch(portIndex){
                 case 0:
                    return FloatNodeData(0.0,tr("OutputData")).type();   
                 }    
          }
       }   
  
}

std::shared_ptr<NodeData> outData(PortIndex port) override{
    return std::static_pointer_cast<NodeData>(output_data_3);    
}

void setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override{
      auto input=std::dynamic_pointer_cast<FloatNodeData>(data);
      if(portIndex==0){
         input_data_1=input;   //we have to use weak_ptr<> To avoid cycling referencing
         return;
      }
      else if(portIndex==1){
          input_data_2=input;
      }
      compute();
      return;
}

QWidget *embeddedWidget() override { return nullptr; }  //No embedded widget

virtual void compute() override{
    
    if(input_data_1.get()==nullptr){
         input_data_1=std::make_shared<FloatNodeData>(0.0,tr("Input Data"));  //when there is no data,input data1=0.0;
    }
   if(input_data_2.get()==nullptr){
     input_data_2=std::make_shared<FloatNodeData>(0.0,tr("Input Data 2"));   //By Default, if there is no value, input data2=0.0;
   }
  auto result=input_data_1->Data()+input_data_2->Data();  //This adds the input data one and input data two together to produce fantastic result
  output_data_3=make_shared<FloatNodeData>(result,"Output Data");  //This creates a result node
  emit dataUpdated(0);  //This updates the output data
}

};






#endif