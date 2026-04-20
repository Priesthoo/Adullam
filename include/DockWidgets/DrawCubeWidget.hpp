#ifndef DRAWCUBEWIDGET_HPP
#define DRAWCUBEWIDGET_HPP
#include<QtWidgets/QWidget>
#include<DoubleLineEdit.hpp>
#include<memory>
#include<QtWidgets/QPushButton>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QVBoxLayout>

#include<OneValueSection.hpp>

class DrawCubeWidget:public QWidget{
public:
std::unique_ptr<OneValueSection> input_valueSection;
std::unique_ptr<QPushButton> submit_button;
  QVBoxLayout* vlayout=nullptr;

  public:
  DrawCubeWidget(QWidget* parent=nullptr):QWidget(parent){
    input_valueSection.reset(new OneValueSection(tr("Draw Cube"),tr("Size:"),2,this,0.0));
    submit_button.reset(new QPushButton(tr("Submit Command"),this));
    vlayout=new QVBoxLayout;
    vlayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    vlayout->addWidget(input_valueSection.get());
    vlayout->addWidget(submit_button.get());
    setLayout(vlayout); 
  }
  ~DrawCubeWidget(){
    if(vlayout){
      delete vlayout;
      vlayout=nullptr;
    }
  }
};



#endif