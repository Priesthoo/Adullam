#pragma once
#include<QtWidgets/QMenu>
#include<memory>

using namespace std;

class TreeFolderMenu:public QMenu{
public:
std::unique_ptr<QAction> NewFileAction;
std::unique_ptr<QAction> NewFolderAction;
std::unique_ptr<QAction> copyAction;
std::unique_ptr<QAction> cutAction;
std::unique_ptr<QAction> renameAction;
std::unique_ptr<QAction> copyFilePathAction;
std::unique_ptr<QAction> pasteAction;
std::unique_ptr<QAction> deleteAction;

public:
TreeFolderMenu(){
    NewFileAction=std::make_unique<QAction>(tr("New File"),nullptr);
    NewFolderAction=std::make_unique<QAction>(tr("New Folder"),nullptr);
    copyAction=std::make_unique<QAction>(tr("Copy"),nullptr);
    cutAction=std::make_unique<QAction>(tr("Cut"),nullptr);
    renameAction=std::make_unique<QAction>(tr("Rename..."),nullptr);
    copyFilePathAction=std::make_unique<QAction>(tr("Copy Path"),nullptr);
    pasteAction=std::make_unique<QAction>(tr("Paste"),nullptr);
    deleteAction=std::make_unique<QAction>(tr("Delete"),nullptr);
    addAction(NewFileAction.get());
    addAction(NewFolderAction.get());
    addAction(copyAction.get());
    addAction(cutAction.get());
    addAction(pasteAction.get());
    addAction(renameAction.get());
    addAction(copyFilePathAction.get());
    
    addAction(deleteAction.get());

}


};