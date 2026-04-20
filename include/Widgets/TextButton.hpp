#pragma once 
#include<QtWidgets/QPushButton>


class TextButton:public QPushButton{
private:
Q_OBJECT
 int buttonId=-1;

public:
TextButton(QWidget* parent,const QString& Title,const int& id):QPushButton(Title,parent){
    buttonId=id;
    connect(this,&TextButton::pressed,this,&TextButton::ButtonHandler);
    return;
}
int ButtonId() const{
    return buttonId;
}
signals:
void EmitId(int id);
public slots:
 void ButtonHandler(){
    emit EmitId(buttonId);
    return;
 }
};