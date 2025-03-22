/*E 字母游戏
波比和哈丽在玩一个字母游戏，波比给出一个字符串S，
要求哈丽按照一定规则，基于该字符串算出一个数字X。

规则是：
（1）求出S的最长重复后缀P
（P是S的后缀且在S中出现大于1次，例如yacbacba的最长重复后缀是acba），
（2）求出在S中去除第二长相等前后缀（
S中所有相等的前后缀中第2长者，
例如abcabcxxxabcabc中最长相等前后缀是abcabc，第二长的相等前后缀则是abc）
后剩下的子串Q（例如abcabcxxxabcabc去除第二长相等前后缀后，剩下abcxxxabc）。

则X=P的长度+Q的长度。

注意一个字符串不能称为自己的前缀或后缀。子串Q至少为空串，其长度大于等于0，不能为负数。

请编写程序帮助哈丽根据给定字符串S，根据上述规则计算出数字X。*/
#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    int* getNextArray(string str) {
        if (str.length() <= 1) {
            return new int [1] {-1};
        }
        int* next = new int[str.length()];
        next[0] = -1;
        next[1] = 0;
        int i = 2;
        int cn = 0;
        while (i < str.length()) {
            if (str[i - 1] == str[cn]) {
                next[i++] = ++cn;
            }
            else if (cn > 0) {
                cn = next[cn];
            }
            else {
                next[i++] = 0;
            }
        }
        return next;
    }
    //找最长相等前后缀的长度
    int getMaxInNextArray(string str) {
        if (str.length() <= 1) {
            return -1;
        }
        int* next = new int[str.length()];
        next[0] = -1;
        next[1] = 0;
        int max = 0;
        int i = 2;
        int cn = 0;
        while (i < str.length()) {
            if (str[i - 1] == str[cn]) {
                next[i++] = ++cn;
                if (next[i - 1] > max) {
                    max = next[i - 1];
                }
            }
            else if (cn > 0) {
                cn = next[cn];
            }
            else {
                next[i++] = 0;
            }
        }
        
        return str[str.length() - 1] == str[next[str.length() - 1]] ? max + 1 : max;
    }
    int KMP(string str1, string str2) {
        if (str1.length() <= 1 || str1.length() < str2.length()) {
            return -1;
        }
        int x = 0;
        int y = 0;
        int* next = getNextArray(str2);
        while (x < str1.length() && y < str2.length()) {
            if (str1[x] == str2[y]) {
                x++;
                y++;
            }
            else if (next[y] == -1) {
                x++;
            }
            else {
                y = next[y];
            }
        }
        delete[]next;
        return y == str2.length() ? x - y : -1;
    }
    //求最长重复后缀，就是在字符串中找最大重复部分，只不过有一个重复部分必须在后面
    //二者就和求Next数组中找最大相等前后缀异曲同工
    //只需要将字符串反过来，再求一次next数组并找到里面的next数组最大值，
    //又因为next数组法有一个问题就是最后一位的next值是前面所有位的最大相等前缀，
    //最后一位自己没有被包含进来
    string revertString(string str) {
        string reverse;
        for (int i = str.length()-1;i >= 0;--i) {
            reverse += str[i];
        }
        return reverse;
    }
};
int main(void) {
    Solution solve;
    string str1;
    while (getline(cin,str1)) {
        if (str1 == ""){
            cout<<0<<endl;
            return 0;
        }
        string str2 = solve.revertString(str1);
        int P = solve.getMaxInNextArray(str2);
        int* next = solve.getNextArray(str1);
        int y = str1.length() - 1;
        int i = next[y];
        int j;
        int tmp;    //第二长相等前后缀的长度
        //如果该串连第一长相等前后缀都没有，那么tmp=0
        if (i == 0){
            tmp = 0;
        }
        //有第一长相等前后缀
        else{
            //直接再取一次i的next值，就是第二长相等前后缀
            j = next[i];
            //next数组法不包含最后一位，所以一旦要算相等前后缀的长度，最后一位一定要考虑
            tmp = str1[j]==str1[y]?j+1:j;
            }
        int Q;
        //如果第二长相等前后缀超过了模式串串长的一半，Q就必须为0
        //最长相等前后缀是可以超过模式串串长的一半的！！！
        //例如aaaaaa， 最长为5，第二长为4，>3
        if(tmp>str1.length()/2){
            Q = 0;
        }
        else{Q = str1.length() - 2 * tmp;}
        int X = P + Q;
        cout << X << "\n";
    }
}