#ifndef MATERIAL_PROPERTY_SECTION_HPP
#define MATERIAL_PROPERTY_SECTION_HPP
#include<memory>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QLabel>
#include<QtWidgets/QWidget>
#include<QtWidgets/QCheckBox>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QComboBox>
#include<QtCore/QStringList>
#include<MyCustomAIS_Shape.hxx>
#include<ShadingTypeMap.hpp>
#include<AIS_InteractiveContext.hxx>
#include<ColorPane.hpp>
#include<MaterialEnumValues.hxx>
#include<Section.h>
class MaterialPropertySection:public Section{
private:
std::unique_ptr<ColorPane> BaseColorPane;

std::unique_ptr<ColorPane> AmbientColorPane;

std::unique_ptr<ColorPane> DiffuseColorPane;

std::unique_ptr<ColorPane> SpecularColorPane;

std::unique_ptr<ColorPane> EmissiveColorPane;

std::unique_ptr<DoubleEdit> RefractiveIndexEdit;

std::unique_ptr<QFormLayout> flayout;

std::unique_ptr<QVBoxLayout> vlayout;

std::unique_ptr<QCheckBox> pbr_check_box;

std::unique_ptr<QCheckBox> convertbox;

std::unique_ptr<QComboBox> shaderTypeCombox;


std::unique_ptr<DoubleEdit> TransparencyEdit;
Graphic3d_MaterialAspect outputMaterial;
public:


bool IsBaseColorPaneSelected=false;
bool IsAmbientColorPaneSelected=false;
bool IsDiffuseColorPaneSelected=false;
bool IsSpecularColorPaneSelected=false;
bool IsEmissiveColorPaneSelected=false;
bool EnablePBR=false;  //by default,pbr is not enabled
MaterialPropertySection(const QString& pSecName,QWidget* parent):Section(pSecName,2,parent){
    flayout.reset(new QFormLayout);
    vlayout.reset(new QVBoxLayout);
    
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    
    BaseColorPane.reset(new ColorPane(this));
    flayout->addRow(tr("Base Color"),BaseColorPane.get());
    AmbientColorPane.reset(new ColorPane(this));
    flayout->addRow(tr("Ambient Color"),AmbientColorPane.get());
    DiffuseColorPane.reset(new ColorPane(this));
    flayout->addRow(tr("Diffuse Color"),DiffuseColorPane.get());
    SpecularColorPane.reset(new ColorPane(this));
    flayout->addRow(tr("Specular Color"),SpecularColorPane.get());
    EmissiveColorPane.reset(new ColorPane(this));
    flayout->addRow(tr("Emissive Color"),EmissiveColorPane.get());
    RefractiveIndexEdit.reset(new DoubleEdit(this,QString::number(0.0),8));
    flayout->addRow(tr("Refractive Index"),RefractiveIndexEdit.get());
    TransparencyEdit.reset(new DoubleEdit(this,QString::number(0.0),8));

    shaderTypeCombox.reset(new QComboBox(this));
    QStringList shadertypelist={tr("Default"),tr("Unlit"),tr("Flat Phong"),tr("Gouraud"),tr("Phong"),tr("Physically Based"),tr("Flat Physically Based")};

    shaderTypeCombox->addItems(shadertypelist);

    flayout->addRow(tr("Shading Model:"),shaderTypeCombox.get());
    flayout->addRow(tr("Transparency"),TransparencyEdit.get());
    vlayout->addLayout(flayout.get());
    
    pbr_check_box.reset(new QCheckBox(tr("Enable PBR"),this));
    convertbox=std::make_unique<QCheckBox>(tr("Convert To Node"),this);

    vlayout->addWidget(pbr_check_box.get());
    vlayout->addWidget(convertbox.get());
    setContentLayout(*vlayout.get());
    
}
void SetPropertiesFromSelectedShape(const Handle(CustomAIS_Shape)& shape,const Quantity_Color& color){
 
   auto& shapeattri=const_cast<Handle(Prs3d_Drawer)&>(shape->Attributes());
   auto shadingaspect=shapeattri->ShadingAspect();
   BaseColorPane->SetColorFromOC(color);
   
   auto materialaspect=const_cast<Graphic3d_MaterialAspect&>(shadingaspect->Material());
   
   AmbientColorPane->SetColorFromOC(materialaspect.AmbientColor());
   DiffuseColorPane->SetColorFromOC(color);
   SpecularColorPane->SetColorFromOC(materialaspect.SpecularColor());
   EmissiveColorPane->SetColorFromOC(materialaspect.EmissiveColor());
   RefractiveIndexEdit->setText(QString::number(materialaspect.RefractionIndex()));
   TransparencyEdit->setText(QString::number(materialaspect.Transparency()));
    return;
}
void SetPropertiesFromSelectedShapeOnCondition(const Handle(CustomAIS_Shape)& shape){
 
   auto& shapeattri=const_cast<Handle(Prs3d_Drawer)&>(shape->Attributes());
   auto shadingaspect=shapeattri->ShadingAspect();
   BaseColorPane->SetColorFromOC(shadingaspect->Color());
   
   auto materialaspect=const_cast<Graphic3d_MaterialAspect&>(shadingaspect->Material());
   
   AmbientColorPane->SetColorFromOC(materialaspect.AmbientColor());
   DiffuseColorPane->SetColorFromOC(materialaspect.DiffuseColor());
   SpecularColorPane->SetColorFromOC(materialaspect.SpecularColor());
   EmissiveColorPane->SetColorFromOC(materialaspect.EmissiveColor());
   RefractiveIndexEdit->setText(QString::number(materialaspect.RefractionIndex()));
   TransparencyEdit->setText(QString::number(materialaspect.Transparency()));
    return;
}
//Sets the properties based on the set condition
void SetPropertiesOnCondition(const MATERIALCOLOR& mat_col){
    

   if(mat_col==MC_BASE){
    IsBaseColorPaneSelected=true;
    IsAmbientColorPaneSelected=false;
    IsDiffuseColorPaneSelected=false;
    IsSpecularColorPaneSelected=false;
    IsEmissiveColorPaneSelected=false;
    return;
   }
   if(mat_col==MC_AMBIENT){
    IsBaseColorPaneSelected=false;
    IsAmbientColorPaneSelected=true;
    IsDiffuseColorPaneSelected=false;
    IsSpecularColorPaneSelected=false;
    IsEmissiveColorPaneSelected=false;
    return;
   }
   if(mat_col==MC_DIFFUSE){
     IsBaseColorPaneSelected=false;
    IsAmbientColorPaneSelected=false;
    IsDiffuseColorPaneSelected=true;
    IsSpecularColorPaneSelected=false;
    IsEmissiveColorPaneSelected=false;
    return;
   }
   if(mat_col==MC_SPECULAR){
     IsBaseColorPaneSelected=false;
    IsAmbientColorPaneSelected=false;
    IsDiffuseColorPaneSelected=false;
    IsSpecularColorPaneSelected=true;
    IsEmissiveColorPaneSelected=false;
    return;
   }
   if(mat_col==MC_EMISSIVE){
     IsBaseColorPaneSelected=false;
    IsAmbientColorPaneSelected=false;
    IsDiffuseColorPaneSelected=false;
    IsSpecularColorPaneSelected=false;
    IsEmissiveColorPaneSelected=true;
    return;
   }
  return;
}
void OnSetProperties(const Quantity_Color& color){
    if(IsBaseColorPaneSelected){
      BaseColorPane->SetColorFromOC(color);
       return;
   }
  if(IsAmbientColorPaneSelected){
    AmbientColorPane->SetColorFromOC(color);
      return;
   }
    if(IsDiffuseColorPaneSelected){
      DiffuseColorPane->SetColorFromOC(color);
      return;
   }
   if(IsSpecularColorPaneSelected){
        SpecularColorPane->SetColorFromOC(color);
        return;    
   }
   if(IsEmissiveColorPaneSelected){
       EmissiveColorPane->SetColorFromOC(color);
       return;
   }
   return;
}

//This updates the object passed as reference to the first parameter and sets the object properties
//pass an object of interactrive context as
//
//
void SetObjectBaseColor(Handle(AIS_InteractiveContext)& context,Handle(CustomAIS_Shape)& shape){
  if(context.IsNull()){
    return;
  }
  if(shape.IsNull()){
    return;
  }
   if(context->HasColor(shape)){
    if(context->IsDisplayed(shape)){
   shape->SetColor(baseColorPane()->GetOCColor());
   context->Redisplay(shape,true);
   }
   }
  return;
}

void SetObjectAmbientColor(Handle(AIS_InteractiveContext)& context,Handle(CustomAIS_Shape)& shape){
  if(shape.IsNull()){
    return;
  }
 auto& ref_material=const_cast<Graphic3d_MaterialAspect&>(shape->Attributes()->ShadingAspect()->Material());
  ref_material.SetAmbientColor(ambientColorPane()->GetOCColor());
  
  if(context.IsNull()){
       return;
}
  if(context->IsDisplayed(shape)){
    shape->SetMaterial(ref_material);
    context->Redisplay(shape,true);
    outputMaterial=ref_material;
  }
   return;
  //Pls remember to set the ambient variable of an object of ais_shape
  //so we have to create a reference to the material aspect 
  
  
  return;
}
void SetObjectDiffuseColor(Handle(AIS_InteractiveContext)& context,Handle(CustomAIS_Shape)& shape){
  if(shape.IsNull()){
       return;
  }
  auto& ref_material=const_cast<Graphic3d_MaterialAspect&>(shape->Attributes()->ShadingAspect()->Material());
  ref_material.SetDiffuseColor(diffuseColorPane()->GetOCColor()); 
if(context->IsDisplayed(shape)){
    shape->SetMaterial(ref_material);
    shape->InitColor(ref_material.DiffuseColor());
    context->Redisplay(shape,true);
     outputMaterial=ref_material;
  }
   
  
  return;
}
void SetObjectSpecularColor(Handle(AIS_InteractiveContext)& context,Handle(CustomAIS_Shape)& shape){
  if(shape.IsNull()){
       return;
  }
  auto& ref_material=const_cast<Graphic3d_MaterialAspect&>(shape->Attributes()->ShadingAspect()->Material());
  ref_material.SetSpecularColor(specularColorPane()->GetOCColor()); 
   if(context->IsDisplayed(shape)){
    shape->SetMaterial(ref_material);
    context->Redisplay(shape,true);
     outputMaterial=ref_material;
  }
   return;

}
void SetObjectEmissiveColor(Handle(AIS_InteractiveContext)& context,Handle(CustomAIS_Shape)& shape){
  if(shape.IsNull()){
       return;
  }
  auto& ref_material=const_cast<Graphic3d_MaterialAspect&>(shape->Attributes()->ShadingAspect()->Material());
  ref_material.SetEmissiveColor(emissiveColorPane()->GetOCColor());
  if(context->IsDisplayed(shape)){
    shape->SetMaterial(ref_material);
     context->Redisplay(shape,true);
      outputMaterial=ref_material;

  }
  return; 
}

 void SetObjectShadingType(Handle(AIS_InteractiveContext)& context,Handle(CustomAIS_Shape)& shape){
    if(shape.IsNull()){
            return;
          } 
      if(!shaderTypeCombox.get()){
              return;
    }
      if(context.IsNull()){
           return;
       }  
      auto& ref_aspect =const_cast<Handle(Graphic3d_AspectFillArea3d)&>(shape->Attributes()->ShadingAspect()->Aspect()); 
      ref_aspect->SetShadingModel(STM::shadertypemap.at(shaderTypeCombox->currentText()));

      if(context->IsDisplayed(shape)){
          context->SetLocalAttributes(shape,shape->Attributes(),true);
          return;
      } 
           return;
}

void SetObjectTransparency(Handle(AIS_InteractiveContext)& context,Handle(CustomAIS_Shape)& shape,const float& transp){
   if(shape.IsNull()){
            return;
}
    if(!TransparencyEdit.get()){
      return;
    } 
    if(context.IsNull()){
      return;
    }
    context->SetTransparency(shape,transp,true);


  return;
}
void SetObjectRefractiveIndex(Handle(AIS_InteractiveContext)& context,Handle(CustomAIS_Shape)& shape,const float& value){
  if(shape.IsNull()){
     return;
  }
  if(!refractEdit()){
    return;
  }
  if(context.IsNull()){
    return;
  }
  auto& ref_material=const_cast<Graphic3d_MaterialAspect&>(shape->Attributes()->ShadingAspect()->Material());
  ref_material.SetRefractionIndex(value);
  if(context->IsDisplayed(shape)){
     shape->SetMaterial(ref_material);
     context->Redisplay(shape,true);
      outputMaterial=ref_material;
  }

  return;
}
ColorPane* baseColorPane() const{
    return BaseColorPane.get();
}
ColorPane* ambientColorPane() const{
    return AmbientColorPane.get();
}
ColorPane* diffuseColorPane() const{
    return DiffuseColorPane.get();
}
ColorPane* specularColorPane() const{
    return SpecularColorPane.get();
}
ColorPane* emissiveColorPane() const{
    return EmissiveColorPane.get();
}
DoubleEdit* refractEdit() const{
   return RefractiveIndexEdit.get();
}
DoubleEdit* transpEdit() const{
  return TransparencyEdit.get();
}
QCheckBox* pbrCheckBox() const{
    return pbr_check_box.get();
}
QComboBox* ShaderTypeComboBox() const{
  return shaderTypeCombox.get();
}
Graphic3d_MaterialAspect OutputMaterial() const{
  return outputMaterial;
}
};
















#endif