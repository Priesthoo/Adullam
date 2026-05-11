#pragma once
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<JsonShapeConverter.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace JsonConverter;
class SinglyShapeNode:public NodeDelegateModel,public NodeInitializer{
 private:
 
 TopoDS_Shape OutputValue; //this contains the transformed shape
 TopoDS_Shape initialShape; //this contains a untransformed shape specified in object space 
 int Index=-1; //Bad Index
 std::shared_ptr<ShapeNodeData> output_data;

 public:
 SinglyShapeNode(){
   return;
 }
 TopoDS_Shape Shape() const{
    return OutputValue;
 }
 TopoDS_Shape InitShape() const{
    return initialShape;
 }
 void SetId(const int& id){
    Index=id;
    return;
 }
 int GetIndex() const{
    return Index;
 }
 QJsonObject save() const override{
    QJsonObject object=NodeDelegateModel::save();
    object["BRep_Shape"]=ToString(OutputValue);
    object["Initial Shape"]=ToString(initialShape);
    object["Shape Index"]=Index;
    return object;
 }
 void load(const QJsonObject& object) override{
    QString value=object["BRep_Shape"].toString();
    QString value1=object["Initial Shape"].toString();
    OutputValue=ToMainShape(value);
    initialShape=ToMainShape(value1);
    Index=object["Shape Index"].toInt();
    if(OutputValue.IsSame(TopoDS_Shape())){
        LoadMessage(tr("Shape Error"),tr("It is Empty"));
    }
    else{
        LoadMessage(tr("Shape Result"),tr("Shape Built Successfully"));
    }
   SetShapeData(OutputValue);
 }
 void SetInitShape(const TopoDS_Shape& sh){
    initialShape=sh;
    return;
 }
 void SetShapeData(const TopoDS_Shape& shape){
    OutputValue=shape;
    if(output_data){
        output_data->SetData(OutputValue);
    }
    else{
        output_data=make_shared<ShapeNodeData>(tr(""));
        output_data->SetData(OutputValue);
    }
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
    return tr("Shape Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Output Shape")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data){
        output_data->SetData(OutputValue);
    }
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};
