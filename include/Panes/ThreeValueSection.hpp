#ifndef THREE_VALUE_SECTION_HPP
#define THREE_VALUE_SECTION_HPP

#include<QtWidgets/QLabel>
#include<QtWidgets/QGridLayout>
#include<DoubleLineEdit>
#include<memory>
class ThreeValueSection:public Section{
   private:
   std::unique_ptr<DoubleEdit> X_Edit;
   std::unique_ptr<DoubleEdit> Y_Edit;
   std::unique_ptr<DoubleEdit> Z_Edit;
   QFormLayout* qformlayout=nullptr;
 public:
 ThreeValueSection(const QString& pSec,const size_t& psz,QWidget* parent,const float& x,const float& y,const float& z):Section(pSec,psz,parent){
     qformlayout=new QFormLayout;
     X_Edit.reset(new DoubleEdit(this,QString::number(x)),8);
     Y_Edit.reset(new DoubleEdit(this,QString::number(y)),8);
     Z_Edit.reset(new DoubleEdit(this,QString(z)),8);
     qformlayout->addRow(tr("X:"),X_Edit.get());
      qformlayout->addRow(tr("Y:"),Y_Edit.get());
     qformlayout->addRow(tr("Z:"),Z_Edit.get()); 
     setContentLayout(*qformlayout); 
 }
 ~ThreeValueSection(){
    if(qformlayout){
        delete qformlayout;
        qformlayout=nullptr;
    }
 }
};



#endif