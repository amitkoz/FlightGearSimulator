//
// Created by idan on 11/12/2019.
//

#ifndef UNTITLED1_SETVARCOMMAND_H
#define UNTITLED1_SETVARCOMMAND_H
#include "allCommands.h"
#include "Command.h"

class SetVarCommand  {
public:
    string type;
    std::size_t found;

    SetVarCommand(string _type) {
        this->type = _type;
    }
    // delete spaces
    string delSpaces(string &str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }
    // return command from a given var
    Command * getCo() {
        string temp;
        string name;
        found = type.find("->");
        if (found != std::string::npos) {
            name = type.substr(1, found-1);
            name = delSpaces(name);
        }
        found = type.find("<-");
        if (found != std::string::npos) {
            name = type.substr(1, found-1);
            name = delSpaces(name);

        }
        found = type.find("(");
        if (found != std::string::npos) {
            temp = type.substr(found + 1, type.size());
            found = temp.find(")");
            if (found != std::string::npos) {
                temp = temp.substr(0, found);
            }
        }
        found = type.find("\"");
        if (found != std::string::npos) {
            temp = type.substr(found + 1, type.size());
            found = temp.find("\"");
            if (found != std::string::npos) {
                temp = temp.substr(0, found);
            }
        }
        found = type.find("=");
        int flag = 0;
        if (found != std::string::npos) {
            flag = 1;
        }
        Command *op = new alltype();
        op->setName(name);
        if (!flag) {
            op->setPath(temp);
        } else {
            string str = type.substr(found + 1, type.size());
            op->setVal(str);
        }
        return op;
    }
};


#endif //UNTITLED1_SETVARCOMMAND_H