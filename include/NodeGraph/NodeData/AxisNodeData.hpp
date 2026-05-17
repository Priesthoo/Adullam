#ifndef AXIS_NODE_DATA_HPP
#define AXIS_NODE_DATA_HPP
#include<NodeData>
#include<gp_Ax2.hxx>
#include<gp_Dir.hxx>
#include<gp_Pnt.hxx>
using namespace QtNodes;
class AxisNodeData:public NodeData{
private:

gp_Ax2  Axis;
QString m_Name;

public:
AxisNodeData(const QString& name):m_Name(name){
    return;
}
AxisNodeData(const float& x_dir,const float& y_dir,const float& z_dir,const float& p_x,const float& p_y,const float& p_z,const QString& name):Axis(gp_Pnt(p_x,p_y,p_z),gp_Dir(x_dir,y_dir,z_dir)),m_Name(name){
    return;
}
AxisNodeData(const gp_Pnt& point,const gp_Dir& dir,const QString& name):Axis(point,dir),m_Name{name}{
    return;
}                                                                                                               
NodeDataType type() const override{
    return {"Axis",m_Name};
}
gp_Ax2 Data() const {
    return Axis;
}
void SetData(const gp_Pnt& point,const gp_Dir& dir){
    Axis.SetDirection(dir);
    Axis.SetLocation(point);
    return;
}
void SetData(const gp_Ax2& axis){
    Axis=axis;
    return;
}
void SetOriginData(const gp_Dir& dir){
    Axis.SetDirection(dir);
    Axis.SetLocation(gp_Pnt(0.0,0.0,0.0));
    return;
}
};



#endif