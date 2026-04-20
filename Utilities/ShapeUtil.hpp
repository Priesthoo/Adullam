#ifndef SHAPE_UTILITY_HPP
#define SHAPE_UTILITY_HPP
#include<TopoDS_Shape.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<TopAbs_ShapeEnum.hxx>
#include<Geom_struct.hpp>
#include<TopExp_Explorer.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<BRepBuilderAPI_MakeWire.hxx>
#include<BRepBuilderAPI_MakeFace.hxx>
#include<BRepPrimAPI_MakeBox.hxx>
#include<BRepPrimAPI_MakeCone.hxx>
#include<BRepPrimAPI_MakeCylinder.hxx>
#include<BRepPrimAPI_MakeTorus.hxx>
#include<BRepPrimAPI_MakeSphere.hxx>
#include<gp_Lin.hxx>
#include<Geom_Line.hxx>
#include<Geom_Curve.hxx>
#include<Geom_Circle.hxx>
#include<Geom_Ellipse.hxx>
#include<Geom_Hyperbola.hxx>
#include<Geom_Parabola.hxx>
#include<Geom_TrimmedCurve.hxx>
#include<Geom_BezierCurve.hxx>
#include<Geom_BSplineCurve.hxx>
#include<Geom_OffsetCurve.hxx>
#include<gp_Trsf.hxx>
#include<gp_Pnt.hxx>
#include<gp_Ax2.hxx>
#include<Precision.hxx>
#include<cmath>
//Shape Type
//0 -> COMPOUND
//1 -> COMPSOLID
//2 ->SOLID
//3-> SHELL
//4-> FACE
//5-> WIRE
//6-> EDGE
//7-> VERTEX
//8 -> SHAPE
const float EPSILON=1e-9;
const float PI=3.1428571;
namespace Shape_Utility{

inline void GetGeometryInfo(const Handle(AIS_Shape)& myShape,Geom_Struct& gstruct){
    if(myShape->Shape().ShapeType()==8){
        return;
    }
    switch(myShape->Shape().ShapeType()){
        case TopAbs_ShapeEnum::TopAbs_SOLID:{
           TopExp_Explorer exp(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_FACE);
           for(;exp.More();exp.Next()){
              ++gstruct.face_cnt;
           }
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp.More();exp.Next()){
             ++gstruct.edge_cnt;
           }
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp.More();exp.Next()){
            ++gstruct.vertex_cnt;
           }
           break;
        }
        case TopAbs_ShapeEnum::TopAbs_SHELL:{
            TopExp_Explorer exp(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_FACE);
           for(;exp.More();exp.Next()){
              ++gstruct.face_cnt;
           }
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp.More();exp.Next()){
             ++gstruct.edge_cnt;
           }
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp.More();exp.Next()){
            ++gstruct.vertex_cnt;
           }
           break;
        }
        case TopAbs_ShapeEnum::TopAbs_FACE:{
          TopExp_Explorer exp;
           gstruct.face_cnt=1;
           
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp.More();exp.Next()){
             ++gstruct.edge_cnt;
           }
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp.More();exp.Next()){
            ++gstruct.vertex_cnt;
           }
           break;
        }
        case TopAbs_ShapeEnum::TopAbs_WIRE:{
            TopExp_Explorer exp(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_FACE);
           for(;exp.More();exp.Next()){
              ++gstruct.face_cnt;
           }
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp.More();exp.Next()){
             ++gstruct.edge_cnt;
           }
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp.More();exp.Next()){
            ++gstruct.vertex_cnt;
           }
           break;
        }
        case TopAbs_ShapeEnum::TopAbs_EDGE:{
            TopExp_Explorer exp;
            gstruct.face_cnt=0;
           
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp.More();exp.Next()){
             ++gstruct.edge_cnt;
           }
           exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp.More();exp.Next()){
            ++gstruct.vertex_cnt;
           }
           break;
        }
        case  TopAbs_ShapeEnum::TopAbs_VERTEX:{
                TopExp_Explorer exp;
                  exp.Init(myShape->Shape(),TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp.More();exp.Next()){
            ++gstruct.vertex_cnt;
           }
           break;

        }
        default:{
            gstruct.face_cnt=0;
            gstruct.edge_cnt=0;
            gstruct.vertex_cnt=0;

        }
    }
    
    
    return;
}



inline TopoDS_Wire DrawRectangle(const gp_Pnt& pt,const float& length,const float& breadth){
   return TopoDS_Wire(); //return an empty wire
}
//By Default,All Object are drawn using gp_Ax2()
inline TopoDS_Shape DrawCube(const float& size,const gp_Ax2& axis=gp_Ax2()){
   TopoDS_Shape shape=BRepPrimAPI_MakeBox(axis,size,size,size).Shape();
   return shape;
}
inline TopoDS_Shape DrawCone(const float& bottomradius,const float& topradius,const float& height,const gp_Ax2& axis=gp_Ax2()){
   TopoDS_Shape shape=BRepPrimAPI_MakeCone(axis,bottomradius,topradius,height).Shape();
   return shape;
}
inline TopoDS_Shape DrawCylinder(const float& bottomRadius,const float& height,const gp_Ax2& axis=gp_Ax2()){
   TopoDS_Shape shape=BRepPrimAPI_MakeCylinder(axis,bottomRadius,height).Shape();

   return shape;
}
//we are stil going to draw different shapes...
inline TopoDS_Shape DrawSphere(const float& r,const gp_Ax2& axis=gp_Ax2()){
   TopoDS_Shape shape=BRepPrimAPI_MakeSphere(axis,r).Shape();
   return shape;
 }
 inline TopoDS_Shape DrawTorus(const float& radius,const float& radius2,const gp_Ax2& axis=gp_Ax2()){
    TopoDS_Shape shape=BRepPrimAPI_MakeTorus(axis,radius,radius2).Shape();
   return shape;
 }

inline TopoDS_Shape DrawCuboid(const float& sz_1,const float& sz_2,const float& sz_3,const gp_Ax2& axis=gp_Ax2()){
   return BRepPrimAPI_MakeBox(axis,sz_1,sz_2,sz_3).Shape();
}
inline bool IsEdge(const TopoDS_Shape& shape){
     if(shape.ShapeType()==TopAbs_ShapeEnum::TopAbs_EDGE){
        return true;
     }
   return false;
}
inline TopoDS_Edge DrawBoundedLine(const gp_Pnt& startPoint,const gp_Dir& dir,const double& p1,const double& p2){
    Handle(Geom_Line) line=new Geom_Line(startPoint,dir); //infinite line in a particular direction specified by dir.

    BRepBuilderAPI_MakeEdge edgeMaker;
    edgeMaker.Init(line,p1,p2); //then bound it in a particular direction
    if(edgeMaker.IsDone()){
      return edgeMaker.Edge();
    }
    return TopoDS_Edge();
}
inline TopoDS_Edge DrawLine(const gp_Pnt& startPoint,const gp_Pnt& endPoint){
    BRepBuilderAPI_MakeEdge edgeMaker(startPoint,endPoint); 
    if(edgeMaker.IsDone()){
      return edgeMaker.Edge();
    }
    
    return TopoDS_Edge();
}
inline TopoDS_Edge DrawCircle(const gp_Ax2& dir,const double& radius){
   Handle(Geom_Circle) circle=new Geom_Circle(dir,radius);
     BRepBuilderAPI_MakeEdge edgeMaker(circle);
     if(edgeMaker.IsDone()){
      return edgeMaker.Edge();
     } 
   return TopoDS_Edge(); //return an empty constructor...
}
}















#endif