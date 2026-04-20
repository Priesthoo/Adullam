#ifndef STRING_INPUT_NODE_HPP
#define STRING_INPUT_NODE_HPP
#include<NodeDelegateModel>
#include<NodeDescription.hpp>
#include<memory>
#include<StringNodeData.hpp>
using namespace std;
using namespace QtNodes;
class StringInputNode:public QtNodes::NodeDelegateModel{
private:
shared_ptr<StringNodeData> output_data;


public:
StringInputNode(){

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
    return tr("String Data");
} 
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
     switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return StringNodeData(tr(""),tr("")).type();
            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port)  override{
    output_data=std::make_shared<StringNodeData>(QString("God Bless"),tr(""));
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};








#endif