#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
class TrieNode{
public:
    unordered_map<char,TrieNode*> children;
    bool isEnd;
    long freq;
    TrieNode():isEnd(false),freq(0){}
};
class Data{
public:
    string word;
    long freq;
    Data(string word,long freq):word(word),freq(freq){}
    
};
class Trie{
public:
    TrieNode* root;
    Trie(){
        root = new TrieNode();
    }
    void dfs(TrieNode* node,string prefix,vector<Data>& results){ 
        if (node->isEnd){
            results.push_back(Data(prefix,node->freq));
        }
        for (auto& child:node->children){
            dfs(child.second,prefix+child.first,results);
        }
    }
    void insert(const string& word,long freq){
        TrieNode* node = root;
        for (char ch: word){
            if (node->children.find(ch)==node->children.end()){
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
        node->freq = freq>(node->freq)?freq:node->freq;
    }
    bool startsWith(const string& prefix){
        TrieNode* node = root;
        for (char ch: prefix){
            if (node->children.find(ch)==node->children.end()){
                return false;
            }
            node = node->children[ch];
        }
        //如果不只有前缀，还有单词，返回true，否则返回false
        if (node->isEnd&&node->children.empty())return false;
        return true;
    }
    void allprefix(const string& prefix,vector<Data>& results){
        TrieNode* node = root;
        for (char ch: prefix){
            if (node->children.find(ch)==node->children.end()){
                return ;
            }
            node = node->children[ch];
        }
        dfs(node,prefix,results);
    }
};
template<class T>
class Greaterheap{
public:
    vector<T> heap; //动态数组用于存放数据
    int heapsize;                   //堆的大小
    bool (*comparator)(T& op1,T& op2);  //比较器
    Greaterheap(bool (*comp)(T& op1,T& op2)):heapsize(0),comparator(comp){}
    bool isEmpty(){
        return heapsize == 0;
    }
    int size(){
        return heapsize;
    }
    T peek(){   //peek方法不用检查堆是否为空，这个错误应由用户承担
        return heap[0];
    }
    void push(T obj){
        heap.push_back(obj);
        heapInsert(heapsize++);
    }
    void heapInsert(int index){
        while (index>0){ 
            //大根堆比较器为<,即如果子节点不是小于其节点，而是大于/等于时会向上调整
            if (!comparator(heap[index],heap[(index-1)/2])){
                swap(index,(index-1)/2);    //交换索引表在swap中实现
                index = (index-1)/2;
            }
            else{
                break;
            } 
        }
    }
    T pop(){
        T ans = heap[0];
        heap[0] = heap[--heapsize];
        heap.pop_back();
        heapify(0);
        return ans;
    }
    void heapify(int index){
        int left = index*2 +1;
        while(left<heapsize){
            int best = left+1<heapsize&&!comparator(heap[left+1],heap[left])?left+1:left;
            //比较器返回true，不交换，而小根堆比较器为op1>op2，所以heap[left+1] > heap[left]
            //大根堆比较器为<，所以left+1<left(堆中值)，那么应该传left
            //问题就出现在这，如果left+1>=heapsize时，如果是comparator（）？left：left+1，就会选择到left+1这个不存在的值
            //重新熟悉一下自定义比较器的堆排序代码
            best = comparator(heap[index],heap[best])?best:index;
            //比较器返回true，不交换，而小根堆比较器为op1>op2，所以heap[index] > heap[best]
            if (best == index)break;
            swap(index,best);
            index = best;
            left = index*2+1;
        }
    }
    void swap(int i,int j){ //交换两个元素时，不仅要交换堆中的元素，还要更新哈希表中的索引
        T o1 = heap[i];
        T o2 = heap[j];
        heap[i] = o2;
        heap[j] = o1;
    }
};
bool comp(Data& op1,Data& op2){
    return op1.freq!=op2.freq?op1.freq<op2.freq:op1.word>op2.word;//频率小的在前，字典序大的在前,用来构建大根堆
}
int main (void){
    int n,m,k;
    cin>>n>>m>>k;
    Trie trie;
    for (int i = 0;i<n;++i){
        string word;
        long freq;
        cin>>freq>>word;
        trie.insert(word,freq);
    }
    for (int i = 0;i<m;++i){
        string prefix;
        cin>>prefix;
        if (!trie.startsWith(prefix)){
            cout<<"no suggestion"<<endl;
        }
        else{
            vector<Data> results = vector<Data>();
            trie.allprefix(prefix,results);
            Greaterheap<Data> heap(comp);
            for (auto& data:results){
                heap.push(data);
            }
            for (int j = 0;j<k;++j){
                if (heap.isEmpty()){
                    break;
                }
                Data data = heap.pop();
                if (data.word==prefix){
                    j--;
                }
                else{
                    cout<<data.word<<endl;
                }
            }
            
        }
        if (i!=m-1)cout<<endl;
        
    }
}