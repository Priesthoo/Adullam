#ifndef GRAPHICLINE_HPP
#define GRAPHICLINE_HPP
#include<QtGui/QPainter>

class GraphicLine{
private:
QPointF StartPoint;
QPointF EndPoint;
QPen pen;

public:
GraphicLine(){
    StartPoint=QPointF(0.0,0.0);
    EndPoint=QPointF(0.0,0.0);
    
}
GraphicLine(const QPointF& p1,const QPointF& p2){
    StartPoint=p1;
    EndPoint=p2;
}
QPointF& GetStartPoint(){
    return StartPoint;
}
QPointF& GetEndPoint(){
    return EndPoint;
}
QPen& GetPen(){
    return pen;
}
 void DrawLine(QPainter& painter){
    painter.save();
    painter.setPen(pen);
    painter.drawLine(StartPoint,EndPoint);
    painter.restore();
    return;
}
};





#endif