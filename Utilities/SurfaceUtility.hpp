#pragma once 
#include<Geom_Surface.hxx>
#include<QtCore/QString>
#include<Geom_ElementarySurface.hxx>
#include<Geom_BSplineSurface.hxx>
#include<Geom_BezierSurface.hxx>
#include<Geom_RectangularTrimmedSurface.hxx>
#include<Geom_ConicalSurface.hxx>
#include<Geom_CylindricalSurface.hxx>
#include<Geom_Plane.hxx>
#include<Geom_SphericalSurface.hxx>
#include<Geom_ToroidalSurface.hxx>
#include<Geom_SurfaceOfLinearExtrusion.hxx>
#include<Geom_SurfaceOfRevolution.hxx>
#include<BRepTopAdaptor_FClass2d.hxx>
#include<BRepAdaptor_Surface.hxx>
#include<Geom_Line.hxx>
#include<Geom_Curve.hxx>
#include<GeomAPI_IntCS.hxx>
#include<gp_Lin.hxx>
#include<BRep_Tool.hxx>
#include<TopLoc_Location.hxx>
#include<gp_Trsf.hxx>
#include<gp_Dir.hxx>
#include<gp_Pnt.hxx>
#include<QtCore/QString>
#include<IntTools_Context.hxx>
#include<BRepExtrema_DistShapeShape.hxx>
#include<BRepBuilderAPI_MakeVertex.hxx>
#include<GProp_GProps.hxx>
#include<BRepGProp.hxx>
#include<BRepClass_FaceClassifier.hxx>
#include<iostream>
//this will provide information of a surface
using namespace std;
namespace SURFACE{
   inline QString GetSurfaceType(const TopoDS_Face& face){
     BRepAdaptor_Surface surface(face);
    
     switch(surface.GetType()){
        case GeomAbs_Plane:
           return QString("Planar Surface");
        case GeomAbs_Cylinder:
          return QString("Cylindrical Surface");
        case GeomAbs_Cone:
          return QString("Conical Surface");
        case GeomAbs_Sphere:
          return QString("Spherical Surface");
        case GeomAbs_Torus:
           return QString("Toriodial Surface");
        case GeomAbs_BezierSurface:
           return QString("Bezier Surface");
        case GeomAbs_BSplineSurface:
           return QString("B-Spline Surface");
        case GeomAbs_SurfaceOfRevolution:
           return QString("Surface Of Revolution");
        case GeomAbs_SurfaceOfExtrusion:
           return QString("Surface Of Extrusion");
        case GeomAbs_OffsetSurface:
           return QString("Surface Of Offset");
        case GeomAbs_OtherSurface:
           return QString("Other Surface");
        default:
          return QString("No Face");
     }
    
    return QString("No Surface");
   }
   struct SurfaceInfo{
     QString surfaceType;
     unsigned int index=0; //0 is an invalid index
     float Umin;
     float Umax;
     float Vmin;
     float Vmax;
     float Vperiod;
     float Uperiod;
     float surfaceTol;  //surface tolerance
     bool IsUClosed;
     bool IsVClosed;
     bool IsUPeriodic;
     bool IsVPeriodic;
     
     
   };
   struct SurfaceIntersect_Info{
      gp_Pnt int_point; //intersection point
      double U; //the respective U parameter
      double V; //the respective V parameter

   };

 inline  void GetSurfaceInfo(const TopoDS_Face& face,SurfaceInfo& info){
    info.surfaceType=SURFACE::GetSurfaceType(face);
    BRepAdaptor_Surface surface(face);
    info.Umin=surface.FirstUParameter();
    info.Umax=surface.LastUParameter();
    info.Vmin=surface.FirstVParameter();
    info.Vmax=surface.LastVParameter();
    info.Vperiod=surface.VPeriod();
    info.Uperiod=surface.UPeriod();
    info.surfaceTol=surface.Tolerance();
    info.IsUClosed=surface.IsUClosed();
    info.IsVClosed=surface.IsVClosed();
    info.IsUPeriodic=surface.IsUPeriodic();
    info.IsVPeriodic=surface.IsVPeriodic();
    
    return;
   }
    inline  void GetSurfaceInfo(const TopoDS_Face& face,SurfaceInfo& info,const unsigned int& id){
    info.surfaceType=SURFACE::GetSurfaceType(face);
    BRepAdaptor_Surface surface(face);
    info.Umin=surface.FirstUParameter();
    info.Umax=surface.LastUParameter();
    info.Vmin=surface.FirstVParameter();
    info.Vmax=surface.LastVParameter();
    info.Vperiod=surface.VPeriod();
    info.Uperiod=surface.UPeriod();
    info.surfaceTol=surface.Tolerance();
    info.IsUClosed=surface.IsUClosed();
    info.IsVClosed=surface.IsVClosed();
    info.IsUPeriodic=surface.IsUPeriodic();
    info.IsVPeriodic=surface.IsVPeriodic();
    info.index=id;
    
    return;
   }
inline void OutputSurfaceProperties(const TopoDS_Face& face){
   SurfaceInfo info;
   GetSurfaceInfo(face,info);
   cout<<"U minimum: "<<info.Umin<<"\n";
   cout<<"U maximum: "<<info.Umax<<"\n";
   cout<<"V minimum: "<<info.Vmin<<"\n";
   cout<<"V maximum: "<<info.Vmax<<"\n"; 
   return;
}
inline void OutputRay(const gp_Lin& ray){
   std::cout<<"ray's X Position:"<<ray.Location().X()<<"\n";
   std::cout<<"ray's Y Position:"<<ray.Location().Y()<<"\n";
   std::cout<<"ray's Z Position:"<<ray.Location().Z()<<"\n";
   
   std::cout<<"ray's direction X: "<<ray.Direction().X()<<"\n";
   std::cout<<"ray's direction Y: "<<ray.Direction().Y()<<"\n";
   std::cout<<"ray's direction Z: "<<ray.Direction().Z()<<"\n";
   return;

}
 
// this technique will only make sense when the selection mode is a face
 inline bool IntersectRayWithFace(const TopoDS_Face& face,const gp_Lin& ray,SurfaceIntersect_Info& s_info,QString& outputMessage){
   BRepTopAdaptor_FClass2d classifier(face,1e-7);
   TopLoc_Location loc;
   SURFACE::OutputSurfaceProperties(face);
   std::cout<<"Before Transformation"<<"\n";
   SURFACE::OutputRay(ray);

   Handle(Geom_Surface) surface=BRep_Tool::Surface(face,loc );
   if(!surface){
      
      outputMessage=QString("Failed To Convert an Object Of TopoDS_Face to an object of Geom_Surface ");
       std::cout<<outputMessage.toUtf8().toStdString()<<"\n";
      return false;   //it failed to cast to a face.....
   }
   auto localLoc=loc.Transformation().Inverted();
   gp_Pnt point=ray.Location().Transformed(localLoc);
   gp_Lin localRay(point,ray.Direction());
   
   std::cout<<"After Transformation:"<<"\n";
   SURFACE::OutputRay(localRay);   

   Handle(Geom_Curve) localCurve=new Geom_Line(localRay);
   if(!localCurve){
        outputMessage=QString("Failed to convert to an object of Geom_Curve");
        std::cout<<outputMessage.toUtf8().toStdString()<<"\n";
      return false;
   }
 
   //we have to perform intersection test with the surface
   GeomAPI_IntCS intersector(localCurve,surface);
   if(!intersector.IsDone() || intersector.NbPoints()==0){
      outputMessage=QString("Intersection Failed");
       std::cout<<outputMessage.toUtf8().toStdString()<<"\n";
       return false; //failed to intersect
   }
   double closestW=RealLast();
   int closestIndex=-1;
   std::cout<<"Number Of Intersection points: "<<intersector.NbPoints()<<std::endl;
   
   for(int i=1;i<=intersector.NbPoints();i++){
      double W;
      intersector.Parameters(i,s_info.U,s_info.V,W);
      if(W<1e-7){ 
         std::cout<<"W is less than tolerance "<<"\n";
         continue;
         }
      std::cout<<"("<<s_info.U<<","<<s_info.V<<")"<<std::endl;
      if(classifier.Perform(gp_Pnt2d(s_info.U,s_info.V))!=TopAbs_OUT){
      if( W<closestW){
         closestW=W;
         closestIndex=i;
         cout<<"Closest W: "<<W<<endl;
          std::cout<<"("<<s_info.U<<","<<s_info.V<<")"<<std::endl;
      }
   }
   else{
      std::cout<<"It is Out"<<"\n";
   }
 }
   if(closestIndex==-1){
      std::cout<<"No intersection point"<<std::endl;
      return false;
   }
   
  s_info.int_point=intersector.Point(closestIndex);
  s_info.int_point.Transform(loc.Transformation());
   outputMessage=QString("SUCCESS");
   std::cout<<outputMessage.toUtf8().toStdString()<<"\n";
   return true;
 }

inline bool IsWithinSurface(const TopoDS_Face& face,const gp_Pnt& point3d){
     TopoDS_Vertex aVertex=BRepBuilderAPI_MakeVertex(point3d);

    BRepExtrema_DistShapeShape anExtreme(face,aVertex);

    if(anExtreme.IsDone() && anExtreme.Value()<=1e-7){
        BRepClass_FaceClassifier classifier(face,point3d,1e-7);
        return (classifier.State()==TopAbs_ON || classifier.State()==TopAbs_IN);
    }   
    return false;
}
inline gp_Pnt GetSurfaceCentre(const TopoDS_Face& face){
   GProp_GProps props;
   BRepGProp::SurfaceProperties(face,props); //obtain centre of mass

   return props.CentreOfMass();
}
}