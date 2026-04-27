#ifndef TREEWIDGET_HPP
#define TREEWIDGET_HPP
#include<QtWidgets/QTreeView>
#include<QtGui/QFileSystemModel>
//Treeview is actually a view part of MVC(model,view,controller),Every 
//A lot of work needs to be done here
class TreeViewWidget:public QTreeView{
 QFileSystemModel* filesystemmodel;
 
public:
TreeViewWidget(QWidget* parent):QTreeView(parent){
   filesystemmodel=new QFileSystemModel(this);
   setModel(filesystemmodel);
   filesystemmodel->setRootPath(tr(""));
   
   setHeaderHidden(true);
   setSortingEnabled(true);
   for(int i=1;i<filesystemmodel->columnCount();i++){
     setColumnHidden(i,true);
   }

}
void SetRootPath(const QString& path){
    filesystemmodel->setRootPath(path);
    setRootIndex(filesystemmodel->index(path));
    return;
}
bool IsDir(const QModelIndex& index){
    return filesystemmodel->isDir(index);
}
QModelIndex Index(const QString& filename) const {
    return filesystemmodel->index(filename);
}
QString FilePath(const QModelIndex& index){
    return filesystemmodel->filePath(index);
}
void UpdateView(const QModelIndex& index){
       filesystemmodel->fetchMore(index);
       return;
}
void MakeDir(const QModelIndex& index,const QString& name){
    filesystemmodel->mkdir(index,name);
    UpdateView(index);
    return;
}

~TreeViewWidget(){
    if(filesystemmodel!=nullptr){
        delete filesystemmodel;
        filesystemmodel=nullptr;
    }

}
};





#endif