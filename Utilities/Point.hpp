#pragma once
#include<gp_Pnt.hxx>
struct Point{
    float m_X;
    float m_Y;
    float m_Z;
    Point(){
        m_X=0.0;
        m_Y=0.0;
        m_Z=0.0;
    }
  Point(const float& _x,const float& _y,const float& _z){
    m_X=_x;
    m_Y=_y;
    m_Z=_z;
  }
  Point(const Point& pt){
    m_X=pt.X();
    m_Y=pt.Y();
    m_Z=pt.Z();
    return;
  }
  void SetX(const float& x){
    m_X=x;
    return;

}
float X() const{
    return m_X;
}
void SetY(const float& y){
    m_Y=y;
    return;
}
void SetZ(const float& z){
    m_Z=z;
    return;
}
float Z() const{
    return m_Z;
}
float Y() const{
    return m_Y;
}
Point& operator=(const Point& pt){
    SetX(pt.X());
    SetY(pt.Y());
    SetZ(pt.Z());

    return *this;
}
Point& operator=(const gp_Pnt& pt){
    SetX(pt.X());
    SetY(pt.Y());
    SetZ(pt.Z());

    return *this;
}
};