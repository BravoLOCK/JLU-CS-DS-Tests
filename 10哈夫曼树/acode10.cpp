/*D 哈夫曼树
编写一个哈夫曼编码译码程序。针对一段文本，根据文本中字符出现频率构造哈夫曼树，
给出每个字符的哈夫曼编码，并进行译码，计算编码前后文本大小。
为确保构建的哈夫曼树唯一，本题做如下限定：
选择根结点权值最小的两棵二叉树时，
选取权值较小者作为左子树。
若多棵二叉树根结点权值相等，
则先生成的作为左子树，后生成的作为右子树，
具体来说：i) 对于单结点二叉树，优先选择根结点对应字母在文本中最先出现者，
如文本为cba，三个字母均出现1次，但c在文本中最先出现，b第二出现，故则选择c作为左子树，b作为右子树。
ii) 对于非单结点二叉树，先生成的二叉树作为左子树，后生成的二叉树作为右子树。
iii. 若单结点和非单结点二叉树根结点权值相等，优先选择单结点二叉树。
生成哈夫曼编码时，哈夫曼树左分支标记为0，右分支标记为1。*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <iterator>
#include <utility>
using namespace std;
class Node {
public:
    char cval;
    int val;
    Node* left;
    Node* right;
    Node() :cval('0'), val(0), left(nullptr), right(nullptr) {}
    Node(char cv, int v) :cval(cv), val(v), left(nullptr), right(nullptr) {}
};
class Vector {
public:
//容器中封装了一个哈希表，一个Node*数组
    unordered_map<char, int> hmap;
    char* cval;
    int* ival;
    Node** nval;
    int capacity;
    int size;
    int top;
    Vector() :cval(new char[5000]), ival(new int[5000]), nval(new Node* [5000]), capacity(5000), size(0), top(0) {}
    Vector(string str) :cval(new char[5000]), ival(new int[5000]), nval(new Node* [5000]), capacity(5000), size(0), top(0) {
        for (int i = 0;i < str.length();++i) {
            auto pos = hmap.find(str[i]);
            //将每个字符添加到哈希表中，并记录下他们的频率
            if (pos == hmap.end()) {
                hmap.insert({ str[i],1 });
                cval[top++] = str[i];
                size++;
            }
            else {
                pos->second++;
            }
        }
        //将频率用一个数组单独记录下来
        for (int i = 0;i < size;++i) {
            int val = hmap.find(cval[i])->second;
            ival[i] = val;
        }
        //按照频率，对字符数组、频率数组进行排序
        sort();
        //将排序的结果写入节点数组
        for (int i = 0;i < size;++i) {
            nval[i] = new Node(cval[i], ival[i]);
        }
    }
    void change(int& i, int& j) {
        i = i ^ j;
        j = i ^ j;
        i = i ^ j;
    }
    void change(char& i, char& j) {
        i = i ^ j;
        j = i ^ j;
        i = i ^ j;

    }
    void change(Node*& i, Node*& j) {
        Node* tmp = i;
        i = j;
        j = tmp;
    }
    void sort() {
        for (int i = 0;i < size;++i) {
            int min = i;
            for (int j = i + 1;j < size;++j) {
                if (ival[j] < ival[min]) {
                    min = j;
                }
            }
            if (min != i) {
                change(ival[i], ival[min]);
                change(cval[i], cval[min]);
                change(nval[i], nval[min]);
            }
            
        }
    }
    //将某个节点从数组中删去
    void erase(int i) {
        if (i > size) {
            return;
        }
        for (int j = i;j < size - 1;++j) {
            cval[j] = cval[j + 1];
            ival[j] = ival[j + 1];
            nval[j] = nval[j + 1];
        }
        size--;
    }
    //在数组中插入
    void insert(char c, int i, int pos, Node* posnode) {
        for (int j = size - 1;j >= pos;j--) {
            cval[j + 1] = cval[j];
            ival[j + 1] = ival[j];
            nval[j + 1] = nval[j];
        }
        cval[pos] = c;
        ival[pos] = i;
        nval[pos] = posnode;
        size++;
    }
};
//在数组中找某元素
int findPos(int* arr, int size, int x) {
    if (size == 0) {
        return 0;
    }
    if (x < arr[0]) {
        return 0;
    }
    else if (x >= arr[size - 1]) {
        return size;
    }
    else {
        for (int i = 0;i < size - 1;++i) {
            if (x >= arr[i] && x < arr[i + 1]) {
                return i + 1;
            }
        }
    }
}
//创建Haffman树
Node* buildHashTree(Vector vct) {
    while (vct.size != 1) {
        int li = vct.ival[0];
        int ri = vct.ival[1];
        //创建空节点，连接两个有效节点
        Node* newNode = new Node('0', li + ri);
        newNode->left = vct.nval[0];
        newNode->right = vct.nval[1];
        //将头两个节点从容器中删去
        vct.erase(0);
        vct.erase(0);
        //将两个节点的频率做和放入容器中，（在容器中找到正确位置放入）
        int pos = findPos(vct.ival, vct.size, li + ri);
        vct.insert('0', li + ri, pos, newNode);
    }
    //最后返回头节点，也就是haffman树的头节点
    return vct.nval[0];
}
void encode(Node* head, unordered_map<char, string>& hmap, string str) {
    if (head->cval >= 'a' && head->cval <= 'z') {
        hmap.insert({ head->cval,str });
        return;
    }
    str += '0';
    encode(head->left, hmap, str);
    str = str.substr(0, str.length() - 1);
    str += '1';
    encode(head->right, hmap, str);
}
void display(unordered_map<char, string>& hmap, Vector& vct) {
    for (int i = 0;i < vct.size;++i) {
        cout << vct.cval[i] << ":" << hmap.find(vct.cval[i])->second << endl;
    }
}
unordered_map<string, char> trans(unordered_map<char, string>& hmap) {
    unordered_map<string, char> hmp;
    for (auto it : hmap) {
        hmp.insert({ it.second,it.first });
    }
    return hmp;
}
void decode(unordered_map<string, char>& hmap, string str) {
    string result;
    int end = 0;
    bool flag = true;
    for (int i = 0;i < str.length();++i) {
        string tmp = str.substr(end, i - end + 1);
        if (hmap.find(tmp) != hmap.end()) {
            end = i + 1;
            result += hmap.find(tmp)->second;
        }
        else if (i == str.length() - 1) {
            flag = false;
        }
    }
    if (flag == true) {
        cout << result << endl;
    }
    else {
        cout << "INVALID" << endl;
    }
}
int figureSize(string str, unordered_map<char, string>& hmap) {
    int size = 0;
    int result = 0;
    for (int i = 0;i < str.length();++i) {
        size += (hmap.find(str[i])->second.length());
    }
    if (size % 8 == 0) {
        result = size / 8;
    }
    else {
        result = size / 8 + 1;
    }
    return result;
}
int main(void) {
    string ori;
    cin >> ori;
    string str1;
    cin >> str1;
    string str2;
    cin >> str2;
    Vector vct1(ori);
    Vector vct2(ori);
    Node* head = buildHashTree(vct1);
    unordered_map<char, string> hmap1;
    string str;
    encode(head, hmap1, str);
    cout << ori.length() << " " << figureSize(ori, hmap1) << endl;
    display(hmap1, vct2);
    unordered_map<string, char> hmap2 = trans(hmap1);
    decode(hmap2, str1);
    decode(hmap2, str2);
}