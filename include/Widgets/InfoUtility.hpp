#pragma once
#include<QtWidgets/QMessageBox>
namespace INFO{
  inline void LoadMessage(const QString& title,const QString& content){
     QMessageBox::information(nullptr,title,content);
     return;
  }
 inline void LoadCritical(const QString& title,const QString& content){
    QMessageBox::critical(nullptr,title,content);
    return;
 }
 inline void LoadAbout(const QString& title,const QString& aboutContent){
    QMessageBox::about(nullptr,title,aboutContent);
    return;
 }
}