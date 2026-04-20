#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP
#include<TopoDS_Shape.hxx>
#include<gp_Trsf.hxx>
#include<ShapeId.hpp>
#include<Quantity_Color.hxx>
#include<AIS_Shape.hxx>
class  SceneObject{
public:
SHAPE_ID id=SHAPE_ID::SID_NONE;
Handle(AIS_Shape) Shape;
SceneObject(){

}
SceneObject(SHAPE_ID id_1,const Handle(AIS_Shape)& shape){
    id=id_1;
    Shape=shape;
    
}

};






#endif