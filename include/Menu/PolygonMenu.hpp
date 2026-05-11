#pragma once 
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;
class PolygonMenu:public QMenu{
public:
std::unique_ptr<QAction> gatheredPointsAction;
std::unique_ptr<QAction> deleteAction; //deletes the transient Polygon
std::unique_ptr<QAction> convertToBSpline;
  std::unique_ptr<QAction> DeCurve;
   std::unique_ptr<QAction> addToContext;
std::unique_ptr<QAction> removeLastAction;
std::unique_ptr<QAction> LineStyleAction;
public:
PolygonMenu(){
    gatheredPointsAction=std::make_unique<QAction>(tr("Convert To Node"),nullptr);
    gatheredPointsAction->setCheckable(true);
    deleteAction=std::make_unique<QAction>(tr("Delete"),nullptr);
    removeLastAction=make_unique<QAction>(tr("Remove Last Vertex"),nullptr);
    LineStyleAction=make_unique<QAction>(tr("Line Presentation"),nullptr);
    convertToBSpline=std::make_unique<QAction>(tr("Convert To BSpline"),nullptr);
    DeCurve=std::make_unique<QAction>(tr("DeCurve"),nullptr);
      addToContext=std::make_unique<QAction>(tr("Add To Context"),nullptr);
    addAction(gatheredPointsAction.get());
    addAction(deleteAction.get());
    addAction(removeLastAction.get());
    addAction(LineStyleAction.get());
     addAction(addToContext.get());
    addAction(convertToBSpline.get());
    addAction(DeCurve.get());
}
};
class BezierMenu:public QMenu{
  public:
  std::unique_ptr<QAction> onModifyPoint;
  
  std::unique_ptr<QAction> convertToEdge;
  std::unique_ptr<QAction> convertToWire;
  std::unique_ptr<QAction> infoAction;
  std::unique_ptr<QAction> linePrsAction;
 
  std::unique_ptr<QAction> deleteAction;
  public:
  BezierMenu():QMenu(){
    onModifyPoint=std::make_unique<QAction>(tr("Modify Point"),nullptr);
    convertToEdge=std::make_unique<QAction>(tr("Convert To EdgeNode"),nullptr);
    convertToEdge->setCheckable(true);
    convertToWire=std::make_unique<QAction>(tr("Convert To Wire Node"),nullptr);
    convertToWire->setCheckable(true);
   
    linePrsAction=std::make_unique<QAction>(tr("Line Presentation"),nullptr);
    infoAction=std::make_unique<QAction>(tr("Show Bezier Info"),nullptr);
    deleteAction=std::make_unique<QAction>(tr("Delete"),nullptr);
  
    addAction(onModifyPoint.get());
    addAction(convertToEdge.get());
    addAction(convertToWire.get());
   
   
    addAction(linePrsAction.get());
    addAction(deleteAction.get());
    addAction(infoAction.get());
  }
};

class BSplineMenu:public QMenu{
  public:
  std::unique_ptr<QAction> IsPeriodicAction;
  std::unique_ptr<QAction> deleteAction;
  std::unique_ptr<QAction> convertToEdgeAction;
  std::unique_ptr<QAction> convertToWireAction;
  std::unique_ptr<QAction> infoAction;

  public:
  BSplineMenu(){
    IsPeriodicAction=std::make_unique<QAction>(tr("Is Periodic"),nullptr);
    IsPeriodicAction->setCheckable(true);
    deleteAction=std::make_unique<QAction>(tr("Delete"),nullptr);
    convertToEdgeAction=make_unique<QAction>(tr("Convert To Edge Node"),nullptr);
    convertToWireAction=make_unique<QAction>(tr("Convert To Wire Node"),nullptr);
    infoAction=make_unique<QAction>(tr("BSpline Curve Info"),nullptr);
    addAction(IsPeriodicAction.get());
    addAction(deleteAction.get());
    addAction(convertToEdgeAction.get());
    addAction(convertToWireAction.get());
    addAction(infoAction.get());
    return;
  }


};