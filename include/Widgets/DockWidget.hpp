#ifndef DOCKWIDGET_HPP
#define DOCKWIDGET_HPP
#include<QtWidgets/QDockWidget>
#include<QtWidgets/QWidget>
#include<QtWidgets/QTextEdit>
#include"TitleBarWidget.hpp"
#include<CollaneWidget.hxx>
#include<QtWidgets/QCheckBox>
#include<QtWidgets/QScrollArea>
#include<QtWidgets/QRadioButton>
#include<TabWidget.hpp>
#include<TreeWidget.hpp>
#include<Section.h>
#include<memory>
//This is a DockWidget that will be inserted into the MainWindow...
class DockWidget:public QDockWidget{
private:
Q_OBJECT

QScrollArea* scrollarea=nullptr;

bool ContainsSplittedWidget=false;

size_t WidgetCount=0;
public:
DockWidget(QWidget* parent_widget,const QString& WidgetTitle);
void SetWidget(QWidget* widget){
    if(!scrollarea){
        return;
    }
    scrollarea->setWidget(widget);
    return;
}
QWidget* GetScrolledWidget() const{
    return scrollarea->widget();
}
void RemoveWidget(){
    if(scrollarea){
        scrollarea->takeWidget();
        return;
    }
    return;
}
~DockWidget(){
   
    if(scrollarea){
        delete scrollarea;
        scrollarea=nullptr;
    }
    
}

signals:
void OnChangeTitleBarWidget(QWidget* widget);
public slots:
void OnSetCurrentTitleBarWidget(QWidget* widget){
    return;
}


};






#endif