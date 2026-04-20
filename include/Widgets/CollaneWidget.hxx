#ifndef COLLAPSIBLE_PANE_HPP
#define COLLAPSIBLE_PANE_HPP
#include<QtWidgets/QToolButton>
#include<QtWidgets/QScrollArea>
#include<QtCore/QPropertyAnimation>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QWidget>
class CollaneWidget:public QWidget{
private:
Q_OBJECT
QToolButton* togglebutton=nullptr;
QScrollArea* scrollarea=nullptr;
QWidget* contentWidget=nullptr;
QVBoxLayout* contentLayout=nullptr;
QVBoxLayout* mainCollLayout=nullptr;
QSize FixedSize;

public:
CollaneWidget(const QString& title,QWidget* parent):QWidget(parent){
    mainCollLayout=new QVBoxLayout(this);
    togglebutton=new QToolButton(this);
    togglebutton->setText(title);
    togglebutton->setCheckable(true);
    togglebutton->setChecked(true);
    togglebutton->setArrowType(Qt::DownArrow);
    togglebutton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    scrollarea=new QScrollArea(this);
    scrollarea->setWidgetResizable(true);
    scrollarea->setVisible(true);
     
   contentWidget=new QWidget;
   contentLayout=new QVBoxLayout(contentWidget);
   contentLayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
   scrollarea->setWidget(contentWidget);

   mainCollLayout->addWidget(togglebutton);
   mainCollLayout->addWidget(scrollarea);
   connect(togglebutton,&QToolButton::toggled,this,&CollaneWidget::toggleButtonClicked);
}
void addContent(QWidget* widget){
    if(widget==nullptr){
        return;
    }
    contentLayout->addWidget(widget,0,Qt::AlignBaseline); 
    
    return;
}
~CollaneWidget(){
    if(togglebutton){
        delete togglebutton;
        togglebutton=nullptr;
    }
    if(scrollarea){
        delete scrollarea;
        scrollarea=nullptr;

    }
    if(contentWidget){
        delete contentWidget;
        contentWidget=nullptr;
    }
    if(contentLayout){
        delete contentLayout;
        contentLayout=nullptr;
    }
    if(mainCollLayout){
        delete mainCollLayout;
        mainCollLayout=nullptr;
    }
}
signals:

public slots:
 void toggleButtonClicked(bool clicked){
    scrollarea->setVisible(clicked);
    togglebutton->setArrowType(clicked? Qt::DownArrow :Qt::RightArrow);   
    contentLayout->invalidate();
    contentWidget->adjustSize();
     updateGeometry();
     return;
 }



};



#endif