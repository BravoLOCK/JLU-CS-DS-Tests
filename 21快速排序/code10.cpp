#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void Qsort(int* R,int start,int end,int n){
    int i ;
    int j ;
    int K ;
    if (start<end){
        i = start;
        j = end+1;
        K = R[start];
        while(i<j){
            i = i+1;
            while(R[i]<=K&&i<=end){
                i++;
            }
            j = j-1;
            while(R[j]>K){
                j = j-1;
            }
            if (i<j){
                int temp = R[i];
                R[i] = R[j];
                R[j] = temp;
            }
        }
        int tmp = R[start];
        R[start] = R[j];
        R[j] = tmp;
        for (int k = 0;k<n;++k){
            cout<<R[k]<<" ";
        }
        cout<<endl;
        Qsort(R,start,j-1,n);
        Qsort(R,j+1,end,n);
    }
}
void exchange(int& a,int& b){
    a = a^b;
    b = a^b;
    a = a^b;
}
int* getRandomArray(int size,int L,int R){
    int* randomArray = new int[size];
    srand(time(0));
    for (int i = 0;i<size;++i){
        randomArray[i] = rand()%(R-L+1)+L;
    }
    return randomArray;
}
int main (void){
    int n;
    cin>>n;
    // int* arr = getRandomArray(n,1,9);
    // for (int i = 0;i<n;++i){
    //     cout<<arr[i]<<" ";
    // }
    // cout<<endl;
    int* arr = new int [n];
    for (int i = 0;i<n;++i){
        cin>>arr[i];  
    }
    
    Qsort(arr,0,n-1,n);
        for (int i = 0;i<n;++i){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}