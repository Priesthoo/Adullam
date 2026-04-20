#ifndef BOOLEAN_NODE_DATA_HPP
#define BOOLEAN_NODE_DATA_HPP
#include<NodeData>

using namespace QtNodes;
class BooleanNodeData:public QtNodes::NodeData{
public:
bool m_Data;
QString m_Name;
BooleanNodeData(){}
BooleanNodeData(const bool& data,const QString& name):m_Data{data},m_Name{name}{
    return;
}
bool Data() const{
    return m_Data;
}
void SetData(const bool& value){
    m_Data=value;
    return;
}
NodeDataType type() const override{
    return {"boolean",m_Name};
}
};










#endif 