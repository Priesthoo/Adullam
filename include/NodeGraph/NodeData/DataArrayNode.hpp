#ifndef DATA_ARRAY_NODE_HPP
#define DATA_ARRAY_NODE_HPP
#include<NodeData>
#include<array>
using namespace QtNodes;

template<size_t N, class T>
class DataArrayNode:public QtNodes::NodeData{
public:
std::array<T,N> m_Data{};
QString m_Name;  //Name to be presented on the nodes
QString m_Type;  //Type for Array
size_t NbElement=N;   //number of elements
DataArrayNode(const QString& name,const QString& type):m_Name{name},m_Type{type}{

}
void SetValueAt(const int& idx,const T& value){
    if(idx > N){
        return;
    }
    if(idx < 0){
        return;
    }
   m_Data[idx]=value;
   return;
}
T GetValueAt(const int& idx) const{
     return m_Data.at(idx);   
}

std::array<T,N> Data() const{
    return m_Data;
}
size_t Size() const{
    return NbElement;
}
void SetData(const std::array<T,N>& arr){
    m_Data=arr;
    return;
}
NodeDataType type() const{
    return {m_Type,m_Name};
}

};













#endif