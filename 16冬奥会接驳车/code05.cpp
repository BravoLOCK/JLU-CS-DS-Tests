/*2022年冬奥会科技感十足，奥组委配备了无人驾驶的接驳车。
假定你是奥组委的软件工程师，请你为无人接驳车编写路径规划程序，使其载着运动员以最短的时间到达目的地。
接驳车的运行范围可以被建模为一张由n行m列单元格组成的地图。
有的单元格是空地，可以走；有的单元格处是障碍物，不能走。
假定接驳车只可以朝上、下、左、右四个方向行驶，不能斜着走。
每行驶过一个位置（单元格）需要1分钟。
给定地图以及运动员的起点和终点，请输出接驳车从起点行驶到终点所需的最短时间。*/
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
class Node{
public:
    int x;
    int y;
    Node(int xx,int yy):x(xx),y(yy){}
};
int BFS(int** matrix,int** visited,Node* start,int m,int n){
    bool Find = false;
    int level = 0;
    queue<Node*> q;
    visited[start->x][start->y] = 1;
    q.push(start);
    Node* curEnd = start;
    Node* NextEnd = nullptr;
    while(!q.empty()){
        Node* node = q.front();
        q.pop();
        if (node->y-1>=0&&visited[node->x][node->y-1] == 0 &&matrix[node->x][node->y-1]!=1){   //左边节点
            Node* tmp = new Node(node->x,node->y-1);
            visited[node->x][node->y-1] = 1;
            q.push(tmp);
            NextEnd = tmp;
        }
        if (node->x-1>=0&&visited[node->x-1][node->y]== 0&&matrix[node->x-1][node->y]!=1){    //上边节点
            Node* tmp = new Node(node->x-1,node->y);
            visited[node->x-1][node->y] = 1;
            q.push(tmp);
            NextEnd = tmp;
        }
        if (node->y+1<n&&visited[node->x][node->y+1] ==0&&matrix[node->x][node->y+1]!=1){    //右边节点
            Node* tmp = new Node(node->x,node->y+1);
            visited[node->x][node->y+1] = 1;
            q.push(tmp);
            NextEnd = tmp;
        }
        if (node->x+1<m&&visited[node->x+1][node->y] == 0&&matrix[node->x+1][node->y]!=1){      //下边节点
            Node* tmp = new Node(node->x+1,node->y);
            visited[node->x+1][node->y] = 1;
            q.push(tmp);
            NextEnd = tmp;
        }
        if (matrix[node->x][node->y] == 4){
            Find = true;
            break;
        }
        if (node == curEnd){
            curEnd = NextEnd;
            level++;
        }
        delete node;
    }
    if (Find == true){
        return level;
    }
    else{
        return -1;
    }
}
int main(void){
    int m,n;
    while(cin>>m>>n){
        int** matrix = new int* [m];
        for (int i = 0;i < m;++i){
            matrix[i] = new int [n];
        }
        int** visited = new int*[m];
        for (int i = 0;i<m;++i){
            visited[i] = new int[n];
        }
        for (int i = 0;i<m;++i){
            for (int j = 0;j<n;++j){
                visited[i][j] = 0;
            }
        }
        Node* start;
        for (int i = 0;i<m;++i){
            for (int j = 0;j < n;++j){
                int tmp;
                cin>>tmp;
                matrix[i][j] = tmp;
                if (tmp == 3){
                    start = new Node(i,j);
                }
            }
        }
        int result = BFS(matrix,visited,start,m,n);
        if (result == -1){
            cout<<"unreachable"<<endl;
        }
        else{
            cout<<result<<endl;
        }
    }
}