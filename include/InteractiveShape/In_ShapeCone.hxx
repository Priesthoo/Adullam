#ifndef DISPLAYED_CONE_HPP
#define DISPLAYED_CONE_HPP
#include<AIS_Shape.hxx>
#include<TopoDS_Shape.hxx>
#include<BRepPrimAPI_MakeCone.hxx>
//In_ means interactive
//
class In_ShapeCone{

private:
TopoDS_Shape Cone;
Handle(AIS_Shape) ConeShape;
double TopRadius=0.0;
double BottomRadius=0.0;
double height=0.0;
gp_Ax2 axis;
public:

In_ShapeCone(const gp_Ax2& p_axis,const double& p_Topradius,const double& p_Bottomradius,const double& p_height){
    axis=p_axis;
    Cone=BRepPrimAPI_MakeCone(axis,p_Topradius,p_Bottomradius,p_height).Shape();
    TopRadius=p_TopRadius;
    BottomRadius=p_Bottomradius;
    height=p_height;
    
    ConeShape=new AIS_Shape(Cone);
}

//Set TopRadius and update the shape
void SetTopRadius(const double& p_Topradius){
   TopRadius=p_Topradius;
   Cone=BRepPrimAPI_MakeCone(axis,p_Topradius,BottomRadius,height).Shape();
   if(!ConeShape.IsNull()){
    ConeShape.Nullify();
   }
   ConeShape=new AIS_Shape(Cone);
   return;
}
void SetBottomRadius(const double& p_BottomRadius){
    BottomRadius=p_BottomRadius;
    Cone=BRepPrimAPI_MakeCone(axis,p_Topradius,BottomRadius,height).Shape();
    if(!ConeShape.IsNull()){
        ConeShape.Nullify();
    }
    ConeShape=new AIS_Shape(Cone);
    return;
}
void SetHeight(const double& p_height){
    height=p_height;
    Cone=BRepPrimAPI_MakeCone(axis,p_Topradius,BottomRadius,height).Shape();
    if(!ConeShape.IsNull()){
        ConeShape.Nullify();
    }
    ConeShape=new AIS_Shape(Cone);
    return;
}

double GetTopRadius() const{
    return TopRadius;
}
double GetBottomRadius() const{
    return BottomRadius;
}
double GetHeight() const{
    return height;
}
};












#endif
