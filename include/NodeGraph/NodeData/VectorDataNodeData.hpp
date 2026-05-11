#pragma once
#include<vector>
#include<NodeData>
using namespace QtNodes;
using namespace std;
//Maximum of 5 elements,call m_Data.reserve(100); //For Multiple node
template<class T>
class VectorDataNode:public QtNodes::NodeData{
public:
std::vector<T> m_Data;
QString m_Name;
QString m_Type;
bool isReserved=false;
VectorDataNode(const QString& name=QString(),const QString& type=QString(),const size_t& re_num=10):m_Name{name},m_Type{type}{
   m_Data.reserve(re_num);
   isReserved=true;
}
std::vector<T>& Data(){
    return m_Data;
}
T GetValue(const int& index){
    return m_Data.at(index);
}
void SetData(const std::vector<T>& vec){
    m_Data=vec;
    return;
}
bool Empty() const{
    return m_Data.empty();
}
size_t Capacity() const{
    return m_Data.capacity();
}
size_t Size() const{
    return m_Data.size();
}
NodeDataType type() const{
    return {m_Type,m_Name};
}

};