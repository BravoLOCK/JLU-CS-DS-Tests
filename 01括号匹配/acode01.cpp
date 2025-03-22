/*编写程序检查给定字符串中包含的括号是否正确匹配，本题中的括号有{ }、[ ]、( )、< >四种。
另外再加上一个新的约束条件：当有多种括号嵌套时，嵌套的顺序应为{ → [ → ( → <，
即a–g+b∗[(d∗<e–f>)]、a+[b+(c–d)∗e]都是正确的匹配，
而a+(b∗[c+d])则不是正确匹配。注意本题不允许相同类型括号的嵌套，
即a+(b∗(c+d))不是正确匹配。
本题不需要判断表达式是否合法，只需判断字符串中包含的括号是否正确匹配。
*/
#include <iostream>
#include <string>
using namespace std;
class Stack {
public:
    char* val;
    int size;
    int capacity;
    int top;
    Stack(int cap) :val(new char[cap]), size(0), capacity(cap), top(0) {}
    bool isEmpty() {
        return size == 0;
    }
    bool isFull() {
        return size == capacity;
    }
    bool push(char data) {
        if (isFull()) {
            return false;
        }
        val[top++] = data;
        size++;
        return true;
    }
    char pop() {
        if (isEmpty()) {
            return -1;
        }
        char tmp = val[--top];
        size--;
        return tmp;
    }
    Stack(const Stack& cop) :val(new char[cop.capacity]), size(0), capacity(cop.capacity), top(0) {
        for (int i = 0; i < cop.size; ++i) {
            push(cop.val[i]);
        }
    }
};
class Solution {
public:
    bool check(string str) {
        Stack sta1(str.length());
        Stack sta2(str.length());
        for (int i = 0; i < str.length(); ++i) {
            if (str[i] == '{' || str[i] == '[' || str[i] == '(' || str[i] == '<') {
                sta1.push(str[i]);
                sta2.push(str[i]);
            }
            if (str[i] == '}' || str[i] == ']' || str[i] == ')' || str[i] == '>') {
                if (sta1.isEmpty()) {
                    return false;
                }
                char tmp1 = sta1.pop();
                if (check01(tmp1, str[i])) {
                    char tmp3 = sta2.pop();
                    while (!sta2.isEmpty()) {
                        char tmp2 = sta2.pop();
                        if (!check02(tmp2, tmp3)) {
                            return false;
                        }
                        tmp3 = tmp2;
                    }
                    sta2 = sta1;
                }
                else {
                    return false;
                }
            }
        }
        if (!sta1.isEmpty()) {
            return false;
        }
        return true;
    }
    bool check01(char c1, char c2) {
        if (c1 == '{') {
            if (c2 == '}') {
                return true;
            }
            return false;
        }
        if (c1 == '[') {
            if (c2 == ']') {
                return true;
            }
            return false;
        }
        if (c1 == '(') {
            if (c2 == ')') {
                return true;
            }
            return false;
        }
        if (c1 == '<') {
            if (c2 == '>') {
                return true;
            }
            return false;
        }
    }
    bool check02(char c1, char c2) {
        if (c1 == '{') {
            if (c2 == '{') {
                return false;
            }
        }
        if (c1 == '[') {
            if (c2 == '{' || c2 == '[') {
                return false;
            }
        }
        if (c1 == '(') {
            if (c2 == '{' || c2 == '[' || c2 == '(') {
                return false;
            }
        }
        if (c1 == '<') {
            if (c2 == '{' || c2 == '[' || c2 == '(' || c2 == '<') {
                return false;
            }
        }
        return true;
    }
};
int main(void) {
    int opnums = 0;
    cin >> opnums;
    string* result = new string[opnums];
    Solution solve;
    for (int i = 0; i < opnums; ++i) {
        string tmp;
        cin >> tmp;
        bool res = solve.check(tmp);
        if (res == true) {
            result[i] = "Match";
        }
        else {
            result[i] = "Fail";
        }
    }
    for (int i = 0; i < opnums; ++i) {
        cout << result[i] << endl;
    }
}