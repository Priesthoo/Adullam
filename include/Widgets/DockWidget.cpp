
#include<DockWidget.hpp>

DockWidget::DockWidget(QWidget* parent_widget,const QString& WidgetTitle):QDockWidget(WidgetTitle,parent_widget){
    
    setMinimumSize(100,100);
    setFeatures(features());
    scrollarea=new QScrollArea(this);
    scrollarea->setWidgetResizable(true);
    scrollarea->setVisible(true);
    setWidget(scrollarea);
    
} 
