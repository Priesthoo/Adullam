#pragma once
//This will contain details about setting float values
#include<QtWidgets/QWidget>
#include<OneValueSection.hpp>
#include<QtWidgets/QVBoxLayout>
#include<memory>
class FloatNodeWidget:public QWidget{
Q_OBJECT
 std::unique_ptr<OneValueSection> FloatInputSection; 
 std::unique_ptr<QVBoxLayout> vlayout; 
public:
 FloatNodeWidget(const QString& desc,const float& value):QWidget(){
   FloatInputSection.reset(new OneValueSection(desc,tr("Input Value:"),2,this,value));
   vlayout.reset(new QVBoxLayout);
   vlayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
   vlayout->addWidget(FloatInputSection.get());
   setLayout(vlayout.get());

 }
 DoubleEdit* ValueEdit() const{
     return FloatInputSection->myValueEdit.get();
 }
 void SetValue(const float& value){
     if(FloatInputSection.get()){
       FloatInputSection->myValueEdit->setText(QString::number(value));
       return;
     }
     return;
 }
 ~FloatNodeWidget(){

 }
 
 
};