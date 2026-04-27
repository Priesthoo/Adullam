#pragma once
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<memory>
#include<BooleanNodeData.hpp>
#include<QtWidgets/QCheckBox>
#include<QtCore/QJsonObject>
using QtNodes::NodeDelegateModel;

using namespace std;
class BooleanNode:public NodeDelegateModel,public NodeInitializer{
private:
    Q_OBJECT
public:

shared_ptr<BooleanNodeData> output_data;
std::unique_ptr<QCheckBox> checkBox;
bool InputValue=false;

BooleanNode(){

}
bool GetInputValue() const{
    if(output_data.get()){
        return output_data->Data();
    }
    return false;
}
QJsonObject save() const override{
    QJsonObject object=NodeDelegateModel::save();
    object["Value"]=InputValue;
    return object;
}
void load(const QJsonObject& object) override{
    InputValue=object["Value"].toBool();
    emit dataUpdated(0);
    return;
}
void SetInputValue(const bool& value){
    if(output_data.get()){
        InputValue=value;
        output_data->SetData(value);
       
    }
    else{
        InputValue=value;
        output_data.reset(new BooleanNodeData(value,tr("")));
    }
    if(checkBox.get()){
        checkBox->setChecked(value);
    }
     emit dataUpdated(0);
    return;
}
unsigned int nPorts(PortType portType) const override{
      switch(portType){
        case PortType::Out:{
            return 1;  //number of output port 
        }
        default:
           return 0;
    }
    return 0;
}
QString caption() const override{
    return tr("Boolean Data");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return BooleanNodeData(InputValue,tr("Value")).type();
            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(!output_data.get()){
        output_data.reset(new BooleanNodeData(InputValue,tr("")));
         return std::static_pointer_cast<NodeData>(output_data);
    }
    
    return static_pointer_cast<NodeData>(output_data);
}

void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}

QWidget* embeddedWidget() override{ 
    if(!checkBox.get()){
        checkBox=std::make_unique<QCheckBox>(tr(""),nullptr);
        checkBox->setCheckable(true);
        QObject::connect(checkBox.get(),&QCheckBox::toggled,this,&BooleanNode::OnSetInputValue);

    }
    return checkBox.get();
 }

signals:
void OnUpdateBoolValue(const bool& value);

public slots:
void OnSetInputValue(const bool& value){
    InputValue=value;
   if(output_data.get()){
     output_data->SetData(value);
   }

    emit dataUpdated(0);
    emit OnUpdateBoolValue(value);
    return;
}


};
