#ifndef NODEGRAPHMODEL_HPP
#define NODEGRAPHMODEL_HPP
#include<DataFlowGraphModel>
#include<NodeData>
#include<Definitions.hpp>
#include<memory>
using QtNodes::NodeDelegateModelRegistry;
using QtNodes::DataFlowGraphModel;
typedef NodeDelegateModelRegistry NodeRegistry;   //This helps us to register aa nodes,the graph model reads the data from the registry 
typedef DataFlowGraphModel NodeGraphModel;  //
using namespace QtNodes; 

class CustomGraphModel:public DataFlowGraphModel{
private:
Q_OBJECT



public:
CustomGraphModel(std::shared_ptr<NodeDelegateModelRegistry> registry):DataFlowGraphModel (registry){
  
}
std::unordered_set<NodeId> allNodeIds() const override{
   return DataFlowGraphModel::allNodeIds();
 }


~CustomGraphModel(){} //inline 

};






#endif