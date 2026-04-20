#pragma once 
#include<QtWidgets/QWidget>
#include<QtWidgets/QVBoxLayout>
#include<SurfaceInfoPane.hpp>
#include<MyCustomAIS_Shape.hxx>
using namespace SURFACE;
class SurfaceInfoWidget:public QWidget{
 private:
 Q_OBJECT
 std::unique_ptr<SurfaceInfoSection> surface_section;
 std::unique_ptr<QVBoxLayout> vlayout;
 Handle(CustomAIS_Shape) prevShape;
 Handle(CustomAIS_Shape) currShape;
 public:
 SurfaceInfoWidget(QWidget* parent=nullptr):QWidget(parent){
  return;
 }
 SurfaceInfoWidget(QWidget* parent,const SurfaceInfo& info,const QString& title){
  surface_section=std::make_unique<SurfaceInfoSection>(info,title,this);
  vlayout=make_unique<QVBoxLayout>();
  vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
  vlayout->addWidget(surface_section.get());
  setLayout(vlayout.get());
  return;
 }
 void SetSurfaceInfo(const SurfaceInfo& info,const QString& title){
    if(surface_section){
        surface_section.reset();
    }
    surface_section=std::make_unique<SurfaceInfoSection>(info,title,this);
    
    if(layout()){
      delete layout();
    }
    if(vlayout){
      vlayout.reset();
    }
    vlayout=make_unique<QVBoxLayout>();
  vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
  vlayout->addWidget(surface_section.get());
  setLayout(vlayout.get());

    return;
 }
 void SetSurfaceInfos(const Handle(CustomAIS_Shape)& shape){
    if(layout()){
      delete layout();
    }
    if(!prevShape.IsNull()){
      if(prevShape==shape){
        return;
      }
    }
    else{
      if(prevShape==shape){
        return;
      }
    }
     vlayout=make_unique<QVBoxLayout>();
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
     SurfaceInfo sface;
     

      for(int i=1;i<=shape->FaceCount();i++){
        GetSurfaceInfo(shape->GetFace(i),sface,i);
        vlayout->addWidget(new SurfaceInfoSection(sface,QString("Surface Info ")+QString::number(i),this,shape));
        
      }
      setLayout(vlayout.get());
      prevShape=shape;
    return;
 }
 void SetCurrentShape(const Handle(CustomAIS_Shape)& shape){
  currShape=shape;
  return;
 }
 Handle(CustomAIS_Shape) GetCurrentShape() const{ 
  return currShape;
 }
 signals:
 void EmitIndex(unsigned int index);


 public slots:
 void OnReceiveIndex(unsigned int index){
     emit EmitIndex(index);
     return;
 }
};
