#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

using namespace std;

//计算两个数的运算结果
int calc(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                throw invalid_argument("division by zero");
            }
            return a / b;
        default: throw invalid_argument("invalid operator: \'" + string(1, op) + '\'');//非法运算符
    }//异常处理：除0或不受支持的符号
}

//计算整个表达式的值
int calcExpr(const string& expr) {
    stack<int> numStack;//数字栈
    stack<char> opStack;//运算符栈

    for (int i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (isdigit(c)) {//数字的读取与转换
            int num = 0;
            while (i < expr.size() && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            numStack.push(num);//数字入栈
        } else if (c == '(') {//如果是左括号则直接入栈
            opStack.push(c);
        } else if (c == ')') {//如果是右括号，一直取出栈顶的数字和运算符进行计算，直到左括号
            while (opStack.top() != '(') {
                char op = opStack.top();
                opStack.pop();
                int b = numStack.top();
                numStack.pop();
                int a = numStack.top();
                numStack.pop();
                numStack.push(calc(op, a, b));//将计算结果压入栈
            }
            opStack.pop();//弹出左括号
        } else if (c == '+' || c == '-') {
            while (!opStack.empty() && opStack.top() != '(') {
                char op = opStack.top();
                opStack.pop();
                int b = numStack.top();
                numStack.pop();
                int a = numStack.top();
                numStack.pop();
                numStack.push(calc(op, a, b));
            }
            opStack.push(c);
        } else if (c == '*' || c == '/') {
            while (!opStack.empty() && (opStack.top() == '*' || opStack.top() == '/')) {
                char op = opStack.top();
                opStack.pop();
                int b = numStack.top();
                numStack.pop();
                int a = numStack.top();
                numStack.pop();
                numStack.push(calc(op, a, b));
            }
            opStack.push(c);
        } else {
            throw invalid_argument("invalid character: " + string(1, c));
        }//异常处理：不受支持的符号
        
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (i + 1 < expr.size() && (expr[i + 1] == '+' || expr[i + 1] == '-' || expr[i + 1] == '*' || expr[i + 1] == '/')) {
                throw invalid_argument("consecutive operators:\'" + string(1, expr[i + 1]) +'\'' );
            }//非法输入：连续的运算符号
        }
    }

    while (!opStack.empty()) {
        char op = opStack.top();
        opStack.pop();
        int b = numStack.top();
        numStack.pop();
        int a = numStack.top();
        numStack.pop();
        numStack.push(calc(op, a, b));
    }

    return numStack.top();
}

int main() {
    string expr;
    cout << "Enter an arithmetic expressions:" << endl;
    getline(cin, expr);

    while (expr.empty()) {
        cout << "Error: Expression cannot be empty.\nEnter an arithmetic expression:" << endl;
        getline(cin, expr);
    }//防止直接回车时栈错误导致程序崩溃

    try {
        int result = calcExpr(expr);
        cout << "Result:" << result << endl;
    } catch (exception &e) {
        cerr << "Error:" << e.what() << endl;
        return 1;
    }//使用try-catch结构处理各种异常情况
    return 0;
}
