#pragma once
#include<iostream>
#include<memory>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QCheckBox>
#include<QtWidgets/QComboBox>
#include<QtWidgets/QFormLayout>
#include<Section.h>
#include<QtCore/QStringList>
using namespace std;
class ViewSettingSection:public Section{
 public:
 std::unique_ptr<QFormLayout>formLayout;
 unique_ptr<QCheckBox> panCheckBox;
 unique_ptr<QCheckBox> orbitCheckBox;
 unique_ptr<QCheckBox> rotateCheckBox;
 std::unique_ptr<QCheckBox> showRotateCentreCheckBox;
 unique_ptr<QCheckBox> invertPitchCheckBox;
 unique_ptr<QCheckBox> lockZUpCheckBox;
 unique_ptr<QCheckBox> stayToRayCheckBox; //this is for stay to ray on rotation
 unique_ptr<QComboBox> navComboBox;
 unique_ptr<QComboBox> rotateComboBox;
 unique_ptr<DoubleEdit> mouseAccelEdit;
 unique_ptr<DoubleEdit> orbitAccelEdit;
 unique_ptr<DoubleEdit> walkAbsSpeedEdit;
 unique_ptr<DoubleEdit> walkRelaSpeedEdit;
 unique_ptr<DoubleEdit> thrustSpeedEdit;
 public:
 ViewSettingSection(QWidget* parent=nullptr):Section(QString("View"),2,parent){
    formLayout=make_unique<QFormLayout>();
    panCheckBox=make_unique<QCheckBox>(tr(""),nullptr);
    orbitCheckBox=make_unique<QCheckBox>(tr(""),nullptr);
    navComboBox=make_unique<QComboBox>(this);
    rotateCheckBox=make_unique<QCheckBox>(tr(""),nullptr);
    QStringList navTypeList={tr("Orbit Navigation"),tr("Flight Mode"),tr("Walk Mode")};
    navComboBox->addItems(navTypeList);
   QStringList rotateTypeList={tr("Bound Box Active"),tr("Last Pick"),tr("Centre Pick"),tr("Camera Centre"),tr("Scene Centre")};
   rotateComboBox=make_unique<QComboBox>(this);
   rotateComboBox->addItems(rotateTypeList);
   invertPitchCheckBox=make_unique<QCheckBox>(tr(""),nullptr);
   lockZUpCheckBox=make_unique<QCheckBox>(tr(""),nullptr);
   stayToRayCheckBox=make_unique<QCheckBox>(tr(""),nullptr);
   mouseAccelEdit=make_unique<DoubleEdit>(this,QString::number(1.0),8);
   orbitAccelEdit=make_unique<DoubleEdit>(this,QString::number(1.0),8);
   walkAbsSpeedEdit=make_unique<DoubleEdit>(this,QString::number(1.0),8);
   walkRelaSpeedEdit=make_unique<DoubleEdit>(this,QString::number(1.0),8);
   thrustSpeedEdit=make_unique<DoubleEdit>(this,QString::number(1.0),8);
   showRotateCentreCheckBox=std::make_unique<QCheckBox>(tr(""),nullptr); 
   formLayout->addRow(tr("Pan: "),panCheckBox.get());
   formLayout->addRow(tr("Orbit: "),orbitCheckBox.get());
   formLayout->addRow(tr("Navigation Mode:"),navComboBox.get());
   formLayout->addRow(tr("Rotation Mode: "),rotateComboBox.get());
   formLayout->addRow(tr("Rotate:"),rotateCheckBox.get());
   formLayout->addRow(tr("Invert Pitch:"),invertPitchCheckBox.get());
   formLayout->addRow(tr("Show Rotation Center:"), showRotateCentreCheckBox.get());
   formLayout->addRow(tr("Lock Z-Up"),lockZUpCheckBox.get());
   formLayout->addRow(tr("Mouse Acceleration:"),mouseAccelEdit.get());
   formLayout->addRow(tr("Orbit Acceleration:"),orbitAccelEdit.get());
   formLayout->addRow(tr("Absolute Walk Speed:"),walkAbsSpeedEdit.get());
   formLayout->addRow(tr("Relative Walk Speed:"),walkRelaSpeedEdit.get());
   formLayout->addRow(tr("Thrust Speed:"),thrustSpeedEdit.get());
   
   setContentLayout(*formLayout.get());
    return;
 }
};
