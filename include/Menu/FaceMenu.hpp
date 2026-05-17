#pragma once
#include<QtWidgets/QMenu>
#include<memory>
class FaceMenu:public QMenu{
public:
std::unique_ptr<QAction> showInfoAction;
std::unique_ptr<QAction> assumeFaceNormal;
std::unique_ptr<QAction> convertAction;
std::unique_ptr<QAction> searchAction;
std::unique_ptr<QAction> DrawAction;

FaceMenu():QMenu(){
    showInfoAction=std::make_unique<QAction>(tr("Show Info"),nullptr);
    convertAction=std::make_unique<QAction>(tr("Convert To Face Node"),nullptr);
    convertAction->setCheckable(true);
    searchAction=std::make_unique<QAction>(tr("Find In NodeGraph"),nullptr);
    DrawAction=std::make_unique<QAction>(tr("Draw Polygons"),nullptr);
    assumeFaceNormal=std::make_unique<QAction>(tr("Assume Face Normal"),nullptr);
    addAction(searchAction.get());
    addAction(assumeFaceNormal.get());
    addAction(showInfoAction.get());
    addAction(convertAction.get());
    addAction(DrawAction.get());
}

};