#pragma once
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;
class EdgeMenu:public QMenu{
 public:
 std::unique_ptr<QAction> showInfoAction;
std::unique_ptr<QAction> convertAction;
std::unique_ptr<QAction> convertToFaceAction;
std::unique_ptr<QAction> convertToWireAction;
EdgeMenu():QMenu(){
    showInfoAction=std::make_unique<QAction>(tr("Show Info"),nullptr);
    convertAction=std::make_unique<QAction>(tr("Convert To Edge Node"),nullptr);
    convertToFaceAction=make_unique<QAction>(tr("Convert To Face Node"),nullptr);
    convertToWireAction=make_unique<QAction>(tr("Convert To Wire Node"),nullptr);
    convertToWireAction->setCheckable(true);
    convertAction->setCheckable(true);
    convertToFaceAction->setCheckable(true);
    addAction(showInfoAction.get());
    addAction(convertAction.get());
    addAction(convertToFaceAction.get());
    addAction(convertToWireAction.get());
}


};

class PointMenu:public QMenu{
public:
std::unique_ptr<QAction> DeleteAction=std::make_unique<QAction>(tr("Delete"),nullptr);
PointMenu():QMenu()
{
  addAction(DeleteAction.get());
}
};