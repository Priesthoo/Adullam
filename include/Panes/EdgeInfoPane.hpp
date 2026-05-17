#pragma once
#include<EdgeUtility.hpp>
#include<Section.h>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QLabel>
#include<TopoDS_Edge.hxx>
#include<memory>
using namespace EDGE;
class EdgeSection:public Section{
private:

std::unique_ptr<QFormLayout> layout;


public:
EdgeSection(const EdgeInfo& info,QWidget* parent=nullptr):Section(tr("Edge Info "),2,parent){
layout=std::make_unique<QFormLayout>();
layout->addRow(tr("Curve Type:"),new QLabel(info.EdgeType,this));
layout->addRow(tr("Is3dCurve:"),new QLabel(info.Is3dCurve,this));
layout->addRow(tr("IsOnSurface:"),new QLabel(info.IsOnSurface,this));
layout->addRow(tr("Continuity:"),new QLabel(info.Continuity,this));
layout->addRow(tr("Degree:"),new QLabel(QString::number(info.Degree),this));
layout->addRow(tr("Number of Points:"),new QLabel(QString::number(info.NbPoles),this));
layout->addRow(tr("Number Of Knots:"),new QLabel(QString::number(info.NbKnots),this));
layout->addRow(tr("Umin:"),new QLabel(QString::number(info.Umin),this));
layout->addRow(tr("Umax:"),new QLabel(QString::number(info.Umax),this));
layout->addRow(tr("Tolerance:"),new QLabel(QString::number(info.Tolerance),this));
layout->addRow(tr("Period:"),new QLabel(QString::number(info.Period),this));
layout->addRow(tr("Is Closed: "),new QLabel(ConvertBoolToString(info.IsClosed),this));
layout->addRow(tr("Is Periodic:"),new QLabel(ConvertBoolToString(info.IsPeriodic),this));
setContentLayout(*layout.get());
return;
}

};