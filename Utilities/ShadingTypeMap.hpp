#pragma once
#include<TopAbs_ShapeEnum.hxx>
#include<map>
#include<QtCore/QString>
#include<AIS_RotationMode.hxx>
#include<AIS_NavigationMode.hxx>
#include<Graphic3d_TypeOfShadingModel.hxx>
namespace STM{
 inline const std::map<QString,Graphic3d_TypeOfShadingModel> shadertypemap{{QString("Default"),Graphic3d_TypeOfShadingModel_DEFAULT},{QString("Unlit"),Graphic3d_TypeOfShadingModel_Unlit},{QString("Flat Phong"),Graphic3d_TypeOfShadingModel_PhongFacet},{QString("Gouraud"),Graphic3d_TypeOfShadingModel_Gouraud},{QString("Phong"), Graphic3d_TypeOfShadingModel_Phong},{QString("Physically Based"), Graphic3d_TypeOfShadingModel_Pbr},{QString("Flat Physically Based"), Graphic3d_TypeOfShadingModel_PbrFacet}};
 inline const std::map<TopAbs_ShapeEnum,QString> shapetypemap{{TopAbs_COMPOUND,QString("Compound")},{TopAbs_COMPSOLID,QString("Compound-Solid")},{TopAbs_SOLID,QString("Solid")},{TopAbs_SHELL,QString("Shell")},{TopAbs_FACE,QString("Face")},{TopAbs_WIRE,QString("WIRE")},{TopAbs_EDGE,QString("Edge")},{TopAbs_VERTEX,QString("Vertex")},{TopAbs_SHAPE,QString("Shape")}};
 inline  const std::map<QString,AIS_RotationMode> rotationMap{{QString("Bound Box Active"),AIS_RotationMode_BndBoxActive},{QString("Last Pick"),AIS_RotationMode_PickLast},{QString("Centre Pick"),AIS_RotationMode_PickCenter},{QString("Camera Centre"),AIS_RotationMode_CameraAt},{QString("Scene Centre"),AIS_RotationMode_BndBoxScene}};
 inline const std::map<QString,AIS_NavigationMode> navMap{{QString("Orbit Navigation"),AIS_NavigationMode_Orbit},{QString("Flight Mode"),AIS_NavigationMode_FirstPersonFlight},{QString("Walk Mode"),AIS_NavigationMode_FirstPersonWalk}};
}







