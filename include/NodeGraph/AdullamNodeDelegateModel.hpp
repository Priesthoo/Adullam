#pragma once 
#include<NodeData>
#include<NodeDelegateModel>
#include<QtWidgets/QWidget>

#include<iostream>
#include<memory>
using namespace std;
using QtNodes::NodeData;
using QtNodes::NodeDelegateModel;
using namespace QtNodes;

enum DATATYPE{
FLOAT_TYPE,
STRING_TYPE,
DOUBLE_TYPE,
INTEGER_TYPE,
VOID_TYPE
};

class CustomDelegateModel:public NodeDelegateModel{
  Q_OBJECT
 DATATYPE type=DATATYPE::VOID_TYPE;
public:
CustomDelegateModel():NodeDelegateModel(){
  
}
void SetType(const DATATYPE type_1){
    type=type_1;
    return;
}
DATATYPE getType(){
    return type;
}
  QString name() const override{
    return QString(tr("Custom"));
 }
  QString caption() const override{
    return name();
 }
unsigned int nPorts(PortType portType) const override{
    return 0;
  }
 NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    return {tr(""),tr("")};
 }
 void setInData(std::shared_ptr<NodeData> data,PortIndex const portIndex) override{
   return;
 }
 std::shared_ptr<NodeData> outData(PortIndex port) override{
    std::shared_ptr<NodeData> ptr;
    return ptr;
 }
 QWidget* embeddedWidget() override{
    return nullptr;
 }
 ~CustomDelegateModel(){ //inline definition

  }
 signals:
  void UpdateDataViaIndex(PortIndex const portIndex);
public slots:
   void Process(){
    return;   
}


};