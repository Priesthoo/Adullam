#ifndef INTEGER_NODE_DATA_HPP
#define INTEGER_NODE_DATA_HPP
#include<NodeData>
using namespace QtNodes;
template<class T>
class TemplatedData:public NodeData{
private:
T m_Data;
QString m_Name;
QString m_Type;
public:
TemplatedData(const QString& name=QString(),const QString& type=QString()){
    m_Name=name;
    m_Type=type;
    return;
}
TemplatedData(const TemplatedData& data){
   m_Data=data.Data();
   return;
}
T Data() const{
    return m_Data;
}
TemplatedData& operator=(const TemplatedData& data){
    m_Data=data.Data();
    return *this;
}
TemplatedData& operator=(const T& data){
    m_Data=data;
    return *this;
}
NodeDataType type() const override{
    return {m_Type,m_Name};
}
};
class IntegerNodeData:public NodeData{
private:
int m_Data;
QString m_Name;
public:
IntegerNodeData(const int& data,const QString& name):m_Data(data),m_Name{name}{

}
int Data() const{
    return m_Data;
}
NodeDataType type() const override{
    return {"Integer",m_Name};
}

};









#endif