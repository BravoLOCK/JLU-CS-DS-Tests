/*改写dijistra算法，使其能返回最短路径和路上的节点个数*/
#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;
class Edge{
public:
    int to;
    int weight;
    Edge* next;
    Edge():to(0),weight(0),next(nullptr){}
    Edge(int t,int w):to(t),weight(w),next(nullptr){}
};
class Node{
public:
    int num;
    Edge* head;
    Node():num(-1),head(nullptr){}
    Node(int n):num(n),head(nullptr){}
};
class Graph{
public:
    Node* node;
    Graph():node(nullptr){}
    Graph(int n):node(new Node[n]){}
};
Graph* buildGraph(int n){
    Graph* graph = new Graph(n+1);
    int edge1 = 0;
    cin>>edge1;
    for (int i = 0;i<edge1;++i){
        int from,to,weight;
        cin>>from>>to>>weight;
        Edge* edgef = new Edge(to,weight);
        graph->node[from].num = from;
        graph->node[to].num = to;
        Edge* tailf = graph->node[from].head;
        if (tailf == nullptr){
            graph->node[from].head = edgef;
        }
        else{
            while(tailf->next!=nullptr){
                tailf = tailf->next;
            }
            tailf->next = edgef;
        }
        Edge* edget = new Edge(from,weight);
        Edge* tailt = graph->node[to].head;
        if (tailt == nullptr){
            graph->node[to].head = edget;
        }
        else{
            while(tailt->next!=nullptr){
                tailt = tailt->next;
            }
            tailt->next = edget;
        }
    }
    return graph;
}
class Info{
public:
    long long* dist;
    long long* count;
    Info():dist(nullptr),count(nullptr){}
    Info(long long int* d,long long int* c):dist(d),count(c){}
};
Info* Dijikstra(Graph* graph,int start,int n){
    //0弃用
    long long* dist = new long long[n+1];
    long long* pathcount = new long long[n+1];
    pathcount[start] = 1;
    for(int i = 1;i<=n;++i){
        dist[i] = 0x3fffffff;
    }
    dist[start] = 0;
    int* visited = new int[n+1];
    for (int i = 1;i<=n;++i){
        visited[i] = 0;
    }
    for (int j = 1;j<=n;++j){
        int min = -1;
        int min_d = 0x3fffffff;
        for (int i = 1;i<=n;++i){
            if (visited[i] == 0&&dist[i]<min_d){
                min = i;
                min_d = dist[i];
            }
        }
        if (min == -1){
            break;
        }
        visited[min] = 1;
        Edge* cur = graph->node[min].head;
        while(cur!=nullptr){
            if (dist[min]+cur->weight<dist[cur->to]){
                dist[cur->to] = dist[min]+cur->weight;
                pathcount[cur->to] = pathcount[min];
            }
            else if (dist[min]+cur->weight == dist[cur->to]){
                pathcount[cur->to] += pathcount[min];
            }
            cur = cur->next;
        }
    }
    Info* temp = new Info(dist,pathcount);
    return temp;
}
int main (void){
    int n;
    cin>>n;
    Graph* graph = buildGraph(n);
    //用info存储Dij和Nij
    Info** info = new Info* [n+1];
    //n^3
    for (int i = 1;i<=n;++i){
        info[i] = Dijikstra(graph,i,n);
    }
    //算k个f（k）
    for (int k = 1;k<=n;++k){
        //算k到各个点的最短距离
        Info* inf = Dijikstra(graph,k,n);    //n^3
        double result  = 0;
        for (int i = 1;i<=n;++i){
            for (int j = 1;j<=n;++j){
                long long Dij = info[i]->dist[j];
                long long Nij = info[i]->count[j];
                long long Nijk = 0;
                if (i == k||j==k||i == j){
                    continue;
                }
                if(inf->dist[i]+info[j]->dist[k] == Dij){
                    Nijk = (inf->count[i])*(info[j]->count[k]);
                    result +=((double)(Dij*Nijk)/Nij);
                }
            }
        }
        printf("%.3f\n",result);
    }
}