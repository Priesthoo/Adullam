#ifndef NODEGRAPHWIDGET_HPP
#define NODEGRAPHWIDGET_HPP
#include<QtWidgets/QWidget>
#include<GraphicsView>
#include<memory>
#include<NodeGraphModel.hpp>
#include<DataFlowGraphicsScene>
#include<NodeGraphicsObject.hpp>
#include<ConnectionGraphicsObject.hpp>
#include<BasicGraphicsScene>
#include<AllNodes.hpp>
#include<TopoDS_Shape.hxx>
#include<QtWidgets/QMenu>
#include <QtWidgets/QGraphicsObject>
#include<QtGui/QMouseEvent>
#include<FloatNodeDialog.hpp>
#include<exception>
#include<NodeSceneMenu.hpp>
#include<AIS_InteractiveContext.hxx>
#include<functional>
#include<iostream>
using namespace std;
using QtNodes::GraphicsView;
using QtNodes::BasicGraphicsScene;
using QtNodes::DataFlowGraphicsScene;
using QtNodes::NodeGraphicsObject;
//This will  be the view for the graph models,we will have to develop our model....
//The architecture is simple,Some nodes might have the same category,we group them according to categories,
//What is the help of NodeRegistry
/*
Category is of type QString for Qt and type std::string for  C++
Registry Helps us to register our nodes in the graph model,This will be used by TreeView to render the name of the Node based on the content of the filter 
We will have to disable categorized nodes by assigning unique Category to each node

*/
//We are going to display the content of the TabWidget based on particular node chosen
//The contents of the menu are thus:
/*
1).Delete Node //at this point,we are going to remove both the node object in the GraphModel and the SceneObjects
2).Delete Connection; //at this point,we are going to delete a connection object from the GraphModel and the SceneObjects
3)

*/ 
enum SHAPEDRAW{
SP_SHAPE,
SP_EDGE,
SP_FACE,
SP_NULL
};
enum RENDER_STATE{
RS_TRANSFORM,  //this one draws the transform node
RS_MATERIAL,
RS_NULL
};
enum AUTO_COMPILE_ACTION{  //this is the auto compilation action...
ACT_NULL,
ACT_ACTIVATE
};

enum VIEW_ACTION{
 VA_COPY,
 VA_PASTE,
 VA_NULL
};
class NodeGraphWidget:public GraphicsView{
private:
Q_OBJECT
std::shared_ptr<NodeRegistry> Registry;
std::shared_ptr<DataFlowGraphicsScene> scene_1;
std::unique_ptr<FloatNodeWidget> fnodewidget;
std::unique_ptr<FloatNodeDialog> fnodedialog;
std::unique_ptr<NodeSceneMenu> nodeSceneMenu=make_unique<NodeSceneMenu>();


std::reference_wrapper<Handle(AIS_InteractiveContext)> context;
DataFlowGraphModel* graph_model=nullptr;
size_t CurrId=0;
int CurrNodeId=-1;
bool IsSelected=false;
bool ShowMenu=false;
public:
NodeGraphicsObject* selectedNode=nullptr;
float x=0.0;
float y=0.0;
float z=0.0;

gp_Trsf NodeInputTransform=gp_Trsf();
TopoDS_Shape NodeInputShape=TopoDS_Shape();
TopoDS_Face nodeInputFace=TopoDS_Face();
FloatInputNode* receivedFloatNode=nullptr;
SHAPEDRAW shapedraw=SP_NULL;
RENDER_STATE rstate=RS_NULL;
AUTO_COMPILE_ACTION compileAction=ACT_NULL;
VIEW_ACTION  vaction=VA_NULL;
BooleanNode* receivedBoolNode=nullptr;
bool IsBoolNodeSet=false;
PrimitiveCubeNode* receivedCubeNode=nullptr;
PrimitiveShapeNode* receivedShape=nullptr;
NodeDelegateModel* selectedModel=nullptr;
FaceNode* receivedFace=nullptr;
EdgeNode* receivedEdge=nullptr;
bool CanDrawPointNode=false;
bool IsCubeNodeSet=false;
bool IsFloatNodeSet=false;


NodeGraphWidget(QWidget* parent_widget,Handle(AIS_InteractiveContext)& context_1):GraphicsView(parent_widget),context{context_1}{
   Registry.reset(new NodeRegistry());
   //Register Model
 
   std::cout<<"I am in NodeGraphWidget Constructor"<<"\n";
    
  
   
   Registry->registerModel<AdditionNode>("Operators");
   Registry->registerModel<OutputNode>([this]()->std::shared_ptr<OutputNode>{
      auto ptr=make_shared<OutputNode>();
      QObject::connect(ptr.get(),&OutputNode::OnSendAIS_Shape,this,&NodeGraphWidget::OnReceiveAIS_Shape);
      
      return ptr;
   },QString("Output"));
   
   Registry->registerModel<MultipleOutputNode>([this]()->std::shared_ptr<MultipleOutputNode>{
      auto ptr=make_shared<MultipleOutputNode>();
      QObject::connect(ptr.get(),&MultipleOutputNode::OnSendShapes,this,&NodeGraphWidget::OnReceiveShapes);
      
      return ptr;
   },QString("Output"));
Registry->registerModel<ConvertToAIS_ShapeNode>("Conversion");
   Registry->registerModel<FloatInputNode>([this]()->std::shared_ptr<FloatInputNode>{
    auto ptr=make_shared<FloatInputNode>();
    QObject::connect(ptr.get(),&FloatInputNode::OnUpdateInput,this,&NodeGraphWidget::OnHandleInputEvent);
    return ptr;   
},tr("DataTypes"));
Registry->registerModel<IntegerInputNode>("DataTypes");
   Registry->registerModel<StringInputNode>("DataTypes");
   Registry->registerModel<DirectionNode>("Direction");
   Registry->registerModel<Point3dNode>("Points");
   Registry->registerModel<AxisNode>("Axis");
   Registry->registerModel<PrimitiveCubeNode>("Primitive Shapes");
   Registry->registerModel<PrimitiveCuboidNode>("Primitive Shapes");
    Registry->registerModel<PrimitiveSphereNode>("Primitive Shapes");
   Registry->registerModel<PrimitiveShapeNode>([this]()->std::shared_ptr<PrimitiveShapeNode>{
    auto ptr=std::make_shared<PrimitiveShapeNode>();
    return ptr;
   },tr("Primitive Shapes"));
   Registry->registerModel<PrimitiveConeNode>(tr("Primitive Shapes"));
Registry->registerModel<PrimitiveTorusNode>(tr("Primitive Shapes"));
   Registry->registerModel<SinglyPointNode>(tr("Points"));
   Registry->registerModel<ShapeArrayNode>("Array");
   Registry->registerModel<VectorToVectorNode>("Conversion");
   Registry->registerModel<ArrayToVectorNode>("Conversion");
   Registry->registerModel<SingleArrayToVectorNode>("Conversion");
   Registry->registerModel<BooleanNode>("Condition");
   Registry->registerModel<SinglyTransformNode>("Transform");
   Registry->registerModel<SinglyShapeNode>("Primitive Shapes");
   Registry->registerModel<PrimitiveCylinderNode>(tr("Primitive Shapes"));
   Registry->registerModel<ColorNode>("Shading");
   Registry->registerModel<RGBColorNode>("Shading");
   Registry->registerModel<RotationNode>("Transform");
   Registry->registerModel<ScaleNode>("Transform");
   Registry->registerModel<TranslateNode>("Transform");
   Registry->registerModel<CombinedTransformNode>(tr("Transform"));
   Registry->registerModel<DirXNode>(tr("Predefined Values"));
   Registry->registerModel<DirYNode>(tr("Predefined Values"));
   Registry->registerModel<DirZNode>(tr("Predefined Values"));
   Registry->registerModel<PositionedDirXNode>(tr("Predefined Values"));
   Registry->registerModel<PositionedDirYNode>(tr("Predefined Values"));
   Registry->registerModel<PositionedDirZNode>(tr("Predefined Values"));
   Registry->registerModel<NegatedPositionedDirXNode>(tr("Predefined Values"));
     Registry->registerModel<NegatedPositionedDirYNode>(tr("Predefined Values"));
     Registry->registerModel<NegatedPositionedDirZNode>(tr("Predefined Values"));
   Registry->registerModel<FaceNode>(tr("Sub Shape"));
   Registry->registerModel<FuseNode>(tr("Boolean Operation"));
   Registry->registerModel<CutNode>(tr("Boolean Operation"));
    Registry->registerModel<CommonNode>(tr("Boolean Operation"));
    Registry->registerModel<SectionNode>(tr("Boolean Operation"));
   Registry->registerModel<TransformedShapeNode>(tr("Transform"));
   Registry->registerModel<MaterialNode>(tr("Shading"));
   Registry->registerModel<EdgeNode>(tr("Sub Shape"));
   Registry->registerModel<GoldMaterialNode>(tr("Predefined Material"));
   Registry->registerModel<BoundedLineNode>(tr("2D Shapes"));
   Registry->registerModel<SketchLineNode>(tr("2D Shapes"));
   Registry->registerModel<SketchCircleNode>(tr("2D Shapes"));
    Registry->registerModel<SinglyFaceNode>(tr("Sub Shape"));
   graph_model=new DataFlowGraphModel(Registry);
   scene_1=std::make_shared<DataFlowGraphicsScene>(*graph_model,this);
   GraphicsView::setScene(scene_1.get());
   QObject::connect(nodeSceneMenu->CompileNodesAction(),&QAction::triggered,this,&NodeGraphWidget::CompileAllNode);
   QObject::connect(nodeSceneMenu->DeleteNodeAction(),&QAction::triggered,this,&NodeGraphWidget::OnDeleteHandler);
   connect(nodeSceneMenu->AutoCompileAction(),&QAction::toggled,this,&NodeGraphWidget::OnHandleAutoCompile);
   QObject::connect(nodeSceneMenu->CopyNodeAction(),&QAction::triggered,this,&NodeGraphWidget::OnHandleCopy);
   QObject::connect(nodeSceneMenu->PasteNodeAction(),&QAction::triggered,this,&NodeGraphWidget::OnHandlePaste);
   setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
   
}
void LoopModelAndFindShape(const TopoDS_Shape& shape){
  auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
  if(!gscene){
    emit SendMessage(tr("Failed To Cast To Scene"));
    return;
  }
 
    auto gmodel=gscene->GraphModel();
     if(gmodel){
      emit SendMessage(tr("Graph Model Created"));
      std::cout<<"Graph Model Created Successfully"<<std::endl;
     }
     for(auto& ref:gscene->items()){
        auto nodeObject=qgraphicsitem_cast<NodeGraphicsObject*>(ref);
        if(nodeObject){
           if(gmodel->Models().empty()){
            return;  //size==0;
           }
           else{
            receivedShape=dynamic_cast<PrimitiveShapeNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
            if(receivedShape){
               if(receivedShape->Shape().IsSame(shape)){
                std::cout<<"Shape Found In GraphModel"<<std::endl;
                if(!nodeObject->isSelected()){
                  nodeObject->setSelected(true);
                  nodeObject->update();
                }
                break;
               }
            }
           }
        }
     }
     return;
}
void UpdateShape(const TopoDS_Shape& p_Shape){
   if(receivedShape){
     receivedShape->SetShape(p_Shape);
     std::cout<<"Shape Is Changed"<<std::endl;
   }
   return;
}
~NodeGraphWidget(){
  if(graph_model){
    delete graph_model;
    graph_model=nullptr;
    return;
  }
}
protected:
void contextMenuEvent(QContextMenuEvent* event) override{
  if(event==nullptr){
    return; 
  }
   if(selectedNode){
      nodeSceneMenu->exec(event->globalPos());
      return;
    }
    GraphicsView::contextMenuEvent(event);
    return;
}
void wheelEvent(QWheelEvent* event) override{
    GraphicsView::wheelEvent(event);
    return;
}
void mousePressEvent(QMouseEvent* event) override{
  GraphicsView::mousePressEvent(event);
  if(event->button()==Qt::RightButton){
   
    return;
  }
  if(CanDrawPointNode){
      //we Collect the respective point value and set it to the Singly Point Variable Node...
       auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
      size_t nodeId = gscene->GraphModel()->addNode(tr("Point Node"));
    if (nodeId != InvalidNodeId){
        gscene->GraphModel()->setNodeData(nodeId, NodeRole::Position, mapToScene(event->pos()));
        auto point_node=dynamic_cast<SinglyPointNode*>(gscene->GraphModel()->Models().at(nodeId).get());
        if(point_node){
          std::cout<<"Current Value of gp_Pnt("<<this->x<<","<<this->y<<","<<this->z<<");"<<endl;
          point_node->SetPoint(Point(this->x,this->y,this->z));
            std::cout<<"Successful Creation of Point Node"<<endl;
            std::unique_ptr<NodeGraphicsObject> ngo=std::make_unique<NodeGraphicsObject>(*gscene,nodeId);
            if(ngo.get()){
              ngo->setVisible(true);
              ngo->update();
              gscene->update();
              updateSceneRect(gscene->sceneRect());
              cout<<"Node Graphics Object successfully rendered"<<endl; 
            }

          return;
        }
        else{
          std::cout<<"Failed to access Point Node"<<endl;
          return;
        }
       
    } 
  }
    if(rstate==RS_TRANSFORM){
       auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
      size_t nodeId = gscene->GraphModel()->addNode(tr("Transform Node")); 
     if(nodeId!= InvalidNodeId){
       gscene->GraphModel()->setNodeData(nodeId, NodeRole::Position, mapToScene(event->pos()));
       auto trans_node=dynamic_cast<SinglyTransformNode*>(gscene->GraphModel()->Models().at(nodeId).get());
       if(trans_node){
         trans_node->SetTransformData(NodeInputTransform);
         if(NodeInputTransform.Form()==gp_Identity){
          std::cout<<"It is an identity matrix"<<endl;
         }
          std::unique_ptr<NodeGraphicsObject> ngo=std::make_unique<NodeGraphicsObject>(*gscene,nodeId);
          if(ngo){
             ngo->setVisible(true);
             ngo->update();
              gscene->update();
              updateSceneRect(gscene->sceneRect());
              cout<<"Node Initiated Successfully"<<std::endl;
              return;
          }
       }
       else{
        std::cout<<"Failed to get a transformation node"<<std::endl;
         return;
       }


       }
       else{
        std::cout<<"Not Created Successfully"<<std::endl;
       }


     return;
    }
    switch(shapedraw){
    case SP_SHAPE:{
      auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
      size_t nodeId = gscene->GraphModel()->addNode(tr("Shape Node"));
       if(nodeId!= InvalidNodeId){
       gscene->GraphModel()->setNodeData(nodeId, NodeRole::Position, mapToScene(event->pos()));
       auto shape_node=dynamic_cast<SinglyShapeNode*>(gscene->GraphModel()->Models().at(nodeId).get());
       if(shape_node){
        if(NodeInputShape.IsSame(TopoDS_Shape())){
          std::cout<<"Node Input Shape Is Empty"<<std::endl;
        }
         shape_node->SetShapeData(NodeInputShape);
          std::unique_ptr<NodeGraphicsObject> ngo=std::make_unique<NodeGraphicsObject>(*gscene,nodeId);
          if(ngo){
             ngo->setVisible(true);
             ngo->update();
              gscene->update();
              updateSceneRect(gscene->sceneRect());
              cout<<"Node Initiated Successfully"<<std::endl;
          }
       }
       else{
        std::cout<<"Failed to get a shape node"<<std::endl;
       }

    }
    else{
      std::cout<<"Invalid Node Id"<<std::endl;
      std::cout<<InvalidNodeId<<std::endl;
      std::cout<<nodeId<<std::endl;
    }
      return; 
    }
  case SP_FACE:{
    auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
       size_t nodeId = gscene->GraphModel()->addNode(tr("Single Face Node")); 
        if(nodeId!= InvalidNodeId){
       gscene->GraphModel()->setNodeData(nodeId, NodeRole::Position, mapToScene(event->pos()));
       auto shape_node=dynamic_cast<SinglyFaceNode*>(gscene->GraphModel()->Models().at(nodeId).get());
       if(shape_node){
        if(nodeInputFace.IsSame(TopoDS_Face())){
          std::cout<<"Node Input Face Is Empty"<<std::endl;
        }
         shape_node->SetFace(nodeInputFace);
          std::unique_ptr<NodeGraphicsObject> ngo=std::make_unique<NodeGraphicsObject>(*gscene,nodeId);
          if(ngo){
             ngo->setVisible(true);
             ngo->update();
              gscene->update();
              updateSceneRect(gscene->sceneRect());
              cout<<"Node Initiated Successfully"<<std::endl;
          }
       }
       else{
        std::cout<<"Failed to get a Face node"<<std::endl;
       }

    }
  
    return;
  
  }
    break;
    default:
    break;
}
  if(compileAction==ACT_ACTIVATE){
    CompileAllNode();
  }
  
  
  auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
  if(!gscene){
    emit SendMessage(tr("Failed To Cast To Scene"));
    return;
  }
  if(vaction==VA_PASTE){
    if(selectedModel){
      size_t nodeId=gscene->GraphModel()->addNode(selectedModel->name());
      if(nodeId!=InvalidNodeId){
         gscene->GraphModel()->setNodeData(nodeId, NodeRole::Position, mapToScene(event->pos()));
         auto nodeModelInit=dynamic_cast<NodeInitializer*>(gscene->GraphModel()->Models().at(nodeId).get());
         if(nodeModelInit){
          std::cout<<"Successful Casting to an Object of NodeInitializer"<<std::endl;

         }
         else{
            std::cout<<"Failed Casting to an Object of NodeInitializer"<<std::endl;

        }
         std::unique_ptr<NodeGraphicsObject> ngo=std::make_unique<NodeGraphicsObject>(*gscene,nodeId);
          if(ngo){
             ngo->setVisible(true);
             ngo->update();
              gscene->update();
              updateSceneRect(gscene->sceneRect());
              cout<<"Node Initiated Successfully"<<std::endl;
          }
       }
      }
      vaction=VA_NULL;
    }
 
    auto gmodel=gscene->GraphModel();
     if(gmodel){
      emit SendMessage(tr("Graph Model Created"));
      std::cout<<"Graph Model Created Successfully"<<std::endl;
     }
   
     
     auto selListItems=gscene->selectedItems();
     if(selListItems.size()!=0){
     for(QGraphicsItem* item: selListItems){
      auto nodeObject=qgraphicsitem_cast<NodeGraphicsObject*>(item);
      if(nodeObject){
         selectedNode=nodeObject;
      }
      else{
        if(selectedNode){
          selectedNode=nullptr;
        }
        return;
      }
      CurrId=nodeObject->nodeId();
      std::cout<<"Current Selected Node Id: "<<CurrId<<std::endl;
      if(gmodel->nodeExists(nodeObject->nodeId())){
          emit SendMessage(tr("The node is created"));
          std::cout<<"Node Created"<<std::endl;
          
          if(gmodel->Models().empty()){
            std::cout<<"models of Graph Model are Empty"<<std::endl;

           }
           else{
            std::cout<<"Graph Model are not Empty"<<std::endl;
             if(gmodel->Models().find(nodeObject->nodeId())!=gmodel->Models().end()){
              std::cout<<"Object Found"<<std::endl;
              receivedFloatNode=dynamic_cast<FloatInputNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
              if(receivedFloatNode){
                std::cout<<"Float Node Found"<<std::endl;
                 IsFloatNodeSet=true;
                emit CreateFloatNodeWidget();
                return;
              }
              else{
              if(IsFloatNodeSet){
                emit DestroyFloatNodeWidget();
                IsFloatNodeSet=false;
              }
              }
              receivedBoolNode=dynamic_cast<BooleanNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
              if(receivedBoolNode){
                 std::cout<<"Bool Node Found"<<std::endl;
                 IsBoolNodeSet=true;
                emit OnCreateBoolWidget();
                return;
              }
              else{
                if(IsBoolNodeSet){
                 std::cout<<"Bool Node Destroyed"<<std::endl;
                 IsBoolNodeSet=false;
                 emit DestroyFloatNodeWidget();

              }
              }
              receivedShape=dynamic_cast<PrimitiveShapeNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
              if(receivedShape){
                if(receivedShape->Shape().IsSame(TopoDS_Shape())){ //if it is the same as the default constructor
                    std::cout<<"Shape Is the Same"<<std::endl;  
                     return;
                }
                if(receivedShape->ShouldSend){
                emit OnSendShape(receivedShape->Shape());
                emit SendMessage(tr("Shape sent Successfully"));
                std::cout<<"Shape Successfully Sent"<<std::endl;
                }
                return;
              }
              receivedFace=dynamic_cast<FaceNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
              if(receivedFace){
                if(receivedFace->outputShape().IsSame(TopoDS_Shape())){
                  std::cout<<"No Shape Is available"<<"\n";
                  return;
                }
                emit EmitParentShape(receivedFace->outputShape());
                emit EmitFaceId(receivedFace->GetId());
                return;
              }
              receivedEdge=dynamic_cast<EdgeNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
              if(receivedEdge){
                if(receivedEdge->outputShape().IsSame(TopoDS_Shape())){
                  std::cout<<"No Shape Is available"<<"\n";
                  return;
                }
                emit EmitParentShape(receivedEdge->outputShape());
                emit EmitEdge(receivedEdge->outputEdge());
                return;
              }
             }
           }
           return;
      }
     
     }
     }
     else{
      if(selectedNode){
        selectedNode=nullptr;
      }
    emit  onDestroyPreviousObject();
     }
     if(compileAction==ACT_ACTIVATE){
         CompileAllNode();
  }
  
      /*
      emit SendNodeId(nodeobject->nodeId());
      CurrNodeId=nodeobject->nodeId();
      we have to check if the model of the nodeObject is a floatDelegateModel,
        if it evaluates to be true, we are going to update the model and redraw it's nodeObject at a particular position on the screen
      void OnReceiveNodeId(const size_t& id){
        if(!scene()){
        emit SendMessage(tr("Scene is not created"));
        return;
        }
      auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
      if(!gscene){
        emit SendMessage(tr("Failed to cast to an Object of DataFlowGraphicsScene"));
        return;
      }
      auto gmodel=dynamic_cast<DataFlowGraphModel*>(&gscene->graphModel());

      if(!gmodel){
         emit SendMessage(tr("Failed to cast to an Object of DataFlowGraphModel"));
         return;
      }
      auto floatmodel=gmodel->delegateModel<FloatInputData>(CurrNodeId));
      if(floatmodel){
         emit CreateNodeWidget();
      
      
      }
      
      
      return;
      }
      
      
      
      
      */
    
  return;
}
void mouseDoubleClickEvent(QMouseEvent* event) override{
  QGraphicsView::mouseDoubleClickEvent(event);
  return;
}

void mouseMoveEvent(QMouseEvent* event) override{
  GraphicsView::mouseMoveEvent(event);
  return;
}
Handle(AIS_InteractiveContext)& Context() {
    return context.get();
}
signals:
void OnSendShape(const TopoDS_Shape& shape);
void OnSendAIS_ShapeToDrawingWidget(const Handle(CustomAIS_Shape)& shape);
void OnSendNodeId(NodeId const nodeId);
void OnSendWidget(bool check);
void SendMessage(const QString& msg);
void CreateFloatNodeWidget();
void OnCreateBoolWidget();
void OnMoveShapes(const std::vector<Handle(CustomAIS_Shape)>& shapes);
void OnUpdateFloatInput(const float& value);  //For fnodewidget;
void OnSendBooleanValue(bool value);
void DestroyFloatNodeWidget();
void NodeModelChanged();
void EmitParentShape(const TopoDS_Shape& shape);
void EmitFaceId(const int& Id);
void EmitEdge(const TopoDS_Shape& edge);
void onDestroyPreviousObject();
//public slots
public slots:
void OnReceiveAIS_Shape(const Handle(CustomAIS_Shape)& shape){
    emit OnSendAIS_ShapeToDrawingWidget(shape);
    return;
}
void OnReceiveShapes(const std::vector<Handle(CustomAIS_Shape)>& shapes){
  emit OnMoveShapes(shapes);
  return;
}
void OnHandleInputEvent(const float& value){
  emit OnUpdateFloatInput(value);
  return;
}
void OnUpdateAllGraphicObjects(){
  auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
   if(!gscene){
    return;
   }
   auto Items=gscene->items();
  if(Items.isEmpty()){
    return;
  }
  for(int i=0;i<Items.size();i++){
    auto nodeObject=qgraphicsitem_cast<NodeGraphicsObject*>(Items.value(i));
    if(nodeObject){
      nodeObject->update();
    }
    else{
      auto connectionObject=qgraphicsitem_cast<ConnectionGraphicsObject*>(Items.value(i));
      if(connectionObject){
        connectionObject->update();
      }
    }
  }
}
void CompileAllNode(){
  //get the node scene and update all nodeDelegateModel
   auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
   if(!gscene){
    return;
   }
   unsigned int portCount=0;
   auto nodeIds=gscene->GraphModel()->allNodeIds();
   if(nodeIds.empty()){
    return;
   }
   for(auto iter=nodeIds.begin();iter!=nodeIds.end();++iter){
     portCount=GetOutPortCount(*iter);
     for(int i=0;i<portCount;i++){
      OnUpdateAllNodeId(*iter,i);
     }
   } //update graphModel
   
   cout<<"Amount of Nodes: "<<nodeIds.size()<<std::endl;
   OnUpdateAllGraphicObjects();
   updateSceneRect(gscene->sceneRect()); //update all nodeGraphicsObject and connectionGraphicsObject  

  return;
}

unsigned int GetOutPortCount(const NodeId& nodeId) {
  auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
  return gscene->GraphModel()->nodeData(nodeId,NodeRole::OutPortCount).value<int>();
}

void OnUpdateAllNodeId(const NodeId& nodeId,const PortIndex& portIndex){
  auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
   if(!gscene){
    return;
   }
   std::unordered_set<ConnectionId> const &connected = gscene->GraphModel()->connections(nodeId,
                                                       PortType::Out,
                                                                    portIndex);
   if(connected.empty()){
    std::cout<<"Node Id:"<<nodeId<<"does not have any output connections"<<endl;
    return;  //no connections at all
   }

    const QVariant portDataToPropagate =gscene->GraphModel()->portData(nodeId, PortType::Out, portIndex, PortRole::Data);

    for (auto const &cn : connected) {
      gscene->GraphModel()->setPortData(cn.inNodeId, PortType::In, cn.inPortIndex, portDataToPropagate, PortRole::Data);
    }
   
  return;
}
void OnDeleteNode(const NodeId& nodeId){
   auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
   if(!gscene){
    return;
   }
   auto facenode=dynamic_cast<FaceNode*>(gscene->GraphModel()->Models().at(nodeId).get());
   if(facenode){
    if(facenode->Output()){  //after finding the facenode,Set it to false;
        if(facenode->Output()->Data().Index()<facenode->Output()->Data().parent().FaceCount()){
        std::cout<<"Face Index: "<<facenode->Output()->Data().Index()<<"\n";
        facenode->Output()->GetData().parent().GetFace(facenode->Output()->GetData().Index()).IsAssigned=false;
      }
      
    }
    gscene->GraphModel()->deleteNode(nodeId);
   updateSceneRect(gscene->sceneRect());
   return;
   }
    auto edgenode=dynamic_cast<EdgeNode*>(gscene->GraphModel()->Models().at(nodeId).get());
   if(edgenode){
    if(edgenode->Output()){  //after finding the facenode,Set it to false;
        if(edgenode->Output()->GetData().Index() > edgenode->Output()->GetData().parent().EdgeCount()){
          std::cout<<"Edge Index: "<<edgenode->Output()->GetData().Index()<<"\n";
          return;
        }
        edgenode->Output()->GetData().parent().GetEdge(edgenode->Output()->GetData().Index()).IsAssigned=false;
      
    }
    gscene->GraphModel()->deleteNode(nodeId);
     updateSceneRect(gscene->sceneRect());
    return;
   }
   gscene->GraphModel()->deleteNode(nodeId);
   updateSceneRect(gscene->sceneRect());
  return;
}
void OnDeleteHandler(){
  if(selectedNode){
    OnDeleteNode(selectedNode->nodeId());
  }
  return;
}
void OnHandleAutoCompile(bool Checked){
  if(Checked){
    compileAction=ACT_ACTIVATE;
  }
  else{
    compileAction=ACT_NULL;
  }
  return;
}
void OnHandleCopy(){
  vaction=VA_COPY;
  if(!selectedNode){
    return;
  }
   auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
   if(!gscene){
    return;
   }
   auto gmodel=gscene->GraphModel();
   if(!gmodel){
    return;
   }
  selectedModel=dynamic_cast<NodeDelegateModel*>(gmodel->Models().at(selectedNode->nodeId()).get());
  return;

}
void OnHandlePaste(){
  vaction=VA_PASTE;
  return;
}
/*void OnUpdateNodeModel(const QVariant&  value){
  auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
  if(!gscene){
    std::cout<<"Cannot cast To an object of DataFlowGraphicScene"<<std::endl;
  }
  try{
  auto& gmodel=dynamic_cast<DataFlowGraphModel&>(gscene->graphModel());
   gmodel.setPortData(CurrNodeId,PortType::Out,0,value);
  }
  catch(const std::bad_cast& e){
   SendMessage(tr("Bad cast"));
  }
 
  return;
}
*/
/*void OnDestroyDialog(){
  fnodedialog->accept();
  return;
}
void OnCloseDialog(){
   fnodedialog->rejected();
   if(fnodedialog.get()){
    QObject::disconnect(fnodedialog->ok_button.get(),&QPushButton::pressed,this,&NodeGraphWidget::OnDestroyDialog);
    QObject::disconnect(fnodedialog->cancel_button.get(),QPushButton::pressed,this,&NodeGraphWidget::OnCloseDialog);
     QObject::disconnect(fnodedialog->Input_ValueSection->myValueEdit.get(),&DoubleEdit::textChanged,this,&NodeGraphWidget::OnValueChanged);
    fnodedialog.reset(); 
   }
   return;
}
void OnValueChanged(const QString& val){
  QLocale locale(QLocale::C);
  bool isOk=false;
  float value=locale.toFloat(val,&isOk);
  if(isOk){
    OnUpdateNodeModel(QVariant(value));
  }
  else{
    SendMessage(tr("Failed in Converting the inputted value"));
  }
  return;
}

*/


};







#endif