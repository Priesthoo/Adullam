#ifndef FLOATNODEDATA_HPP
#define FLOATNODEDATA_HPP
#include<NodeData>
using namespace QtNodes;
class FloatNodeData:public QtNodes::NodeData{
public:
float m_Data;
QString m_Name;
FloatNodeData(const QString& name):m_Name{name}{
    return;
}
FloatNodeData(const float& data,const QString& name):m_Data{data},m_Name{name}{
}
float Data() const{
    return m_Data;
}
void SetData(const float& data){
    m_Data=data;
    return;
}
NodeDataType type() const override{
    return {"float",m_Name};
}

};







#endif