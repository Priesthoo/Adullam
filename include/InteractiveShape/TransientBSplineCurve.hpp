#pragma once 
#include<TransientVisualObject.hpp>
#include<GeomAPI_Interpolate.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<Geom_BSplineCurve.hxx>
#include<GeomAPI_PointsToBSpline.hxx>
#include<TransientPolygon.hpp>
#include<InfoUtility.hpp>
#include<memory>
using namespace std;
using namespace INFO;

class TransientBSplineCurve:public TransientVisualObject{
 private:
 std::unique_ptr<TransientPolygon> polygon;
 bool isPeriodic=false; //it is not periodic by default

 public:
 TransientBSplineCurve(Handle(AIS_InteractiveContext)& con):TransientVisualObject(con){
    polygon=std::make_unique<TransientPolygon>(con);
    return;
 }
 void AddBSplinePoles(const gp_Pnt& point){
    polygon->AddPoint(point);
    return;
 }
 void BuildShape() override{
   
    if(polygon->Points().size()<2){
        return;
    }
    
    return;
 }
 void SetIsPeriodic(bool value){
    isPeriodic=value;
    return;
 }
 bool IsPeriodic() const{
    return isPeriodic;
 }
  TransientPolygon* Polygon() const{
    return polygon.get();
  } 
};