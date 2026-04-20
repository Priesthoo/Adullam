#pragma once
#include<NodeData>
#include<Quantity_Color.hxx>
using namespace QtNodes;
class ColorNodeData:public NodeData{
private:
Quantity_Color m_Data;
QString m_Name;

public:
ColorNodeData(){
 return;
}
ColorNodeData(const QString& name){
  m_Name=name;
  return;
}
void SetData(const Quantity_Color& color){
    m_Data=color;
    return;
}
void SetName(const QString& name){
     m_Name=name;
  return;
}
Quantity_Color Data() const{
    return m_Data;
}
NodeDataType type() const override{
    return {"Color",m_Name};
}
};