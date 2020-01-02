#include <bits/stdc++.h>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>

#include "Expression.h"
#include "Expression.cpp"
#include "S_yard.h"

using namespace std;


Variable &Variable::operator++() {
    this->num = this->num + 1;
    return *this;
}

Variable &Variable::operator++(int x) {
    this->num = this->num + 1;
    return *this;
}

Variable &Variable::operator--() {
    this->num = this->num - 1;
    return *this;
}

Variable &Variable::operator--(int x) {
    this->num = this->num + 1;
    return *this;
}

Variable &Variable::operator+=(const Variable &x) {
    this->num = this->num + x.num;
    return *this;
}

Variable &Variable::operator-=(const Variable &x) {
    this->num = this->num - x.num;
    return *this;
}


/////////////////////////////
// part 2:
// replace vars to numbers.
string Interpreter::findAndReplaceAll(string data, string toSearch, string replaceStr) {
    // Get the first occurrence
    size_t pos = data.find(toSearch);

    // Repeat till end is reached
    while (pos != std::string::npos) {
        data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
    }
    return data;
}

void Interpreter::Cheakstring(string s, map<string, string> mp) {
    int count = 0;
    int count2 = 0;

    // check if the string is valid
    if (mp.size() != 0) {
        for (std::map<string, string>::iterator it = mp.begin(); it != mp.end(); ++it) {
            s = findAndReplaceAll(s, it->first, it->second);
        }
    }
    for (int i = 0; i < s.length(); i++) {
        //if(precedence(s[i]) != 0 && precedence(s[i+1]) != 0) {
        //throw ("bad input");
        // }
        if (s[i] == '(') {
            count++;
        }
        if (s[i] == ')') {
            count2++;
        }
        if (s[i] == ' ') {
            throw ("bad input");
        }
        if (s[i] == ')' && s[i + 1] == '(') {
            throw ("illegal math expression");
        }
        if (s[i] == '(' && s[i + 1] == ')') {
            throw ("illegal math expression");
        }
        if (!isdigit(s[i])) {
            if ((s[i] != '+') && (s[i] != '-') && (s[i] != '*') && (s[i] != '/') && (s[i] != '(') && (s[i] != ')') &&
                (s[i] != '.')) {
                throw ("illegal math expression");
            }
        }

    }
    if (count != count2) {
        throw ("bad input");
    }
}

// set the Variables
void Interpreter::setVariables(string s) {
    s = s + ';';
    string part = "";
    string left = "";
    string right = "";
    int flag = 1;
    for (auto x:s) {
        if (x == ';') {
            for (auto y:part) {
                if (y == '=') {
                    flag = 0;
                    continue;
                }
                if (flag) {
                    if ((!isdigit(y)) && (!(y >= 'a' && y <= 'z') && !(y >= 'A' && y <= 'Z')) && (y != '_')) {
                        throw ("illegal variable assignment!");
                    }
                    if (y == '.') {
                        throw ("illegal variable assignment!");
                    }
                    left = left + y;
                } else {
                    right = right + y;
                }
            }
            flag = 1;
            try {
                double value = std::stod(right);
            } catch (exception &e) {
                throw ("illegal variable assignment!");
            }
            if (this->mp.find(left) != this->mp.end()) {
                this->mp.erase(this->mp.find(left));
            }
            if (left == "") {
                throw ("illegal variable assignment!");
            }
            if (isdigit(left[0])) {
                throw ("illegal variable assignment!");
            }
            this->mp.insert(std::pair<string, string>(left, right));
            part = "";
            left = "";
            right = "";
        } else {
            part = part + x;
        }
    }
}


Expression *Interpreter::makeExpressions(Expression *a, Expression *b, char op) {
    Expression *e;
    switch (op) {
        case '+':
            e = new Plus(a, b);
            break;
        case '*':
            e = new Mul(a, b);
            break;

        case '-':
            e = new Minus(a, b);
            break;

        case '/':
            e = new Div(a, b);
            break;
        default:;

    }
    return e;
}

int Interpreter::precedence(char Operator) {
    if (Operator == '+' || Operator == '-')
        return 1;
    if (Operator == '*' || Operator == '/')
        return 2;
    return 0;
}

Expression *Interpreter::interpret(string s) {
    if (mp.size() != 0) {
        for (std::map<string, string>::iterator it = mp.begin(); it != mp.end(); ++it) {
            s = findAndReplaceAll(s, it->first, it->second);
        }
    }
    Cheakstring(s, mp);
    stack<Expression *> values;
    stack<char> ops;
    if (s[0] == '+') {
        int temp = 0;
        Expression *e = new Value(temp);
        values.push(e);
    }
    if (s[0] == '-') {
        int temp = 0;
        Expression *e = new Value(temp);
        values.push(e);
    }
    for (unsigned int i = 0; i < s.length(); i++) {
        // if its '(' push to ops
        if (s[i] == '(') {
            ops.push(s[i]);
            if (s[i + 1] == '+') {
                double temp = 0;
                Expression *e = new Value(temp);
                values.push(e);
            }
            if (s[i + 1] == '-') {
                double temp = 0;
                Expression *e = new Value(temp);
                values.push(e);
            }
        }
            // Current "i" is a number, push
            // it to stack for numbers.
        else if (isdigit(s[i])) {
            double val = 0;
            if (s[i + 1] == '.') {
                val = s[i] - '0';
                unsigned int j = i + 2;
                double temp;
                double temp2 = 1;
                while (j < s.length() &&
                       isdigit(s[j])) {
                    temp = (s[j] - '0') / (pow(10, temp2));
                    j = j + 1;
                    temp2 = temp2 + 1;
                    i = j - 1;
                }
                val = val + temp;
                // There may be more than one
                // digits in number.
            } else {
                while (i < s.length() &&
                       isdigit(s[i])) {
                    val = (val * 10) + (s[i] - '0');
                    i = i + 1;
                    if (!isdigit(s[i])) {
                        i = i - 1;
                        break;
                    }
                }
                if (s[i + 1] == '.') {
                    unsigned int j = i + 2;
                    double temp;
                    double temp2 = 1;
                    while (j < s.length() &&
                           isdigit(s[j])) {
                        temp = (s[j] - '0') / (pow(10, temp2));
                        j = j + 1;
                        temp2 = temp2 + 1;
                        i = j - 1;
                    }
                    val = val + temp;
                }
            }
            Expression *e = new Value(val);
            values.push(e);

        }

            // Closing brace encountered (solve equation)
        else if (s[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                Expression *y = values.top();
                values.pop();

                Expression *x = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();
                Expression *e = makeExpressions(x, y, op);
                values.push(e);
            }

            // pop op.
            if (!ops.empty())
                ops.pop();
        }

            // Current "i" is an operator.
        else {
            // check of operators and
            // push new expression by it
            while (!ops.empty() && precedence(ops.top())
                                   >= precedence(s[i])) {
                Expression *y = values.top();
                values.pop();

                Expression *x = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                Expression *e = makeExpressions(x, y, op);
                values.push(e);
            }

            // Push current i to 'ops'.
            ops.push(s[i]);
        }
    }
    // output: full expression.
    while (!ops.empty()) {
        Expression *y = values.top();
        values.pop();

        Expression *x = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        Expression *e = makeExpressions(x, y, op);
        values.push(e);
    }

    // return result.
    Expression *y = values.top();
    return y;
}