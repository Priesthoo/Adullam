#ifndef NODE_DESCRIPTION_HPP
#define NODE_DESCRIPTION_HPP
#include<QtCore/QString>
//This is a class that will be inherited to give the description of an node,This will be rendered under the description Collapsible Pane
class NodeDescription{
public:
NodeDescription(){

}
virtual QString Description() const {
    return QString("This is a node");
}

};









#endif