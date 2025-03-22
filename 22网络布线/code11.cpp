/*亚洲杯赛期间需要保证运动员公寓网络畅通，以使运动员都能正常上网。
假定公寓楼内有n个房间，编号为0…n−1，每个房间都需要网络连接。房间 i 有网络，当且仅当满足如下2个条件之一：
（1）房间 i 安装了路由器（成本为 r i>0）
（2）房间 i 和房间 j 有网线连接且房间 j 有网络（在房间 i 和房间 j 之间布置网线的成本为 f ij>0）
假定你是赛事组委会的网络工程师，请编写程序设计一个网络布线方案（哪些房间安装路由器，哪些房间之间布置网线），使得所有房间都有网络，且总成本最小。
例如下图包含7个房间和10个可能的连接，安装路由器的成本为括号内数字，房间之间布置网线的成本为边的权值。其解决方案为右下图，即在房间1和4安装路由器，并进行图中的网线布置。总成本为120。
可引入一个虚拟顶点，将该顶点与其他所有顶点用边相连，边权等于那些顶点的权值。进而形成一个新图，对新图求最小支撑树。注意本题顶点编号从0开始。*/
#include <iostream>
#include <cstdlib>
using namespace std;
int** buildGraph(int vertex,int edge){
     int** graph = new int* [vertex+1];
     for (int i = 0;i<vertex+1;++i){
          graph[i] = new int[vertex+1];
     }
     for (int i = 0;i<vertex+1;++i){
          for (int j = 0;j<vertex+1;++j){
               graph[i][j] = 0;
          }
     }
     for (int i = 0;i<vertex;++i){
          int weight;
          scanf("%d ",&weight);
          // cin>>weight;
          graph[vertex][i] = weight;
          graph[i][vertex] = weight;
     }
     graph[vertex][vertex] = 0;
     for (int i =  0;i<edge;++i){
          int from,to,weight;
          scanf("%d %d %d",&from,&to,&weight);
          // cin>>from>>to>>weight;
          graph[from][to] = weight;
          graph[to][from] = weight;
     }
     return graph;
}
class Next{
public:
     int vex;
     int lowcost;
     Next():vex(0),lowcost(-1){}
};
class Node{
public:
     int head;
     int tail;
     int cost;
};
void Prim(int** graph,int vertex,int edge,Next* closeedge,Node* TE){
     for (int i = 0;i<vertex+1;++i){
          if (graph[0][i] == 0){
               closeedge[i].lowcost = 0x3fffffff;
          }
          else{
               closeedge[i].lowcost = graph[0][i];
               
          }
          closeedge->vex = 0;
     }
     closeedge[0].vex = -1;//顶点1进入集合U
     int count = 0;
     //Prim2
     for (int i = 1;i<vertex+1;++i){
          int v = 0;
          int min = 0x3fffffff;
          for (int j = 0;j<vertex+1;++j){
               if (closeedge[j].vex!=-1&&closeedge[j].lowcost!=0&&closeedge[j].lowcost<min){//选择当前权值最小的跨集合边
                    v =j;
                    min = closeedge[j].lowcost;
               }
          }
          if(v == 0){
               return ;
          }
          else{
               TE[count].head = closeedge[v].vex;//将选择的边加入集合，计数器加一
               TE[count].tail = v;
               TE[count].cost = closeedge[v].lowcost;
               count++;
               closeedge[v].lowcost = 0;//顶点v进入集合u
               closeedge[v].vex = -1;//加入集合中，某些顶点的值要相应修改
               for (int j = 0;j<vertex+1;++j){
                    if (closeedge[j].vex!=-1&&graph[v][j]!=0&&graph[v][j]<closeedge[j].lowcost){
                         closeedge[j].lowcost = graph[v][j];
                         closeedge[j].vex = v;
                    }
               }
          }
     }
}
int main (void){
     int vertex,edge;
     cin>>vertex>>edge;
     int** graph = buildGraph(vertex,edge);
     // for (int i = 0;i<vertex+1;++i){
     //      for (int j = 0;j<vertex+1;++j){
     //           cout<<graph[i][j]<<"\t";
     //      }
     //      cout<<endl;
     // }
     Next* closeedge = new Next[vertex+1];
     Node* TE = new Node[vertex+1];
     Prim(graph,vertex,edge,closeedge,TE);
     int  sum = 0;
     for (int i = 0;i<vertex;++i){
          sum+=TE[i].cost;
     }
     cout<<sum<<endl;     
}