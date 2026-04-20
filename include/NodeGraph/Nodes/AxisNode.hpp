#ifndef AXIS_NODE_HPP
#define AXIS_NODE_HPP
#include<DirectionNodeData.hpp>
#include<PointNodeData.hpp>
#include<AxisNodeData.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<memory>
using namespace std;
using namespace QtNodes;
class AxisNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<DirectionNodeData>input_dir_data;
std::weak_ptr<PointNodeData> input_pnt_data;
std::shared_ptr<AxisNodeData> output_Axis_data;
 gp_Dir dir=gp_Dir(1.0,0.0,0.0);
Point pnt=Point(0.0,0.0,0.0);
public:
AxisNode(){

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
           return 0;
    }
    return 0;
}
QString caption() const override{
    return tr("AxisNode");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                 return DirectionNodeData(1.0,0.0,0.0,tr("Direction")).type();
                case 1:
                  return PointNodeData(1.0,0.0,0.0,tr("Position")).type();
               

            }
        case PortType::Out:{
            switch(portIndex){
                case 0:
                  return AxisNodeData(QString("Output_Axis")).type();
            }
        }
        }
        
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_Axis_data.get()){
        output_Axis_data->SetData(gp_Pnt(pnt.X(),pnt.Y(),pnt.Z()),dir);
        return std::static_pointer_cast<NodeData>(output_Axis_data);
    }
    output_Axis_data=std::make_shared<AxisNodeData>(tr(""));
    output_Axis_data->SetData(gp_Pnt(pnt.X(),pnt.Y(),pnt.Z()),dir);
    return std::static_pointer_cast<NodeData>(output_Axis_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    //since we have two input
    if(!data.get()){
        return;
    }
   
    switch(portIndex){
        case 0:{
          auto input=std::dynamic_pointer_cast<DirectionNodeData>(data);
          input_dir_data=input;
          if(input_dir_data.lock()){
          dir=input_dir_data.lock()->Data();
          
          }
          break;
        }
        case 1:{
          auto input=std::dynamic_pointer_cast<PointNodeData>(data);
          input_pnt_data=input;
          if(input_pnt_data.lock()){
          pnt=input_pnt_data.lock()->Data();
          }
          break;
        }
        default:
            break;
    }
    if(output_Axis_data.get()){
        output_Axis_data->SetData(gp_Pnt(pnt.X(),pnt.Y(),pnt.Z()),dir);
        emit dataUpdated(0);
        return;
    }
    else{
       output_Axis_data=std::make_shared<AxisNodeData>(tr(""));
        output_Axis_data->SetData(gp_Pnt(pnt.X(),pnt.Y(),pnt.Z()),dir);
        emit dataUpdated(0);
        return;
    }
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};







#endif 