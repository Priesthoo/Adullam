#pragma once 
#include<iostream>
#include<QtWidgets/QWidget>

using namespace std;
class DisplayedWidget:public QWidget{
private:
Q_OBJECT
QWidget* ContentWidget;

public:
DisplayedWidget():QWidget(){

}
void SetContentWidget(QWidget* widget){
    if(widget==nullptr){
        std::cout<<"Widget is nullptr in SetContentWidget() of DisplayedWidget"<<std::endl;
    }
    ContentWidget=widget;
    return;
}
QWidget* contentWidget(){
    return ContentWidget;
}
~DisplayedWidget(){
    if(ContentWidget){
        delete ContentWidget;
         ContentWidget=nullptr;
}
   
}
};