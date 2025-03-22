/*C 表达式求值
给定一个中缀表达式，请编写程序计算该表达式的值。
表达式包含+、-、*、/、^、(、)，
所有运算均为二元运算，操作数均为正整数，但可能不止一位，不超过10位。运算结果为整数，值域为[−2^31,2 ^31)。
除法运算结果若为小数则进行截尾取整。
若除法运算中除数为0，则输出INVALID。
幂运算须自行实现，不允许调用pow等系统函数。
测试数据保证幂运算中指数为非负，底数不为0。*/
#include <iostream>
#include <string>
using namespace std;
template <class T>
class Stack {
public:
//封装一个模版数组
    T* data;
    int size;
    int capacity;
    int top;
    Stack(int cap) :data(new T[cap]), size(0), capacity(cap), top(0) {}
    bool isEmpty() {
        return size == 0;
    }
    bool isFull() {
        return size == capacity;
    }
    bool push(T val) {
        if (isFull()) {
            return false;
        }
        data[top++] = val;
        size++;
        return true;
    }
    T pop() {
        //不要使用exit（0），会产生运行错误
        if (isEmpty()) {
            exit(-1);
        }
        T tmp = data[--top];
        size--;
        return tmp;
    }
    //查看栈顶元素
    T peek() {
        if (isEmpty()) {
            exit(-1);
        }
        return data[top - 1];
    }
};
//定义运算符类
class Operation {
public:
//封装字符和它的优先级
    char val;
    int priority;
    Operation() :val(0), priority(0) {}
    Operation(char c, int prio = 0) :val(c), priority(prio) {}
};
class Solution {
public:
//封装运算符栈，操作数栈，中缀表达式和后缀表达式
//后缀表达式用于计算求值
    Stack<Operation> st1;
    Stack<long long int>st2;
    string suffix;
    string cenfix;
    Solution(string str) :st1(10),st2(10),cenfix(str) {}
    long long int Operate(int& Error) {
        string numstring = "";
        Error = 0;
        for (int i = 0;i < suffix.length();++i) {
            if (suffix[i] == '$') {
                long long int num = stoll(numstring);
                numstring = "";
                st2.push(num);
            }
            else if (suffix[i] == '+' || suffix[i] == '-' || suffix[i] == '*' || suffix[i] == '/' || suffix[i] == '^') {
                Operation op(suffix[i], getPriority(suffix[i]));
                long long int Rnum = st2.pop();
                long long int Lnum = st2.pop();
                long long int result = figure(op.val,Lnum, Rnum, Error);
                st2.push(result);
                if (Error == 1) {
                    break;
                }
            }
            else {
                numstring += suffix[i];
            }
        }
        return st2.peek();
    }
    //中缀转后缀
    //shiyongle$符号作为操作数的间隔，用于区别操作符和操作数，
    //但细想一下就会发现非常不合理，因为这个机制，引发了许多对边界情况的处理（比如右括号）
    //更合理的做法应该是将suffix改用一个string队列来存放，可以完全避免边界处理的问题
    void cenfixToSuffix() {
        //开辟运算符栈
        Stack<Operation> st3(100);
        //将#压入运算符栈，为的是让表达式中第一个运算符能够压入栈中
        Operation init('#', 0);
        st3.push(init);
        //遍历中缀表达式
        for (int i = 0;i < cenfix.length();++i) {
            //如果是运算符
            if (cenfix[i] == '+' || cenfix[i] == '-' || cenfix[i] == '*' || cenfix[i] == '/' || cenfix[i] == '^') {
                //表达式中运算符前面可能是操作数，也可能是右括号
                //不是右括号的时候，就要
                if (cenfix[i - 1] != ')') {
                    suffix += '$';
                }
                //创建运算符对象
                Operation op (cenfix[i], getPriority(cenfix[i]));
                //获取栈顶运算符的值
                Operation st3Top = st3.peek();
                //如果大于栈顶，则将该运算符压入，因为只有小于栈顶时才说明这个运算符必须立刻计算
                
                if (op.priority > st3Top.priority) {
                    st3.push(op);
                }
                //如果小于栈顶，那么将栈内运算符中小于op优先级的运算符全都弹出，放入后缀表达式中，并将op放入栈中
                //因为越是优先级高的运算符，越是要更早的被放入到后缀表达式中
                else {
                     PopTillThePrioIsNotHigher(st3, op.priority);
                     st3.push(op);
                }
            }
            //遇到左括号时将括号压入栈中，
            //优先级设置为1的目的是为了使括号内第一个运算符能够被正常的放入栈中
            //和#被设置为0一个道理
            else if (cenfix[i] == '(') {
                Operation bracket('(', 1);
                st3.push(bracket);
            }
            //遇到右括号时，意味着前面一个操作数要加上$来表示结束
            //否则必须要找下一个操作符来结算，但此时括号内运算符先操作数一步被放入suffix中，结算失败
            else if (cenfix[i] == ')') {
                //为了排除双重括号，但更往上的就不行了
                if(cenfix[i-1]!=')'){
                    suffix+='$';
                }
                //将括号内的操作符全都弹栈入suffix中
                PopTillTheLeftBracket(st3);
            }
            //遇到字符时，正常入suffix中
            else {
                suffix += cenfix[i];
            }
        }
        //边界处理最后一个字符，如果不是括号（括号可以自己加$），则手动添加
        if (cenfix[cenfix.length() - 1] != ')') {
            suffix += '$';
        }
        //将栈中所有没弹掉都弹掉
        PopTillTheStackIsEmpty(st3);
    }
    void PopTillThePrioIsNotHigher(Stack<Operation>& st,int prio) {
        //#号不能被入栈
        while (st.peek().val!='#'&&st.peek().priority >= prio) {
            suffix += st.pop().val;
        }
    }
    void PopTillTheLeftBracket(Stack<Operation>& st) {
        while (st.peek().val != '(') {
            suffix += st.pop().val;
        }
        st.pop();
    }
    void PopTillTheStackIsEmpty(Stack<Operation>& st) {
        //#不入栈
        while (st.peek().val!='#') {
            suffix += st.pop().val;
        }
    }
    //使用分治法求幂级数,分治法可以将时间复杂度从N降到logN
    int Pow(double base, int exponent) {
        if (exponent == 0) {
            return 1.0;
        }
        //如果exp为偶数，则可以用half*half的方式来求
        if (exponent % 2 == 0) {
            int half = Pow(base, exponent / 2);
            return half * half;
        }
        //如果为奇数，则base^exp = base^(exp-1)*base
        else {
            return base * Pow(base, exponent - 1);
        }
    }

    int getPriority(char c) {
        if (c == '+') {
            return 2;
        }
        else if (c == '-') {
            return 2;
        }
        else if (c == '*') {
            return  3;
        }
        else if (c == '/') {
            return 3;
        }
        else {
            return 4;
        }
    }
    int  figure(char c, int L, int R,int& Error) {
        if (c == '+')
        {
            return L + R;
        }
        else if (c == '-') {
            return L - R;
        }
        else if (c == '*') {
            return L * R;
        }
        else if (c == '/') {
            if (R == 0) {
                Error = 1;
                return -1;
            }
            return L / R;
        }
        else {
            return Pow(L, R);
        }
    }
};
int main(void) {
    string cinfix;
    while (cin >> cinfix) {
        int Error = 0;
        Solution solve(cinfix);
        solve.cenfixToSuffix();
        long long int result = solve.Operate(Error);
        if (Error == 0) {
            cout << result << endl;
        }
        else {
            cout << "INVALID" << endl;
        }
    }
}