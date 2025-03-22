/*寒假到了，小明准备坐火车回老家，现在他从学校出发去火车站，CC市去火车站有两种方式：轻轨和公交车。
小明为了省钱，准备主要以乘坐公交为主。
CC市还有一项优惠政策，持学生证可以免费乘坐一站轻轨（但只能乘坐一站）。
小明想尽快到达火车站，请编写程序为小明找到一条从学校到火车站最快的路线及换乘轻轨的方案。
假设换乘时间忽略不计，公交车与轻轨站点相同，但线路和速度不一定相同，所有线路都是双向的。
可以第一站就乘坐轻轨，也可以最后一站乘坐轻轨，也可以在中间某站坐轻轨。
如果乘坐轻轨和不乘坐轻轨到达火车站的时间相同，则无需换乘轻轨。
最多坐一站轻轨。*/
#include <iostream>
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

int* Dijistra(Graph* graph,int start,int n){
    //0弃用
    int* dist = new int[n+1];
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
            }
            cur = cur->next;
        }
    }
    return dist;     
}
int main (void){
    int n,start,end;
    while(cin>>n>>start>>end){
        int change = -1;
        int chdistance = -1;
        //n为节点数，但在函数内部开辟n+1个空间
        Graph* graph = buildGraph(n);
        Graph* metor = buildGraph(n);
        int* dist1 = Dijistra(graph,start,n);
        int* dist2 = Dijistra(graph,end,n);
        int s3 = dist1[end];
        chdistance = s3;
        for (int i = 1;i<=n;++i){
            if (metor->node[i].num!=-1){
                Edge* cur = metor->node[i].head;
                while(cur!=nullptr){
                    int s1 = dist1[metor->node[i].num];
                    int s2 = dist2[cur->to];
                    if (s1+s2+cur->weight<chdistance){
                        change = metor->node[i].num;
                        chdistance = s1+s2+cur->weight;
                    }
                    cur = cur->next;
                }

            }
        }
        cout<<chdistance<<endl;
        if (change == -1){
            cout<<"no metro"<<endl;
        }
        else{
            cout<<change<<endl;
        }
    }
}