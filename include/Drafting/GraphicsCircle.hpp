#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include<Geom2d_Circle.hxx>
#include<gp_Pnt.hxx>
#include<gce_MakeCirc2d.hxx>
#include<GCE2d_MakeCircle.hxx>
#include<memory>
//We have different types of circles,we have circle with radius,end point circles, three point circles 
//Like I mentioned,there are different ways to create a circle,There are listed below:
//A Circle that is concentric with another and passing through a point
//A Circle that is concentric with another at a distance (Distance)
//A Circle that passes through 3 points 
//A Circle that has a center and a point given the radius
// A Circle that has an axis of definition and a radius
//Concentricity actually means that the this->Circle and Another Circle share the same center point
enum CIRCLE_TYPE{
 CT_CIRCLE_RADIUS, //circle with radius and center point
 CT_THREE_POINTS   //Circle constructed by passing through three points   
};
//Since we are not displaying the circle's object on the screen,it is advisable to use gp_Circ2d
class Circle:public Geom2d_Circle{
public:
gp_Trsf Transform;
bool isSelected=false;
bool isPersistent=false;
bool isCircleDrawn=false;
bool isForbiddenRadius=false;
std::unique_ptr<GCE2d_MakeCircle> circlemaker;
Circle(const gp_Circ2d& C):Geom2d_Circle(C){
 
}
Circle(const gp_Ax2d& Axis,const double& radius):Geom2d_Circle(Axis,radius){
      if(radius<=0.0){
        isForbiddenRadius=true;
        return;
      }
      isCircleDrawn=true;  //At this point,circle is drawn or constructed   
}
void ConstructParallelCircleFromDistance(const double& distance){
  if(isCircleDrawn){
   if(circlemaker.get()!=nullptr){
      circlemaker.reset();
   }
   circlemaker.reset(new GCE2d_MakeCircle(Circ2d(),distance));
  }
  
}
gp_Circ2d GetNDistancedCircle() const{
    return circlemaker->Value()->Circ2d();
}

};




#endif