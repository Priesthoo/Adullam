#include<TitleBarWidget.hpp>


ADTitleBarWidget::ADTitleBarWidget(QWidget* parent,TitleBarContainOptions option_1):QWidget(parent){
    Widget_Count=0;
    option=option_1;
    
}
size_t ADTitleBarWidget::GetWidgetCount() const{
    return Widget_Count;
}
bool ADTitleBarWidget::GetContainWidget() const{
    return ContainWidget;
}
