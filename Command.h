#ifndef UNTITLED1_COMMAND_H
#define UNTITLED1_COMMAND_H

#include <iostream>
#include <string>
#include <list>
#include "Expression.h"
#include "S_yard.h"
#include "connectControlClient.h"

using namespace std;

class Command {
protected:

    string path;
    string val;


public:
    list<string> valus;
    string name;
    map<string, Command *> giveinfomap;
    list<Command *> test;
    connectControlClient *client;

    void setVal(string v) {
        this->val = v;
    }

    void setPath(string p) {
        this->path = p;
    }

    string getPath() {
        return this->path;
    }

    string getVal() {
        return this->val;
    }

    void setName(string s) {
        this->name = s;
    }

    virtual string stringFixer(string VAR) {}

    virtual int execute() = 0;

    virtual string getName() {};

    virtual ~Command() {};

};


#endif //UNTITLED1_COMMAND_H