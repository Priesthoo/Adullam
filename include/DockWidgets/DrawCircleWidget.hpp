#ifndef DRAWCIRCLEWIDGET_HPP
#define DRAWCIRCLEWIDGET_HPP
#include<QtWidgets/QWidget>
#include<DoubleLineEdit.hpp>
#include<memory>
#include<QtWidgets/QPushButton>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QVBoxLayout>

#include<OneValueSection.hpp>
/*L
+ InputValueSection
--------------------------------------
Input Value : |____________________|
----------------------------
+


*/
class DrawCircleWidget:public QWidget{
  private:
  std::unique_ptr<Section> input_valueSection;
  std::unique_ptr<QPushButton> submit_button;
  QVBoxLayout* vlayout=nullptr;

  public:
  DrawCircleWidget(QWidget* parent):QWidget(parent){
    input_valueSection.reset(new OneValueSection(tr("Draw Circle"),tr("Radius:"),2,this,0.0));
    submit_button.reset(new QPushButton(tr("Submit Command"),this));
    vlayout=new QVBoxLayout;
    vlayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    vlayout->addWidget(input_valueSection.get());
    vlayout->addWidget(submit_button.get());
    setLayout(vlayout); 
  }
  ~DrawCircleWidget(){
    if(vlayout){
      delete vlayout;
      vlayout=nullptr;
    }
  }

};















#endif