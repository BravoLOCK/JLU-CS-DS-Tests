/*编写程序找出非空二叉树中和最大的路径，二叉树结点为不等于0的整数。
本题的“路径”定义为二叉树中的结点序列vi,...,vj,
序列中前一个结点是后一个结点的父结点，
但路径不一定是以根结点为起点，
也不一定是以叶结点为终点。
路径的和定义为该路径所包含的所有结点的数据值之和。*/
#include <iostream>
#include <string>
using namespace std;
class Node;
class Stack{
public:
    Node** data;
    int top;
    int size;
    int capacity;
    Stack():data(new Node* [100]),top(0),size(0),capacity(100){}
    bool isEmpty(){
        return size ==0;
    }
    bool isFull(){
        return size == capacity;
    }
    bool push(Node* head){
        if (isFull()){
            return false;
        }
        data[top++] = head;
        size++;
        return true;
    }
    Node* pop(){
        if (isEmpty()){
            return nullptr;
        }
        size--;
        return data[--top];
    }
};
class Node{
public:
    Node* left;
    Node* right;
    Stack node;
    int dist;
    int val;
    Node():left(nullptr),right(nullptr),dist(0),val(0){}
    Node(int data):left(nullptr),right(nullptr),dist(0),val(data){}
};

int max(int x,int y){
    return x>y?x:y;
}
int figureDis(Node* head){
    if (head == nullptr){
        return 0;
    }
    int Ldistance = figureDis(head->left);
    int Rdistance = figureDis(head->right);
    int Ndistance = 0;
    if (max(Ldistance,Rdistance)>0){
        Ndistance = max(Ldistance,Rdistance)+head->val;
        if (Ldistance>Rdistance){
            head->node = head->left->node;
            head->node.push(head);
        }
        else if(Rdistance>Ldistance){
            head->node = head->right->node;
            head->node.push(head);
        }
        else if(head->left!=nullptr&&head->right!=nullptr&&(head->left->node.size)<=(head->right->node.size)){
            head->node = head->left->node;
            head->node.push(head);
        }
        else if (head->left!=nullptr&&head->right!=nullptr&&(head->left->node.size)>(head->right->node.size)){
            head->node = head->right->node;
            head->node.push(head);
        }
        else{
            head->node.push(head);
        }
    }
    else{
        head->node.push(head);
        Ndistance = head->val;
    }
    head->dist = Ndistance;
    return Ndistance;
}
void preSerial(Node* head,int& max,Stack& node,int& size){
    if (head == nullptr){
        return ;
    }
    if (head->dist>=max&&head->node.size<size){
        max = head->dist;
        size = head->node.size;
        node = head->node;
    }
    preSerial(head->left,max,node,size);
    preSerial(head->right,max,node,size);
}
Node* buildTree(){
    int k;
    cin>>k;
    if (k == 0){
        return nullptr;
    }
    Node* newNode = new Node(k);
    newNode->left = buildTree();
    newNode->right = buildTree();
    return newNode;
}
int main (void){
    Node* head = buildTree();
    figureDis(head);
    int max = 0;
    int size = 1000;
    Stack st;
    preSerial(head,max,st,size);
    cout<<max<<endl;
    while(!st.isEmpty()){
        cout<<st.pop()->val<<" ";
    }
    cout<<endl;
}
