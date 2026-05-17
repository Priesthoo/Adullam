#pragma once
#include<EdgeInfoPane.hpp>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QStackedWidget>
#include<memory>
#include<QtWidgets/QWidget>
using namespace std;
class EdgeInfoWidget:public QStackedWidget{
private:
std::unique_ptr<QVBoxLayout> vlayout;
std::unique_ptr<EdgeSection> edgeSection;

public:
EdgeInfoWidget(QWidget* parent=nullptr){
    return;
}
void SetEdgeInfo(const EdgeInfo& info){

        if(edgeSection){
        removeWidget(edgeSection.get());
         edgeSection->setParent(nullptr);
         edgeSection.reset();
        }
    
    edgeSection=std::make_unique<EdgeSection>(info,this);
    addWidget(edgeSection.get());
    setCurrentWidget(edgeSection.get());
    return;
    
}

};