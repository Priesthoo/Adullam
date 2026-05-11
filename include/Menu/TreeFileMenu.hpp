#pragma once 
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;
class TreeFileMenu:public QMenu{
public:
std::unique_ptr<QAction> openAction;
std::unique_ptr<QAction> copyAction;
std::unique_ptr<QAction> cutAction;
std::unique_ptr<QAction> renameAction;
std::unique_ptr<QAction> copyFilePathAction;
std::unique_ptr<QAction> copyRelativePathAction;
std::unique_ptr<QAction> deleteAction;


public:
TreeFileMenu(){
    openAction=std::make_unique<QAction>(tr("Open .nCAD"),nullptr);
    copyAction=std::make_unique<QAction>(tr("Copy"),nullptr);
    cutAction=std::make_unique<QAction>(tr("Cut"),nullptr);
    renameAction=std::make_unique<QAction>(tr("Rename..."),nullptr);
    copyFilePathAction=std::make_unique<QAction>(tr("Copy Path"),nullptr);
    copyRelativePathAction=std::make_unique<QAction>(tr("Copy Relative Path"),nullptr);
    deleteAction=std::make_unique<QAction>(tr("Delete"),nullptr);
    addAction(openAction.get());
    addAction(copyAction.get());
    addAction(cutAction.get());
    addAction(renameAction.get());
    addAction(copyFilePathAction.get());
    addAction(copyRelativePathAction.get());
    addAction(deleteAction.get());
    
}


};