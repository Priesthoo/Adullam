#ifndef OBJECTINFOWIDGET_HPP
#define OBJECTINFOWIDGET_HPP
#include<QtWidgets/QWidget>
#include<MyCustomAIS_Shape.hxx>
#include<QtWidgets/QVBoxLayout>
#include<ObjectPresentationWidget.hpp>
#include<SurfaceInfoPane.hpp>
#include<iostream>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QLabel>
#include<TextButton.hpp>
#include<memory>
using namespace std;
using namespace SURFACE;

class ObjectInfoWidget:public QWidget{
    private:
    Q_OBJECT
    std::unique_ptr<QVBoxLayout> vboxlayout;
    std::unique_ptr<Section> PrimitiveInfoSection;
    std::unique_ptr<Section> faceSection;  //this will tell us more about the index of the object and face type
    std::unique_ptr<Section> edgeSection;  //this will also tell us more anout the index of the edge and the edge type
    std::unique_ptr<QLabel> faceLabel;   
    std::unique_ptr<QLabel> edgeLabel;
    std::unique_ptr<MaterialPropertySection> objectprs;
     std::unique_ptr<QFormLayout> flayout;
     std::unique_ptr<QVBoxLayout> formlayout;
    int ButtonId=-1; //invalid Id;
    public:
    ObjectInfoWidget(QWidget* parent):QWidget(parent){
      vboxlayout=make_unique<QVBoxLayout>();
        vboxlayout->setAlignment(Qt::AlignLeft| Qt::AlignTop);

        PrimitiveInfoSection=make_unique<Section>(tr("Primitve Info"),2,this);
      
        faceLabel=make_unique<QLabel>(tr("0"),PrimitiveInfoSection.get());
        edgeLabel=make_unique<QLabel>(tr("0"),PrimitiveInfoSection.get());
        flayout=make_unique<QFormLayout>();
        flayout->addRow(tr("Face Count:"),faceLabel.get());
        flayout->addRow(tr("Edge Count:"),edgeLabel.get());
        PrimitiveInfoSection->setContentLayout(*flayout.get());
        vboxlayout->addWidget(PrimitiveInfoSection.get());
        faceSection=make_unique<Section>(tr("Face"),2,this);
         objectprs=make_unique<MaterialPropertySection>(tr("Material Property"),this);
         
         vboxlayout->addWidget(faceSection.get());
        vboxlayout->addWidget(objectprs.get());
         
         setLayout(vboxlayout.get());
      
    }
    ObjectInfoWidget(QWidget* parent,const Handle(CustomAIS_Shape)& shape,const Quantity_Color& color):QWidget(parent){
        //For PrimitveSection
       
        vboxlayout=make_unique<QVBoxLayout>();
        vboxlayout->setAlignment(Qt::AlignLeft| Qt::AlignTop);

        PrimitiveInfoSection=make_unique<Section>(tr("Primitve Info"),2,this);
      
        faceLabel=make_unique<QLabel>(tr("0"),PrimitiveInfoSection.get());
        edgeLabel=make_unique<QLabel>(tr("0"),PrimitiveInfoSection.get());
        flayout=make_unique<QFormLayout>();
        flayout->addRow(tr("Face Count:"),faceLabel.get());
        flayout->addRow(tr("Edge Count:"),edgeLabel.get());
        PrimitiveInfoSection->setContentLayout(*flayout.get());
        vboxlayout->addWidget(PrimitiveInfoSection.get());
        faceSection=make_unique<Section>(tr("Face"),2,this);
        objectprs=make_unique<MaterialPropertySection>(tr("Material Property"),this);
         SetProperties(shape,color);
         vboxlayout->addWidget(faceSection.get());
        vboxlayout->addWidget(objectprs.get());
         
         setLayout(vboxlayout.get());
      

        return;
    }
    void SetProperties(const Handle(CustomAIS_Shape)& object,const Quantity_Color& color){
        if(objectprs.get()){
          objectprs->SetPropertiesFromSelectedShape(object,color);
        }
       if(PrimitiveInfoSection){
           faceLabel->setText(QString::number(object->FaceCount()));
           edgeLabel->setText(QString::number(object->EdgeCount()));
       }
          FillFaceSection(object);
       return;
    }
  void FillFaceSection(const Handle(CustomAIS_Shape)& shape){
       if(faceSection->layout()){
         
          delete faceSection->layout();   //so we can set it....
      }
      if(vboxlayout){
         vboxlayout->removeWidget(faceSection.get());
      }
      
 
      formlayout=make_unique<QVBoxLayout>();
      
      SurfaceInfo sface;
     

      for(int i=1;i<=shape->FaceCount();i++){
        GetSurfaceInfo(shape->GetFace(i),sface);
        formlayout->addWidget(new SurfaceInfoSection(sface,QString("Surface Info")+QString::number(i),faceSection.get()));
    
      }

      if(formlayout){
        cout<<"Form Layout's Size after addition: "<<formlayout->count()<<"\n";
        faceSection->setContentLayout(*formlayout.get());
        if(faceSection->layout()){

          std::cout<<"Face Section's layout is not empty"<<"\n";

        }
      }
      vboxlayout->addWidget(faceSection.get());
      
    return;
  }
signals:

void EmitSubshapeId(int id);
public slots:
void HandleButtonSignal(int id){
    emit EmitSubshapeId(id);
    return;
}

};

















#endif