#ifndef TITLEBAR_WIDGET_HPP
#define TITLEBAR_WIDGET_HPP
#include<QtWidgets/QWidget>
enum TitleBarContainOptions{
   TITLE_BAR_CONTAIN_OPTIONS_NO_WIDGET,    //Title bar cannot contain any widget
   TITLE_BAR_CONTAIN_OPTIONS_ONE_WIDGET,
   TITLE_BAR_CONTAIN_OPTIONS_MORE_THAN_WIDGET
};
//we have to define the slots associated with TitleBarWidget
class ADTitleBarWidget:public QWidget{
private:
Q_OBJECT
bool ContainWidget=false;
size_t Widget_Count;
TitleBarContainOptions option;
bool hasTitle=false;
public:
ADTitleBarWidget(QWidget* parent,TitleBarContainOptions option_1);
void AddControls(QWidget* widget);
size_t GetWidgetCount() const;
bool GetContainWidget() const;
void SetTitleBarContainOptions(TitleBarContainOptions opt){
   option=opt;
}
TitleBarContainOptions GetTitleBarContainOption() const{
   return option;
}
signals:

public slots:

};








#endif