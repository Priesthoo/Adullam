#ifndef TREEWIDGET_HPP
#define TREEWIDGET_HPP
#include<QtWidgets/QTreeView>
#include<QtGui/QFileSystemModel>
#include<TreeFileMenu.hpp>
#include<QtWidgets/QWidget>
#include<TreeFolderMenu.hpp>
#include<QtWidgets/QFileDialog>
#include<QtCore/QDir>
#include<QtCore/QFileInfo>
#include<QtGui/QMouseEvent>
//Treeview is actually a view part of MVC(model,view,controller),Every 
//A lot of work needs to be done here
class TreeViewWidget:public QTreeView{

 
 QFileSystemModel* filesystemmodel;
public:
 std::unique_ptr<TreeFileMenu> fileMenu;
 std::unique_ptr<TreeFolderMenu> folderMenu;
 bool isCutClicked=false;
 QString copiedFilePath;//it can either be file or folder
public:
TreeViewWidget(QWidget* parent):QTreeView(parent){
   filesystemmodel=new QFileSystemModel(this);
   setModel(filesystemmodel);
   filesystemmodel->setRootPath(tr(""));
   fileMenu=std::make_unique<TreeFileMenu>();
   folderMenu=std::make_unique<TreeFolderMenu>();
   
   setHeaderHidden(true);
   setSortingEnabled(true);
   for(int i=1;i<filesystemmodel->columnCount();i++){
     setColumnHidden(i,true);
   }
   


}
QAction* OpenAction() const{
    return fileMenu->openAction.get();
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
void Remove(const QModelIndex& index){
    if(IsDir(index)){
        filesystemmodel->rmdir(index);
        UpdateView(QModelIndex());
    }
    else{
        filesystemmodel->remove(index);
         UpdateView(QModelIndex());
    }
    return;
}

~TreeViewWidget(){
    if(filesystemmodel!=nullptr){
        delete filesystemmodel;
        filesystemmodel=nullptr;
    }

}
protected:
void mousePressEvent(QMouseEvent* event) override{
     QTreeView::mousePressEvent(event);
    if(event->button()==Qt::RightButton){
        auto index=currentIndex();
        if(IsDir(index)){
           folderMenu->exec(event->globalPosition().toPoint());
        }
        else{
            fileMenu->exec(event->globalPosition().toPoint());
        }
    }
    if(event->button()==Qt::LeftButton){
        auto index=indexAt(event->pos());
        if(!index.isValid()){
          selectionModel()->clearSelection();
          selectionModel()->setCurrentIndex(QModelIndex(),QItemSelectionModel::NoUpdate);
        }
    }
   
    return;
}


};





#endif