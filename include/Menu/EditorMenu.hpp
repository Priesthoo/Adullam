#pragma once 
#include<QtWidgets/QMenu>
#include<QtWidgets/QWidget>
#include<memory>
using namespace std;
class EditorMenu:public QMenu{
public:
std::unique_ptr<QAction> enableCADView;
std::unique_ptr<QAction> enableNodeGraph;
std::unique_ptr<QAction> enableFileSystem;
std::unique_ptr<QAction> enableChildCADView;
std::unique_ptr<QAction>enableChildNodeGraph;
EditorMenu():QMenu(){
    enableCADView=make_unique<QAction>(tr("CAD View"),nullptr);
    enableNodeGraph=make_unique<QAction>(tr("NodeGraph"),nullptr);
    enableFileSystem=make_unique<QAction>(tr("File System"),nullptr);
    enableChildCADView=make_unique<QAction>(tr("Other View"),nullptr);
    enableChildNodeGraph=make_unique<QAction>(tr("Other Node Graph"),nullptr);
    enableCADView->setCheckable(true);
    enableNodeGraph->setCheckable(true);
    enableFileSystem->setCheckable(true);
    enableChildCADView->setCheckable(true);
    enableChildNodeGraph->setCheckable(true);
    addAction(enableCADView.get());
    addAction(enableNodeGraph.get());
    addAction(enableFileSystem.get());
    addAction(enableChildCADView.get());
    addAction(enableChildNodeGraph.get());
}

};






