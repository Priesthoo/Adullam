#ifndef ONE_VALUE_SECTION_HPP
#define ONE_VALUE_SECTION_HPP
#include<QtWidgets/QFormLayout>
#include<DoubleLineEdit.hpp>
#include<memory>
#include<Section.h>
class OneValueSection:public Section{
public:
std::unique_ptr<DoubleEdit> myValueEdit;
QFormLayout* formlayout=nullptr;


public:
OneValueSection(const QString& psec,const QString& label_name,const size_t& sz,QWidget* parent,const float& edit_value):Section(psec,sz,parent){
   formlayout=new QFormLayout;
   myValueEdit.reset(new DoubleEdit(this,QString::number(edit_value),8));
   formlayout->addRow(label_name,myValueEdit.get());
   setContentLayout(*formlayout);
}
~OneValueSection(){
    if(formlayout){
        delete formlayout;
        formlayout=nullptr;
    }
}
};






#endif 