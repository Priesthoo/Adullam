#ifndef CAMERA_ANIMATOR_HPP
#define CAMERA_ANIMATOR_HPP
#include"V3d_View.hxx"
#include"gp_Dir.hxx"
#include"gp_Vec.hxx"
#include"gp_Quaternion.hxx"
#include"gp_Mat.hxx"
#include"gp_QuaternionSLerp.hxx"
enum INTERPOLATION_TYPE{
  LINEAR,
  SLERP
};
class CameraAnimator{

public:
double m_t=0;  //interpolating parameter
 gp_Vec StartDirection;
gp_Vec EndDirection;
gp_Quaternion startquat;
gp_Quaternion endquat;
gp_Vec WorldUp=gp_Vec(0.0,0.0,1.0);
gp_Quaternion Interpolatedquat;
gp_Vec InterpolatedDir;
static gp_Vec CrossProduct(const gp_Vec& vec1,const gp_Vec& vec2){
 gp_Vec crossproduct(vec1.Y()*vec2.Z()-vec1.Z()*vec2.Y(),vec1.Z()*vec2.X()-vec1.X()*vec2.Z(),vec1.X()*vec2.Y()-vec1.Y()*vec2.X());
 return crossproduct;
}
static gp_Vec NormalizeVector(const gp_Vec& inputVector){
  return inputVector.Normalized();  //Normalize vector
}

//We use a column major order
static gp_Mat BuildBasisFromCameraVector(const gp_Vec& vec1,const gp_Vec& world_up){
 gp_Vec forward=vec1;
 gp_Vec right=CameraAnimator::NormalizeVector(CameraAnimator::CrossProduct(world_up,forward));
 gp_Vec trueup=CameraAnimator::NormalizeVector(CameraAnimator::CrossProduct(forward,right));
 //The camera looks along the positive -z axis,This uses a column order
 return gp_Mat(
  right.X(),trueup.X(),-forward.X()
 ,right.Y(),trueup.Y(),-forward.Y()
 ,right.Z(),trueup.Z(),-forward.Z());
}
static gp_Quaternion ConstructQuaternionFromBasisVector(const gp_Mat& quatmat){
  gp_Quaternion quat;
  quat.SetMatrix(quatmat);
  return quat;
}
static gp_Quaternion SphericalInterpolate(const gp_Quaternion& quat,const gp_Quaternion& quat_1,const double& t1){
  return gp_QuaternionSLerp::Interpolate(quat,quat_1,t1);
}
static gp_Vec GetViewDirectionFromQuatMatrix(const gp_Mat& quatmat){
    return gp_Vec(quatmat.Value(1,3),quatmat.Value(2,3),quatmat.Value(3,3)).Normalized();

}
public:
CameraAnimator()=default;
explicit CameraAnimator(const gp_Vec& p_start,const gp_Vec& p_end,const gp_Vec& upvector,const double& t1){
    StartDirection=p_start;
    EndDirection=p_end;
    WorldUp=upvector; 
    
    m_t=std::clamp(t1,0.0,1.0);
    startquat=CameraAnimator::ConstructQuaternionFromBasisVector(CameraAnimator::BuildBasisFromCameraVector(StartDirection,upvector));
    endquat=CameraAnimator::ConstructQuaternionFromBasisVector(CameraAnimator::BuildBasisFromCameraVector(EndDirection,upvector));
    Interpolatedquat=CameraAnimator::SphericalInterpolate(startquat,endquat,m_t);
    
    gp_Mat quatmat=Interpolatedquat.GetMatrix();
    
    InterpolatedDir=gp_Vec(quatmat.Value(1,3),quatmat.Value(2,3),quatmat.Value(3,3)).Normalized();
    
  
}
static void SetInterpolatingParameter(CameraAnimator& anim,const double& p_t ){
   anim.m_t=p_t;
   return;
}

~CameraAnimator(){
}


};




#endif