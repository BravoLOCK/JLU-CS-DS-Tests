/*F 小龙猜数字
我们称一个字符串的秩为：
该字符串长度减去该字符串的最短相等前后缀的长度。
若该字符串不存在相等的前后缀，则其秩为0。
例如：abcabcxabcabc最短相等前后缀为abc，
该字符串的秩为10。
Pororo和小龙玩猜字游戏，
Pororo给出一个字符串S，
小龙需计算S及S中所有前缀子串的秩之和。
请编写程序帮助小龙猜数字。
输入格式:
输入为2行，第1行为字符串S的长度，第2行为具体的字符串。字符串长度不超过10^6
输出格式:
输出 一个整数表示字符串S及其所有前缀的秩之和。
注：结果超出int型变量范围，请使用long long型变量
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
class Solution{
public:
    long long* getShortArray(string str){
        long long  head = 0;
        long long* shortArray = new long long [str.length()];
        shortArray[0] = 0;
        long long  i = 1;       //用i遍历str，计算每个short值
        long long  x =0;       //x只在头匹配成功的情况和前一个x匹配成功的情况下前移
        long long repeathead = 1;
        //计算前缀的重复头节点数
        for (int i = 1;i<str.length();++i){
            if (str[i] != str[0]){
                break;
            }
            else{
                repeathead++;
            }
        }
        //计算遇到了几个重复头
        long long count = 0;
        while(i<str.length()){
            //遇到头，改点short值为1，同时count++，将遇到的重复头的个数写入x，让x指向下一个这个位置，继续比较
            if (str[i] == str[head]){
               shortArray[i++] = 1;
               count++;
                x = count;
               
            }
            else if (str[i] == str[x]){//i不为head，但未x
                //当count==repeathead时，说明重复前缀头已被遍历完，只要x所指位置和i所指位置两个位置值相同，则其short为repeathead+1
                //同时x指向下一个，count清零，因为x已经结束了重复前缀头
                if (count == repeathead){
                    shortArray[i++] = repeathead+1;
                    x++;
                    count = 0;
                    continue;
                }
                shortArray[i++] = shortArray[i-1]+1;
                x++;
                count = 0;
            }
            else{
                shortArray[i++] = 0;
                x = 0;
                count = 0;
            }
        }
        return shortArray;
    }
int* getNextArray(string& str1) {
	if (str1.length() == 1) {
		return new int[1] {-1};
	}
	int* next = new int[str1.length()];
	next[0] = -1;
	int i = 1;
	int cn = 0;
	while (i < str1.length()) {
		if (str1[i] == str1[cn]) {
			next[i++] = ++cn-1;
		}
		else if (cn > 0) {
			cn = next[cn - 1] + 1;
		}
		else {
			next[i++] = -1;
		}
	}
	return next;
}
    int* getShort(string str,int len){
        int* next = getNextArray(str);
        int i =1;
        int* arrayShort = new int [len];
        arrayShort[0] = -1;
        while (i<len){
            int cn = i;
            arrayShort[i] = -1;
            while(next[cn] != -1){
                arrayShort[i] = next[cn];
                cn = next[cn];
            }
            i++;
        }
        return arrayShort;
    }
    long long int figureZhi(string str,int len){
        int* next = getNextArray(str);
        long long int result = 0;
        for (int i = 1;i<len;++i){
            if (next[i] == -1){
                result+=0;
                continue;
            }
            while(next[next[i]] != -1){
                next[i] = next[next[i]];
            }
            result += i-next[i];
        }
        return result;
    }
};
class comparator{
public:
    char* getRandomArray(int size,char L,char R){
        char* randomArray = new char[size];
        srand(time(0));
        for (int i = 0;i<size-1;++i){
            randomArray[i] = rand()%(R-L+1)+L;
        }
        randomArray[size-1] = '\0';
        return randomArray;
    }
};
int main (void){
    int strlength = 0;
    cin>>strlength;
    string str;
    cin>>str;
    Solution solve;
    //int * arrayShort = solve.getShort(str,str.length());
    // for (int i = 0;i<str.length();++i){
    //     cout<<arrayShort[i];
    // }
    cout<<solve.figureZhi(str,strlength)<<endl;
    // comparator comp;
    // for (int i = 0;i<5000000;++i){
    //     int breakp = 0;
    //     const char* arr1 = comp.getRandomArray(100,'a','z');
    //     string str;
    //     str = arr1;
    //     int len = str.length();
    //     int* arr3 = solve.getShort(str,str.length());
    //     for (int j = 0;j<str.length();++j){
    //         arr3[j] +=1;
    //     }
    //     long long * arr4 = solve.getShortArray(str);
    //     for (int k = 0;k<str.length();++k){
    //         if (arr3[k]!=arr4[k]){
    //             breakp = 1;
    //             for (int s = 0;s<100;++s){
    //                 cout<< arr1[s];
    //             }
    //             break;
    //         }
    //     }
    //     if (breakp == 1){
    //         break;
    //     }
        
    // }
}