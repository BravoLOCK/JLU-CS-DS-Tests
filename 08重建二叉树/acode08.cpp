/*给定非空二叉树的中根序列和后根序列，
请编写程序创建该二叉树，计算其高度和先根序列；
如给定的中根和后根序列不合法，则亦能识别。*/
#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    Node* left;
    Node* right;
    Node* parent;
    char val;
    Node() :left(nullptr), right(nullptr), parent(nullptr), val(0) {}
    Node(char data) :left(nullptr), right(nullptr), val(data) {}
};
bool check(string str1, string str2) {  //str1为中序，str2为后序
    if (str1 == ""&& str2 == ""){
        return true;
    }
    string sub1;
    string sub2;
    string sub3;
    string sub4;
    char root = str2[str2.length()-1];
    int pos = str1.find(root);
    bool result1 = true;
    if (pos == string::npos) {
        result1 = false;
        return false;
    }
    sub1 = str1.substr(0, pos);
    if (pos!=str1.length()-1){
        sub2 = str1.substr(pos + 1);
    }
    else{
        sub2 = "";
    }
    sub3 = str2.substr(0, sub1.length());
    sub4 = str2.substr(pos, sub2.length());
    bool result2 = check(sub1, sub3);
    bool result3 = check(sub2, sub4);
    if (result2 && result3) {
        return true;
    }
    else {
        return false;
    }
}
Node* buildTree(string str1, string str2) {     //str1为中序，str2为后序
    if(str1 ==""&& str2 == ""){
        return nullptr;
    }
    string sub1;
    string sub2;
    string sub3;
    string sub4;
    char root = str2[str2.length() - 1];
    int pos = str1.find(root);
    sub1 = str1.substr(0, pos);
    if (pos!=str1.length()-1){
        sub2 = str1.substr(pos + 1);
    }
    else{
        sub2 = "";
    }
    sub3 = str2.substr(0, sub1.length());
    sub4 = str2.substr(pos, sub2.length());
    Node* head = new Node(root);
    head->left = buildTree(sub1, sub3);
    head->right = buildTree(sub2, sub4);
    return head;
}
int max(int x, int y) {
    return x > y ? x : y;
}
int FigureHeight(Node* head) {
    if (head == nullptr) {
        return -1;
    }
    int LHeight = FigureHeight(head->left);
    int RHeight = FigureHeight(head->right);
    int NHeight = max(LHeight, RHeight) + 1;
    return NHeight;
}
void preSerial(Node* head) {
    if (head == nullptr) {
        return;
    }
    cout << head->val;
    preSerial(head->left);
    preSerial(head->right);
}
int main(void) {
    string str2;
    string str1;
    while (cin >> str2) {
        cin >> str1;
        if (check(str1, str2)) {
            Node* head = buildTree(str1, str2);
            cout << FigureHeight(head)<<endl;
            preSerial(head);
            cout << endl;
        }
        else {
            cout << "INVALID" << endl;
        }
    }
}