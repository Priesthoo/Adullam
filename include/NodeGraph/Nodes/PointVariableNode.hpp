//This is either a 2D point or 3D point
#ifndef POINT_VARIABLE_NODE_HPP
#define POINT_VARIABLE_NODE_HPP
#include<NodeInitializer.hpp>
#include<PointNodeData.hpp>
#include<FloatNodeData.hpp>
#include<NodeDelegateModel>

using QtNodes::NodeDelegateModel;
using namespace std;
class Point3dNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<FloatNodeData> x_input_data;
std::weak_ptr<FloatNodeData> y_input_data;
std::weak_ptr<FloatNodeData> z_input_data;
std::shared_ptr<PointNodeData> output_data;



public:
Point3dNode(){

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
           return 0;
    }
    return 0;
}
QString caption() const override{
    return tr("3D Point Node ");
}
QString name() const override{
    return caption();
}
 
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                 return FloatNodeData(0.0,tr("X")).type();
                case 1:
                  return FloatNodeData(0.0,tr("Y")).type();
                case 2:
                  return FloatNodeData(0.0,tr("Z")).type();

            }
        case PortType::Out:{
            switch(portIndex){
                case 0:
                  return PointNodeData(1.0,0.0,0.0,QString("Output_Point")).type();
            }
        }
        }
        
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
        return std::static_pointer_cast<NodeData>(output_data);
    }
    output_data=std::make_shared<PointNodeData>(1.0,0.0,0.0,tr(""));
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    //since we have three input
    float x,y,z=0.0f;
    switch(portIndex){
        case 0:{
          auto input=std::dynamic_pointer_cast<FloatNodeData>(data);
          x_input_data=input;
          x=x_input_data.lock()->Data();
          break;
        }
        case 1:{
          auto input=std::dynamic_pointer_cast<FloatNodeData>(data);
          y_input_data=input;
          y=y_input_data.lock()->Data();
          break;
        }
        case 2:{
          auto input=std::dynamic_pointer_cast<FloatNodeData>(data);
          z_input_data=input;
          z=z_input_data.lock()->Data();
          break;
        }
        default:
            break;
    }
    if(x_input_data.lock().get() && y_input_data.lock().get() && z_input_data.lock().get()){
        output_data=std::make_shared<PointNodeData>(x,y,z,tr(""));
         emit dataUpdated(0);
        return;
    }
    else{
        output_data=std::make_shared<PointNodeData>(x,y,z,tr(""));
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