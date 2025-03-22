/*表达式可以对应一个树结构，称为表达式树。其中的叶结点对应表达式中的操作数，非叶结点对应运算符，
假定所有运算均为二元运算。根据后缀表达式可以构造出表达式二叉树，
方法是：从左向右扫描后缀表达式，每扫描到一个符号就生成一个二叉树结点，
该符号作为结点的数据域值；若扫描到的符号是操作数，则将此操作数结点压栈；
若扫描到的符号是运算符，则从栈中弹出两个结点，分别作为当前运算符结点的右、左孩子，
再将当前运算符结点压栈。表达式扫描完成后，栈顶即为表达式树的根结点。
表达式树的后根序列即为后缀表达式。
现给定一个后缀表达式exp，请编写程序求出exp的“最右子表达式”。
exp的“最右子表达式”是指从exp对应的表达式树右边看向树，从第0层到最底层所能看到的各结点。
例如后缀表达式abcdef+−g+∗−h∗+对应的表达式树如图1所示，其最右子表达式为 +∗h∗+g+f */
#include <iostream>
#include <string>
using namespace std;
template <class T>
class Node {
public:
    Node* left;
    Node* right;
    Node* parent;
    T val;
    Node() :left(nullptr), right(nullptr), parent(nullptr), val(0) {}
    Node(T data) :left(nullptr), right(nullptr), parent(nullptr), val(data) {}
};
template <class T>
class Queue {
public:
    T* data;
    int capacity;
    int size;
    int front;
    int rear;
    Queue() :data(new T[500]), capacity(500), size(0), front(0), rear(0) {}
    Queue(int cap) :data(new T[cap]), capacity(cap), size(0), front(0), rear(0) {}
    bool isEmpty() {
        return size == 0;
    }
    bool isFull() {
        return size == capacity;
    }
    bool inqueue(T val) {
        if (isFull()) {
            return false;
        }
        data[front] = val;
        front = (front + 1) % capacity;
        size++;
        return true;
    }
    T equeue() {
        if (isEmpty()) {
            return 0;
        }
        T tmp = data[rear];
        rear = (rear + 1) % capacity;
        size--;
        return tmp;
    }
};
template<class T>
class Stack {
public:
    T* data;
    int capacity;
    int top;
    Stack() :data(new T[500]), capacity(500), top(0) {}
    Stack(int val) :data(new T[val]), capacity(val), top(0) {}
    bool push(T val) {
        if (isFull() == false) {
            data[top++] = val;
            return true;
        }
        return false;
    }
    T pop() {
        if (isEmpty() == false) {
            return data[--top];
        }
        else {
            return 0;
        }
    }
    bool isFull() {
        return top == capacity;
    }
    bool isEmpty() {
        return top == 0;
    }
};
bool isOpnum(char c) {
    return c >= 'A' && c <= 'Z';
}
Node<char>* buildTree(string str) {
    Stack<Node<char>*> st;
    for (int i = 0;i < str.length();++i) {
        Node<char>* newNode = new Node<char>(str[i]);
        if (isOpnum(str[i])) {
            Node<char>* RN = st.pop();
            Node<char>* LN = st.pop();
            newNode->left = LN;
            LN->parent = newNode;
            newNode->right = RN;
            RN->parent = newNode;
            st.push(newNode);
        }
        else {
            st.push(newNode);
        }
    }
    return st.pop();
}
string RightExp(Node<char>* head) {
    string result = "";
    Node<char>* curEnd = head;
    Node<char>* nextEnd = nullptr;
    Queue<Node<char>*> qu;
    qu.inqueue(head);
    while (!qu.isEmpty()) {
        Node<char>* cur = qu.equeue();
        if (cur->left != nullptr) {
            qu.inqueue(cur->left);
            nextEnd = cur->left;
        }
        if (cur->right != nullptr) {
            qu.inqueue(cur->right);
            nextEnd = cur->right;
        }
        if (cur == curEnd) {
            result += cur->val;
            curEnd = nextEnd;
        }
    }
    return result;
}
void postSerial(Node<char>* head) {
    if (head == nullptr) {
        return;
    }
    postSerial(head->left);
    postSerial(head->right);
    cout << head->val;
}
int main(void) {
    int opnums = 0;
    cin >> opnums;
    for (int i = 0;i < opnums;++i) {
        string str;
        cin >> str;
        Node<char>* head = buildTree(str);
        //postSerial(head);
        string result = RightExp(head);
        cout << result << endl;
    }
}