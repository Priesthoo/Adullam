#pragma once
#include<TopAbs_ShapeEnum.hxx>
#include<map>
#include<QtCore/QString>
#include<Graphic3d_TypeOfShadingModel.hxx>
namespace STM{
 inline const std::map<QString,Graphic3d_TypeOfShadingModel> shadertypemap{{QString("Default"),Graphic3d_TypeOfShadingModel_DEFAULT},{QString("Unlit"),Graphic3d_TypeOfShadingModel_Unlit},{QString("Flat Phong"),Graphic3d_TypeOfShadingModel_PhongFacet},{QString("Gouraud"),Graphic3d_TypeOfShadingModel_Gouraud},{QString("Phong"), Graphic3d_TypeOfShadingModel_Phong},{QString("Physically Based"), Graphic3d_TypeOfShadingModel_Pbr},{QString("Flat Physically Based"), Graphic3d_TypeOfShadingModel_PbrFacet}};
 inline const std::map<TopAbs_ShapeEnum,QString> shapetypemap{{TopAbs_COMPOUND,QString("Compound")},{TopAbs_COMPSOLID,QString("Compound-Solid")},{TopAbs_SOLID,QString("Solid")},{TopAbs_SHELL,QString("Shell")},{TopAbs_FACE,QString("Face")},{TopAbs_WIRE,QString("WIRE")},{TopAbs_EDGE,QString("Edge")},{TopAbs_VERTEX,QString("Vertex")},{TopAbs_SHAPE,QString("Shape")}};

}







