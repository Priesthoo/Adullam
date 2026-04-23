#ifndef FILEMENU_HPP
#define FILEMENU_HPP
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;
class FileMenu:public QMenu{
Q_OBJECT
public:
unique_ptr<QAction> createNewFolder;
unique_ptr<QAction> openFolderAction;  //open the current working folder
unique_ptr<QAction> openNCADFile; //open .nCAD file(this stores the nodes)
unique_ptr<QAction>saveIGESModel; //save IGES model
unique_ptr<QAction>closeFolderAction; //close the current working folder
std::unique_ptr<QAction> createNewFile; //open a new file and we will save the name using 
std::unique_ptr<QAction> autoSave;
public:
bool isStepFile=false;  //This will be used when we want to create a step file
bool isIgesFile=false;  //This will be used when we want an Iges File

FileMenu():QMenu(){
 openFolderAction=std::make_unique<QAction>(tr("Open Folder"),nullptr);
 openNCADFile=std::make_unique<QAction>(tr("Open .nCAD file"),nullptr);
 saveIGESModel=std::make_unique<QAction>(tr("Save .IGES file"),nullptr); 
 closeFolderAction=std::make_unique<QAction>(tr("Close Folder"),nullptr);
 createNewFolder=std::make_unique<QAction>(tr("Create New Folder"),nullptr);
 createNewFile=std::make_unique<QAction>(tr("Create New File"),nullptr);
 autoSave=std::make_unique<QAction>(tr("Auto Save")); //this applies to .nCAD
 autoSave->setCheckable(true);
 addAction(createNewFolder.get());
 addAction(createNewFile.get());
 addAction(openFolderAction.get());
 addAction(openNCADFile.get());
 addAction(saveIGESModel.get());
 addAction(autoSave.get());
 addAction(closeFolderAction.get());
}
signals:
void CanOpenFileDialog(bool CanOpenFile);
void CanCreateNewFile(bool CanSaveFile);
void CanAutoSaveFile(bool CanAutoSave);

public slots:

};








#endif