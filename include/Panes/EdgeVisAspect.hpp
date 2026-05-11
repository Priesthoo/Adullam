#pragma once 
#include<Section.h>
#include<QtWidgets/QWidget>
#include<FixedColorPane.hpp>
#include<QtWidgets/QFormLayout>
#include<DoubleLineEdit.hpp>
#include<memory>
using namespace std;

class EdgeVisual:public Section{
public:
std::unique_ptr<QFormLayout> formlayout;
std::unique_ptr<VariableColorPane> colorPane;
std::unique_ptr<DoubleEdit> doubleEdit;


public:
EdgeVisual(QWidget* parent,const QString& title):Section(title,2,parent){
    formlayout=make_unique<QFormLayout>();
    colorPane=make_unique<VariableColorPane>(this,QSize(80,80));
    doubleEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8);
    formlayout->addRow(tr("Line Color"),colorPane.get());
    formlayout->addRow(tr("Line Width"),doubleEdit.get());
    setContentLayout(*formlayout.get()); 
}
};