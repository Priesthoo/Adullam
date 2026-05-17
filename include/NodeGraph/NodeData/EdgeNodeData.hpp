#pragma once
#include<NodeData>
#include<TopoDS_Edge.hxx>
#include<ParentShapeNodeData.hpp>
using namespace QtNodes;
class EdgeNodeData:public NodeData{
    private:
    EdgePair m_Data;
    QString m_Name;
    public:
    EdgeNodeData()=default;
    EdgeNodeData(const QString& name){
        m_Name=name;
        return;
    }
    void SetData(const EdgePair& edge){
        m_Data=edge;
        return;
    }
    void SetEdge(const TopoDS_Edge& edge){
        m_Data.SetEdge(edge);
    }
    TopoDS_Edge edge() const{
        return m_Data.Edge();
    }
    EdgePair Data() const{
        return m_Data;
    }
    EdgePair& GetData() {
        return m_Data;
    }
    NodeDataType type() const override{
        return{"Edge",m_Name};
    }
};