#ifndef DIRECTION_NODE_DATA_HPP
#define DIRECTION_NODE_DATA_HPP
#include<NodeData>
#include<gp_Dir.hxx>
using namespace std;
using namespace QtNodes;
class DirectionNodeData:public NodeData{
private:
gp_Dir m_Data;
QString m_Name;


public:
DirectionNodeData(const QString& name){
    m_Name=name;
    return;
}
DirectionNodeData(const float& dir_x,const float& dir_y,const float& dir_z,const QString& name):m_Data(dir_x,dir_y,dir_z),m_Name{name}{

}
gp_Dir Data() const{
    return m_Data;
}
void SetData(const gp_Dir& dir){
    m_Data.SetX(dir.X());
    m_Data.SetY(dir.Y());
    m_Data.SetZ(dir.Z());
    return;
}
NodeDataType type() const override{
    return {"Direction",m_Name};
} 

};









#endif