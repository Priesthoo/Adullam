#ifndef TRANSFORM_PANE_HPP
#define TRANSFORM_PANE_HPP
#include<Section.hpp>
#include<ThreeValueSection.hpp>
#include<QtWidgets/QVBoxLayout>
class TransformSection:public QSection{
private:
std::unique_ptr<ThreeValueSection> trans_trsfsection;
std::unique_ptr<ThreeValueSection> rot_trsfsection;
std::unique_ptr<ThreeValueSection> scale_trsfsection;
QVBoxLayout* vlayout=nullptr;
public:
TransformSection(QWidget* parent=nullptr):QWidget(parent){

}
TransformSection(QWidget* parent,const float& t_x,const float& t_y,const float& t_z,const float& r_x,const float& r_y,const float& r_z,const float& uniformScale):QWidget(parent){
   trans_trsfsection.reset(new ThreeValueSection(tr("Translation"),2,this,t_x,t_y,t_z));
   rot_trsfsection.reset(new ThreeValueSection(tr("Rotation"),2,this,r_x,r_y,r_z));
   scale_trsfsection.reset(new ThreeValueSection(tr("Scale"),2,this,uniformScale,uniformScale,uniformScale));
   vlayout=new VBoxLayout;
   vlayout->setAlignment(Qt::AlignTop|AlignLeft);
   vlayout->addWidget(trans_trsfsection.get());
   vlayout->addWidget(rot_trsfsection.get());
   vlayout->addWidget(scale_trsfsection.get());

   setContentLayout(*vlayout);
}
~TransformSection(){
   if(vlayout){
      delete vlayout;
      vlayout=nullptr;
   }
}
};

#endif