#pragma once 
#include<NodeData>
#include<Graphic3d_MaterialAspect.hxx>
using namespace  QtNodes;
class MaterialNodeData:public NodeData{
private:
Graphic3d_MaterialAspect m_Data;
QString m_Name;
public:
MaterialNodeData(const QString& name){
   m_Name=name;
}
void SetData(const Graphic3d_MaterialAspect& mat_asp){
    m_Data=mat_asp;
    return;
}
void SetDiffuse(const Quantity_Color& color){
     m_Data.SetDiffuseColor(color);
     return;
}
void SetAmbient(const Quantity_Color& color){
    m_Data.SetAmbientColor(color);
    return;
}
void SetSpecular(const Quantity_Color& color){
    m_Data.SetSpecularColor(color);
    return;
}
void SetEmissive(const Quantity_Color& color){
    m_Data.SetEmissiveColor(color);
    
    return;
}
void SetShine(const float& value){
    m_Data.SetShininess(value);
    return;
}
void SetTransValue(const float& value){
    m_Data.SetTransparency(value);
    return;
}
void SetRefractIndex(const float& value){
    m_Data.SetRefractionIndex(value);
    return;
}

Graphic3d_MaterialAspect Data() const{
    return m_Data;
}
Graphic3d_MaterialAspect& GetData(){
    return m_Data;
}

NodeDataType type() const override{
    return {"Material",m_Name};
}

};