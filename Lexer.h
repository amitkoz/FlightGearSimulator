#ifndef UNTITLED1_LEXER_H
#define UNTITLED1_LEXER_H
using namespace std;

#include <list>
#include <string>
#include <array>
#include <algorithm>

class Lexer {
    list<string> ls;
public:
    Lexer(list<string> &list) {
        this->ls = list;
    }

    string delSpaces(string &str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }

    //get list of string and lexer it by our definition
    list<string> lex() {
        int size = this->ls.size();
        for (int i = 0; i < size; i++) {
            std::list<string>::iterator it = this->ls.begin();
            string temp = *it;
            std::size_t found = temp.find("\t");
            if (found != std::string::npos) {
                temp.erase(found, found + 1);
            }
            this->ls.pop_front();
            if ((found = temp.find("while")) != std::string::npos) {
                this->ls.push_back("while");
                string lineStart = temp.erase(found, 5);
                found = temp.find("{");
                if (found != std::string::npos) {
                    string lineEnd = lineStart.substr(0, found);
                    this->ls.push_back(lineEnd);
                    this->ls.push_back("{");
                    temp = "";
                }
            }
            found = temp.find("}");
            if (found != std::string::npos) {
                this->ls.push_back("}");
                temp = "";
            }
            if ((found = temp.find("if")) != std::string::npos) {
                this->ls.push_back("if");
                string lineStart = temp.erase(found, 2);
                found = temp.find("{");
                if (found != std::string::npos) {
                    string lineEnd = lineStart.substr(0, found);
                    this->ls.push_back(lineEnd);
                    this->ls.push_back("{");
                    temp = "";
                }
            }
            found = temp.find("}");
            if (found != std::string::npos) {
                this->ls.push_back("}");
                temp = "";
            }
            if ((found = temp.find("openDataServer")) != std::string::npos) {
                string lineEnd = temp.erase(found, 14);
                found = temp.find("(");
                lineEnd = temp.erase(0, found + 1);
                found = temp.find(")");
                lineEnd = temp.substr(0, found);
                this->ls.push_back("openDataServer");
                this->ls.push_back(lineEnd);
                temp = "";
            }
            if ((found = temp.find("connectControlClient")) != std::string::npos) {
                string lineEnd = temp.erase(found, 20);
                lineEnd.erase(lineEnd.begin());
                lineEnd.erase(lineEnd.end() - 1);
                this->ls.push_back("connectControlClient");
                std::size_t find = lineEnd.find(",");
                if (found != std::string::npos) {
                    string lineEnd2 = lineEnd.substr(0, find);
                    lineEnd = lineEnd.substr(find + 1, lineEnd.size());
                    this->ls.push_back(lineEnd2);
                    this->ls.push_back(lineEnd);
                }
                temp = "";
            }
            found = temp.find("var");
            if (found != std::string::npos) {
                string lineStart = temp.erase(found, 3);
                this->ls.push_back("var");
                this->ls.push_back(temp);
                temp = "";
            }
            found = temp.find("Print");
            if (found != std::string::npos) {
                string lineEnd = temp.erase(found, 5);
                found = temp.find("(");
                lineEnd = temp.erase(0, found + 1);
                found = temp.find(")");
                lineEnd = temp.substr(0, found);
                this->ls.push_back("Print");
                this->ls.push_back(lineEnd);
                temp = "";
            }
            found = temp.find("Sleep");
            if (found != std::string::npos) {
                string lineEnd = temp.erase(found, 5);
                found = temp.find("(");
                lineEnd = temp.erase(0, found + 1);
                found = temp.find(")");
                lineEnd = temp.substr(0, found);
                this->ls.push_back("Sleep");
                this->ls.push_back(delSpaces(lineEnd));
                temp = "";
            }
            found = temp.find("=");
            if (found != std::string::npos) {
                string lineStart = temp.substr(0, found);
                lineStart = delSpaces(lineStart);
                string lineEnd = temp.substr(found + 1, this->ls.size());
                lineEnd = delSpaces(lineEnd);
                this->ls.push_back(lineStart);
                this->ls.push_back(lineEnd);
                temp = "";
            }

        }

        return this->ls;
    }

};


#endif //UNTITLED1_LEXER_H