/*一个工程被分解成n个子任务，编号为0至n-1。
要完成整个工程需要完成所有的子任务。
其中一些子任务必须先于另外一些子任务被完成。
给定各子任务之间的先后关系，请编写程序给出一个合理的任务完成顺序，若工程不可行，程序亦能识别。*/
#include <iostream>
#include <string>
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
    int in;
    int out;
    int num;
    Edge* head;
    Vertex():num(-1),in(0),out(0),head(nullptr){}
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
    graph->verarr[fromv].out++;
    graph->verarr[tov].in++;
  }
  return graph;
}
void figureIndegree(Graph* graph,int* indegree,int n){
    for(int i = 0;i<n;++i){
        indegree[i] = graph->verarr[i].in;
    }
}
int findZero(int* indegree,int n){
    for (int i = 0;i<n;++i){
        if (indegree[i] == 0){
            return i;
        }
    }
    return -1;
}
bool isAllVisited(int* visited,int n){
    for (int i = 0;i<n;++i){
        if (visited[i] == 0){
            return false;
        }
    }
    return true;
}
string topperSort(Graph* graph,int nodenums){
    string result = "";
    bool breakP = false;
    int* indegree = new int [nodenums];
    figureIndegree(graph,indegree,nodenums);
    int* visited = new int[nodenums];
    memset(visited,0,sizeof(int)*nodenums);
    while(!isAllVisited(visited,nodenums)){
        int index = findZero(indegree,nodenums);
        if (index == -1){
            cout<<"unworkable project"<<endl;
            breakP = true;
            break;
        }
        else{
            Edge* cur = graph->verarr[index].head;
            while(cur!=nullptr){
                graph->verarr[cur->to].in--;
                cur = cur->next;
            }
            graph->verarr[index].in = -1;
            visited[index] = 1;
            figureIndegree(graph,indegree,nodenums);
            result += to_string(graph->verarr[index].num);
            result+=" ";
        }
    }
    if (breakP){
        return "";
    }
    else{
        return result;
    }
}
// void DFS(Graph* graph,int start,int* visited){
//     stack<int> st;
//     st.push(start);
//     while(!st.empty()){
//         int node = st.top();
//         st.pop();
//         if(visited[node]==0){
//             visited[node] = 1;
//             cout<<node<<" ";
//             Edge* head = graph->verarr[node].head;
//             while(head!=nullptr){
//                 if (visited[head->to] == 0){
//                     st.push(head->to);
//                 }
//                 head = head->next;
//             }
//         }
//     } 
// }
// void DFSINGraph(Graph* graph,int nodenums){
//     int* visited = new int[nodenums];
//     memset(visited,0,sizeof(int)*nodenums);
//     for (int i = 0;i<nodenums;++i){
//         if (visited[i] == 0){
//             DFS(graph,i,visited);
//         }
//     }
// }
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
  cout<<topperSort(graph,nodenums);

}