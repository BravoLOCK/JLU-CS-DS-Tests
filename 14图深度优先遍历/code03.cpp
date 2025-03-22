/*编写程序对给定的有向图（不一定连通）进行深度优先遍历，图中包含n个顶点，编号为0至n-1。
本题限定在深度优先遍历过程中，
如果同时出现多个待访问的顶点，则优先选择编号最小的一个进行访问，以顶点0为遍历起点。*/
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
class Vertex;
class Edge{
public:
    int to;
    int weight;
    Edge* next;
    Edge():to(0),weight(0),next(nullptr){}
    Edge(int t):to(t),next(nullptr){}
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
    cin>>fromv>>tov;
    graph->verarr[fromv].num = fromv;
    graph->verarr[tov].num = tov;
    Edge* edge = new Edge(tov);
    if (graph->verarr[fromv].head == nullptr)
    {
      graph->verarr[fromv].head = edge;
    }
    else if(edge->to>graph->verarr[fromv].head->to){
      edge->next = graph->verarr[fromv].head;
      graph->verarr[fromv].head = edge;
    }
    else{
      Edge* cur = graph->verarr[fromv].head;
      while(cur->next!=nullptr&&cur->next->to>edge->to){
        cur = cur->next;
      }
      edge->next = cur->next;
      cur->next = edge;
    }
  }
  return graph;
}
void DFS(Graph* graph,int start,int* visited){
    stack<int> st;
    st.push(start);
    while(!st.empty()){
        int node = st.top();
        st.pop();
        if(visited[node]==0){
            visited[node] = 1;
            cout<<node<<" ";
            Edge* head = graph->verarr[node].head;
            while(head!=nullptr){
                if (visited[head->to] == 0){
                    st.push(head->to);
                }
                head = head->next;
            }
        }
    } 
}
void DFSINGraph(Graph* graph,int nodenums){
    int* visited = new int[nodenums];
    memset(visited,0,sizeof(int)*nodenums);
    for (int i = 0;i<nodenums;++i){
        if (visited[i] == 0){
            DFS(graph,i,visited);
        }
    }
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
  DFSINGraph(graph,nodenums);
}