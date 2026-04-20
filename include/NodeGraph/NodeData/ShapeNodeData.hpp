#ifndef SHAPENODEDATA_HPP
#define SHAPENODEDATA_HPP
#include<NodeData>
#include<TopoDS_Shape.hxx>
#include<Graphic3d_MaterialAspect.hxx>
using namespace QtNodes;
class ShapeNodeData:public NodeData{
    private:
    TopoDS_Shape m_Data;
     Graphic3d_MaterialAspect mat_aspect;
   
    QString m_Name;
    bool hasMaterial=false;  //ByDefault the object has no material
 public:
 static int shapeCounter;   //it belongs to this class and not to an object of Shape
 ShapeNodeData(const QString& name=QString(""),const TopoDS_Shape& shape=TopoDS_Shape()):m_Name(name){
     m_Data=shape;
 }
 ShapeNodeData(const ShapeNodeData&& data){
  *this=std::move(data);
  return;
 }
 ShapeNodeData(const ShapeNodeData& data){
   *this=data;
   return;
 }
 TopoDS_Shape Data() const{
    return m_Data;
 }
 void SetTransform(const gp_Trsf& trsf){
    m_Data.Location(trsf);
    return;
 }
 void SetData(const TopoDS_Shape& shape){
   m_Data=shape;
   return;
 }
 void SetHasMaterialAspect(const bool& truth){
    hasMaterial=truth;
    return;
 }
 bool HasMaterial() const{
  return hasMaterial;
 }
 void SetHasMaterial(bool truth){
   hasMaterial=truth;
   return;
 }

 Graphic3d_MaterialAspect aspect() const{
   return mat_aspect;
 }
 void SetAspect(const Graphic3d_MaterialAspect& mat){
   mat_aspect=mat;
   return;
 }
 NodeDataType type() const override{
    return {"Shape",m_Name};
 }
 ShapeNodeData& operator=(const ShapeNodeData&& data){
   m_Data=std::move(data.Data());
   
   return *this;
 }
 ShapeNodeData& operator=(const ShapeNodeData& shapedata){
   m_Data=shapedata.Data();
   SetAspect(shapedata.aspect());
   SetHasMaterial(shapedata.HasMaterial());
   return *this;
 }
};
#endif