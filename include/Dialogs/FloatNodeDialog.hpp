#ifndef FLOAT_NODE_DIALOG_HPP
#define FLOAT_NODE_DIALOG_HPP
#include<QtWidgets/QDialog>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QHBoxLayout>
#include<OneValueSection.hpp>
#include<QtWidgets/QPushButton>
#include<memory>
class FloatNodeDialog:public QDialog{
public:
std::unique_ptr<OneValueSection> Input_ValueSection;
std::unique_ptr<QPushButton> ok_button;
std::unique_ptr<QPushButton> cancel_button;
QVBoxLayout* vlayout=nullptr;  //this will reposition the 
QHBoxLayout* hlayout=nullptr;  //this willreposition the ok button and cancel button 
public:
FloatNodeDialog(QWidget* parent,const float& val):QDialog(parent){
   BuildWidgets(val);  //at this point, we have built the widget using layouts and other subwidgets......
}
void BuildWidgets(const float& val){
  Input_ValueSection.reset(new OneValueSection(tr("Input"),tr("Input Value:"),2,this,val));
  ok_button.reset(new QPushButton(tr("Ok"),this));
  cancel_button.reset(new QPushButton(tr("Cancel"),this));
  hlayout=new QHBoxLayout;
  hlayout->addWidget(ok_button.get());
  hlayout->addSpacing(5); //horizontal spacing 
  hlayout->addWidget(cancel_button.get());
  vlayout=new QVBoxLayout;
  vlayout->setAlignment(Input_ValueSection.get(),Qt::AlignLeft|Qt::AlignTop);
  vlayout->setAlignment(hlayout,Qt::AlignRight|Qt::AlignBottom);
  setLayout(vlayout);
  return;
}
~FloatNodeDialog(){
     if(vlayout){
        delete vlayout;
        vlayout=nullptr;
     }
     if(hlayout){
        delete hlayout;
        hlayout=nullptr;
     }
}

};












#endif