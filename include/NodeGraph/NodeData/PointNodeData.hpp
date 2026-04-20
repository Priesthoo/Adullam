#ifndef POINT_NODE_DATA_HPP
#define POINT_NODE_DATA_HPP
#include<gp_Pnt.hxx>
#include<Point.hpp>
#include<NodeData>
using namespace QtNodes;
class PointNodeData:public NodeData{
private:
Point point_3d;
QString m_Name;
public:
PointNodeData(const QString& strName=QString("")){
   m_Name=strName;
}
PointNodeData(const float& p_x,const float& p_y,const float& p_z,const QString name):point_3d(p_x,p_y,p_z),m_Name{name}{
}
Point Data() const{
    return point_3d;
}
NodeDataType type () const override{
    return {"3dPoint",m_Name};
}
gp_Pnt ToPnt(){
    return gp_Pnt(point_3d.X(),point_3d.Y(),point_3d.Z());
}
void SetData(const Point& pnt){
    point_3d.SetX(pnt.X());
    point_3d.SetY(pnt.Y());
    point_3d.SetZ(pnt.Z());
    return; 
}


};











#endif