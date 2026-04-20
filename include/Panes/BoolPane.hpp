#pragma once
#include<QtWidgets/QCheckBox>
#include<Section.h>
#include<QtWidgets/QVBoxLayout>
#include<memory>
class BoolPane:public Section{
private:
std::unique_ptr<QCheckBox> m_checkbox;
std::unique_ptr<QVBoxLayout> vlayout;
public:
BoolPane(const bool& value,const QString& value_1,const QString& title,QWidget*parent=nullptr):Section(title,2,parent){
    m_checkbox.reset(new QCheckBox(value_1,this));
    vlayout.reset(new QVBoxLayout);
    if(m_checkbox.get()){
        m_checkbox->setCheckable(value);
    }
   vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
   vlayout->addWidget(m_checkbox.get());
   setContentLayout(*vlayout.get());

   return;
}

QCheckBox* boolCheckBox() const{
    return m_checkbox.get();
}
};