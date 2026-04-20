#ifndef VIEW_DIRECTION_HPP
#define VIEW_DIRECTION_HPP
#include<gp_Dir.hxx>
//These are the view direction that will be available in Adullam project,we are using a left coordinate system
//OUR camera uses a coordinate system such that it's z axis points into the screen
enum VIEW_DIRECTION{
FRONT,
BACK,
LEFT,
RIGHT,
TOP,
BOTTOM,
TOP_RIGHT,
TOP_LEFT,
TOP_FRONT,
TOP_BACK,
BOTTOM_RIGHT,
BOTTOM_LEFT,
BOTTOM_FRONT,
BOTTOM_BACK,
TOP_RIGHT_BACK,
TOP_RIGHT_FRONT,
TOP_LEFT_BACK,
TOP_LEFT_FRONT,
BOTTOM_RIGHT_BACK,
BOTTOM_RIGHT_FRONT,
BOTTOM_LEFT_BACK,
BOTTOM_LEFT_FRONT
};
namespace View{
  static const gp_Dir Front=gp_Dir(0,0.0,1.0);
  static const gp_Dir Back=gp_Dir(0,0.0,1.0);
  static const gp_Dir Left=gp_Dir(-1.0,0,0);
  static const gp_Dir Right=gp_Dir(1.0,0.0,0.0);
  static const gp_Dir Top=gp_Dir(0.0,1.0,0.0);
}









#endif