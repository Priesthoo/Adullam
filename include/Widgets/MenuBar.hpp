#ifndef MENUBAR_HPP
#define MENUBAR_HPP
#include<QtWidgets/QMenuBar>
#include<QtWidgets/QWidget>
//This will contain all items on the menubar, File, Edit,
class MenuBar:public QMenuBar{
Q_OBJECT
size_t MenuBarItemNum;
public:
MenuBar(QWidget* widget):QMenuBar(widget){  
    MenuBarItemNum=0;  //since there are no items yet,
}
};









#endif 