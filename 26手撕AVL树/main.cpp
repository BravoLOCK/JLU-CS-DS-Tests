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
void insert(AVL*& root,int K){
    if (root == nullptr){
        root = new AVL(K);
    }
    else if (K<root->key){
        insert(root->left,K);
        if (height(root->left)-height(root->right)==2){
            if (K<root->left->key){
                LL(root);
            }
            else{
                LR(root);
            }
        }
    }
    else if (K>root->key){
        insert(root->right,K);
        if (height(root->right)-height(root->left)==2){
            if (K>root->right->key){
                RR(root);
            }
            else{
                RL(root);
            }
        }
    }
    root->height = max(height(root->left),height(root->right))+1;
}
void remove(AVL*& root,int K){
    if (root == nullptr){
        return;
    }
    if (K<root->key){
        remove(root->left,K);
        if (height(root->right)-height(root->left)==2){
            if (height(root->right->left)>height(root->right->right)){
                RL(root);
            }
            else{
                RR(root);
            }
        }
        
    }
    else if (K>root->key){
        remove(root->right,K);
        if (height(root->left)-height(root->right)==2){
            if (height(root->left->right)>height(root->left->left)){
                LR(root);
            }
            else{
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
            remove(root->right,temp->key);
            if (height(root->left)-height(root->right)==2){
                if (height(root->left->right)>height(root->left->left)){
                    LR(root);
                }
                else{
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
    cin>>n;
    char op[10];
    int opnum;
    AVL* root = nullptr;
    for (int i = 0; i<n;i++){
        scanf("%s",op);
        getchar();
        scanf("%d",&opnum);
        if (i!=n-1)getchar();
        if (strcmp(op,"Insert")==0){
            insert(root,opnum);
        }
        else if (strcmp(op,"Remove")==0){
            remove(root,opnum);
        }
    }
    inOrder(root);
    cout<<endl;
    cout<<endl;
    preOrder(root);
    return 0;
}