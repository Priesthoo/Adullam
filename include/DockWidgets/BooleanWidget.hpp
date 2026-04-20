#pragma once 
#include<BoolPane.hpp>
#include<QtWidgets/QWidget>
#include<memory>


class BooleanWidget:public QWidget{
public:
std::unique_ptr<BoolPane> m_Pane;
std::unique_ptr<QVBoxLayout> vlayout;
BooleanWidget(){

}
BooleanWidget(const bool& value,const QString& name,QWidget* parent,const QString& title):QWidget(parent){
    m_Pane.reset(new BoolPane(value,name,title,this));
    boolPane()->boolCheckBox()->setCheckable(true);
    vlayout.reset(new QVBoxLayout);
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    vlayout->addWidget(m_Pane.get());
    setLayout(vlayout.get());
}
void SetChecked(bool value){
    if(m_Pane.get()){
        m_Pane->boolCheckBox()->setChecked(value);
        return;
    }
    return;
}
BoolPane* boolPane() const{
    return m_Pane.get();
}
};