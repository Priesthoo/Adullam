#pragma once
#include<EdgeVisAspect.hpp>
#include<QtWidgets/QWidget>
#include<QtWidgets/QVBoxLayout>
#include<memory>
using namespace std;
class EdgeWidget:public QWidget{
private:
std::unique_ptr<EdgeVisual> edgevisual;
std::unique_ptr<QVBoxLayout> layout;
bool ShouldSet=false;
public:
EdgeWidget(){
    edgevisual=std::make_unique<EdgeVisual>(this,tr("Edge Visual"));
    layout=make_unique<QVBoxLayout>();
    layout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    layout->addWidget(edgevisual.get());
    setLayout(layout.get());
    return;
}
EdgeVisual* edgePrs() const{
    return edgevisual.get();
}
void SetShouldSet(const bool& value){
    ShouldSet=value;
    return;
}
bool shouldSet() const{
    return ShouldSet;
}
VariableColorPane* colorPane() const {
   return edgevisual->colorPane.get();
}
DoubleEdit* WidthEdit() const{
    return edgevisual->doubleEdit.get();
}
};