#ifndef DRAWCUBEDIALOG_HPP
#define DRAWCUBEDIALOG_HPP
#include<QtWidgets/QDialog>
#include<DoubleLineEdit.hpp>
#include<memory>
#include<QtWidgets/QPushButton>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QVBoxLayout>

#include<OneValueSection.hpp>

class DrawCubeDialog:public QDialog {
private:
std::unique_ptr<OneValueSection> input_valueSection;
std::unique_ptr<QPushButton> submit_button;
  QVBoxLayout* vlayout=nullptr;

public:
DrawCubeDialog(QWidget* parent):QDialog(parent){
    input_valueSection.reset(new OneValueSection(tr("Draw Cube"),tr("Size:"),2,this,0.0));
    submit_button.reset(new QPushButton(tr("Submit Command"),this));
    vlayout=new QVBoxLayout;
    vlayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    vlayout->addWidget(input_valueSection.get());
    vlayout->addWidget(submit_button.get());
    setLayout(vlayout); 

}
~DrawCubeDialog(){
    if(vlayout){
        delete vlayout;
        vlayout=nullptr;
    }
}
};








#endif