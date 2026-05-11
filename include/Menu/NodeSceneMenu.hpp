#pragma once
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;
class NodeSceneMenu:public QMenu{
private:
std::unique_ptr<QAction> openFileAction;
std::unique_ptr<QAction> deleteNodeAction;
std::unique_ptr<QAction> compileNodesAction;
std::unique_ptr<QAction> autoCompileAction;
std::unique_ptr<QAction> copyNodeAction;
std::unique_ptr<QAction> pasteNodeAction;
std::unique_ptr<QAction> saveFileAction;
std::unique_ptr<QAction> saveAsAction;
std::unique_ptr<QAction> clearAction;
std::unique_ptr<QAction> nodeInfoAction;
std::unique_ptr<QAction> enableDragModeAction;
public:
NodeSceneMenu(){
    deleteNodeAction=make_unique<QAction>(tr("Delete Node"),nullptr);
    compileNodesAction=make_unique<QAction>(tr("Compile Nodes"),nullptr);
    autoCompileAction=make_unique<QAction>(tr("Auto Compile"),nullptr);
    autoCompileAction->setCheckable(true);
    openFileAction=make_unique<QAction>(tr("Open .nCAD file"),nullptr);
    copyNodeAction=make_unique<QAction>(tr("Copy"),nullptr);
    pasteNodeAction=make_unique<QAction>(tr("Paste"),nullptr);
    saveFileAction=make_unique<QAction>(tr("Save .nCAD"),nullptr);
    saveAsAction=std::make_unique<QAction>(tr("Save As"),nullptr);
    clearAction=std::make_unique<QAction>(tr("Clear"),nullptr);
    nodeInfoAction=std::make_unique<QAction>(tr("Show NodeInfo"),nullptr);
    enableDragModeAction=std::make_unique<QAction>(tr("Enable Drag Mode"),nullptr);
    enableDragModeAction->setCheckable(true);
    addAction(deleteNodeAction.get());
    addAction(compileNodesAction.get());
    addAction(autoCompileAction.get());
    addAction(openFileAction.get());
    addAction(copyNodeAction.get());
    addAction(pasteNodeAction.get());
    addAction(saveFileAction.get());
    addAction(saveAsAction.get());
    addAction(clearAction.get());
    addAction(enableDragModeAction.get());
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
QAction* OpenFileAction() const{
    return openFileAction.get();
}
QAction* EnableDragMode()const{
    return enableDragModeAction.get();
}
};


class SinglyShapeMenu:public QMenu{
private:
std::unique_ptr<QAction> highlightAction;
std::unique_ptr<QAction> deleteAction;
std::unique_ptr<QAction> deleteNodeAction;
std::unique_ptr<QAction> getIndexAction;

public:
SinglyShapeMenu():QMenu(){
 highlightAction=std::make_unique<QAction>(tr("Highlight"),nullptr);
 deleteAction=std::make_unique<QAction>(tr("Delete"),nullptr);
 deleteNodeAction=std::make_unique<QAction>(tr("Delete Node"),nullptr);
 getIndexAction=std::make_unique<QAction>(tr("Show Index"),nullptr);
 addAction(highlightAction.get());
 addAction(deleteAction.get());
 addAction(deleteNodeAction.get());
 addAction(getIndexAction.get());
    return;
}
QAction* HighlightAction() const{
    return highlightAction.get();
}
QAction* DeleteAction() const{
    return deleteAction.get();
}
QAction* DeleteNodeAction() const{
    return deleteNodeAction.get();
}
QAction* GetIndexAction() const{
    return getIndexAction.get();
}
};
class DragMenu:public QMenu{
public:
std::unique_ptr<QAction> disableDragAction;
std::unique_ptr<QAction> convertToCmdShape;
std::unique_ptr<QAction> deleteNodes;
DragMenu():QMenu(){
    disableDragAction=std::make_unique<QAction>(tr("Disable Drag"),nullptr);
    disableDragAction->setCheckable(true);
    convertToCmdShape=std::make_unique<QAction>(tr("Convert To Command Shape"),nullptr);
    deleteNodes=std::make_unique<QAction>(tr("Delete Node(s)"));
    addAction(disableDragAction.get());
    addAction(convertToCmdShape.get());
    addAction(deleteNodes.get());
    return;
}
};