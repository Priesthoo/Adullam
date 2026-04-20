#pragma once
#include<QtWidgets/QMenu>
#include<memory>
class FaceMenu:public QMenu{
public:
std::unique_ptr<QAction> showInfoAction;
std::unique_ptr<QAction> convertAction;

FaceMenu():QMenu(){
    showInfoAction=std::make_unique<QAction>(tr("Show Info"),nullptr);
    convertAction=std::make_unique<QAction>(tr("Convert To Node"),nullptr);
    convertAction->setCheckable(true);
    addAction(showInfoAction.get());
    addAction(convertAction.get());
}

};