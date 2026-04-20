#pragma once 
#include<ColorPane.hpp>
//create a tabwidget, nodewidget array
class FixedColorPane:public ColorPane{
private:


public:
FixedColorPane(QWidget* parent=nullptr):ColorPane(parent){
   setFixedSize(QSize(60,60));
}

};
class VariableColorPane:public ColorPane{
private:


public:
VariableColorPane(QWidget* parent,const QSize& sz):ColorPane(parent){
   setFixedSize(sz);
   return;
}

};

