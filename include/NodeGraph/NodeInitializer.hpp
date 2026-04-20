//All nodes DelegateModel will inherit this,
#pragma once
#include<QtCore/QString>
#include<NodeDelegateModel>
using QtNodes::NodeDelegateModel;


class NodeInitializer{
    QString NodeDescription;
public:

NodeInitializer(){

}
virtual void Initialize(NodeDelegateModel* model){
    return;
}
void SetNodeDescription(const QString& value){
    NodeDescription=value;
    return;
}
QString nodeDescription() const{
    return NodeDescription;
}
virtual ~NodeInitializer()=default;
};