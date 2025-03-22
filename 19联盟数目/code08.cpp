/*艾迪是一家集团公司的老板，该集团包含n家公司，为了管理公司，艾迪会时常通过网络向各公司发送消息。
各公司间的网络是单向的，每个公司都有一个分发列表，表示其能向哪些公司直接传达消息。
例如A公司的分发列表为B、C，表示A可将消息直接传送给B和C（由于网络是单向的，B或C不一定能向A传送消息），这样艾迪若想向A、B、C公司发送消息，则只需向A发送消息即可，随后A可将消息传送到B和C。
为了便于管理各公司，艾迪打算将n家公司分成若干组，每组称为一个区域联盟，每组满足如下条件：组内的任意公司消息互相可达。即对于组内任意公司u和v，u可将消息传送到v（可由u直接传送到v，也可通过组内其他公司中转传送到v），v也可将消息传送到u。可以认为一个公司可以将消息传送给自己，即一个公司可以自成一组。
艾迪希望组的数量尽可能少，即在满足上述条件的情况下，每组包含的公司数目尽可能多。
现给定每个公司的分发列表，请编写程序告知艾迪，他的集团最少能分成多少组。*/
#include <stack>
#include <iostream>
#include <vector>
using namespace std;
int** buildGraph(int n){
    int** matrix = new int* [n];
    for (int i = 0;i<n;++i){
        matrix[i] = new int [n];
    }
    //初始化矩阵
    for (int i = 0;i<n;++i){
        for (int j = 0;j<n;++j){
            if (i == j){
                matrix[i][j] = 1;
            }
            else{
                matrix[i][j] = 0;
            }
        }
    }
    //有边，则改值
    for (int i = 0;i<n;++i){
        int temp = -1;
        while(temp!=0){
            cin>>temp;
            if (temp == 0){
                break;
            }
            matrix[i][temp-1] = 1;    
        }
    }
    return matrix;
}
class Node{
public:
    int num;
    Node(int xx):num(xx){}
};
int All_component(int** graph,int n){
    int lt = 0;
    int* markedlist = new int[n];
    //初始化markedlist矩阵，使其全为0
    for (int i = 0;i<n;++i){
        markedlist[i] = 0;
    }
    for(int i = 0;i<n;++i){
        if (markedlist[i]==0){
            markedlist[i] = 1;
            for (int j = 1;j<n;++j){
                if (graph[i][j] == 1&&graph[j][i] == 1){
                    markedlist[j] = 1;
                }
            }
            lt++;
        }
    }
    return lt;
}

int** WarShell(int** graph,int n){
    for (int k = 0;k<n;++k){
        for (int i = 0;i<n;++i){
            if (graph[i][k] == 1){
                for (int j = 0;j<n;++j){
                    graph[i][j] = graph[i][j]|graph[k][j];
                }
            }
        }
    }
    return graph;
}
int main (void){
    int group = 0;
    cin>>group;
    for (int i = 0;i<group;++i){
        int n = 0;
        cin>>n;
        int** matrix = buildGraph(n);
        // for (int i = 0;i<n;++i){
        //     for (int j = 0;j<n;++j){
        //         cout<<matrix[i][j]<<'\t';
        //     }
        //     cout<<endl;
        // }

        WarShell(matrix,n);
        // for (int i = 0;i<n;++i){
        //     for (int j = 0;j<n;++j){
        //         cout<<matrix[i][j]<<'\t';
        //     }
        //     cout<<endl;
        // }
        cout<<All_component(matrix,n)<<endl;
    }
}