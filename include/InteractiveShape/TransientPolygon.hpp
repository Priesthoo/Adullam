#pragma once 
#include<TransientVisualObject.hpp>
#include<BRepBuilderAPI_MakePolygon.hxx>
#include<NCollection_Array1.hxx>
#include<vector>
#include<TColgp_HArray1OfPnt.hxx>
using namespace std;
class TransientPolygon:public TransientVisualObject{
private:
BRepBuilderAPI_MakePolygon polygonBuilder;
Handle(TColgp_HArray1OfPnt) handle_points;
std::vector<gp_Pnt> points;


public:
TransientPolygon():TransientVisualObject(){
  return;
}
TransientPolygon( Handle(AIS_InteractiveContext)& con):TransientVisualObject(con){
   return;
}
void RemoveLastPoint(){
    points.pop_back();
    return;
}
std::vector<gp_Pnt> Points() const{
    return points;
}
void AddPoint(const gp_Pnt& pnt){
    points.emplace_back(pnt.X(),pnt.Y(),pnt.Z());
    return;
}
void Clear(){
    points.clear();
    return;
}
void BuildShape() override{
    if(CheckDisplayStatus(DisplayedShape())){
        RemoveShape();
    }
    BRepBuilderAPI_MakePolygon polygonBuilder;
    for(int i=0;i<points.size();i++){
         polygonBuilder.Add(points[i]);
    }
    if(!polygonBuilder.IsDone()){
        return;
    }
    if(!DisplayedShape().IsNull()){
        SetShape(polygonBuilder.Wire());
    }
    else{
    SetDisplayedShape(new CustomAIS_Shape(polygonBuilder.Wire()));
    }
    DisplayShape();
    return;
}
TopoDS_Wire BuiltShape(){
    BRepBuilderAPI_MakePolygon polygonBuilder;
    for(int i=0;i<points.size();i++){
         polygonBuilder.Add(points[i]);
    }
    if(!polygonBuilder.IsDone()){
        return TopoDS_Wire();
    }
  return  polygonBuilder.Wire();
}
NCollection_Array1<gp_Pnt> To_Array_One(){
    return NCollection_Array1<gp_Pnt>(points.front(),0,static_cast<int>(points.size()-1));
}
void SetHandlePoints(){
    if(handle_points){
        handle_points.Nullify();
    }
    handle_points=new TColgp_HArray1OfPnt(0,static_cast<int>(points.size()-1),points.front());
  return;
}
Handle(TColgp_HArray1OfPnt) GetArrayPoints() const{
    return handle_points;
}
};