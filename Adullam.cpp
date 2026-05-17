#include<QApplication>
#include<QPushButton>
#include<QMessageBox>
#include"WindowFrame.hpp"
#include<QtGui/QIcon>
#include<memory>
int main(int argc, char* argv[]){
    QApplication app(argc,argv);
    //style sheets for all widget
    app.setStyleSheet(R"(
     QWidget { background-color:rgb(50,50,50); 
               color: White;
               border-width:1px;
               padding:1px; 
               }
      QLineEdit{
          border-radius: 4px;
      }
      QMenu::item:selected{
        border-color:rgb(19,10,10);
        background:rgb(51,255,255);
      }
      

    
    )");
    QFont font=app.font();
    font.setPointSizeF(font.pointSizeF()-0.2);
    app.setFont(font);
    QApplication::setWindowIcon(QIcon(QString("../Utilities/IconNodeCAD.png")));
    std::unique_ptr<Window_Frame> WindowFrame;
    WindowFrame.reset(new Window_Frame(nullptr));   //Allocate Memory for Window_Frame
     WindowFrame->resize(500,500);
   WindowFrame->show();     //Show Window Frame
  
    app.exec();      //For event handling
    return 0;
}