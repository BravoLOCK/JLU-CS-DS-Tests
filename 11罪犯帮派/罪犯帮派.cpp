/*Tabu市的警察局决定结束混乱，因此要采取行动根除城市中的几大帮派。目前的问题是，给出两个罪犯，他们是属于同一帮派么？城市里一共有多少个帮派？假设在Tabu市现有n名罪犯，编号为1到n，给出m条消息表示属于同一帮派的两个罪犯编号。请基于这些不完全的信息帮助警方计算出他们想要的信息。

输入格式:
输入第一行为三个正整数，n、m和q。n为罪犯数；m为给出的已知信息数量；q为查询数。接下来m行，每行2个正整数a和b，表示罪犯a和罪犯b属于同一帮派。接下来q行，每行2个正整数c和d，即查询罪犯c和d是否属于同一帮派。每行输入的整数以空格间隔，n、m、q均不超过1000。

输出格式:
输出为q+1行，前q行对应于输入的q个查询的结果，如果属于同一帮派，则输出“In the same gang.”，否则输出“In different gangs.”。最后一行为一个整数，表示帮派数目。

*/
#include <iostream>
using namespace std;
class Node {
public:
    int index;
    int val;
    int father;
    Node() :index(0), val(0), father(0) {}
    Node(int data) :index(0), val(data), father(0) {}
};
class Vector {
public:
    Node** arr;
    int size;
    int top;
    int capacity;
    Vector() :arr(new Node* [1000]), size(0), top(0), capacity(1000) {}
    void push(Node* node) {
        arr[top] = node;
        node->father = top;
        node->index = top;
        top++;
        size++;
    }
    int FD(int x) {
        if (arr[x]->father == x) {
            return x;
        }
        return FD(arr[x]->father);
    }
    void UN(int x, int y) {
        int fx = FD(x);
        int fy = FD(y);
        if (fx!=fy)arr[fy]->father = FD(fx);
    }
    Node* findKNode(int k) {
        for (int i = 0;i < size;++i) {
            if (arr[i]->val == k) {
                return arr[i];
            }
        }
        return nullptr;
    }
};
class Case {
public:
    int* arr;
    int top;
    int size;
    int capacity;
    Case() :arr(new int[1000]), top(0), size(0), capacity(1000) {}
    void push(int i) {
        arr[top++] = i;
        size++;
    }
    bool check(int x) {
        for (int i = 0;i < size;++i) {
            if (arr[i] == x) {
                return true;
            }
        }
        return false;
    }
};
int main(void) {
    int n, m, q;
    cin >> n;
    cin >> m;
    cin >> q;
    Case ca;
    Vector vct;
    for (int i = 0;i < n;++i) {
        Node* pt = new Node(i + 1);
        vct.push(pt);
    }
    for (int i = 0;i < m;++i) {
        int a, b;
        cin >> a;
        cin >> b;
        Node* pta;
        Node* ptb;
        pta = vct.arr[a-1];
        ptb = vct.arr[b-1];
        vct.UN(pta->index, ptb->index);    
    }
    for (int i = 0;i < q;++i) {
        int a, b;
        cin >> a;
        cin >> b;
        Node* pta = vct.arr[a-1];
        Node* ptb = vct.arr[b-1];
        if (vct.FD(pta->index) == vct.FD(ptb->index)) {
            cout << "In the same gang." << endl;
        }
        else {
            cout << "In different gangs." << endl;
        }
    }
    int ans = 0;
    for (int i = 0;i < n;++i) {
        if (vct.FD(i) == i) {
            ans++;
        }
    }
    cout << ans << endl;
}