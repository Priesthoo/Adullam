#pragma once
#include<TopoDS.hxx>
#include<TopoDS_Shape.hxx>
#include<memory>
#include<vector>
#include<TopoDS_Face.hxx>
#include<TopoDS_Edge.hxx>
#include<TopoDS_Wire.hxx>
#include<TopoDS_Vertex.hxx>
#include<TopoDS_Wire.hxx>
#include<TopExp_Explorer.hxx>
#include<functional>

#include<ShapeUtil.hpp>
class ShapePair;

struct EdgePair{
 std::reference_wrapper<ShapePair> Parent;
 unsigned int index;
 TopoDS_Edge edge;
 bool IsAssigned=false;
 TopoDS_Shape edgeShape;
 EdgePair(ShapePair* pa=nullptr):Parent{*pa}{
  
 }

 EdgePair(ShapePair& shape,const unsigned int& in,const TopoDS_Edge& edge_1,const TopoDS_Shape& edshape):Parent{shape}{
 
   index=in;
   edge=edge_1;
   edgeShape=edshape;
   return;

 }



 EdgePair& operator=(const EdgePair& edge_1){
    Parent=edge_1.Parent;
  index=edge_1.index;
  edge=edge_1.edge;
  IsAssigned=edge_1.IsAssigned;
  edgeShape=edge_1.edgeShape;
  return *this;
 }

  ShapePair& parent(){
    return Parent.get();
  }
  TopoDS_Edge Edge() const{
    return edge;
  }
  TopoDS_Shape EdgeShape() const{
    return edgeShape;
  }
  void SetEdge(const TopoDS_Edge& edge_1){
    edge=edge_1;
  }
  unsigned int Index() const{
    return index;
  }
};

struct FacePair{
  std::reference_wrapper<ShapePair> Parent;
  TopoDS_Face face;
  unsigned int index;
  bool IsAssigned=false;
  TopoDS_Shape faceShape;
    FacePair(ShapePair* pa=nullptr):Parent{*pa}{
  
 }

  FacePair(ShapePair& shape,const unsigned int& in,const TopoDS_Face& face_1,const TopoDS_Shape& fshape):Parent{shape}{
   index=in;
   face=face_1;
  
   faceShape=fshape;
   return;
  }
  
  FacePair& operator=(const FacePair& pairFace){
     Parent=pairFace.Parent;
    face=pairFace.face;
    index=pairFace.index;
    IsAssigned=pairFace.IsAssigned;
    faceShape=pairFace.faceShape;
    return *this;
  }
  ShapePair& parent(){
    return Parent.get();
  }
  TopoDS_Face Face() const{
    return face;
  }
  void SetFace(const TopoDS_Face& f){
    face=f;
    return;
  }
  unsigned int Index() const{
    return index;
  }
  TopoDS_Shape FaceShape()const {
    return faceShape;
  }
};

struct VertexPair{
   std::reference_wrapper<ShapePair> Parent;
   TopoDS_Vertex vertex;

   unsigned int index;
   bool IsAssigned=false;
   TopoDS_Shape vertexShape;
    VertexPair(ShapePair* pa=nullptr):Parent{*pa}{
  
 }
   VertexPair(ShapePair& shape,const unsigned int& in,const TopoDS_Vertex& vertex_1,const TopoDS_Shape& vshape):Parent{shape}{
      index=in;
      vertex=vertex_1;
      
      vertexShape=vshape;
      return;
   }
  

   VertexPair& operator=(const VertexPair& pairVertex){
    index=pairVertex.index;
    vertex=pairVertex.vertex;
    Parent=pairVertex.Parent;
    IsAssigned=pairVertex.IsAssigned;
    return *this;
   }

    ShapePair& parent(){
    return Parent.get();
  }
  TopoDS_Vertex Vertex() const{
    return vertex;
  }
  TopoDS_Shape VertexShape() const{
    return vertexShape;
  }
};


// main shape
class ShapePair{
private:
TopoDS_Shape ParentShape;
size_t faceCount=0;
size_t edgeCount=0;
size_t vertexCount=0;
public:
std::vector<EdgePair> edgePairs;
std::vector<FacePair> facePairs;
std::vector<VertexPair> vertexPairs;


public:
ShapePair()=default;

explicit ShapePair(const TopoDS_Shape& p_shape){
     SetShape(p_shape);
}

void SetShape(const TopoDS_Shape& p_shape){
  if(ParentShape.IsSame(p_shape)){
    return;
  }
  if(!vertexPairs.empty()){
    vertexPairs.clear();
  }
  if(!edgePairs.empty()){
     edgePairs.clear();
  }
  if(!facePairs.empty()){
    facePairs.clear();
  }
   vertexCount=0;
   edgeCount=0;
   faceCount=0;
    ParentShape=p_shape;
      if(ParentShape.IsNull()){
         return;
      }
      switch(ParentShape.ShapeType()){
        case TopAbs_COMPOUND:{
            TopExp_Explorer exp(ParentShape,TopAbs_ShapeEnum::TopAbs_FACE);
           for(;exp.More();exp.Next()){
            facePairs.emplace_back(*this,faceCount,TopoDS::Face(exp.Current()),exp.Current());
             ++faceCount;
           }
           TopExp_Explorer exp1;
           exp1.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp1.More();exp1.Next()){
             edgePairs.emplace_back(*this,edgeCount,TopoDS::Edge(exp1.Current()),exp1.Current());
             ++edgeCount;
             
           }
             TopExp_Explorer exp2;
           exp2.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp2.More();exp2.Next()){
           vertexPairs.emplace_back(*this,vertexCount,TopoDS::Vertex(exp2.Current()),exp2.Current());
            ++vertexCount;
           }
        }
        case TopAbs_COMPSOLID:{
            TopExp_Explorer exp(ParentShape,TopAbs_ShapeEnum::TopAbs_FACE);
           for(;exp.More();exp.Next()){
            facePairs.emplace_back(*this,faceCount,TopoDS::Face(exp.Current()),exp.Current());
             ++faceCount;
           }
           TopExp_Explorer exp1;
           exp1.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp1.More();exp1.Next()){
             edgePairs.emplace_back(*this,edgeCount,TopoDS::Edge(exp1.Current()),exp1.Current());
             ++edgeCount;
             
           }
             TopExp_Explorer exp2;
           exp2.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp2.More();exp2.Next()){
           vertexPairs.emplace_back(*this,vertexCount,TopoDS::Vertex(exp2.Current()),exp2.Current());
            ++vertexCount;
           }
        }
         case TopAbs_SOLID:{
            TopExp_Explorer exp(ParentShape,TopAbs_ShapeEnum::TopAbs_FACE);
           for(;exp.More();exp.Next()){
            facePairs.emplace_back(*this,faceCount,TopoDS::Face(exp.Current()),exp.Current());
             ++faceCount;
           }
           TopExp_Explorer exp1;
           exp1.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp1.More();exp1.Next()){
             edgePairs.emplace_back(*this,edgeCount,TopoDS::Edge(exp1.Current()),exp1.Current());
             ++edgeCount;
             
           }
             TopExp_Explorer exp2;
           exp2.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp2.More();exp2.Next()){
           vertexPairs.emplace_back(*this,vertexCount,TopoDS::Vertex(exp2.Current()),exp2.Current());
            ++vertexCount;
           }
         }
         break;
         case TopAbs_SHELL:{
             TopExp_Explorer exp(ParentShape,TopAbs_ShapeEnum::TopAbs_FACE);
           for(;exp.More();exp.Next()){
            facePairs.emplace_back(*this,faceCount,TopoDS::Face(exp.Current()),exp.Current());
             ++faceCount;
           }
           TopExp_Explorer exp1;
           exp1.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp1.More();exp1.Next()){
             edgePairs.emplace_back(*this,edgeCount,TopoDS::Edge(exp1.Current()),exp1.Current());
             ++edgeCount;
             
           }
             TopExp_Explorer exp2;
           exp2.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp2.More();exp2.Next()){
           vertexPairs.emplace_back(*this,vertexCount,TopoDS::Vertex(exp2.Current()),exp2.Current());
            ++vertexCount;
           }
         }
         break;
         case TopAbs_FACE:{
           TopExp_Explorer exp1;
           exp1.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp1.More();exp1.Next()){
             edgePairs.emplace_back(*this,edgeCount,TopoDS::Edge(exp1.Current()),exp1.Current());
             ++edgeCount;
             
           }
             TopExp_Explorer exp2;
           exp2.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp2.More();exp2.Next()){
           vertexPairs.emplace_back(*this,vertexCount,TopoDS::Vertex(exp2.Current()),exp2.Current());
            ++vertexCount;
           }  
           faceCount=1;
         }
         break;
         case TopAbs_WIRE:{
             TopExp_Explorer exp1;
           exp1.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_EDGE);
           for(;exp1.More();exp1.Next()){
             edgePairs.emplace_back(*this,edgeCount,TopoDS::Edge(exp1.Current()),exp1.Current());
             ++edgeCount;
             
           }
             TopExp_Explorer exp2;
           exp2.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp2.More();exp2.Next()){
           vertexPairs.emplace_back(*this,vertexCount,TopoDS::Vertex(exp2.Current()),exp2.Current());
            ++vertexCount;
           }  
         }
         break;
         case TopAbs_EDGE:{
              TopExp_Explorer exp2;
           exp2.Init(ParentShape,TopAbs_ShapeEnum::TopAbs_VERTEX);
           for(;exp2.More();exp2.Next()){
           vertexPairs.emplace_back(*this,vertexCount,TopoDS::Vertex(exp2.Current()),exp2.Current());
            ++vertexCount;
           } 
           edgeCount=1; 
         }
         
         break;
      case TopAbs_VERTEX:{
         vertexCount=1;
      }
      break;
      default:
        break;
      }

   return;
}
TopoDS_Shape parentShape() const{
   return ParentShape;
}
TopAbs_ShapeEnum shapeType() const{
     return ParentShape.ShapeType();
}
VertexPair& GetVertex(const size_t& index){
       return vertexPairs.at(index);
}
EdgePair& GetEdge(const size_t& index) {
     return edgePairs.at(index);
}
FacePair& GetFace(const size_t& index) {
    return facePairs.at(index);
}
size_t VertexCount() const{
  return vertexCount;
}
size_t FaceCount() const{
  return faceCount;
}
size_t EdgeCount() const{
   return edgeCount;
}
~ShapePair(){
   
}

};

