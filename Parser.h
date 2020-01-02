#ifndef UNTITLED1_PARSER_H
#define UNTITLED1_PARSER_H

using namespace std;

#include <mutex>
#include <algorithm>
#include <list>
#include <string>
#include <map>
#include <iostream>
#include <cstring>
#include "openDataServer.h"
#include "connectControlClient.h"
#include "SetVarCommand.h"
#include "allCommands.h"
#include "ReadData.h"
#include "While_and_If_Command.h"


class Parser : public Command {
    list<string> ls;
    map<string, string> varsMap = {};
    mutex m;

public:
    list<Command *> todelete;

    list<Command *> giveinfolist;
    map<string, Command *> getinfoMap = {};

    Parser(list<string> &list, connectControlClient *c) {
        this->ls = list;
        this->client = c;
    }

    // parser the text we got after lexer
    void parsIt() {
        for (list<string>::iterator it = ls.begin(); it != ls.end(); ++it) {
            if (*it == "var") {
                ++it;
                string type = *(it);
                size_t found = type.find("=");
                if (found != std::string::npos) {
                    string start = type.substr(1, found - 2);
                    string cheack = type.substr(found + 2, type.size());
                    string val = stringFixer(cheack);
                    varsMap[start] = {val};
                } else {
                    size_t found = type.find("->");
                    if (found != std::string::npos) {
                        SetVarCommand *se = new SetVarCommand(*it);
                        Command *op = se->getCo();
                        m.try_lock();
                        giveinfomap[op->getName()] = {op};
                        m.unlock();
                        delete se;
                    } else {
                        SetVarCommand *se = new SetVarCommand(*it);
                        Command *op = se->getCo();
                        this->test.push_back(op);
                        delete se;
                    }
                }
                continue;
            } else if (*it == "if") {
                list<string> check2;
                ++it;
                string range = *it;
                ++it;
                if (*it == "{") {
                    ++it;
                    while (*it != "}") {
                        string Do = setVar(*it);
                        check2.push_back(Do);
                        ++it;
                    }
                }
                Command *op = new IfCommand(range, check2, this);
                m.try_lock();
                this->giveinfolist.push_back(op);
                m.unlock();
                this->todelete.push_back(op);
            } else if (*it == "while") {
                list<string> check2;
                ++it;
                string range = *it;
                ++it;
                if (*it == "{") {
                    ++it;
                    while (*it != "}") {
                        string Do = setVar(*it);
                        check2.push_back(Do);
                        ++it;
                    }
                }

                Command *op = new WhileCommand(range, check2, this);
                this->todelete.push_back(op);
                m.try_lock();
                this->giveinfolist.push_back(op);
                m.unlock();
            } else if (*it == "Sleep") {
                ++it;
                string sleep = *it;
                sleepCommand *op = new sleepCommand(sleep);
                m.try_lock();
                this->giveinfolist.push_back(op);
                m.unlock();
                this->todelete.push_back(op);
            } else if (*it == "Print") {
                ++it;
                string toPrint = stringFixer(*it);
                printCommand *op = new printCommand(toPrint);
                m.try_lock();
                this->giveinfolist.push_back(op);
                m.unlock();
                this->todelete.push_back(op);
            } else {
                string name = *it;
                if (giveinfomap.find(name) != giveinfomap.end()) {
                    m.try_lock();
                    string comm = *it;
                    ++it;
                    string val = *it;
                    giveinfomap.find(comm)->second->setVal(val);
                    giveinfomap.find(comm)->second->valus.push_back(val);
                    this->giveinfolist.push_back(giveinfomap.find(comm)->second);
                    m.unlock();
                } else {
                    string comm = *it;
                    ++it;
                    string val = *it;
                    for (auto x:test) {
                        if (x->name == comm) {
                            x->setVal(val);
                        }
                    }
                }
            }
        }
    }

    //delete all spaces
    string delSpaces(string &str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }

    //check string and correct it to evaluation
    string stringFixer(string VAR) {
        for (auto x: giveinfomap) {
            m.try_lock();
            // Get the first occurrence
            size_t pos = VAR.find(x.second->name);
            // Repeat till end is reached
            while (pos != std::string::npos) {
                VAR.replace(pos, x.second->name.size(), x.second->getVal());
                pos = VAR.find(x.second->name, pos + x.second->getVal().size());
                VAR = delSpaces(VAR);
            }
            m.unlock();
        }
        for (auto y : test) {
            m.try_lock();
            string path = y->getPath();
            for (auto x:  getinfoMap) {
                if (x.second->getPath() == path) {
                    y->setVal(x.second->getVal());
                    break;
                }
            }
            // Get the first occurrence
            size_t pos = VAR.find(y->name);
            // Repeat till end is reached
            while (pos != std::string::npos) {
                VAR.replace(pos, y->name.size(), y->getVal());
                pos = VAR.find(y->name, pos + y->getVal().size());
                VAR = delSpaces(VAR);
            }
            m.unlock();
        }
        for (auto x:  varsMap) {
            // Get the first occurrence
            size_t pos = VAR.find(x.first);
            // Repeat till end is reached
            while (pos != std::string::npos) {
                VAR.replace(pos, x.first.size(), x.second);
                pos = VAR.find(x.first, pos + x.second.size());
                VAR = delSpaces(VAR);
            }
        }
        return VAR;
    }

    int execute() { return 0; };

    string setVar(string s) {
        for (auto x:  varsMap) {
            // Get the first occurrence
            size_t pos = s.find(x.first);
            // Repeat till end is reached
            while (pos != std::string::npos) {
                s.replace(pos, x.first.size(), x.second);
                pos = s.find(x.first, pos + x.second.size());
                s = delSpaces(s);
            }
        }
        return s;
    }

    string getName() { return "Parser"; };

    // destructor
    ~Parser() {
        for (auto y:giveinfomap) {
            if (y.second != NULL) {
                delete y.second;
            }
        }
        for (auto z:test) {
            if (z != NULL) {
                delete z;
            }
        }
        for (auto x:todelete) {
            delete x;
        }
    }
};


#endif //UNTITLED1_PARSER_H