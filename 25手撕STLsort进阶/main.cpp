#include <iostream>
#include <math.h>
#include <cassert>
using namespace std;
int threshold = 16;
int Partition(int R[], int m, int n);
void InsertSort(int R[], int n);
void quicksort(int* arr,int L,int R,int level,int depthLimit);
int* netherlandflag(int* arr,int L,int R,int num);
void swap(int& a,int& b);
void heapsort(int* arr,int size);
int getDepthLimit(int size);
void sort(int* arr,int size);
int getMedianOfThree(int* arr,int L,int R);
void heapify(int* arr,int index,int heapsize);
void buildHeap(int* arr,int size);
void heapsort(int* arr,int size);
void swap(int& a,int& b){
    int temp = a;
    a = b;
    b = temp;
}
int* netherlandflag(int* arr,int L,int R,int num){
    int less = L-1;//小于区域的闭区间右边界
    int more = R+1;//大于区域的闭区间左边界
    int cur = L;//当前位置
    while(cur<more){
        if (arr[cur]<num){
            swap(arr[++less],arr[cur++]);
        }
        else if (arr[cur]>num){
            swap(arr[--more],arr[cur]);
        }
        else{
            cur++;
        }
    }
    return new int[2]{less+1,more-1};
}
void quicksort(int* arr,int L,int R,int level,int depthLimit){

    while(R-L+1>threshold){
        if (level>=depthLimit){
            int* newHeap = new int[R-L+1];
            for (int i = L;i<=R;++i){
                newHeap[i-L] = arr[i];
            }
            heapsort(newHeap,R-L+1);
            for (int i = L;i<=R;++i){
                arr[i] = newHeap[i-L];
            }
            delete[] newHeap;
            return;
        }
        int num = getMedianOfThree(arr,L,R);
        int* p = netherlandflag(arr,L,R,num);
        if (p[0]-L<=R-p[1]){
            quicksort(arr,L,p[0]-1,level+1,depthLimit);
            L = p[1]+1;
            level++;
        }
        else{
            quicksort(arr,p[1]+1,R,level+1,depthLimit);
            R = p[0]-1;
            level++;
        }
    }   
}
//这种双递归，递归的结构其实就是二叉树，而递归的深度就是二叉树的深度
//所以在递归的时候，传入level+1，因为下一次递归的深度是当前递归深度+1
//！！！！递归本身是不代表任何行为的，真正有效的行为是递归以外的代码，比如这里就是netherlandflag
//递归就是在分解问题的过程中，问题规模变小，不断对小问题进行有效的行为，最后解决问题
//递归就是进入了下一层
//尾递归优化时，就是原本从两端进入，变成了从一端进入，但通过调整参数，模拟了从另一端进入
//当我用level来表示递归深度时，传level+1表示进入下一层。当从另一端进入时，就需要level++，模拟进入下一层
void heapify(int* arr,int index,int heapsize){
    int left = index*2+1;
    while(left<heapsize){
        int largest = left+1<heapsize&&arr[left+1]>arr[left]?left+1:left;
        largest = arr[largest]>arr[index]?largest:index;
        if (largest == index){
            break;
        }
        swap(arr[largest],arr[index]);
        index = largest;
        left = index*2+1;
    }
}
void buildHeap(int* arr,int size){
    for (int i = size/2-1;i>=0;--i){
        heapify(arr,i,size);
    }
}
void heapsort(int* arr,int size){
    buildHeap(arr,size);
    cout<<"Heap:";
    for (int i = 0;i<size;++i){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    for (int i = size-1;i>0;--i){
        swap(arr[0],arr[i]);
        heapify(arr,0,i);
    }
}
void InsertSort(int R[], int n){
    for(int j=2;j<=n;j++){
    //R[1]..... R[j-1]  R[j]
        int i=j-1; // 指针i扫描R[1]..... R[j-1]
        int K=R[j];
        while (i>0 && R[i]>K){
        //从右往左找第1个  R[j]的元素
            R[i+1]=R[i];
            i--;
        }
        R[i+1]=K;
    }
}
int getDepthLimit(int size){
    double result = 2.0*log2(size);
    return static_cast<int>(result);
}
int Partition(int R[], int m, int n){ //对子数组Rm…Rn分划
    int i=m, j=n+1, K=R[m]; // Rm为基准元素
    while(i<j) {
        while(++i<=n && R[i]<=K); //从左向右找第一个>K的元素
        while(R[--j]>K); //从右向左找第一个<=K的元素
        if(i<j) swap(R[i],R[j]);
    }
    swap(R[m],R[j]);
    return j;
}
void sort(int* arr,int size){
    int depthLimit = getDepthLimit(size);
    cout<<"depth_limit:"<<depthLimit<<endl;
    int level = 0;
    quicksort(arr,1,size,level,depthLimit);
    cout<<"Intermediate:";
    for (int i = 1;i<=size;++i){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    InsertSort(arr,size);
}
int getMedianOfThree(int* arr,int L,int R){
    int mid = L+((R-L)/2);
    swap(arr[mid],arr[L+1]);
    if(arr[L+1]>arr[R]){
        swap(arr[L+1],arr[R]);
    }
    if (arr[L]>arr[R]){
        swap(arr[L],arr[R]);
    }
    if (arr[L+1]>arr[L]){
        swap(arr[L+1],arr[L]);
    }
    return arr[L];
}
int main()
{
    int n,i;
    int a[50010];
    scanf("%d %d", &n, &threshold);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    
    sort(a,n);
    
    printf("Final:");
    for (i = 1; i <= n; i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}