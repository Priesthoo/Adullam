#pragma once
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QLabel>
#include<memory>
#include<Section.h>
class ShapeTypePane:public Section{
 private:
 std::unique_ptr<QFormLayout> formlayout;
 std::unique_ptr<QLabel> label;
 public:
 ShapeTypePane(QWidget* parent):Section(tr("Shape Type"),2,parent){
    formlayout.reset(new QFormLayout);
    label.reset(new QLabel(tr(""),this));
     formlayout->addRow(tr("Shape Type:"),label.get());
     setContentLayout(*formlayout.get());

  }
 QLabel* ShapeTypeLabel() const{
    return label.get();
 }
};
//Data->Hash function->Hash->Encrypt hash using private key->Signature->Attach Data->Signed data
//Encrypt Data(data)-> hash , privatekey.sign(hash_data)