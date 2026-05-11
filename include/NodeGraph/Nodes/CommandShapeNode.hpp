#pragma once 
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<JsonShapeConverter.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace JsonConverter;
class CommandShape:public NodeDelegateModel{
 private:
 std::shared_ptr<ShapeNodeData>output_data;
 TopoDS_Shape shape=TopoDS_Shape();
 QString fileName=QString();


 public:
 CommandShape(){
    
 }
 QJsonObject save() const{
    QJsonObject object=NodeDelegateModel::save();
    object["Cmd_Shape"]=ToString(shape);
    object["File Path"]=fileName;

    return object;
 }
 void load(const QJsonObject& object) override{
    auto value=object["Cmd_Shape"].toString();
    fileName=object["File Path"].toString();
    shape=ToMainShape(value);
    SetShape(shape);
    return;
 }
 void SetFileName(const QString& file){
    fileName=file;
    return;
 }
 QString GetFileName() const{
    return fileName;
 }
 TopoDS_Shape Shape() const{
    return shape;
 }
 void SetShape(const TopoDS_Shape& sh){
    shape=sh;
    if(output_data){
        output_data->SetData(shape);
    }
    else{
        output_data=std::make_shared<ShapeNodeData>(tr(""));
        output_data->SetData(shape);
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
    return tr("Cmd Shape Node");
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
        output_data->SetData(shape);
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