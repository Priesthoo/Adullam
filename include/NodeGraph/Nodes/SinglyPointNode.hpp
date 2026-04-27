#ifndef SINGLY_POINT_NODE_HPP
#define SINGLY_POINT_NODE_HPP
#include<PointNodeData.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>

#include<iostream>
#include<QtCore/QJsonObject>
using namespace QtNodes;
using namespace std;
class SinglyPointNode:public NodeDelegateModel,public NodeInitializer{
   private:
   std::shared_ptr<PointNodeData> output_data;
   Point InputValue;
   public:
   SinglyPointNode(){
     return;
   }
QJsonObject save() const override{
    QJsonObject object=NodeDelegateModel::save();
    object["X"]=InputValue.X();
    object["Y"]=InputValue.Y();
    object["Z"]=InputValue.Z();
    return object;
}
void load(const QJsonObject& object) override{
    InputValue.SetX(object["X"].toDouble(1.0));
    InputValue.SetY(object["Y"].toDouble(1.0));
    InputValue.SetZ(object["Z"].toDouble(1.0));
    emit dataUpdated(0);
    return;
}


   void SetPoint(const Point& pnt){
     InputValue=pnt;
     cout<<InputValue.X()<<endl;
     cout<<InputValue.Y()<<std::endl;
     cout<<InputValue.Z()<<endl;
     emit dataUpdated(0);
     return;
   }
   unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 0;
        }
        case PortType::Out:{
            return 1;
        }
       
    }
    return 0;
}
QString caption() const override{
    return tr("Point Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return PointNodeData(1.0,0.0,0.0,QString("Output Point")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
        output_data->SetData(InputValue);
        return std::static_pointer_cast<NodeData>(output_data);
    }
    output_data=std::make_shared<PointNodeData>(1.0,0.0,0.0,tr(""));
    output_data->SetData(InputValue);
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};  //zero input,single output;










#endif