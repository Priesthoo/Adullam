#pragma once
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;
class ImageMenu:public QMenu{
public:
 unique_ptr<QAction> loadImageAction;
 unique_ptr<QAction> copyAction;
 unique_ptr<QAction> pasteAction;
 public:
 ImageMenu(){
    loadImageAction=make_unique<QAction>(tr("Load Image"),nullptr);
    copyAction=make_unique<QAction>(tr("Copy"),nullptr);
    pasteAction=make_unique<QAction>(tr("Paste"),nullptr);
    addAction(loadImageAction.get());
    addAction(copyAction.get());
    addAction(pasteAction.get());
    return;
 }

};