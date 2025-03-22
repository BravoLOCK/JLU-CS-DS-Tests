#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
using namespace std;
class AVL{
public:
    int key;
    int height;
    AVL* left;
    AVL* right;
    AVL(int key):key(key),height(0),left(nullptr),right(nullptr){}
};
int height(AVL* root){
    return root==nullptr?-1:root->height;
}
int max(int a,int b){
    return a>b?a:b;
}
void LL(AVL*& root){
    AVL* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max(height(root->left),height(root->right))+1;
    temp->height = max(height(temp->left),height(temp->right))+1;
    root = temp;
}
void RR(AVL*& root){
    AVL* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = max(height(root->left),height(root->right))+1;
    temp->height = max(height(temp->left),height(temp->right))+1;
    root = temp;
}
void LR(AVL*& root){
    RR(root->left);
    LL(root);
}
void RL(AVL*& root){
    LL(root->right);
    RR(root);
}
void insert(AVL*& root,int K,int level,bool& flag){
    if (root == nullptr){
        root = new AVL(K);
    }
    else if (K<root->key){
        insert(root->left,K,level+1,flag);
        if (height(root->left)-height(root->right)==2){
            if (K<root->left->key){
                flag = true;
                cout<<"Insert "<<K<<": "<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with right rotation. ";
                LL(root);
            }
            else{
                flag = true;
                cout<<"Insert "<<K<<": "<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with left rotation and right rotation. ";
                LR(root);
            }
        }
    }
    else if (K>root->key){
        insert(root->right,K,level+1,flag);
        if (height(root->right)-height(root->left)==2){
            if (K>root->right->key){
                flag = true;
                cout<<"Insert "<<K<<": "<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with left rotation. ";
                RR(root);
            }
            else{
                flag = true;
                cout<<"Insert "<<K<<": "<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with right rotation and left rotation. ";
                RL(root);
            }
        }
    }
    root->height = max(height(root->left),height(root->right))+1;
    
}
void remove(AVL*& root,int K,int level,int origin,bool& repeat,bool& flag){
    if (root == nullptr){
        return;
    }
    if (K<root->key){
        remove(root->left,K,level+1,origin,repeat,flag);
        if (height(root->right)-height(root->left)==2){
            if (height(root->right->left)>height(root->right->right)){
                flag = true;
                if (repeat == false){
                    cout<<"Remove "<<origin<<": ";
                    repeat = true;
                }
                
                cout<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with right rotation and left rotation. ";
                RL(root);
            }
            else{
                flag = true;
                if(repeat == false){
                    cout<<"Remove "<<origin<<": ";
                    repeat = true;
                }
                cout<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with left rotation. ";
                RR(root);
            }
        }
        
    }
    else if (K>root->key){
        remove(root->right,K,level+1,origin,repeat,flag);
        if (height(root->left)-height(root->right)==2){
            if (height(root->left->right)>height(root->left->left)){
                flag = true;
                if(repeat == false){
                    cout<<"Remove "<<origin<<": ";
                    repeat = true;
                }
                cout<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with left rotation and right rotation. ";
                LR(root);
            }
            else{
                flag = true;
                if(repeat == false){
                    cout<<"Remove "<<origin<<": ";
                    repeat = true;
                }
                cout<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with right rotation. ";
                LL(root);
            }
        }
    }
    else{
        if (root->left!=nullptr&&root->right!=nullptr){
            
            AVL* temp = root->right;
            while(temp->left!=nullptr){
                temp = temp->left;
            }
            root->key = temp->key;
            remove(root->right,temp->key,level+1,origin,repeat,flag);
            if (height(root->left)-height(root->right)==2){
                if (height(root->left->right)>height(root->left->left)){
                    flag = true;
                    if (repeat == false){
                        cout<<"Remove "<<origin<<": ";
                        repeat = true;
                    }
                    cout<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with left rotation and right rotation. ";
                    LR(root);
                }
                else{
                    flag = true;
                    if (repeat == false){
                        cout<<"Remove "<<origin<<": ";
                        repeat = true;
                    }
                    cout<<"Rebalance subtree rooted at node "<<root->key<<" on level "<<level<<" with right rotation. ";
                    LL(root);
                }
            }
        }
        else{
            AVL* temp = root;
            root = root->left!=nullptr?root->left:root->right;
            delete temp;
        }
    }
    if (root!=nullptr){
        root->height = max(height(root->left),height(root->right))+1;
        
    }
}
void inOrder(AVL* root){
    if (root == nullptr){
        return;
    }
    inOrder(root->left);
    cout<<root->key<<" ";
    inOrder(root->right);
}
void preOrder(AVL* root){
    if (root == nullptr){
        return;
    }
    cout<<root->key<<" ";
    preOrder(root->left);
    preOrder(root->right);
}
int main (void){
    int n;
    bool ftime = false;
    int count = 0;
    while(cin>>n){
        count++;
        if (ftime != false){
            cout<<endl;
            
        }
        ftime = true;
        cout<<"Case "<<count<<":"<<endl;
        char op[10];
        int opnum;
        AVL* root = nullptr;
        bool flag = false;
        for (int i = 0; i<n;i++){
            scanf("%s",op);
            getchar();
            scanf("%d",&opnum);
            if (i!=n-1)getchar();
            bool flag1 = false;
            bool flag2 = false;
            bool repeat = false;
            if (strcmp(op,"Insert")==0){
                insert(root,opnum,0,flag1);
                if (flag1 == true){
                    cout<<endl;
                }
            }
            else if (strcmp(op,"Remove")==0){
                remove(root,opnum,0,opnum,repeat,flag2);
                if (flag2 == true){
                    cout<<endl;
                }
            }
            if (flag1||flag2){
                flag = true;
            }
        }
        if (flag){
            cout<<endl;
        }
        inOrder(root);
        cout<<endl;
        cout<<endl;
        preOrder(root);
        cout<<endl;
    }
    return 0;

}