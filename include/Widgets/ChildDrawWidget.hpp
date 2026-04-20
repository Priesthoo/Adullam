#pragma once 
#include<QtWidgets/QWidget>
#include<AIS_ViewCube.hxx>
#include<AIS_ViewController.hxx>
#include<V3d_View.hxx>
#include<QtGui/QMouseEvent>
#include<QtGui/QWheelEvent>
#include<QtGui/QResizeEvent>
#include<EventManager.hpp>
#include<SurfaceUtility.hpp>
//used for drawing subpart 
class ChildDrawWidget:public QWidget,public V3d_View{
  Q_OBJECT
  public:
  
};