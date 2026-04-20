#ifndef COLORCOLLECTION_HPP
#define COLORCOLLECTION_HPP
#include<ColorPane.hpp>
#include<QtWidgets/QWidget>
#include<Quantity_Color.hxx>
#include<Quantity_NameOfColor.hxx>
#include<QtWidgets/QVBoxLayout>
#include<QScrollArea>
#include<iostream>
#include<array>
#include<Section.h>
#include<QtWidgets/QFormLayout>
#include<iostream>
namespace NC{
    inline const std::array<Quantity_NameOfColor,58> colorarray{ Quantity_NOC_BLACK,
  Quantity_NOC_MATRABLUE,
  Quantity_NOC_MATRAGRAY,
  Quantity_NOC_ALICEBLUE,
  Quantity_NOC_ANTIQUEWHITE,
  Quantity_NOC_ANTIQUEWHITE1,
  Quantity_NOC_ANTIQUEWHITE2,
  Quantity_NOC_ANTIQUEWHITE3,
  Quantity_NOC_ANTIQUEWHITE4,
  Quantity_NOC_AQUAMARINE1,
  Quantity_NOC_AQUAMARINE2,
  Quantity_NOC_AQUAMARINE4,
  Quantity_NOC_AZURE,
  Quantity_NOC_AZURE2,
  Quantity_NOC_AZURE3,
  Quantity_NOC_AZURE4,
  Quantity_NOC_BEIGE,
  Quantity_NOC_BISQUE,
  Quantity_NOC_BISQUE2,
  Quantity_NOC_BISQUE3,
  Quantity_NOC_BISQUE4,
  Quantity_NOC_BLANCHEDALMOND,
  Quantity_NOC_BLUE,
  Quantity_NOC_BLUE2,
  Quantity_NOC_BLUE3,
  Quantity_NOC_BLUE4,
  Quantity_NOC_BLUEVIOLET,
  Quantity_NOC_BROWN,
  Quantity_NOC_BROWN1,
  Quantity_NOC_BROWN2,
  Quantity_NOC_BROWN3,
  Quantity_NOC_BROWN4,
  Quantity_NOC_BURLYWOOD,
  Quantity_NOC_BURLYWOOD1,
  Quantity_NOC_BURLYWOOD2,
  Quantity_NOC_BURLYWOOD3,
  Quantity_NOC_BURLYWOOD4,
  Quantity_NOC_CADETBLUE,
  Quantity_NOC_CADETBLUE1,
  Quantity_NOC_CADETBLUE2,
  Quantity_NOC_CADETBLUE3,
  Quantity_NOC_CADETBLUE4,
  Quantity_NOC_CHARTREUSE,
  Quantity_NOC_CHARTREUSE2,
  Quantity_NOC_CHARTREUSE3,
  Quantity_NOC_CHARTREUSE4,
  Quantity_NOC_CHOCOLATE,
  Quantity_NOC_CHOCOLATE1,
  Quantity_NOC_CHOCOLATE2,
  Quantity_NOC_CHOCOLATE3,
  Quantity_NOC_CHOCOLATE4,
  Quantity_NOC_CORAL,
  Quantity_NOC_CORAL1,
  Quantity_NOC_CORAL2,
  Quantity_NOC_CORAL3,
  Quantity_NOC_CORAL4,
  Quantity_NOC_CORNFLOWERBLUE,
  Quantity_NOC_CORNSILK1
  };
}

class ColorCollectionWidget:public QWidget{
   private:
    //Store collections of colour
    Q_OBJECT
    Quantity_Color ChosenColor;
    
    std::unique_ptr<Section>ColorSection;
    std::unique_ptr<QVBoxLayout> vlayout_1; //
    std::unique_ptr<QFormLayout> formlayout;
    size_t NbColor=0;
   public:
   ColorCollectionWidget(QWidget *parent=nullptr):QWidget(parent){
      
      vlayout_1.reset(new QVBoxLayout);
      formlayout.reset(new QFormLayout);
      ColorSection.reset(new Section(tr("Colour Section"),2,this));
      
      vlayout_1->setAlignment(Qt::AlignLeft|Qt::AlignTop);
      if(NC::colorarray.empty()){
        std::cout<<"Colour Array Is Empty"<<std::endl;
        return;
      }
      for(auto c:NC::colorarray){
        formlayout->addRow(QString("Color ")+QString::number(NbColor),new ColorPane(ColorSection.get(),Quantity_Color(c),NbColor));
        QObject::connect(static_cast<ColorPane*>(formlayout->itemAt(NbColor,QFormLayout::FieldRole)->widget()),&ColorPane::IsDoubleClicked,this,&ColorCollectionWidget::isChosen);
        
         ++NbColor;
      }
      if(formlayout->count()==GetNbColor()){
        std::cout<<"They are equal"<<formlayout->count()<<std::endl;
      }
      ColorSection->setContentLayout(*formlayout.get());
     vlayout_1->addWidget(ColorSection.get());
     setLayout(vlayout_1.get());
   }
Quantity_Color GetChosenColor() const{
    return ChosenColor;
   }
size_t GetNbColor() const{
    return NbColor;
}
 ~ColorCollectionWidget(){
    
}  
signals:
void GetSelectedColor();   //at this point, the color is selected
public slots:
 
void isChosen(size_t ind){
        if(!formlayout.get()){
            return;
        }
        ChosenColor=static_cast<ColorPane*>(formlayout->itemAt(ind,QFormLayout::FieldRole)->widget())->GetOCColor();
    
    
    emit GetSelectedColor();
    std::cout<<"Current Chosen Index:"<<ind<<std::endl;
    return;
}


 
};














#endif