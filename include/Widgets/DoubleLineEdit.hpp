#ifndef DOUBLE_LINE_EDIT_HPP
#define DOUBLE_LINE_EDIT_HPP
#include<QtWidgets/QLineEdit>
#include<QtGui/QValidator>
class DoubleEdit:public QLineEdit{
private:
Q_OBJECT
public:
QDoubleValidator* validator=nullptr;
bool isConverted=false;  //This tells us if we have successfully converted from string to float,by default,it is false
public:

DoubleEdit(QWidget* parent,const QString& content,const size_t& decimal):QLineEdit(content,parent){
    validator=new QDoubleValidator;
    validator->setNotation(QDoubleValidator::StandardNotation);
    validator->setDecimals(decimal);
    setValidator(validator);
    setAlignment(Qt::AlignHCenter);
   connect(static_cast<QLineEdit*>(this),&QLineEdit::textEdited,this,&DoubleEdit::OnConvertToFloat);
}
QLocale GetLocale() const{
    return validator->locale();
}
~DoubleEdit(){
    if(validator){
        delete validator;
        validator=nullptr;
    }
}

signals:
void GetValue(const float& value);

public slots:
void OnConvertToFloat(const QString& str){
    if(str.isEmpty()){
        return;
    }
    //At this point,the string is not empty
    float value=GetLocale().toFloat(str,&isConverted);
    emit GetValue(value);
    return;
}
void OnTextEdited(const QString& str){
    
    return;
}
void SetValue(const float val){
    setText(QString::number(val));
    emit GetValue(val);
    return;
}



};










#endif