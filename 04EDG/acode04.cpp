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
};
int main(void) {
    int opnums = 0;
    cin >> opnums;
    Solution solve;
    string model = "edgnb";
    int* result = new int[opnums];
    for (int i = 0;i < opnums;++i) {
        string str1;
        cin >> str1;
        int rnum = 1;
        cin >> rnum;
        string str2 = "edgnb";
        for (int i = 0;i < rnum - 1;++i) {
            str2 += model;
        }
        int flag = 0;
        int nums = 0;
        int lth = rnum * 5;
        while ((flag = solve.KMP(str1, str2)) != -1) {
            nums++;
            bool isEqual = 1;
            while (isEqual == 1) {
                for (int i = 0;i < 5;++i) {
                    if (flag + lth + i >= str1.length()) {
                        isEqual = 0;
                        break;
                    }
                    if (str1[flag + lth + i] != model[i]) {
                        isEqual = 0;
                        break;
                    }
                }
                if (isEqual == 1) {
                    nums++;
                    flag += 5;
                }
                else {
                    str1 = str1.substr(flag + lth);
                }
            }
        }
        result[i] = nums;
    }
    for (int i = 0;i < opnums;++i) {
        cout << result[i] << endl;
    }
}