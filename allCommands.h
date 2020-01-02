#ifndef UNTITLED1_ALLCOMMANDS_H
#define UNTITLED1_ALLCOMMANDS_H

#include <chrono>
#include "Command.h"

// generic type of command obj
class alltype : public Command {
public:
    int execute() { return 0; }

    string getName() {
        return this->name;
    }

};

//print type command
class printCommand : public Command {
public:
    string stringToprint;

    printCommand(string basicString) {
        this->stringToprint = basicString;
    }

    //delete all spaces
    string delSpaces(string &str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }

    int execute() {
        Interpreter *i = new Interpreter();
        // if the input is string, just print it
        size_t found = this->stringToprint.find('\"');
        if (found != string::npos) {
            string finalString = "";
            for (unsigned int i = 1; i < stringToprint.length() - 1; i++) {
                finalString += stringToprint[i];
            }
            cout << finalString << endl;
            delete i;
        } else {
            //switch val to int
            this->stringToprint = delSpaces(this->stringToprint);
            Expression *e = i->interpret(this->stringToprint);
            cout << e->calculate() << endl;
            delete e;
            delete i;
        }
        return 0;
    }

    string getName() {
        return "print";
    }
};

//sleep type command
class sleepCommand : public Command {
    string sleepStr;
public:
    //delete all spaces
    string delSpaces(string &str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }

    explicit sleepCommand(string s) : sleepStr(s) {}

    // calc the num of mili' seconds and sleep
    int execute() {
        Interpreter *i = new Interpreter();
        Expression *e = nullptr;
        sleepStr = delSpaces(sleepStr);
        e = i->interpret(sleepStr);
        unsigned int time = e->calculate();
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        delete e;
        delete i;
        return 0;
    }

    string getName() {
        return "sleep";
    }
};

#endif //UNTITLED1_ALLCOMMANDS_H