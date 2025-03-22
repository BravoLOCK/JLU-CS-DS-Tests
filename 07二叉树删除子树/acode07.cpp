/*A 二叉树删除子树
编写程序对给定二叉树执行若干次删除子树操作，
输出每次删除子树后剩余二叉树的中根序列。
二叉树结点的数据域值为不等于0的整数。
每次删除操作是在上一次删除操作后剩下的二叉树上执行。*/
#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    Node* left;
    Node* right;
    Node* parent;
    long long val;
    Node() :left(nullptr), right(nullptr), parent(nullptr), val(0) {}
    Node(int data) :left(nullptr), right(nullptr), val(data) {}
};
template <class T>
class Queue {
public:
    T* val;
    int size;
    int capacity;
    int front;
    int rear;
    Queue() :val(new T[5000]), size(0), capacity(5000), front(0), rear(0) {}
    Queue(int cap) :val(new T[cap]), size(0), capacity(cap), front(0), rear(0) {}
    bool isEmpty() {
        return size == 0;
    }
    bool isFull() {
        return size == capacity;
    }
    bool inqueue(T data) {
        if (isFull()) {
            return false;
        }
        val[front] = data;
        front = (front + 1) % capacity;
        size++;
        return true;
    }
    T equeue() {
        if (size == 0) {
            return 0;
        }
        T temp = val[rear];
        rear = (rear + 1) % capacity;
        size--;
        return temp;
    }
};
Node* buildBypreserial() {
    int val;
    cin>>val;
    if (val == 0) {
        return nullptr;
    }
    Node* head = new Node(val);
    Node* LN = buildBypreserial();
    head->left = LN;
    if (LN != nullptr)LN->parent = head;
    Node* RN = buildBypreserial();
    head->right = RN;
    if (RN != nullptr)RN->parent = head;
    return head;
}

void deleteNode(Node* head) {
    if (head == nullptr) {
        return;
    }
    deleteNode(head->left);
    deleteNode(head->right);
    if (head->parent != nullptr && head->parent->left == head) {
        head->parent->left = nullptr;
    }
    else if (head->parent != nullptr && head->parent->right == head) {
        head->parent->right = nullptr;
    }
    delete head;
}
Node* findKNodeInBTree(Node* head, int k) {        //delete ,是否delete
    if (head == nullptr) {
        return nullptr;
    }
    Node* pt = nullptr;
    if (head->val == k) {
        pt = head;
    }
    Node* result1 = findKNodeInBTree(head->left, k);
    Node* result2 = findKNodeInBTree(head->right, k);
    if (pt != nullptr) {
        return pt;
    }
    else if (result1 != nullptr) {
        return result1;
    }
    else if (result2 != nullptr) {
        return result2;
    }
    else {
        return nullptr;
    }
}
void InSerial(Node* head) {
    if (head == nullptr) {
        return;
    }
    InSerial(head->left);
    cout << head->val << " ";
    InSerial(head->right);
}
int main(void) {
    Node* head = buildBypreserial();
    int opnum = 0;
    cin >> opnum;
    for (int i = 0; i < opnum; ++i) {
        long long int k;
        cin >> k;
        Node* pos = findKNodeInBTree(head, k);
        if (pos) {
            deleteNode(pos);
            InSerial(head);
            cout << endl;
        }
        else {
            cout << 0 << endl;
        }
    }
}
