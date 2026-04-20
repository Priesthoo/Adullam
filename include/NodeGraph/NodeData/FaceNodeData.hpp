#pragma once 
#include<NodeData>
#include<TopoDS_Face.hxx>
#include<ParentShapeNodeData.hpp>
using namespace QtNodes;
class FaceNodeData:public NodeData{
  private:
  FacePair m_Data;
  QString m_Name;
  public:
  FaceNodeData()=default;
  FaceNodeData(const QString& name){
    m_Name=name;
  }  
  void SetData(const FacePair& face){
    m_Data=face;
    return;
  }
  void SetFaceData(const TopoDS_Face& face){
     m_Data.SetFace(face);
     return;
  }
  FacePair Data() const{
    return m_Data;
  }
  FacePair& GetData(){
    return m_Data;
  }
  NodeDataType type() const override{
    return {"Edge",m_Name};
}
};