#pragma once
#include<QtWidgets/QWidget>
#include<QtWidgets/QLabel>
#include<QtWidgets/QFormLayout>
#include<memory>

#include<SurfaceUtility.hpp>
#include<MyCustomAIS_Shape.hxx>
#include<QtWidgets/QCheckBox>
#include<Section.h>
using namespace std;
using namespace SURFACE;
//Surface info is set already
class SurfaceInfoSection:public Section{
 private:
 Q_OBJECT
 std::unique_ptr<QFormLayout> flayout;
 std::unique_ptr<QCheckBox> hilightCheckBox; 
 
 Handle(CustomAIS_Shape) Shape;  //chosen shape....
 unsigned int Index=0;
 public:
 SurfaceInfoSection(const SURFACE::SurfaceInfo& surfaceInfo,const QString& sectionTitle,QWidget* parent):Section(sectionTitle,2,parent){
  

  flayout=make_unique<QFormLayout>();
  flayout->addRow(tr("Surface Type:"),new QLabel(surfaceInfo.surfaceType,this));
  flayout->addRow(tr("Umin:"),new QLabel(QString::number(surfaceInfo.Umin),this));
  flayout->addRow(tr("Umax:"),new QLabel(QString::number(surfaceInfo.Umax),this));
  flayout->addRow(tr("Vmin:"),new QLabel(QString::number(surfaceInfo.Vmin),this));
  flayout->addRow(tr("Vmax:"),new QLabel(QString::number(surfaceInfo.Vmax),this));
  flayout->addRow(tr("VPeriod:"),new QLabel(QString::number(surfaceInfo.Vperiod),this));
  flayout->addRow(tr("UPeriod:"),new QLabel(QString::number(surfaceInfo.Uperiod),this));
  flayout->addRow(tr("Surface Tolerance:"),new QLabel(QString::number(surfaceInfo.surfaceTol),this));
  
  if(surfaceInfo.IsUClosed){
        flayout->addRow(tr("Is U Closed: "),new QLabel(tr("True"),this));
  }
  else{
      flayout->addRow(tr("Is U Closed: "),new QLabel(tr("False"),this));
  }
  if(surfaceInfo.IsVClosed){
        flayout->addRow(tr("Is V Closed: "),new QLabel(tr("True"),this));
  }
  else{
      flayout->addRow(tr("Is V Closed: "),new QLabel(tr("False"),this));
  }
  if(surfaceInfo.IsUPeriodic){
        flayout->addRow(tr("Is U Periodic: "),new QLabel(tr("True"),this));
  }
  else{
      flayout->addRow(tr("Is U Periodic: "),new QLabel(tr("False"),this));
  }
  if(surfaceInfo.IsVPeriodic){
        flayout->addRow(tr("Is V Periodic: "),new QLabel(tr("True"),this));
  }
  else{
      flayout->addRow(tr("Is V Periodic: "),new QLabel(tr("False"),this));
  }
  hilightCheckBox=std::make_unique<QCheckBox>(tr(""),this);
  
  flayout->addRow(tr("Highlight State"),hilightCheckBox.get());
      setContentLayout(*flayout.get());

 }


SurfaceInfoSection(const SURFACE::SurfaceInfo& surfaceInfo,const QString& sectionTitle,QWidget* parent,const Handle(CustomAIS_Shape)& shape):Section(sectionTitle,2,parent){
  

  flayout=make_unique<QFormLayout>();
  flayout->addRow(tr("Surface Type:"),new QLabel(surfaceInfo.surfaceType,this));
  flayout->addRow(tr("Umin:"),new QLabel(QString::number(surfaceInfo.Umin),this));
  flayout->addRow(tr("Umax:"),new QLabel(QString::number(surfaceInfo.Umax),this));
  flayout->addRow(tr("Vmin:"),new QLabel(QString::number(surfaceInfo.Vmin),this));
  flayout->addRow(tr("Vmax:"),new QLabel(QString::number(surfaceInfo.Vmax),this));
  flayout->addRow(tr("VPeriod:"),new QLabel(QString::number(surfaceInfo.Vperiod),this));
  flayout->addRow(tr("UPeriod:"),new QLabel(QString::number(surfaceInfo.Uperiod),this));
  flayout->addRow(tr("Surface Tolerance:"),new QLabel(QString::number(surfaceInfo.surfaceTol),this));
  
  if(surfaceInfo.IsUClosed){
        flayout->addRow(tr("Is U Closed: "),new QLabel(tr("True"),this));
  }
  else{
      flayout->addRow(tr("Is U Closed: "),new QLabel(tr("False"),this));
  }
  if(surfaceInfo.IsVClosed){
        flayout->addRow(tr("Is V Closed: "),new QLabel(tr("True"),this));
  }
  else{
      flayout->addRow(tr("Is V Closed: "),new QLabel(tr("False"),this));
  }
  if(surfaceInfo.IsUPeriodic){
        flayout->addRow(tr("Is U Periodic: "),new QLabel(tr("True"),this));
  }
  else{
      flayout->addRow(tr("Is U Periodic: "),new QLabel(tr("False"),this));
  }
  if(surfaceInfo.IsVPeriodic){
        flayout->addRow(tr("Is V Periodic: "),new QLabel(tr("True"),this));
  }
  else{
      flayout->addRow(tr("Is V Periodic: "),new QLabel(tr("False"),this));
  }
   hilightCheckBox=std::make_unique<QCheckBox>(tr(""),this);
   
  flayout->addRow(tr("Highlight State:"),hilightCheckBox.get());
   
    Shape=shape;
    Index=surfaceInfo.index;
    connect(hilightCheckBox.get(),&QCheckBox::toggled,this,&SurfaceInfoSection::OnHighlightSubShape);
    
      setContentLayout(*flayout.get());

 }
 signals:
 void EmitFaceIndex(unsigned int index);
 void EmitNullifyFaceIndex();

 public slots:
 void OnEditSurface(bool value){
    if(value){
      emit EmitFaceIndex(Index);
      return;
    }
    else{
        emit EmitNullifyFaceIndex(); 
    }
    return;
 }
 void OnHighlightSubShape(bool value){
    if(value){
     if(Index>0){
        if(Shape){
            Shape->ShadeFace(Index,Quantity_NOC_ORANGE);
            if(Shape->GetContext()){
                if(Shape->GetContext()->IsDisplayed(Shape)){
                     Shape->GetContext()->Redisplay(Shape,true);
                }
            }
        }
     }
    }
    else{
        if(Index>0){
        if(Shape){
            Shape->UnShadeFace(Index);
            if(Shape->GetContext()){
                if(Shape->GetContext()->IsDisplayed(Shape)){
                     Shape->GetContext()->Redisplay(Shape,true);
                }
        }
     }
    }
    return;
 }
 }
};