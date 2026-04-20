#ifndef CUBE_HPP
#define CUBE_HPP
#include<memory>
#include<BRepPrimAPI_MakeBox.hxx>
#include<gp_Trsf.hxx>
class Cube:public BRepPrimAPI_MakeBox{
private:
double height;
double width;
double length;
float angle;
public:
Cube(const double& m_h,const double& m_w,const double& m_len):BRepPrimAPI_MakeBox(m_w,m_len,m_h){
    height=m_h;
    width=m_w;
    length=m_len;
    angle=0.0f;
}
void SetHeight(const double& h){
    height=h;
    return;
}
void SetWidth(const double& w){
    width=w;
    return;
}
void SetLength(const double& l){
    length=l;
    return;
}
double& Height(){
    return height;
}
double& Width(){
    return width;
}
double& Length(){
    return length;
}

};




#endif