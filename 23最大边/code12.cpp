/*给定一个包含n个顶点的无向正权连通图，顶点编号为1到n。
请编写程序计算其最小支撑树中任意两个顶点间路径中，权值最大的边的权值。*/
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
void Prim(int** graph,int** maxcount,int vertex,int edge,Next* closeedge,Node* TE){
     for (int i = 1;i<vertex+1;++i){
          if (graph[1][i] == 0){
               closeedge[i].lowcost = 0x3fffffff;
          }
          else{
               closeedge[i].lowcost = graph[1][i];
               maxcount[1][i] = graph[1][i];
               maxcount[i][1] = graph[1][i];
          }
          closeedge[i].vex = 1;
     }
     closeedge[1].vex = -1;//顶点1进入集合U
     int count = 0;
     int v = 0;
     int pre = 1;
     int timer = 1;
     //Prim2
     for (int i = 2;i<vertex+1;++i){
          int min = 0x3fffffff;
          if (timer == 1){
               timer++;
          }
          else{
               pre = v;
          }
          for (int j = 1;j<vertex+1;++j){
               if (closeedge[j].vex!=-1&&closeedge[j].lowcost<min){//选择当前权值最小的跨集合边
                    v = j;
                    min = closeedge[j].lowcost;
               }
          }
          if(v == 0){
               return ;
          }
          else{
               for (int s = 1;s<vertex+1;++s){
                    if(closeedge[s].vex==-1&&s!=pre&&closeedge[v].lowcost>maxcount[s][pre]){
                         maxcount[s][v] = closeedge[v].lowcost;
                         maxcount[v][s] = closeedge[v].lowcost;
                    }
                    else if(closeedge[s].vex == -1&&s == pre){
                         maxcount[s][v] = closeedge[v].lowcost;
                         maxcount[v][s] = closeedge[v].lowcost;
                    }
                    else if(closeedge[s].vex == -1&&s!=pre&&closeedge[v].lowcost<=maxcount[s][pre]){
                         maxcount[s][v] = maxcount[s][pre];
                         maxcount[v][s] = maxcount[s][pre];
                    }
               }
               TE[count].head = closeedge[v].vex;//将选择的边加入集合，计数器加一
               TE[count].tail = v;
               TE[count].cost = closeedge[v].lowcost;
               count++;
               closeedge[v].lowcost = 0;//顶点v进入集合u
               closeedge[v].vex = -1;//加入集合中，某些顶点的值要相应修改
               for (int j = 1;j<vertex+1;++j){
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
    //  for (int i = 1;i<vertex+1;++i){
    //       for (int j = 1;j<vertex+1;++j){
    //            cout<<graph[i][j]<<"\t";
    //       }
    //       cout<<endl;
    //  }
     Next* closeedge = new Next[vertex+1];
     Node* TE = new Node[vertex+1];
     int** maxcount = new int* [vertex+1];
     for (int i = 0;i<vertex+1;++i){
          maxcount[i] = new int [vertex+1];
     }
     for (int i = 0;i<vertex+1;++i){
          for (int j = 0;j<vertex+1;++j){
               maxcount[i][j] = 0;
          }
     }
     Prim(graph,maxcount,vertex,edge,closeedge,TE);
     int n;
     cin>>n;
     for (int i = 0;i<n;++i){
          int from,to;
          cin>>from>>to;
          cout<<maxcount[from][to]<<endl;
     }
    //  int  sum = 0;
    //  for (int i = 0;i<vertex-1;++i){
    //       sum+=TE[i].cost;
    //  }
    //  cout<<sum<<endl;     
}