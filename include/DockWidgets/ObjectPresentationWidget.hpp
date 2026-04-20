#pragma once
#include<QtWidgets/QComboBox>
#include<DoubleLineEdit.hpp>
#include<ColorPane.hpp>
#include<MaterialPropertySection.hpp>
#include<QtWidgets/QVBoxLayout>

class ObjectPresentationWidget:public QWidget{
private:
std::unique_ptr<MaterialPropertySection> propertysection;
std::unique_ptr<QVBoxLayout> vboxlayout;
//we are going to render the widget based on the selected object 
bool isLineObject=false;
bool isPointObject=false;
bool isTextObject=false; 
bool isShapeObject=false;
public:
ObjectPresentationWidget(QWidget* parent):QWidget(parent){
    isShapeObject=true;
    if(isShapeObject){
      vboxlayout.reset(new QVBoxLayout);
      propertysection.reset(new MaterialPropertySection(tr("Material Property"),this));
      vboxlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);

      vboxlayout->addWidget(propertysection.get());
      setLayout(vboxlayout.get());
      return;
    }
}
MaterialPropertySection* propsection() const{
    return propertysection.get();
}
//set isLineObject to true and render
void SetIsLineObject(const bool& result){
    isLineObject=result;
    if(isLineObject){
    if(layout()){
        setLayout(nullptr);
        
    }
    if(vboxlayout.get()){
        vboxlayout.reset();
    }
    }
    return;
}
};