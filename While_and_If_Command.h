#ifndef UNTITLED1_WHILE_AND_IF_COMMAND_H
#define UNTITLED1_WHILE_AND_IF_COMMAND_H

#include <array>
#include "allCommands.h"

//while type command
class WhileCommand : public Command {

private:
    string range;
    list<string> todo;
    Command *p;
    array<double, 2> arr;

public:
    WhileCommand(string _range, list<string> _todo, Command *_p) {
        this->range = _range;
        this->todo = _todo;
        this->p = _p;
    }

    string getName() {
        return "while";
    }

    // set the range of while loop
    array<double, 2> setRnge(string s) {
        string temp = this->range;
        temp = this->p->stringFixer(temp);
        size_t found = temp.find(s);
        Interpreter *I = new Interpreter();
        string start = temp.substr(0, found);
        string end = temp.substr(found + s.size(), temp.size());
        Expression *e1 = I->interpret(start);
        double x = e1->calculate();
        arr[0] = x;
        Expression *e2 = I->interpret(end);
        double y = e2->calculate();
        arr[1] = y;
        delete I;
        delete e1;
        delete e2;
        return arr;
    }

    // while range is true, do all the commands inside the while loop
    int execute() {
        size_t found = this->range.find("<=");
        if (found != std::string::npos) {
            arr = setRnge("<=");
            double x = arr[0];
            double y = arr[1];
            while (x <= y) {
                doInwhile();
                arr = setRnge("<=");
                x = arr[0];
                y = arr[1];
            }
            return 0;
        } else if ((found = this->range.find(">=")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge(">=");
                double x = arr[0];
                double y = arr[1];
                while (x >= y) {
                    doInwhile();
                    arr = setRnge(">=");
                    x = arr[0];
                    y = arr[1];
                }
                return 0;
            }
        } else if ((found = this->range.find(">")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge(">");
                double x = arr[0];
                double y = arr[1];
                while (x > y) {
                    doInwhile();
                    arr = setRnge(">");
                    x = arr[0];
                    y = arr[1];
                }
                return 0;
            }
        } else if ((found = this->range.find("<")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge("<");
                double x = arr[0];
                double y = arr[1];
                while (x < y) {
                    doInwhile();
                    arr = setRnge("<");
                    x = arr[0];
                    y = arr[1];
                }
                return 0;
            }
        } else if ((found = this->range.find("!=")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge("!=");
                double x = arr[0];
                double y = arr[1];
                while (x != y) {
                    doInwhile();
                    arr = setRnge("!=");
                    x = arr[0];
                    y = arr[1];
                }
                return 0;
            }

        } else if ((found = this->range.find("==")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge("==");
                double x = arr[0];
                double y = arr[1];
                while (x == y) {
                    doInwhile();
                    arr = setRnge("==");
                    x = arr[0];
                    y = arr[1];
                }
                return 0;
            }
        }
        return 0;
    }

    // check if string is valid
    string cheakValid(string num) {
        size_t pos = num.find("--");
        while (pos != std::string::npos) {
            num.replace(pos, 2, "+");
            pos = num.find("--", pos + 1);
        }
        pos = num.find("++");
        while (pos != std::string::npos) {
            num.replace(pos, 2, "+");
            pos = num.find("++", pos + 1);
        }
        return num;
    }

    // do all the commands inside while loop
    void doInwhile() {
        for (std::list<string>::iterator it = todo.begin(); it != todo.end(); ++it) {
            if (*it == "Print") {
                ++it;
                string s = *it;
                s = this->p->stringFixer(s);
                Command *c = new printCommand(s);
                c->execute();
                delete c;
            } else if (*it == "Sleep") {
                ++it;
                string s = *it;
                s = this->p->stringFixer(s);
                Command *c = new sleepCommand(*it);
                c->execute();
                delete c;
            } else {
                for (auto y: this->p->giveinfomap) {
                    if (*it == y.second->name) {
                        Interpreter *i = new Interpreter();
                        Command *c = y.second;
                        ++it;
                        string num = this->p->stringFixer(*it);
                        num = cheakValid(num);
                        Expression *e = i->interpret(num);
                        num = to_string(e->calculate());
                        y.second->setVal(num);
                        string space = " ";
                        string s = "set" + space + c->getPath() + space + num;
                        this->p->client->writeData(s);
                        delete i;
                        delete e;
                        continue;
                    }
                }
            }
        }
    }
};

// if type command
class IfCommand : public Command {
private:
    string range;
    list<string> todo;
    Command *p;
    array<double, 2> arr;


public:
    IfCommand(string _range, list<string> _todo, Command *_p) {
        this->range = _range;
        this->todo = _todo;
        this->p = _p;
    }

    string getName() {
        return "if";
    }

    // set the range of if command
    array<double, 2> setRnge(string s) {
        string temp = this->range;
        temp = this->p->stringFixer(temp);
        size_t found = temp.find(s);
        Interpreter *I = new Interpreter();
        string start = temp.substr(0, found);
        string end = temp.substr(found + s.size(), temp.size());
        Expression *e1 = I->interpret(start);
        double x = e1->calculate();
        arr[0] = x;
        Expression *e2 = I->interpret(end);
        double y = e2->calculate();
        arr[1] = y;
        delete I;
        delete e1;
        delete e2;
        return arr;
    }

    // if range in true, do all command in if command
    int execute() {

        size_t found = this->range.find("<=");
        if (found != std::string::npos) {
            arr = setRnge("<=");
            double x = arr[0];
            double y = arr[1];
            if (x <= y) {
                doInwhile();
                arr = setRnge("<=");
            }
            return 0;
        } else if ((found = this->range.find(">=")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge(">=");
                double x = arr[0];
                double y = arr[1];
                if (x >= y) {
                    doInwhile();
                    arr = setRnge(">=");
                }
                return 0;
            }
        } else if ((found = this->range.find(">")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge(">");
                double x = arr[0];
                double y = arr[1];
                if (x >= y) {
                    doInwhile();
                    arr = setRnge(">");
                }
                return 0;
            }

        } else if ((found = this->range.find("<")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge("<");
                double x = arr[0];
                double y = arr[1];
                if (x < y) {
                    doInwhile();
                    arr = setRnge("<");
                }
                return 0;
            }
        } else if ((found = this->range.find("!=")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge("!=");
                double x = arr[0];
                double y = arr[1];
                if (x != y) {
                    doInwhile();
                    arr = setRnge("!=");
                }
                return 0;
            }

        } else if ((found = this->range.find("==")) != std::string::npos) {
            if (found != std::string::npos) {
                arr = setRnge("==");
                double x = arr[0];
                double y = arr[1];
                if (x == y) {
                    doInwhile();
                    arr = setRnge("==");
                }
                return 0;
            }
        }
        return 0;
    }

    // check if the string is valid
    string cheakValid(string num) {
        size_t pos = num.find("--");
        while (pos != std::string::npos) {
            num.replace(pos, 2, "+");
            pos = num.find("--", pos + 1);
        }
        pos = num.find("++");
        while (pos != std::string::npos) {
            num.replace(pos, 2, "+");
            pos = num.find("++", pos + 1);
        }
        return num;
    }

    //do all the commands inside if command
    void doInwhile() {
        for (std::list<string>::iterator it = todo.begin(); it != todo.end(); ++it) {
            if (*it == "Print") {
                ++it;
                string s = *it;
                s = this->p->stringFixer(s);
                Command *c = new printCommand(s);
                c->execute();
                delete c;
            } else if (*it == "Sleep") {
                ++it;
                string s = *it;
                s = this->p->stringFixer(s);
                Command *c = new sleepCommand(*it);
                c->execute();
                delete c;
            } else {
                for (auto y: this->p->giveinfomap) {
                    if (*it == y.second->name) {
                        Interpreter *i = new Interpreter();
                        Command *c = y.second;
                        ++it;
                        string num = this->p->stringFixer(*it);
                        num = cheakValid(num);
                        Expression *e = i->interpret(num);
                        num = to_string(e->calculate());
                        y.second->setVal(num);
                        string space = " ";
                        string s = "set" + space + c->getPath() + space + num;
                        this->p->client->writeData(s);
                        delete i;
                        delete e;
                        continue;
                    }
                }
            }
        }
    }
};


#endif //UNTITLED1_WHILE_AND_IF_COMMAND_H