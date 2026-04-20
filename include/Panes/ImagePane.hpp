#ifndef IMAGE_PANE_HPP
#define IMAGE_PANE_HPP
#include<QtWidgets/QWidget>
#include<QtGui/QImage>
///This is to draw an image on a widget of a particular size.....
class ImagePane:public QWidget{
private:
QImage loadedimage;
QString Error;   //this will store the error result

public:
ImagePane(const QString& file_name,QWidget* parent):QWidget(parent){
setAutoFillBackground(true);
loadedimage.load(file_name,nullptr);

if(loadedimage.isNull()){
    Error=QString(tr("Failed to load image,check the supported file format or the file path"));
    return;
}

}
void paintEvent(QPaintEvent* event) override{
    
  return;  
}

};







#endif