#ifndef FLOAT_INPUT_DATA_HPP
#define FLOAT_INPUT_DATA_HPP
#include<FloatNodeData.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<FloatNodeWidget.hpp>
#include<NodeDescription.hpp>
#include<memory>
#include<iostream>
#include<DoubleLineEdit.hpp>
#include<iostream>
#include<QtCore/QJsonObject>
using QtNodes::NodeDelegateModel;
using namespace std;
class FloatInputNode :public NodeDelegateModel,public NodeInitializer{
private:
Q_OBJECT
//We have only one output  data
 
shared_ptr<FloatNodeData> output_data;
std::unique_ptr<DoubleEdit> double_edit;
float InputValue=1.0f;
public:
FloatInputNode(){
   return;
   
    
}
QJsonObject save() const override{
   QJsonObject object=NodeDelegateModel::save();
   object["InputValue"]=InputValue;
   return object;
}
void load(const QJsonObject& object) override{
     InputValue=object["InputValue"].toDouble(1.0);
      if(!double_edit.get()){
        double_edit.reset(new DoubleEdit(nullptr,QString::number(InputValue),8));
       QObject::connect(double_edit.get(),&DoubleEdit::GetValue,this,&FloatInputNode::OnReceiveValue);

    }
    
 double_edit->SetText(InputValue); 
 emit dataUpdated(0);
     return;
}
float GetData() const{
    if(output_data.get()){
   return output_data->Data();
    }
    return 0.0;
}
void SetFloatData(const float& data){
    if(output_data.get()){
        InputValue=data; 
        output_data->SetData(data);
    }
    else{
        InputValue=data;
        output_data.reset(new FloatNodeData(InputValue,tr("")));
}
   
    if(double_edit.get()){
        double_edit->setText(QString::number(data));
    }
    return;
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
    return tr("Float Data");
}
QString name() const override{
    return caption();
}
QString Desc() const{
    return tr("This is a node that consist of a Float data,it can be use to set the value of float or display the value");
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return FloatNodeData(InputValue,tr("")).type();
            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(!output_data.get()){
        output_data.reset(new FloatNodeData(InputValue,tr("")));
         return std::static_pointer_cast<NodeData>(output_data);
    }
    output_data->SetData(InputValue);
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
    if(!double_edit.get()){
        double_edit.reset(new DoubleEdit(nullptr,QString::number(InputValue),8));
       QObject::connect(double_edit.get(),&DoubleEdit::GetValue,this,&FloatInputNode::OnReceiveValue);

    }
    return double_edit.get();
 }
 

signals:
 void UpdateDataViaIndex(PortIndex const portIndex);
 void OnUpdateInput(const float& value);   //This updates the inputWidget on the screen;
public slots:
void OnReceiveValue(float value){
    InputValue=value;
    if(InputValue>=0.0 && InputValue<=0.9999999999){
        return;
    }
    emit dataUpdated(0); //update the output value
    emit OnUpdateInput(value);
    std::cout<<"Value Updated: "<<value<<std::endl;
    return;
}

};












#endif 