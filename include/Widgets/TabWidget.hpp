#ifndef TABWIDGETS_HPP
#define TABWIDGETS_HPP
#include<QtWidgets/QTabWidget>
#include<QtWidgets/QWidget>
class TabWidget:public QTabWidget{
private:
Q_OBJECT



public:
TabWidget(QWidget* parent_widget):QTabWidget(parent_widget){
    setTabsClosable(true);
    setUsesScrollButtons(true);
    setTabPosition(QTabWidget::West);
    setTabShape(QTabWidget::Rounded);
    connect(this,&QTabWidget::tabCloseRequested,this,&TabWidget::OnRemoveTab);
}
signals:

public slots:
void OnRemoveTab(int index){
    removeTab(index);
    return;
}


};




#endif