/*贝蒂是个打字高手，打字时有不看屏幕的习惯。
在一次贝蒂打字时，调皮的哈利常常趁贝蒂不注意按下Home键、End键、左右方向键和退格键。
当Home键被按下时，输入光标会跳到文本最开头；
当End键被按下时，输入光标会跳到文本末尾；
当左/右方向键被按下时，输入光标会向左/右移动一位；
当退格键被按下时，输入光标左面的一个字符会被删除。
现给出贝蒂和哈利按键的字符串，其中'{'表示Home键，'}'表示End键，'<'表示左方向键，'>'表示右方向键，'#'表示退格键，其余字符均表示输入的内容，
请输出屏幕上最终显示的文本。*/
#include <iostream>
#include <string>
using namespace std;
class Node{
    public:
    char val;
    Node* left;
    Node* right;
    Node(char va):val(va),left(nullptr),right(nullptr){}
    Node():val(0),left(nullptr),right(nullptr){}
};
class DoubleEndLinkList{
    public:
    Node* head;
    Node* tail;
    DoubleEndLinkList():head(new Node()),tail(head){}
    void toHead(Node*& cur){
        if (cur == head){
            return;
        }
        cur = head;
    }
    void toTail(Node*& cur){
        if (cur == head){
            return ;
        }
        cur = tail;
    }
    void goLeft(Node*& cur){
        if (cur == head){
            return;
        }
        else{
            cur = cur->left;
        }
    }
    void goRight(Node*& cur){
        if (cur == tail){
            return ;
        }
        else{
            cur = cur->right;
        }
    }
    void Appending(Node*& curNode,char data){
        Node* newNode = new Node(data);
        if (curNode == tail){
            curNode->right = newNode;
            newNode->left = curNode;
            tail = newNode;
            curNode = newNode;
        }
        else{
            Node* tmp = curNode->right;
            newNode->left = curNode;
            newNode->right = tmp;
            curNode->right = newNode;
            tmp->left = newNode;
            curNode = newNode;
        }
    }
    void backspace(Node*& cur){
        if (cur == head){
            return;
        }
        else if (cur!=tail){
            Node* LNode = cur->left;
            Node* RNode = cur->right;
            LNode->right = RNode;
            RNode->left = LNode;
            delete cur;
            cur = LNode;
        }
        else{
            cur->left->right = nullptr;
            tail = cur->left;
            delete cur;
            cur = tail;
        }
    }
    void show(){
        Node* cur = head->right;
        while(cur != nullptr){
            cout<<cur->val;
            cur = cur->right;
        }
    }
};
int main (void){
    DoubleEndLinkList buf;
    string tmp;
    getline(cin,tmp);
    Node* cur = buf.head;
    for (int i = 0;i<tmp.length();++i){
        if (tmp[i] == '{'){
            buf.toHead(cur);
        }
        else if (tmp[i] == '}'){
            buf.toTail(cur);
        }
        else if (tmp[i]=='<'){
            buf.goLeft(cur);
        }
        else if (tmp[i]== '>'){
            buf.goRight(cur);
        }
        else if (tmp[i] == '#'){
            buf.backspace(cur);
        }
        else{
            buf.Appending(cur,tmp[i]);
        }
    }
    buf.show();
 }