#pragma once
// DrawBoundedLine(const gp_Pnt& startPoint,const gp_Dir& dir,const double& p1,const double& p2)
#include<NodeDelegateModel>
#include<PointNodeData.hpp>
#include<ShapeUtil.hpp>
#include<AxisNodeData.hpp>
#include<FloatInputData.hpp>
#include<ShapeNodeData.hpp>
#include<NodeInitializer.hpp>
#include<memory>
using namespace Shape_Utility;
using namespace QtNodes;
class BoundedLineNode:public NodeDelegateModel,public NodeInitializer{
 private:
 std::weak_ptr<AxisNodeData> axis_input;
 std::weak_ptr<PointNodeData> point_data;
 std::weak_ptr<FloatNodeData> first_param;
 std::weak_ptr<FloatNodeData> second_param;
 std::shared_ptr<ShapeNodeData> output_shape;
 gp_Ax2 axis;
 gp_Pnt pnt;
 double p1=0.0; //by default
 double p2=1.0; //by default
 public:
 BoundedLineNode(){
    axis.SetDirection(gp_Dir(1.0,0.0,0.0));

 }
 unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 4;
        }
        case PortType::Out:{
            return 1;
        }
       
    }
    return 0;
}
QString caption() const override{
    return tr("Bounded Line");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                    return AxisNodeData(QString("Input_Axis")).type();
                case 1:
                   return  PointNodeData(tr("Start Point")).type();
                case 2:
                   return FloatNodeData(0.0,tr("First Parameter")).type();
                case 3:
                   return FloatNodeData(0.0,tr("Second Parameter")).type();
                
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("Output Shape")).type();
             }
        }
        
    }
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data.get()){ //analogous to data.ptr, such that ptr is apointer
        return;
    }
    
   
   
    switch(portIndex){
        case 0:{
            axis_input=std::dynamic_pointer_cast<AxisNodeData>(data);
            if(axis_input.lock()){
               axis=axis_input.lock()->Data();
            }
            
            std::cout<<"First Data set"<<std::endl;
            break;
        }
        case 1:{
            point_data=std::dynamic_pointer_cast<PointNodeData>(data);
            if(point_data.lock()){
            pnt=point_data.lock()->ToPnt();
            }
            std::cout<<"Second Data set"<<std::endl;
            break;
        }
        case 2:{
            first_param=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(first_param.lock()){
            p1=first_param.lock()->Data();
            }
            std::cout<<"Third Data set"<<std::endl;
            break;
        }
         case 3:{
            second_param=std::dynamic_pointer_cast<FloatNodeData>(data);
            if(second_param.lock()){
            p2=second_param.lock()->Data();
            }
            std::cout<<"Fourth Data set"<<std::endl;
            break;
        }
        default:
          break;
    }
    if(output_shape.get()){
        output_shape->SetData(DrawBoundedLine(pnt,axis.Axis().Direction(),p1,p2));
    }
    else{
        output_shape=std::make_shared<ShapeNodeData>(tr(""));
        output_shape->SetData(DrawBoundedLine(pnt,axis.Axis().Direction(),p1,p2));
    }
     emit dataUpdated(0);
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_shape.get()){
        return std::static_pointer_cast<NodeData>(output_shape);
    }
  std::shared_ptr<NodeData> m_ptr;
  return m_ptr;
}
QWidget* embeddedWidget() override{return nullptr;}
};