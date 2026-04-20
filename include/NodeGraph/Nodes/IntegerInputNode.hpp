#ifndef INTEGER_INPUT_NODE_HPP
#define INTEGER_INPUT_NODE_HPP
#include<IntegerNodeData.hpp>
#include<NodeDelegateModel>
#include<NodeDescription.hpp>
using namespace std;
using namespace QtNodes;
class IntegerInputNode:public QtNodes::NodeDelegateModel{
private:
std::shared_ptr<IntegerNodeData> output_data;

public:
IntegerInputNode(){

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::Out:{
            return 1;  //number of output node
        }
        default:
           return 0;
    }
    return 0;
}

QString caption() const override{
    return tr("Integer");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
     switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return IntegerNodeData(0,tr("")).type();
            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port)  override{
    output_data=std::make_shared<IntegerNodeData>(7,tr(""));
    return static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    return;
}
QWidget* embeddedWidget() override{ return nullptr;}

};








#endif