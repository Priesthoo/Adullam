#pragma once
#include<gp_Trsf.hxx>
#include<BRepBuilderAPI_GTransform.hxx>
#include<BRepBuilderAPI_Transform.hxx>
#include<gp_GTrsf.hxx>
#include<NodeData>
using namespace QtNodes;
class TransformNodeData:public NodeData{
    private:
    gp_Trsf m_Data;
    QString name;
    public:
    TransformNodeData(const QString& m_Name,const gp_Trsf& trans=gp_Trsf()){
         name=m_Name;

    }
  void SetData(const gp_Trsf& trsf){
    m_Data=trsf;
    return;
  }
  gp_Trsf Data() const{
    return m_Data;
  }
  NodeDataType type() const override{
    return {"Transform",name};
  }
};

