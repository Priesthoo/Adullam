#pragma once
#include<BRepAdaptor_Curve.hxx>//For curves in 3d Space
#include<BRepAdaptor_Curve2d.hxx> //For curves that lie on the surface(Getting their parametric value)
#include<GCPnts_AbscissaPoint.hxx> //To Get their midpoints
#include<Adaptor3d_CurveOnSurface.hxx> //For curves on surfaces(Getting their 3d Points)
#include<TopoDS_Edge.hxx>
#include<BRep_Tool.hxx>
#include<QtCore/QString>
namespace EDGE{
 inline QString GetEdgeType(const TopoDS_Edge& edge){
    BRepAdaptor_Curve curve(edge);
    switch(curve.GetType()){
        case GeomAbs_Line:
          return QString("Line");
        case GeomAbs_Circle:
          return QString("Circle");
        case GeomAbs_Ellipse:
           return QString("Ellipse");
        case GeomAbs_Hyperbola:
           return QString("Hyperbola");
        case GeomAbs_Parabola:
          return QString("Parabola");
        case GeomAbs_BezierCurve:
          return QString("Bezier Curve");
        case GeomAbs_BSplineCurve:
          return QString("B-Spline Curve");
        case GeomAbs_OffsetCurve:
          return QString("Offset Curve");
        case GeomAbs_OtherCurve:
          return QString("Other Curve");
        default:
           return QString("No Curve");
    }
    return QString("");
   }
inline QString EdgeIsOnSurface(const TopoDS_Edge& edge){
    BRepAdaptor_Curve curve(edge);
    if(edge.IsCurveOnSurface()){
        return QString("True");
    }
    return QString("False");
   }
 inline QString Is3dCurve(const TopoDS_Edge& edge){
      BRepAdaptor_Curve curve(edge);
      if(curve.Is3dCurve()){
        return QString("True");
      }
      return QString("False");
   }
 inline QString GetContinuity(const TopoDS_Edge& edge){
     BRepAdaptor_Curve curve(edge);
     switch(curve.Continuity()){
        case GeomAbs_C0:
          return QString("C0");
        case GeomAbs_G1:
          return QString("G1");
        case GeomAbs_C1:
          return QString("C1"); 
        case GeomAbs_G2:
          return QString("G2");
        case GeomAbs_C2: 
          return QString("C2");
         case GeomAbs_C3:
          return QString("C3");   
         case GeomAbs_CN:
          return QString("CN");   
     }
    
    
    return QString("No Continuity");
 }
 struct EdgeInfo{
  QString EdgeType;
  QString Is3dCurve;
  QString IsOnSurface;
  QString Continuity;
  int Degree; //number of degrees
  int NbPoles; //number of poles;
  int NbKnots; //number of knots
  float Umin;
  float Umax;
  float Tolerance;
  float Period;

  bool IsClosed;
  bool IsPeriodic;
  bool IsRational;
 };

 inline void GetEdgeInfo(const TopoDS_Edge& edge,EdgeInfo& info){
    info.EdgeType=EDGE::GetEdgeType(edge);
    info.Is3dCurve=EDGE::Is3dCurve(edge);
    info.IsOnSurface=EDGE::EdgeIsOnSurface(edge);
    info.Continuity=EDGE::GetContinuity(edge);
    
    BRepAdaptor_Curve curve(edge);
    info.Degree=curve.Degree();
    info.NbPoles=curve.NbPoles();
    info.NbKnots=curve.NbKnots();
    info.Umin=curve.FirstParameter();
    info.Umax=curve.LastParameter();
    info.Tolerance=curve.Tolerance();
    info.Period=curve.Period();

    info.IsClosed=curve.IsClosed();
    info.IsPeriodic=curve.IsPeriodic();

   return;
 
 
 }
 inline gp_Pnt GetEdgeMidPoint(const TopoDS_Edge& edge){
   

    return gp_Pnt();
 }
}









