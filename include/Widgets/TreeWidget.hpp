#ifndef TREEWIDGET_HPP
#define TREEWIDGET_HPP
#include<QtWidgets/QTreeView>
#include<QtGui/QFileSystemModel>
//Treeview is actually a view part of MVC(model,view,controller),Every 
class TreeViewWidget:public QTreeView{
 QFileSystemModel* filesystemmodel;
 
public:
TreeViewWidget(QWidget* parent):QTreeView(parent){
   filesystemmodel=new QFileSystemModel(this);
   setModel(filesystemmodel);
   filesystemmodel->setRootPath(QDir::currentPath());
   setRootIndex(filesystemmodel->index(QDir::currentPath()));
}


~TreeViewWidget(){
    if(filesystemmodel!=nullptr){
        delete filesystemmodel;
        filesystemmodel=nullptr;
    }

}
};





#endif