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
#include<QtWidgets/QFileDialog>
#include<QtWidgets/QInputDialog>
#include<QtCore/QFileInfo>
#include<functional>
#include<iostream>
#include<QtWidgets/QMessageBox>
#include<InfoUtility.hpp>
#include<QtCore/QJsonArray>
#include<QtCore/QJsonDocument>
#include<ConnectionIdUtils>
#include<QtWidgets/QGraphicsRectItem>
using namespace INFO;
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
SP_WIRE,
SP_CMDSHAPE,
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

enum DragStatus{
  DS_NULL,
  DS_DRAG
};
enum ContextMenuStatus{
  CMS_NODE,
  CMS_SINGLENODE,
  CMS_DRAG,
  CMS_EDGE,
  CMS_FACE,
  CMS_NULL
};
class NodeGraphWidget:public GraphicsView{
private:
Q_OBJECT
std::shared_ptr<NodeRegistry> Registry;
std::shared_ptr<DataFlowGraphicsScene> scene_1;
std::unique_ptr<FloatNodeWidget> fnodewidget;
std::unique_ptr<FloatNodeDialog> fnodedialog;
std::unique_ptr<NodeSceneMenu> nodeSceneMenu=make_unique<NodeSceneMenu>();
std::unique_ptr<SinglyShapeMenu> singlyNodeMenu=std::make_unique<SinglyShapeMenu>();
std::unique_ptr<DragMenu> dragMenu=std::make_unique<DragMenu>();
std::unique_ptr<QGraphicsRectItem> rubberRect;
std::unique_ptr<QMenu> faceNodeMenu;
std::unique_ptr<QMenu> edgeNodeMenu;
std::unique_ptr<QAction> highlightFaceAction=std::make_unique<QAction>(tr("Highlight"),nullptr);
std::unique_ptr<QAction> highlightEdgeAction=std::make_unique<QAction>(tr("Highlight"),nullptr);
std::unique_ptr<QAction> deleteEdgeAction=std::make_unique<QAction>(tr("Delete Edge"),nullptr);
std::unique_ptr<QAction> deleteFaceAction=std::make_unique<QAction>(tr("Delete Face"),nullptr);
std::unique_ptr<QAction> showIndex=std::make_unique<QAction>(tr("Show Index"),nullptr);
std::unique_ptr<QAction> showIndex1=std::make_unique<QAction>(tr("Show Index"),nullptr);

QPointF startPoint;
QPointF endPoint;
std::reference_wrapper<Handle(AIS_InteractiveContext)> context;
DataFlowGraphModel* graph_model=nullptr;
size_t CurrId=0;
int CurrNodeId=-1;
int prevNodeIds; //this is check if changes have happened
int currNodeIds; //this is to check if changes have happened
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
TopoDS_Edge nodeInputEdge=TopoDS_Edge();
TopoDS_Shape NodeInitialShape=TopoDS_Shape();
FloatInputNode* receivedFloatNode=nullptr;
SHAPEDRAW shapedraw=SP_NULL;
RENDER_STATE rstate=RS_NULL;
ContextMenuStatus cms=CMS_NULL;
AUTO_COMPILE_ACTION compileAction=ACT_NULL;
VIEW_ACTION  vaction=VA_NULL;
BooleanNode* receivedBoolNode=nullptr;
bool IsBoolNodeSet=false;
PrimitiveCubeNode* receivedCubeNode=nullptr;
PrimitiveShapeNode* receivedShape=nullptr;
NodeDelegateModel* selectedModel=nullptr;
FaceNode* receivedFace=nullptr;
EdgeNode* receivedEdge=nullptr;
SinglyShapeNode* singleNode=nullptr;
SinglyEdgeNode* edgeNode=nullptr;
SinglyFaceNode* faceNode=nullptr;
bool CanDrawPointNode=false;
bool IsCubeNodeSet=false;
bool IsFloatNodeSet=false;
bool isFileSaved=false;
bool isContentAdded=false;
bool isCmdRendered=false;
bool isRectDrawn=false;
QString FileName; //this is currently the File name of our node graph
QByteArray fileArray;
int ShapeId=-1;
int ParentId=-1;
int subShapeId=-1;
TopoDS_Shape sentShape;
TopoDS_Shape cmdShape=TopoDS_Shape();
QString cmdFilePath;
TopoDS_Wire chosenWire;
int sentId=-1;
DragStatus dstatus=DS_NULL;
QRect BoundRect; //For the rubber band selection
std::vector<int> nodeIDs;

NodeGraphWidget(QWidget* parent_widget,Handle(AIS_InteractiveContext)& context_1):GraphicsView(parent_widget),context{context_1}{
   Registry.reset(new NodeRegistry());
   //Register Model
 
   std::cout<<"I am in NodeGraphWidget Constructor"<<"\n";
    
  
   rubberRect=std::make_unique<QGraphicsRectItem>(nullptr);
   faceNodeMenu=std::make_unique<QMenu>();
   edgeNodeMenu=std::make_unique<QMenu>();
   faceNodeMenu->addAction(highlightFaceAction.get());
   edgeNodeMenu->addAction(highlightEdgeAction.get());
   faceNodeMenu->addAction(deleteFaceAction.get());
   edgeNodeMenu->addAction(deleteEdgeAction.get());
  faceNodeMenu->addAction(showIndex.get());
   edgeNodeMenu->addAction(showIndex1.get());
   
   
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
Registry->registerModel<CommandShape>(tr("Command"));
Registry->registerModel<CommandEntryShapeNode>(tr("Command"));
   Registry->registerModel<SinglyPointNode>(tr("Points"));
   Registry->registerModel<ShapeArrayNode>("Array");
   Registry->registerModel<VectorToVectorNode>("Conversion");
   Registry->registerModel<ArrayToVectorNode>("Conversion");
   Registry->registerModel<SingleArrayToVectorNode>("Conversion");
   Registry->registerModel<BooleanNode>("Condition");
   Registry->registerModel<SinglyTransformNode>("Transform");
   Registry->registerModel<SinglyShapeNode>("Primitive Shapes");
   Registry->registerModel<SinglyWireNode>("Primitive Shapes");
   Registry->registerModel<FiveShapeNode>("Array");
   Registry->registerModel<TenSizedArrayNode>("Array");
   Registry->registerModel<ArrayToVectorNode>("Array");
   Registry->registerModel<ArrayVectorNode>("Array");
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
   Registry->registerModel<SinglyEdgeNode>(tr("Sub Shape"));
   Registry->registerModel<GoldMaterialNode>(tr("Predefined Material"));
   Registry->registerModel<BoundedLineNode>(tr("2D Shapes"));
   Registry->registerModel<SketchLineNode>(tr("2D Shapes"));
   Registry->registerModel<SketchCircleNode>(tr("2D Shapes"));
    Registry->registerModel<SinglyFaceNode>(tr("Sub Shape"));
   Registry->registerModel<ExtrusionNode>(tr("CAD operations"));
   Registry->registerModel<RevolveNode>(tr("CAD operations"));
   graph_model=new DataFlowGraphModel(Registry);
   scene_1=std::make_shared<DataFlowGraphicsScene>(*graph_model,this);
   GraphicsView::setScene(scene_1.get());
   QObject::connect(nodeSceneMenu->CompileNodesAction(),&QAction::triggered,this,&NodeGraphWidget::CompileAllNode);
   QObject::connect(nodeSceneMenu->DeleteNodeAction(),&QAction::triggered,this,&NodeGraphWidget::OnDeleteHandler);
   
   QObject::connect(nodeSceneMenu->CopyNodeAction(),&QAction::triggered,this,&NodeGraphWidget::OnHandleCopy);
   QObject::connect(nodeSceneMenu->PasteNodeAction(),&QAction::triggered,this,&NodeGraphWidget::OnHandlePaste);
   setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
   connect(nodeSceneMenu->SaveFileAction(),&QAction::triggered,this,&NodeGraphWidget::OnSaveNCADFile);
   connect(nodeSceneMenu->SaveAsAction(),&QAction::triggered,this,&NodeGraphWidget::OnSaveAsNCAD);
   connect(nodeSceneMenu->ClearAction(),&QAction::triggered,this,&NodeGraphWidget::ShouldClearScene);
   connect(nodeSceneMenu->OpenFileAction(),QAction::triggered,this,&NodeGraphWidget::OnOpenNCADFile);
   connect(singlyNodeMenu->HighlightAction(),QAction::triggered,this,&NodeGraphWidget::OnSendId);
  connect(singlyNodeMenu->DeleteAction(),&QAction::triggered,this,&NodeGraphWidget::OnDeleteSinglyNode);
  connect(singlyNodeMenu->DeleteNodeAction(),&QAction::triggered,this,&NodeGraphWidget::OnDeleteHandler);
  connect(singlyNodeMenu->GetIndexAction(),&QAction::triggered,this,&NodeGraphWidget::GetSinglyIndex);
  connect(nodeSceneMenu->EnableDragMode(),&QAction::toggled,this,&NodeGraphWidget::OnHandleDrag);
  connect(dragMenu->disableDragAction.get(),&QAction::toggled,this,&NodeGraphWidget::OnHandleEndDrag);
  connect(dragMenu->convertToCmdShape.get(),&QAction::triggered,this,&NodeGraphWidget::OnConvertToCommandShape);
  connect(this,&NodeGraphWidget::CmdIsRendered,this,&NodeGraphWidget::OnHandleCmdIsRendered);
  connect(highlightFaceAction.get(),&QAction::triggered,this,&NodeGraphWidget::OnHandleFaceParentIndex);
  connect(highlightEdgeAction.get(),&QAction::triggered,this,&NodeGraphWidget::OnHandleParentIndex);
  connect(showIndex.get(),&QAction::triggered,this,&NodeGraphWidget::CheckFaceInfo);
  connect(showIndex1.get(),&QAction::triggered,this,&NodeGraphWidget::CheckEdgeInfo);
  connect(deleteEdgeAction.get(),&QAction::triggered,this,&NodeGraphWidget::OnDeleteHandler);
  connect(deleteFaceAction.get(),&QAction::triggered,this,&NodeGraphWidget::OnDeleteHandler);
  connect(dragMenu->deleteNodes.get(),&QAction::triggered,this,&NodeGraphWidget::OnDeleteNodes);
  return;
}
void OnFindSinglyShape(){
  auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
  if(!gscene){
    emit SendMessage(tr("Failed To Cast To Scene"));
    return;
  }
  bool isFound=false;
    auto gmodel=gscene->GraphModel();
     if(gmodel){
      emit SendMessage(tr("Graph Model Created"));
      std::cout<<"Graph Model Created Successfully"<<std::endl;
     }
     if(gmodel->Models().empty()){
        LoadMessage(tr("Empty Model"),tr("The Model of the Node Graph is empty"));
        return;
     }
     for(auto& ref:gscene->items()){
        auto nodeObject=qgraphicsitem_cast<NodeGraphicsObject*>(ref);
        if(nodeObject){
          auto nodalShape=dynamic_cast<SinglyShapeNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
            if(nodalShape){
               if(nodalShape->InitShape().IsSame(sentShape) && nodalShape->GetIndex()==sentId){
                isFound=true;
                std::cout<<"Shape Found In GraphModel"<<std::endl;
                if(!nodeObject->isSelected()){
                  nodeObject->setSelected(true);
                  nodeObject->update();
                  }
                  auto ndItem=qgraphicsitem_cast<QGraphicsItem*>(nodeObject);
                  if(ndItem){
                    centerOn(ndItem);
                    gscene->update();
                    updateSceneRect(gscene->sceneRect());
                  }
                
                break;
               }
            }
           
        }
     }
     if(isFound==false){
      LoadMessage(tr(""),tr("Shape with a particular Index not found"));
     }
     return;
  
  
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
void OnSendId(){
   if(ShapeId==-1){
    LoadMessage(tr("Shape ID Error"),tr("Cannot access an object with negative shape id"));
    return;
   }
    OnEmitShapeId(ShapeId);
    return;
}

void UpdateShape(const TopoDS_Shape& p_Shape){
   if(receivedShape){
     receivedShape->SetShape(p_Shape);
     std::cout<<"Shape Is Changed"<<std::endl;
   }
   return;
}

void ClearScene(){
  auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
    if(!isFileSaved && gscene->GraphModel()->Models().size()!=0){
    auto ret=QMessageBox::question(nullptr,tr("NodeCAD question"),tr("Do you want to save content"));
    if(ret==QMessageBox::StandardButton::Yes){
       OnSaveAsNCAD();
         gscene->clearScene();
    }
    else{
        gscene->clearScene();
    }
    }
    else{
      if(gscene->GraphModel()->Models().size()!=0){
        OnSaveNCADFile();
       gscene->clearScene();
      }
    }
    
    
  return;
}
void LoadScene(const QJsonObject& scenejson){
   if(scenejson.empty()){
    cout<<"Scene Json is Empty"<<"\n";
    return;
   }
   auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
    gscene->GraphModel()->load(scenejson);
     CompileAllNode();
    gscene->update();
   
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
  if(cms==CMS_DRAG){
   dragMenu->exec(event->globalPos());
   return;
  }
  if(cms==CMS_SINGLENODE){
    singlyNodeMenu->exec(event->globalPos());
    return;
  }
   if(cms==CMS_NODE){
      nodeSceneMenu->exec(event->globalPos());
      return;
    }
    if(cms==CMS_EDGE){
      edgeNodeMenu->exec(event->globalPos());
     return;
    }
    if(cms==CMS_FACE){
     faceNodeMenu->exec(event->globalPos());
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
  if(event->button()==Qt::LeftButton){
  if(dstatus==DS_DRAG){
    if(!rubberRect){
      rubberRect=std::make_unique<QGraphicsRectItem>(nullptr);
    
    }
    startPoint=event->pos();
    rubberRect->setRect(QRectF(startPoint,QSizeF()));
    nodeScene()->addItem(rubberRect.get());
    isRectDrawn=true;
     return;
  }
  
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
    case SP_EDGE:{
     auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
       size_t nodeId = gscene->GraphModel()->addNode(tr("Single Edge Node")); 
        if(nodeId!= InvalidNodeId){
       gscene->GraphModel()->setNodeData(nodeId, NodeRole::Position, mapToScene(event->pos()));
       auto shape_node=dynamic_cast<SinglyEdgeNode*>(gscene->GraphModel()->Models().at(nodeId).get());
       if(shape_node){
        if(nodeInputEdge.IsSame(TopoDS_Edge())){
          std::cout<<"Node Input Edge Is Empty"<<std::endl;
        }
         shape_node->SetEdge(nodeInputEdge);
         shape_node->SetParentIndex(ParentId);
         shape_node->SetIndex(subShapeId);
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
    case SP_WIRE:{
       auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
      
      size_t nodeId = gscene->GraphModel()->addNode(tr("Wire Node"));
       if(nodeId!= InvalidNodeId){
       gscene->GraphModel()->setNodeData(nodeId, NodeRole::Position, mapToScene(event->pos()));
       auto shape_node=dynamic_cast<SinglyWireNode*>(gscene->GraphModel()->Models().at(nodeId).get());
       if(shape_node){
         shape_node->SetWire(chosenWire);
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
       return;
    }
    case SP_CMDSHAPE:{
      auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
      
      size_t nodeId = gscene->GraphModel()->addNode(tr("Cmd Shape Node"));
       if(nodeId!= InvalidNodeId){
       gscene->GraphModel()->setNodeData(nodeId, NodeRole::Position, mapToScene(event->pos()));
       auto shape_node=dynamic_cast<CommandShape*>(gscene->GraphModel()->Models().at(nodeId).get());
       if(shape_node){
         shape_node->SetFileName(cmdFilePath);
         shape_node->SetShape(cmdShape);
         std::unique_ptr<NodeGraphicsObject> ngo=std::make_unique<NodeGraphicsObject>(*gscene,nodeId);
          if(ngo){
             ngo->setVisible(true);
             ngo->update();
              gscene->update();
              updateSceneRect(gscene->sceneRect());
              isCmdRendered=true;
              cout<<"Node Initiated Successfully"<<std::endl;
          }

       }
      shapedraw=SP_NULL;
      emit CmdIsRendered(); //it is emitted either when the command shape is rendered or not...
      return;
    }
    }
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
         shape_node->SetInitShape(NodeInitialShape);
         cout<<"CurrShape Id: "<<ShapeId<<endl;
         shape_node->SetId(ShapeId);
         ShapeId=-1;
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
         shape_node->SetParentIndex(ParentId);
         shape_node->SetIndex(subShapeId);
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
  cms=CMS_NULL;
  
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
         cms=CMS_NODE;
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
               singleNode=dynamic_cast<SinglyShapeNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
             if(singleNode){
              ShapeId=singleNode->GetIndex();
              cms=CMS_SINGLENODE;
              return;
             }
             edgeNode=dynamic_cast<SinglyEdgeNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
             if(edgeNode){
              ParentId=edgeNode->parentIndex();
              subShapeId=edgeNode->index();
              cms=CMS_EDGE;
              return;
             }
            faceNode=dynamic_cast<SinglyFaceNode*>(gmodel->Models().at(nodeObject->nodeId()).get());
             if(faceNode){
              ParentId=faceNode->parentIndex();
              subShapeId=faceNode->index();
              cms=CMS_FACE;
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
  if(dstatus==DS_DRAG){
    if(isRectDrawn){
      nodeScene()->removeItem(rubberRect.get());
      endPoint=event->pos();
      rubberRect->setRect(QRectF(startPoint,QSizeF(endPoint.x(),endPoint.y())));
      nodeScene()->addItem(rubberRect.get());
      return;
    }
  }
  GraphicsView::mouseMoveEvent(event);
  return;
}
void mouseReleaseEvent(QMouseEvent* event) override{
  GraphicsView::mouseReleaseEvent(event);
  if(event->button()==Qt::LeftButton){
    if(dstatus==DS_DRAG){
   if(isRectDrawn){
    isRectDrawn=false;
    endPoint=event->pos();
    nodeScene()->removeItem(rubberRect.get());
    rubberRect->setRect(QRectF(startPoint,QSizeF(endPoint.x(),endPoint.y())));
    nodeScene()->addItem(rubberRect.get());
    nodeScene()->removeItem(rubberRect.get());
    auto objectList=nodeScene()->items(rubberRect->rect());
    if(objectList.empty()){
      LoadMessage(tr(""),tr("No Objects Selected"));
      return;
    }
    for(auto& ref:objectList){
      ref->setFlags(ref->flags()|QGraphicsItem::ItemIsSelectable);
      ref->setSelected(true);
    }
   }
    
    cms=CMS_DRAG;
    }
    
  }
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
void OnEmitShapeId(const int Id);
void onDestroyPreviousObject();
void emitCurrentFile(const QString& str);
void emitChosenFile(const QString& filename);
void emitExistingFile(const QString& str);
void CmdIsRendered();
void EmitParentChildIndex(const int& p,const int& c);
void EmitFaceParentChildIndex(const int& p,const int& c);
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
void OnUpdateConnections(){
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
void OnSaveNCADFile(){
   auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
  
   bool Ok;
   if(FileName==tr("")){
       FileName=QInputDialog::getText(nullptr,tr("NodeCAD Text Input Dialog"),tr("Filename"),QLineEdit::Normal,tr(""),&Ok);
       if(FileName==tr("")){
        FileName=tr("New File");
       }
       if(Ok){
        fileArray=QJsonDocument(gscene->GraphModel()->save()).toJson();

         emit emitCurrentFile(FileName);
       } // register it to the current directory
      
   }
   else{
    //Write To a File, we believe that it is written to the filename that has a filepath
      if(!QFileInfo::exists(FileName)){
           cout<<"File Does not Exist"<<"\n";
      return;
      }
     fileArray=QJsonDocument(gscene->GraphModel()->save()).toJson();
    QFile file(FileName);

    if(file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
       file.write(fileArray);
       file.close();
    }


   }
}
void OnSaveAsNCAD(){
   auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
       if(!gscene){
        return;
       }
  bool Ok;
   FileName=QInputDialog::getText(nullptr,tr("NodeCAD Text Input Dialog"),tr("Filename"),QLineEdit::Normal,tr(""),&Ok);
    if(FileName==tr("")){
       FileName=tr("NewFile");
    }
      if(Ok){
        fileArray=QJsonDocument(gscene->GraphModel()->save()).toJson();

         emit emitCurrentFile(FileName);
       } // register it to the current directory
      
  return;
}
void OnDeleteSinglyNode(){
  if(singleNode){
    singleNode=nullptr;
  }
  ShapeId=-1;
}
void OnOpenNCADFile(){
   QString currFile=QFileDialog::getOpenFileName(this,tr("NodeCAD Open File Dialog"),QDir::homePath(),tr("CAD Files (*.nCAD)"));
   if(currFile.isEmpty()){
   LoadMessage(tr("File Opening Status"),tr("No file was chosen"));
   return;
   }
   emit  emitChosenFile(currFile);
   return;
}
void ShouldClearScene(){
  ClearScene();
  return;
}
void GetSinglyIndex(){
   if(singleNode){
    LoadMessage(tr("Shape Index:"),QString("Shape Index:")+QString::number(singleNode->GetIndex()));
    
   }
   return;

}
void OnHandleDrag(const bool value){
  if(value){
  dstatus=DS_DRAG;
  }
return;
}
void OnHandleEndDrag(const bool value){
 if(value==true){
   
   nodeSceneMenu->EnableDragMode()->setChecked(false);
   cms=CMS_NULL;
   dstatus=DS_NULL;
   isRectDrawn=false;
   if(rubberRect){
    rubberRect.reset();
   }
 }

return;
}
void OnConvertToCommandShape(){
  
   auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
   if(!gscene){
    LoadMessage(tr("Failed To Cast Scene"),tr("Scene Casting Failed"));
    return;
   }
  if(!rubberRect){
    LoadMessage(tr(""),tr("disable Drag mode has been enabled"));
    return;
  }
  if(!rubberRect->rect().isNull()){
    auto rectf=rubberRect->rect(); //floating point rectangle
    QRect recti(static_cast<int>(rectf.x()),static_cast<int>(rectf.y()),static_cast<int>(rectf.width()),static_cast<int>(rectf.height()));
    auto objectList=gscene->items(mapToScene(recti).boundingRect());
    if(objectList.empty()){
      LoadMessage(tr(""),tr("No Selected Object(s)"));
      return;
    }
    //for instance, we have,QGraphicsItem*& item
    int value=0;//To determine the amount of CommandEntry Shape node
    CommandEntryShapeNode* cmdNodeShape=nullptr;
    if(!nodeIDs.empty()){
      nodeIDs.clear();
    }
    std::vector<QtNodes::ConnectionId>connIDs;
    TopoDS_Shape outputShape;
    for(const auto& ref:objectList){
        auto nodeObject=qgraphicsitem_cast<NodeGraphicsObject*>(ref);
        if(nodeObject){
          nodeIDs.emplace_back(nodeObject->nodeId()); 
          cmdNodeShape=dynamic_cast<CommandEntryShapeNode*>(gscene->GraphModel()->Models().at(nodeObject->nodeId()).get());
          if(cmdNodeShape){
            ++value;
          }
          if(value==1){
            outputShape=cmdNodeShape->Shape();
          }
        }
        else{
          auto connectObject=qgraphicsitem_cast<ConnectionGraphicsObject*>(ref);
          if(connectObject){
            connIDs.emplace_back(connectObject->connectionId());
          }
        }

    }
  
  if(value>1 ){
    LoadMessage(tr(""),tr("Cannot Have More than one object of CommandEntryShapeNode"));
    return;
  }
 if(value==1){
   LoadMessage(tr(""),tr("A Command Entry Shape Is Found"));
 }
  if(!cmdNodeShape){
    LoadMessage(tr(""),tr("There is no object of CommandEntryShape Node"));
    return;
  }
  cmdShape=cmdNodeShape->Shape();
 QJsonArray array1;
 QJsonArray array2;
 ConvertToJsonArray(nodeIDs,connIDs,array1,array2);

 QJsonObject subSceneJson;
 subSceneJson["nodes"]=array1;
 subSceneJson["connections"]=array2;
 fileArray=QJsonDocument(subSceneJson).toJson();

  auto ret=QMessageBox::question(nullptr,tr(""),tr("Do you want to save the nodes in an existing file or a new file,\n Click Ok for existing file \nClick Cancel for new file"));
  if(ret==QMessageBox::Ok){
    auto filepath=QFileDialog::getSaveFileName(nullptr,tr("NodeCAD File Dialog"),QDir::homePath(),tr("CAD Files (*.nCAD)"));
     if(filepath.size()==0){
      LoadMessage(tr(""),tr("No file Chosen"));
      return;
     }
     OnWriteToExistingFile(filepath);
    
  }
  else{
  bool Ok;
   auto filename=QInputDialog::getText(nullptr,tr("NodeCAD Text Input Dialog"),tr("Filename"),QLineEdit::Normal,tr(""),&Ok);
   if(!Ok && filename.size()==0){
      LoadMessage(tr(""),tr("Failed to convert or file name is empty"));
      return;
   }
    emit emitCurrentFile(FileName);
  }
  QDir homeDir(QDir::homePath());

  cmdFilePath=homeDir.relativeFilePath(FileName);
  shapedraw=SP_CMDSHAPE;
  LoadMessage(tr("Info"),tr("Select at any point in NodeGraph to position the command shape"));
  return;
  }
}
void OnWriteToExistingFile(const QString& filePath){
       QFile file(filePath);
        FileName=filePath;
      if(file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        file.write(fileArray);
        file.close();
         std::cout<<"Successfully Saved"<<endl;
        isFileSaved=true;
      }
  }


 void ConvertToJsonArray(const vector<int>& Ids,const vector<QtNodes::ConnectionId>& connIds,QJsonArray& array,QJsonArray& array1){
  auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
   if(!gscene){
    return;
   }
   auto gmodel=gscene->GraphModel();
   if(!gmodel){
    return;
   }
  if(Ids.empty()){
     LoadMessage(tr(""),tr("Empty Nodes"));
     return;
  }
  if(connIds.empty()){
    LoadMessage(tr(""),tr("No Connection"));
    return;
  }
  for(const auto& id:Ids){
    array.append(gmodel->saveNode(id));
  }
  for(const auto& id:connIds){
    array1.append(QtNodes::toJson(id));
  }
  return;
}
void OnHandleCmdIsRendered(){
  if(isCmdRendered){ //delete all node Ids and
    if(!nodeIDs.empty()){ 
      for(const auto& val: nodeIDs)
     OnDeleteNode(val);
    }
  }
  isCmdRendered=false;
  nodeIDs.clear();
  return;
}
void OnHandleParentIndex(){
if(edgeNode){
  emit EmitParentChildIndex(edgeNode->parentIndex(),edgeNode->index());
  return;

}
return;
}
void OnHandleFaceParentIndex(){
if(faceNode){
  emit EmitFaceParentChildIndex(faceNode->parentIndex(),faceNode->index());
  return;

}
return;
}
void CheckEdgeInfo(){
if(edgeNode){
 LoadMessage(tr(""),QString("Parent Index:")+QString::number(edgeNode->parentIndex())+QString("\n")+QString("Edge Index:")+QString::number(edgeNode->index()));
 return;
}
 return;
}

void CheckFaceInfo(){
if(faceNode){
 LoadMessage(tr(""),QString("Parent Index:")+QString::number(faceNode->parentIndex())+QString("\n")+QString("Face Index:")+QString::number(faceNode->index()));
 return;
}
 return;
}
void OnDeleteNodes(){
if(nodeIDs.empty()){
LoadMessage(tr(""),tr("No Nodes Are Selected"));
return;
}
for(int i=0;i<nodeIDs.size();i++){
   OnDeleteNode(nodeIDs.at(i));
}
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