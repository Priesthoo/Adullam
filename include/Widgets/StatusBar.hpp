#ifndef STATUS_BAR_HPP
#define STATUS_BAR_HPP
#include<QtWidgets/QStatusBar>
#include<QtWidgets/QWidget>
class StatusBar:public QStatusBar{
Q_OBJECT

size_t WidgetsCount;
bool AnyWidgetInserted;
public:
StatusBar(QWidget* parent):QStatusBar(parent){
WidgetsCount=0;
AnyWidgetInserted=false;
}

signals:

public slots:

};







#endif 