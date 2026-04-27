#pragma once
#include<QtWidgets/QMenu>
#include<iostream>
#include<memory>
using namespace std;
class NodeSceneMenu:public QMenu{
private:
std::unique_ptr<QAction> deleteNodeAction;
std::unique_ptr<QAction> compileNodesAction;
std::unique_ptr<QAction> autoCompileAction;
std::unique_ptr<QAction> copyNodeAction;
std::unique_ptr<QAction> pasteNodeAction;
std::unique_ptr<QAction> saveFileAction;
std::unique_ptr<QAction> saveAsAction;
std::unique_ptr<QAction> clearAction;
std::unique_ptr<QAction> nodeInfoAction;
public:
NodeSceneMenu(){
    deleteNodeAction=make_unique<QAction>(tr("Delete Node"),nullptr);
    compileNodesAction=make_unique<QAction>(tr("Compile Nodes"),nullptr);
    autoCompileAction=make_unique<QAction>(tr("Auto Compile"),nullptr);
    autoCompileAction->setCheckable(true);
    copyNodeAction=make_unique<QAction>(tr("Copy"),nullptr);
    pasteNodeAction=make_unique<QAction>(tr("Paste"),nullptr);
    saveFileAction=make_unique<QAction>(tr("Save .nCAD"),nullptr);
    saveAsAction=std::make_unique<QAction>(tr("Save As"),nullptr);
    clearAction=std::make_unique<QAction>(tr("Clear"),nullptr);
    nodeInfoAction=std::make_unique<QAction>(tr("Show NodeInfo"),nullptr);

    addAction(deleteNodeAction.get());
    addAction(compileNodesAction.get());
    addAction(autoCompileAction.get());
    addAction(copyNodeAction.get());
    addAction(pasteNodeAction.get());
    addAction(saveFileAction.get());
    addAction(saveAsAction.get());
    addAction(clearAction.get());
    addAction(nodeInfoAction.get());

    
    return;
}
QAction* DeleteNodeAction() const{
    return deleteNodeAction.get();
}
QAction* CompileNodesAction() const{
    return compileNodesAction.get();
}
QAction* AutoCompileAction() const{
    return autoCompileAction.get();
}
QAction* CopyNodeAction() const{
    return copyNodeAction.get();
}
QAction* PasteNodeAction() const{
    return pasteNodeAction.get();
}
QAction* SaveFileAction() const{
    return saveFileAction.get();
}
QAction* SaveAsAction() const{
    return saveAsAction.get();
}
QAction*  ClearAction() const{
    return clearAction.get();
}
QAction* NodeInfoAction() const{
    return nodeInfoAction.get();
}
};