#ifndef DIR_X_HPP
#define DIR_X_HPP
#include<AxisNodeData.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<memory>
using namespace std;
using namespace QtNodes;
class DirXNode:public NodeDelegateModel,public NodeInitializer{
  std::shared_ptr<AxisNodeData> output_Axis_data;
   gp_Dir axis=gp_Dir(1.0,0.0,0.0);
public:
  DirXNode(){
    output_Axis_data=make_shared<AxisNodeData>(tr(""));
     output_Axis_data->SetOriginData(axis);
    return;
  }
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::Out:{
            return 1;
        }
        default:
           return 0;
    }
    return 0;
}
QString caption() const override{
    return tr("Unit X Direction");  //
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                  return AxisNodeData(QString("output ")).type();
            }
        }
        }
        
    
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
 return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_Axis_data){
        return std::static_pointer_cast<NodeData>(output_Axis_data);
    }
    return std::static_pointer_cast<NodeData>(output_Axis_data);
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};












#endif