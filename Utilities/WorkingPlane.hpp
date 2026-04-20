#ifndef WORKING_PLANE_HPP
#define WORKING_PLANE_HPP
#include<gp_Ax3.hxx>
#include<gp_Pln.hxx>
#include<Geom_Plane.hxx>
#include<Geom_Axis2Placement.hxx>
#include<gp_Dir.hxx>
#include<gp_Vec.hxx>
#include<unordered_map>
//I nned to add a modify menu item to menubar
//Selection filter(Edge,Face,Vertex)
class WorkingPlane{
public:
enum NORMAL_STATUS{
NS_IS_NORMALIZED,
NS_IS_NOT_NORMALIZED
};

enum NORMAL_DIRECTION{
 ND_UP,  //0,0,1.0
 ND_RIGHT,
 ND_LEFT,
 ND_DOWN,
 ND_FRONT,
 ND_BACK,
 ND_USER_DEFINED //This is affected by rotation
 
};

bool myisShown=false; // This will be set to true when we display a working plane
bool myIsNormalized=false; //This checks if This is normalized
gp_Vec myw_pDir; //working plane direction
gp_Pnt myOrigin;   //This is the origin of the plane
bool DirectionIsSet=false;
static std::unordered_map<NORMAL_DIRECTION,gp_Dir> NormalDirMapper; 
WorkingPlane(){
    myw_pDir=gp_Dir(0,0,1.0);  //By default it is up
    myOrigin=gp_Pnt(0.0,0.0,0.0);  //it is at the origin
    
}
bool  IsNormalized() const{
    return myIsNormalized; 
}
// after calling this you can check the status of normal by using IsNormalized() method
NORMAL_STATUS Check_If_Normalized(){
    double myx=myw_pDir.X();
    double myy=myw_pDir.Y();
    double myz=myw_pDir.Z();
    myx*=myx;
    myy*=myy;
    myz*=myz;
    double mag=std::sqrt(myx+myy+myz);
    if(mag<=gp::Resolution()){
        myIsNormalized=true;
     return NS_IS_NORMALIZED;
    }
    myIsNormalized=false;
    return NS_IS_NOT_NORMALIZED;

}
void NormalizePlaneNormal(){
    if(IsNormalized()){
        return;
    }
    this->myw_pDir=this->myw_pDir.Normalized();
    return;
}
void TranslateOriginByVector(const gp_Vec& vector){
  myOrigin.Translate(vector);
  return;
}

void RotateWorkingPlane(const gp_Ax1& axis,const double& ang){
  if(IsNormalized()){
    myw_pDir.Rotate(axis,ang);  //Rotate the working plane about an axis
  return;
  }
}
};


#endif