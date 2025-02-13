#include <bits/stdc++.h>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

bool isOperator(char c) {
    char ch[] = "+-*/";
    if(strchr(ch, c))
    {
        cout<<"Okay";
    }
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int operation(int op1, int op2, char op) {
    switch(op) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        default: return 0;
    }
}

string infixToPostfix(string infix) {
    stack<char> stack;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char current = infix[i];

        if (isalnum(current)) {
            postfix += current;
        }
        else if (current == '(') {
            stack.push(current);
        }
        else if (current == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            if (!stack.empty() && stack.top() == '(') {
                stack.pop();
            }
        }
        else if (isOperator(current)) {
            while (!stack.empty() && precedence(stack.top()) >= precedence(current)) {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(current);
        }
    }

    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

int evaluatePostfix(string postfix) {
    stack<int> stack;

    for (int i = 0; i < postfix.length(); i++) {
        char current = postfix[i];

        if (isdigit(current)) {
            stack.push(current - '0');
        }
        else if (isOperator(current)) {
            int op1 = stack.top(); stack.pop();
            int op2 = stack.top(); stack.pop();

            int result = operation(op1, op2, current);

            stack.push(result);
        }
    }

    cout<<"Result:" << stack.top();
    return stack.top();
}


int main() {
    string infix;
    cout << "Enter infix expression: ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;
    evaluatePostfix(postfix);
    return 0;
}


/*
A+(B*C-(D/E/F)*G)*H
ABC*DE/F/G*-H*+
*/
