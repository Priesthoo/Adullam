#pragma once
#include<NodeData>
#include<TopoDS_Shape.hxx>
#include<TopoDS_Wire.hxx>
using namespace QtNodes;
class WireNodeData:public NodeData {
private:
TopoDS_Wire m_Data;
QString m_Name;

public:
WireNodeData(const QString& name=QString("")):m_Name{name}{
    return;
}
void SetData(const TopoDS_Wire& wire){
    m_Data=wire;
    return;
}
TopoDS_Wire Data() const{
    return m_Data;
}
NodeDataType type() const override{
    return {"Wire",m_Name};
}
};