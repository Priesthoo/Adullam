#ifndef PARENT_SHAPE_NODE_DATA_HPP
#define PARENT_SHAPE_NODE_DATA_HPP
#include<NodeData>
#include<ParentShape.hpp>
#include<optional>
using namespace QtNodes;
class ParentShapeNodeData:public NodeData{
private:
std::optional<std::reference_wrapper<ShapePair>> shape; //we could either use a reference or a pointer to store the PrimitiveShapeNode's shape's Shape();
QString m_Name;

public:
ParentShapeNodeData(const QString& name=QString(""),ShapePair* parent=nullptr){
    m_Name=name;
}
void SetShape(ShapePair& sh){
    shape.emplace(sh);
    return;
}
std::optional<std::reference_wrapper<ShapePair>>& GetShape(){
    return shape;
}
ShapePair& GetOwnShape(){  //pls shape should check if it has value
    return shape.value().get();
}
NodeDataType type() const override{
    return {"Parent Shape",m_Name};
}
~ParentShapeNodeData(){
    
}
};












#endif 