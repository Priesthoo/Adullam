#ifndef CUBEBUILDER_HPP
#define CUBEBUILDER_HPP
#include<Cube.hpp>
#include<AIS_InteractiveContext.hxx>
class CubeBuilder{
private:
std::unique_ptr<Cube>Builder;
bool isDrawingWidth=false;
bool isDrawingHeight=false;
bool isDrawingLength=false; 
};






#endif