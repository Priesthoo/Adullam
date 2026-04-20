#ifndef MODELACTIONMENU_HPP
#define MODELACTIONMENU_HPP
#include<QtWidgets/QMenu>
#include<memory>
class ModelMenu:public QMenu{
private:
Q_OBJECT
public:
std::unique_ptr<QAction> DrawCircleAction;
std::unique_ptr<QAction> Draw2DCurveAction;
std::unique_ptr<QAction> Draw3DCurveAction;
std::unique_ptr<QAction> DrawLineAction;
std::unique_ptr<QAction> DrawCubeAction;
std::unique_ptr<QAction> DrawSphereAction;
std::unique_ptr<QAction> DrawTorusAction;
std::unique_ptr<QAction> DrawCylinderAction;
std::unique_ptr<QMenu> PrimitiveShapeAction;
std::unique_ptr<QAction> CubeAction;
std::unique_ptr<QAction> SphereAction;
std::unique_ptr<QAction> CuboidAction;
std::unique_ptr<QAction> TorusAction;
std::unique_ptr<QAction> ConeAction;
std::unique_ptr<QAction> CylinderAction;

public:
ModelMenu():QMenu(){
 DrawCircleAction.reset(new QAction(tr("Draw Circle"),nullptr));
DrawCircleAction->setCheckable(true);
addAction(DrawCircleAction.get());

DrawCubeAction.reset(new QAction(tr("Draw Cube"),nullptr));
DrawCubeAction->setCheckable(true);
addAction(DrawCubeAction.get());

Draw2DCurveAction.reset(new QAction(tr("Draw 2D Curve"),nullptr));
Draw2DCurveAction->setCheckable(true);
addAction(Draw2DCurveAction.get());

DrawLineAction.reset(new QAction(tr("Draw 2D Line"),nullptr));
DrawLineAction->setCheckable(true);
addAction(DrawLineAction.get());

PrimitiveShapeAction.reset(new QMenu(tr("Primitive"),nullptr));
CubeAction.reset(new QAction(tr("Cube"),nullptr));
CubeAction->setCheckable(true);
SphereAction.reset(new QAction(tr("Sphere"),nullptr));
SphereAction->setCheckable(true);
CuboidAction.reset(new QAction(tr("Cuboid"),nullptr));
CuboidAction->setCheckable(true);
TorusAction.reset(new QAction(tr("Torus"),nullptr));
TorusAction->setCheckable(true);
PrimitiveShapeAction->addAction(CubeAction.get());
PrimitiveShapeAction->addAction(SphereAction.get());
PrimitiveShapeAction->addAction(CuboidAction.get());
PrimitiveShapeAction->addAction(TorusAction.get());
ConeAction.reset(new QAction(tr("Cone"),nullptr));
ConeAction->setCheckable(true);

PrimitiveShapeAction->addAction(ConeAction.get());
CylinderAction.reset(new QAction(tr("Cylinder"),nullptr));
CylinderAction->setCheckable(true);
PrimitiveShapeAction->addAction(CylinderAction.get());
addMenu(PrimitiveShapeAction.get());
}
signals:
void CanDrawCircle(bool CanDrawCircle);
public slots:

};




#endif