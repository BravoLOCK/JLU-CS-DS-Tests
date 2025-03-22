#include <iostream>
#include <math.h>
#include <cassert>
using namespace std;
int threshold = 16;
int Partition(int R[], int m, int n);
void heapsort(int* arr,int L,int R);
void InsertSort(int R[], int n);
void quicksort(int* arr,int L,int R,int& level,int depthLimit);
int* netherlandflag(int* arr,int L,int R,int num);
void swap(int& a,int& b);
void heapsort(int* arr,int size);
int getDepthLimit(int size);
void sort(int* arr,int size);
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
void quicksort(int* arr,int L,int R,int& level,int depthLimit){
    if (R-L+1<=threshold){
        return;
    }
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
    if (L<R){
        int p = Partition(arr,L,R);
        quicksort(arr,L,p-1,++level,depthLimit);
        --level;
        quicksort(arr,p+1,R,++level,depthLimit);
        --level;
    }
}
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
    for (int i = size-1;i>=0;--i){
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
    double result = 2*log2(size);
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