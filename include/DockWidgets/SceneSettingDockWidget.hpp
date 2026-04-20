#ifndef SCENESETTING_WIDGET_H
#define SCENESETTING_WIDGET_H
#include<Section.h>
#include<QtWidgets/QWidget>
#include<QtWidgets/QCheckBox>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QRadioButton>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QFormLayout>
#include<DoubleLineEdit.hpp>
#include<HighlightSection.hpp>
#include<ShapeTypePane.hpp>
//This will contain the information about the scene,
/*
The scene setting will contain ShowViewCube,ShowTriedhron,Set Settings,DrawWireFrame,DrawShaded,DrawShaded and WireFrame,SetColor
Display settings like Display Mode
*/
//This will contain all the settings of IneractiveContext,View,Display group,Ray Tracing,Background Images
class SceneSettingWidget:public QWidget{
  Q_OBJECT
  public:
  Section* SelFilterSection=nullptr;
  Section* DispModeSection=nullptr;
  Section* GridSection=nullptr; 
  Section* PlaneSection=nullptr;
  Section* ViewSection=nullptr;
  QRadioButton* Wi_RadioButton=nullptr;
  QRadioButton* Sh_RadioButton=nullptr;
  QRadioButton* Wi_ShRadioButton=nullptr;
  QRadioButton* FaceRadioButton=nullptr;
  QRadioButton* VertexRadioButton=nullptr;
  QRadioButton* WireRadioButton=nullptr;
  QRadioButton* EdgeRadioButton=nullptr;
  QRadioButton* ShapeRadioButton=nullptr;
  QCheckBox* isAutoHilightCheckBox=nullptr;
  QCheckBox* ShowViewCubeCheckBox=nullptr;
  QCheckBox* ShowGridCheckBox=nullptr;
  QCheckBox* UseWindowCheckBox=nullptr;
  DoubleEdit* SetXEdit=nullptr;
  DoubleEdit* SetYEdit=nullptr;
  DoubleEdit* SpaceEdit=nullptr;  //This is for SetRectangularValues of DrawingCentralWidget
  DoubleEdit* SizeXEdit=nullptr;
  DoubleEdit* SizeYEdit=nullptr;
  QVBoxLayout* SelLayout=nullptr;
  QFormLayout* gridFormLayout=nullptr;
  QFormLayout* planeFormLayout=nullptr;
  QVBoxLayout* DispLayout=nullptr;
  QVBoxLayout* ViewLayout=nullptr;
  QVBoxLayout* GridVlayout=nullptr;
  QVBoxLayout* ScLayout=nullptr;
  std::unique_ptr<SelectedHighlightSection> hilisection;
  std::unique_ptr<QRadioButton> boundboxr_button; //when pressed, display the bounding box of the shape
  std::unique_ptr<ShapeTypePane> shapetypepane;
  public:
  SceneSettingWidget():QWidget(){
    ScLayout=new QVBoxLayout;
    ScLayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    //Selection Filter section
    SelFilterSection=new Section(tr("Selection Filter"),2,this);
    SelLayout=new QVBoxLayout;
    SelLayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    WireRadioButton=new QRadioButton(tr("Wire"),SelFilterSection);
    VertexRadioButton=new QRadioButton(tr("Vertex"),SelFilterSection);
    FaceRadioButton=new QRadioButton(tr("Face"),SelFilterSection);
    EdgeRadioButton=new QRadioButton(tr("Edge"),SelFilterSection);
    ShapeRadioButton=new QRadioButton(tr("Shape"),SelFilterSection);
    SelLayout->addWidget(VertexRadioButton);
    SelLayout->addWidget(EdgeRadioButton);
    SelLayout->addWidget(FaceRadioButton);
    SelLayout->addWidget(WireRadioButton);
    SelLayout->addWidget(ShapeRadioButton);
    SelFilterSection->setContentLayout(*SelLayout);
    //End of Selection Filter Section
    
    //Display mode Section
    DispModeSection=new Section(tr("Display Mode"),2,this);
    DispLayout=new QVBoxLayout;
    DispLayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    Wi_RadioButton=new QRadioButton(tr("WireFrame"),DispModeSection);
    Sh_RadioButton=new QRadioButton(tr("Shaded"),DispModeSection);
    Wi_ShRadioButton=new QRadioButton(tr("WireFrame and Shaded"),DispModeSection);
    boundboxr_button.reset(new QRadioButton(tr("Bounding Box"),DispModeSection));

    DispLayout->addWidget(Wi_RadioButton);
    DispLayout->addWidget(Sh_RadioButton);
    DispLayout->addWidget(Wi_ShRadioButton);
    DispLayout->addWidget(boundboxr_button.get());
    
    DispModeSection->setContentLayout(*DispLayout);
    //End of DispModeSection
   
      //GridSection
      GridSection=new Section(tr("Grid"),2,this);
      GridVlayout=new QVBoxLayout;
      GridVlayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
      SetXEdit=new DoubleEdit(GridSection,QString::number(0.0),8);
      SetYEdit=new DoubleEdit(GridSection,QString::number(0.0),8);
      SpaceEdit=new DoubleEdit(GridSection,QString::number(0),8);
      ShowGridCheckBox=new QCheckBox(tr("Show Grid"),GridSection);
      ShowGridCheckBox->setCheckable(true);
      ShowGridCheckBox->setChecked(true);
      gridFormLayout=new QFormLayout;
      gridFormLayout->addRow(tr("X"),SetXEdit);
      gridFormLayout->addRow(tr("Y"),SetYEdit);
      gridFormLayout->addRow(tr("Grid Space"),SpaceEdit);
      UseWindowCheckBox=new QCheckBox(tr("Use Window Size"),GridSection);
      GridVlayout->addWidget(ShowGridCheckBox);
      GridVlayout->addWidget(UseWindowCheckBox);
      GridVlayout->addLayout(gridFormLayout);
      GridSection->setContentLayout(*GridVlayout);
      //End of gridSection

     //PlaneSection
      PlaneSection=new Section(tr("Plane"),2,this);
      planeFormLayout=new QFormLayout;
      SizeXEdit=new DoubleEdit(PlaneSection,QString::number(0.0),8);
      SizeYEdit=new DoubleEdit(PlaneSection,QString::number(0.0),8);
      planeFormLayout->addRow(tr("Size in X direction:"),SizeXEdit);
      planeFormLayout->addRow(tr("Size in Y direction:"),SizeYEdit);    
      PlaneSection->setContentLayout(*planeFormLayout);
      //End of PlaneSection 
    //This is highlight section
    hilisection.reset(new SelectedHighlightSection(tr("Selection Aspect"),2,this,80));
    shapetypepane=std::make_unique<ShapeTypePane>(this);
    ScLayout->addWidget(SelFilterSection);
    ScLayout->addWidget(DispModeSection);
    ScLayout->addWidget(GridSection);
    ScLayout->addWidget(PlaneSection);
    ScLayout->addWidget(hilisection.get());
    ScLayout->addWidget(shapetypepane.get());
    setLayout(ScLayout);



  }
  QLocale GetLocale() const{
    return SetXEdit->GetLocale();
  }
  QLabel*  STLabel() const{
    return shapetypepane->ShapeTypeLabel();
  }
SelectedHighlightSection* highlightSection(){
  return  hilisection.get();
}
  ~SceneSettingWidget(){
    if(SelFilterSection){
      delete SelFilterSection;
      SelFilterSection=nullptr;
    }
    if(DispModeSection){
      delete DispModeSection;
      DispModeSection=nullptr;
    }
    if(ScLayout){
      delete ScLayout;
      ScLayout=nullptr;
    }
    if(SelLayout){
      delete SelLayout;
      SelLayout=nullptr;
    }
    if(WireRadioButton){
      delete WireRadioButton;
      WireRadioButton=nullptr;
    }
    if(VertexRadioButton){
      delete VertexRadioButton;
      WireRadioButton=nullptr;
    }
    if(EdgeRadioButton){
      delete EdgeRadioButton;
      EdgeRadioButton=nullptr;
    }
    if(FaceRadioButton){
      delete FaceRadioButton;
      FaceRadioButton=nullptr;
    }
    if(ShapeRadioButton){
      delete ShapeRadioButton;
      ShapeRadioButton=nullptr;
    }
    if(DispLayout){
      delete DispLayout;
      DispLayout=nullptr;
    }
    if(DispModeSection){
      delete DispModeSection;
      DispModeSection=nullptr;
    }
    if(Wi_RadioButton){
      delete Wi_RadioButton;
      Wi_RadioButton=nullptr;
    }
    if(Wi_ShRadioButton){
      delete Wi_ShRadioButton;
      Wi_RadioButton=nullptr;
    }
    if(Sh_RadioButton){
      delete Sh_RadioButton;
      Sh_RadioButton=nullptr;
    }
    if(PlaneSection){
      delete PlaneSection;
      PlaneSection=nullptr;
    }
    if(GridSection){
      delete GridSection;
      GridSection=nullptr;
    }
    if(GridVlayout){
      delete GridVlayout;
      GridVlayout=nullptr;
    }
    if(gridFormLayout){
      delete gridFormLayout;
      gridFormLayout=nullptr;
    }
    if(planeFormLayout){
    delete planeFormLayout;
    planeFormLayout=nullptr;
  }
  if(SizeXEdit){
  delete SizeXEdit;
  SizeXEdit=nullptr;    
  }
  if(SizeYEdit){
    delete SizeYEdit;
    SizeYEdit=nullptr;
  }
  if(UseWindowCheckBox){
    delete UseWindowCheckBox;
    UseWindowCheckBox=nullptr;
  }
  
  }
  
};




#endif