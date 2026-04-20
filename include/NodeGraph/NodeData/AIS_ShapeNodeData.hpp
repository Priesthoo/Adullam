#ifndef AIS_SHAPE_NODE_DATA_HPP
#define AIS_SHAPE_NODE_DATA_HPP
#include<NodeData>
#include<MyCustomAIS_Shape.hxx>
using namespace QtNodes;
class AIS_ShapeNodeData:public NodeData{
private:
Handle(CustomAIS_Shape) m_Data;
QString m_Name;

public:
AIS_ShapeNodeData(const QString& name):m_Name(name){

}
void SetData(const Handle(CustomAIS_Shape)& shape){
    m_Data=shape;
    return;
}
Handle(CustomAIS_Shape) Data() const{
    return m_Data;
}
NodeDataType type() const override{
     return {"Displayed_Shape",m_Name};
}
};



#endif