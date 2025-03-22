/*请编写程序创建一个有向图。有向图中包含n个顶点，编号为0至n-1。 
*/
#include <iostream>
using namespace std;
class Vertex;
class Edge{
public:
    int to;
    int weight;
    Edge* next;
    Edge():to(0),weight(0),next(nullptr){}
    Edge(int t,int wei):to(t),weight(wei),next(nullptr){}
};
class Vertex{
public:
    int num;
    Edge* head;
    Vertex():num(-1),head(nullptr){}
};
class Graph{
public:
  Vertex* verarr;
  Graph():verarr(nullptr) {}
  Graph(int vertexnum):verarr(new Vertex[vertexnum]){}
};
Graph* buildGraph(int vertexnum,int edgenum){
  Graph* graph = new Graph(vertexnum);
  for (int i = 0;i<edgenum;++i){
    int fromv  = 0;
    int tov = 0;
    int weight = 0;
    cin>>fromv>>tov>>weight;
    graph->verarr[fromv].num = fromv;
    Edge* edge = new Edge(tov,weight);
    if (graph->verarr[fromv].head == nullptr)
    {
      graph->verarr[fromv].head = edge;
    }
    else if(edge->to<graph->verarr[fromv].head->to){
      edge->next = graph->verarr[fromv].head;
      graph->verarr[fromv].head = edge;
    }
    else{
      Edge* cur = graph->verarr[fromv].head;
      while(cur->next!=nullptr&&cur->next->to<edge->to){
        cur = cur->next;
      }
      edge->next = cur->next;
      cur->next = edge;
    }
  }
  return graph;
}
void insertionSort(Edge*& sortedhead,Edge* node){
  if (!sortedhead||sortedhead->to>=node->to){
    node->next = sortedhead;
    sortedhead = node;
  }
  else{
    Edge* cur = sortedhead;
    while(cur->next!=nullptr&&cur->next->to<node->to){
      cur = cur->next;
    }
    node->next = cur->next;
    cur->next = node;
  }
}
Edge* sortInLinkList(Edge* head){
  Edge* sortedhead = nullptr;
  Edge* node = head;
  while(node){
    Edge* nextNode = node->next;
    insertionSort(sortedhead,node);
    node = nextNode;
  }
  return sortedhead;
}
void display(Graph* graph,int vertexnum){
  for (int i = 0;i<vertexnum;++i){
    if (graph->verarr[i].num!= -1){
      cout<<graph->verarr[i].num<<":";
      Edge* head = graph->verarr[i].head;
      while(head!=nullptr){
        cout<<"("<<graph->verarr[i].num<<","<<head->to<<","<<head->weight<<")";
        head = head->next;
      }
      cout<<endl;
    }
  }
}
int main(void){
  int edgenums = 0;
  int nodenums = 0;
  cin>>nodenums>>edgenums;
  Graph* graph = buildGraph(nodenums,edgenums);
  display(graph,nodenums);
}