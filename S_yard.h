#ifndef UNTITLED1_S_YARD_H
#define UNTITLED1_S_YARD_H


#include "Expression.h"
#include "string"
#include "map"

class ex1 {
};

class Variable : public Expression {
    char name;
    string s;
    double num;
public:
    Variable(char _name, double _value) {
        this->name = _name;
        this->num = _value;
    }

    Variable(string _n, double _value) {
        this->s = _n;
        this->num = _value;
    }

    double calculate() {
        return this->num;
    }

    Variable &operator++();

    Variable &operator++(int x);

    Variable &operator--(int x);

    Variable &operator--();

    Variable &operator+=(const Variable &x);

    Variable &operator-=(const Variable &x);
};

class Value : public Expression {
private:
    const double num;
public:
    Value(double _num) : num(_num) {
    }

    double calculate() {
        return this->num;
    }
};

class UnaryOperator : public Expression {

protected:
    Expression *num;

    UnaryOperator(Value *_num) {
        this->num = _num;

    }

    UnaryOperator(Expression *_num) {
        this->num = _num;

    }

    double calculate() {
        return this->num->calculate();
    }

    ~UnaryOperator() {
        if (num != NULL) {
            delete num;
        }
    }
};

class BinaryOperator : public Expression {

protected:
    Expression *left;
    Expression *right;

    BinaryOperator(Expression *_left, Expression *_right) {
        this->left = _left;
        this->right = _right;
    }

    double calculate() {
        return 0;
    }

    ~ BinaryOperator() {
        if (left != NULL) {
            delete left;
        }
        if (right != NULL) {
            delete right;
        }
    }
};

class Plus : public BinaryOperator {

public:
    Plus(Expression *_left, Expression *_right) : BinaryOperator(_left, _right) {
    }

    double calculate() {
        double returnNum = this->left->calculate() + this->right->calculate();
        return returnNum;
    }


};

class Minus : public BinaryOperator {

public:
    Minus(Expression *_left, Expression *_right) : BinaryOperator(_left, _right) {
    }


    double calculate() {
        double returnNum = this->left->calculate() - this->right->calculate();
        return returnNum;
    }

};

class Mul : public BinaryOperator {

public:
    Mul(Expression *_left, Expression *_right) : BinaryOperator(_left, _right) {
    }


    double calculate() {
        double returnNum = this->left->calculate() * this->right->calculate();
        return returnNum;
    }

};

class Div : public BinaryOperator {

public:
    Div(Expression *_left, Expression *_right) : BinaryOperator(_left, _right) {
    }

    double calculate() {
        if (right->calculate() == 0) {
            throw ("division by zero");
        } else {
            double returnNum = this->left->calculate() / this->right->calculate();
            return returnNum;
        }
    }


};

class UPlus : public UnaryOperator {

public:
    UPlus(Value *_num) : UnaryOperator(_num) {
    }

    UPlus(Expression *_num) : UnaryOperator(_num) {
    }


};

class UMinus : public UnaryOperator {
public:

    UMinus(Value *_num) : UnaryOperator(_num) {

    }

    UMinus(Expression *_num) : UnaryOperator(_num) {
    }

    double calculate() {
        return -num->calculate();
    }
};

/////////////////////////////////////////////
class Interpreter {
    map<string, string> mp = {};

    string findAndReplaceAll(string data, string toSearch, string replaceStr);

    void Cheakstring(string s, map<string, string> mp);

// check which operator is more importent
    int precedence(char Operator);

public:
    // if we get vars instead of numbers
    void setVariables(string s);

    // check the operator
    Expression *makeExpressions(Expression *a, Expression *b, char op);

    Expression *interpret(string s);


};


#endif //UNTITLED1_S_YARD_H