/*请编写程序求给定正权有向图的单源最短路径长度。图中包含n个顶点，编号为0至n-1，以顶点0作为源点。 */
#include <iostream>
#include <cstring>
#include <queue>
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
    graph->verarr[tov].num = tov;
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
void initDistance(int* distance,int n){
    for(int i = 0;i<n;++i){
        distance[i] = 0x3fffffff;
    }
}
bool isAllSelected(int* selected,int n){
    for(int i =0;i<n;++i){
        if (selected[i] == 0){
            return false;
        }
    }
    return true;
}
class Info{
public:
    int num;
    int distance;
    Info():num(0),distance(0){}
    Info(int n,int d):num(n),distance(d){}
    bool operator < (const Info& info) const{
        return this->distance>info.distance;
    }
};
// int findMin(int* distance,int n,int* selected){
//     priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
//     for (int i = 0;i<n;++i){
//         if (selected[i] == 0){
//             q.push({distance[i],i});
//         }
//     }
//     return q.top().second;
// }
void Dijikstra(Graph* graph,int nodenums,int start){
    int count = 0;
    int* distance = new int [nodenums];
    int* selected = new int [nodenums];
    memset(selected,0,sizeof(int)*nodenums);
    //selected[start] = 1;
    //count++;
    initDistance(distance,nodenums);
    distance[start] = 0;
    // Edge* cur = graph->verarr[start].head;
    // while(cur!=nullptr){
    //     distance[cur->to] = cur->weight;
    //     cur = cur->next;
    // }
    priority_queue<Info> q;
    q.push(Info(start,distance[start]));
    while(!q.empty()){
        int num = q.top().num;
        int dis = q.top().distance;
        q.pop();
        Edge* tmp = graph->verarr[num].head;
        while(tmp){
            if (dis+tmp->weight<distance[tmp->to]){
                distance[tmp->to] = dis+tmp->weight;
                q.push({tmp->to,distance[tmp->to]});
            }
            tmp = tmp->next;
        }
    }
    // while(count<nodenums){
        
    //     selected[index] = 1;
    //     count++;
    //     Edge* tmp = graph->verarr[index].head;
    //     while(tmp!=nullptr){
    //         if (selected[tmp->to]!=1&&distance[index]+tmp->weight<distance[tmp->to]){
    //             distance[tmp->to] = distance[index]+tmp->weight;
    //         }
    //         tmp = tmp->next;
    //     }
    // }
    for (int i = 0;i<nodenums;++i){
        if (i!=start){
            if (distance[i]!=0x3fffffff){
                cout<<distance[i]<<" ";
            }
        }
    }
}
int main(void){
  int edgenums = 0;
  int nodenums = 0;
  cin>>nodenums>>edgenums;
  Graph* graph = buildGraph(nodenums,edgenums);
  Dijikstra(graph,nodenums,0);
}