#ifndef INTEGER_NODE_DATA_HPP
#define INTEGER_NODE_DATA_HPP
#include<NodeData>
using namespace QtNodes;
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