#ifndef COLOR_PANE_HPP
#define COLOR_PANE_HPP
#include<QtWidgets/QWidget>
#include<QtGui/QColor>
#include<QtGui/QBrush>
#include<QtGui/QMouseEvent>
#include<QtGui/QPainter>
#include<QtGui/QPainterPath>
#include<Quantity_Color.hxx>
class ColorPane:public QWidget{
private:
Q_OBJECT
QColor myCurrentColor;
bool isDoubleClicked=false;

size_t index=0;
public:
ColorPane(QWidget* parent=nullptr,const Quantity_Color& color=Quantity_Color(),const size_t& idx=0):QWidget(parent){
   setAutoFillBackground(true);
   resize(50,50);
   SetColorFromOC(color);
   index=idx;
}
void SetColour(const QColor& pcolor){
    myCurrentColor=pcolor;
    update();  //this calls the paint event;
    return;
}
Quantity_Color GetOCColor() const{
  //inplace construction
  return Quantity_Color(myCurrentColor.redF(),myCurrentColor.greenF(),myCurrentColor.blueF(),Quantity_TOC_sRGB);

}
void SetColorF(const float& pr,const float& pg,const float& pb){
  myCurrentColor.setRedF(pr);
  myCurrentColor.setGreenF(pg);
  myCurrentColor.setBlueF(pb);

  update();
  return;
} //floating point precision 
void SetColorFromOC(const Quantity_Color& color){
  SetColorF(color.Red(),color.Green(),color.Blue());

  return;
}
size_t GetIndex() const{
  return index;
}
void paintEvent(QPaintEvent* event){
    QPainter painter(this);  //this inherits from QPainterDevice 
    QPainterPath myPath;
    
    painter.setBackground(QBrush(Qt::transparent));
    painter.setBrush(QBrush(myCurrentColor));
    QPen pen(Qt::white);
    QRectF rectf(static_cast<float>(rect().x()),static_cast<float>(rect().y()),static_cast<float>(size().width()),static_cast<float>(size().height()));

    
    myPath.addRoundedRect(rectf,5.0,5.0);
    painter.fillPath(myPath,painter.brush()); //fill the rectnagle with painter's brush
     
    painter.setClipPath(myPath);
    painter.strokePath(myPath,pen);
    
}
void SetIsDoubleClicked(const bool& isClicked){
  isDoubleClicked=isClicked;
  return;
}
virtual ~ColorPane(){}
protected:
void mousePressEvent(QMouseEvent* event) override {
   QWidget::mousePressEvent(event);
   if(event->button()==Qt::RightButton){
    return;
   }
   isDoubleClicked=true; //the mouse is doubled clicked on this widget
   
   emit IsDoubleClicked(index);
    
    
    
   
   return;
}
signals:
void IsDoubleClicked(size_t ind);

};






#endif