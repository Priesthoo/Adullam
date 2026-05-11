#pragma once
#include<TransientVisualObject.hpp>
#include<Geom_BezierCurve.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<TransientPolygon.hpp>
#include<InfoUtility.hpp>
#include<memory>
using namespace std;
using namespace INFO;
class TransientBezierCurve:public TransientVisualObject{
 private:
 std::unique_ptr<TransientPolygon> polygon;
 


 public:
 TransientBezierCurve(Handle(AIS_InteractiveContext)& con):TransientVisualObject{con}{
    polygon=make_unique<TransientPolygon>(con);
    
 }
 void AddBezierPoles(const gp_Pnt& point){
    polygon->AddPoint(point);
    return;
 }
 void BuildShape() override{
    polygon->BuildShape();
    if(polygon->Points().size()<2){
        return;
    }
    Handle(Geom_BezierCurve) curve=new Geom_BezierCurve(polygon->To_Array_One());
    if(curve.IsNull()){
       LoadMessage(QString("Curve Status"),QString("Failed To Construct Curve"));
       return;
    }
    BRepBuilderAPI_MakeEdge edge(curve);
    if(edge.Error()!=BRepBuilderAPI_EdgeDone){
        LoadMessage(QString("Edge Error"),QString("Failed To Construct Edge"));
       return;
    }
     if(!DisplayedShape().IsNull()){
        SetShape(edge.Edge());
    }
    else{
    SetDisplayedShape(new CustomAIS_Shape(edge.Edge()));
    }
    DisplayShape();
 }
  TransientPolygon* Polygon() const{
    return polygon.get();
  } 
  
};
//OnGatherBezier 
//OnDeleteBezier
