#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>

using namespace std;

map<char, int> precedence;

void initialize_precedence() {  // Приоритетность операторов
    precedence['+'] = 1;
    precedence['-'] = 1;
    precedence['*'] = 2;
    precedence['/'] = 2;
    precedence['^'] = 3;
}

bool is_operator(char c) {  // Является ли символ оператором?
    return c == '+' || c == '-' || c == '*' ||
        c == '/' || c == '^';
}

bool is_operand(char c) {   // Является ли оператор цифрой?
    return c >= '0' && c <= '9';
}

bool has_higher_precedence(char op1, char op2) {    // Приоритет выше?
    return (precedence[op1] >= precedence[op2]);
}

string infix_to_postfix(string infix) {
    stack<char> s;  // стэк
    string postfix = "";    // выходная строка

    for (int i = 0; i < infix.length(); i++) {  // проход по входной строке
        if (infix[i] == ' ') {  // пробелы пропускаем
            continue;
        }

        if (is_operand(infix[i])) {
            postfix += infix[i];
        }
        else if (is_operator(infix[i])) {
            // Выталкиваем в выходную строку из стека все операторы, имеющие приоритет выше рассматриваемого
            while (!s.empty() && s.top() != '(' &&
                has_higher_precedence(s.top(), infix[i])) {
                postfix += s.top();
                s.pop();
            }

            s.push(infix[i]);
        }
        else if (infix[i] == '(') {
            s.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }

            s.pop();
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    initialize_precedence(); // Приоритеты операторов

    string infix;
    getline(fin, infix);

    string postfix = infix_to_postfix(infix);

    fout << "Infix expression: " << infix << endl;
    fout << "Postfix expression: " << postfix;

    return 0;
}