#pragma once
#include<NodeData>
#include<TopoDS_Vertex.hxx> 
#include<ParentShapeNodeData.hpp>
using namespace QtNodes;

class VertexNodeData:public NodeData{
 private:
 VertexPair m_Data;
 QString m_Name;
 public:
 VertexNodeData(const QString& name){
   m_Name=name;
   return;
 }
 void SetData(const VertexPair& vert ){
    m_Data=vert;
    return;
 }
 VertexPair Data() const{
    return m_Data;
 }
 VertexPair& GetData(){
   return m_Data;
 }
 NodeDataType type() const override{
    return {"Vertex",m_Name};
 }
};