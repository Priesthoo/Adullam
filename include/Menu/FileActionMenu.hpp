#ifndef FILEMENU_HPP
#define FILEMENU_HPP
#include<QtWidgets/QMenu>
#include<memory>
class FileMenu:public QMenu{
Q_OBJECT
   std::unique_ptr<QAction> OpenStepFileAction;
    std::unique_ptr<QAction> OpenIgesFileAction;
    std::unique_ptr<QAction> AutoSaveAction;
    std::unique_ptr<QAction> NewStepFileAction;
    std::unique_ptr<QAction> NewIgesFileAction;
    std::unique_ptr<QAction> SaveStepFileAction;
    std::unique_ptr<QAction> SaveIgesFileAction;
    std::unique_ptr<QAction> FileHistoryAction;
    std::unique_ptr<QAction> CloseFileAction;

public:
bool isStepFile=false;  //This will be used when we want to create a step file
bool isIgesFile=false;  //This will be used when we want an Iges File

FileMenu():QMenu(){
 OpenStepFileAction.reset(new QAction(tr("Open .Step file"),nullptr));
 OpenStepFileAction->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_O));  //Use CTRL + O to open file 
  addAction(OpenStepFileAction.get());
  OpenIgesFileAction.reset(new QAction(tr("Open .Iges File"),nullptr));
  OpenIgesFileAction->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_P));
  addAction(OpenIgesFileAction.get());
  addSeparator();
  AutoSaveAction.reset(new QAction(tr("Auto Save"),nullptr));
  AutoSaveAction->setCheckable(true); 
  AutoSaveAction->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_A));
  addAction(AutoSaveAction.get()); 
  addSeparator(); 
  NewStepFileAction.reset(new QAction(tr("New .Step File"),nullptr));
  NewStepFileAction->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_N));
  addAction(NewStepFileAction.get());

  NewIgesFileAction.reset(new QAction(tr("New .Iges File"),nullptr));
  NewIgesFileAction->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_M));
  addAction(NewIgesFileAction.get());
  addSeparator();
  SaveStepFileAction.reset(new QAction(tr("Save .Step File"),nullptr));
  SaveStepFileAction->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_S));
  addAction(SaveStepFileAction.get());
  SaveIgesFileAction.reset(new QAction(tr("Save.Iges File"),nullptr));
  addAction(SaveIgesFileAction.get());
  SaveIgesFileAction->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_C));
  addSeparator();
   FileHistoryAction.reset(new QAction(tr("File History"),nullptr));
   addSeparator();
  CloseFileAction.reset(new QAction(tr("Close File"),nullptr));
 
}
QAction* OpenStepFile(){
  return OpenStepFileAction.get();
}
QAction* OpenIgesFile(){
  return OpenIgesFileAction.get();
}
QAction* NewStepFile(){
  return NewStepFileAction.get();
}
QAction* NewIgesFile(){
  return NewIgesFileAction.get();
}
QAction* SaveStepFile(){
  return SaveStepFileAction.get();
}
QAction* SaveIgesFile(){
  return SaveIgesFileAction.get();
}
QAction* FileHistory(){
  return FileHistoryAction.get();
}
QAction* CloseFile(){
  return CloseFileAction.get();
}

signals:
void CanOpenFileDialog(bool CanOpenFile);
void CanCreateNewFile(bool CanSaveFile);
void CanAutoSaveFile(bool CanAutoSave);

public slots:

};








#endif