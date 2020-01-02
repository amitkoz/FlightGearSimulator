#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <mutex>
#include "Lexer.h"
#include "Parser.h"

using namespace std;
std::mutex m;
openDataServer *server;

void readText(string fileName, list<string> &vec) {
    string line;
    fstream file;
    file.open(fileName, ios::in | ios::binary);
    if (!file.is_open()) {
        throw ("cant open file");
    }
    if (file.is_open()) {

        while (getline(file, line)) {
            vec.push_back(line);
        }
    } else {
        file.close();
        throw ("error");
    }

}

void getinfo(string port, map<string, Command *> *gMap) {
    server = new openDataServer(port);
    cout << "wait the server to connection" << endl;
    server->execute();
    ReadData *rd = new ReadData();
    rd->makeMap();
    while (server->isConnect() >= 0) {
        m.try_lock();
        //updated the given info
        string data = server->updateData();
        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
        *gMap = rd->setData(data);
        m.unlock();
    }
    delete rd;
    server->closeIt();
    delete server;
    return;
}

static void giveinfo(list<Command *> *glist, Parser *p, connectControlClient *c) {
    int flag = 0;
    while (c->isConnect() >= 0) {
        for (auto x:*glist) {
            m.try_lock();
            if (x->getName() == "while") {
                x->execute();
            } else if (x->getName() == "if") {
                x->execute();
            } else if (x->getName() == "sleep") {
                x->execute();
            } else if (x->getName() == "print") {
                x->execute();
            } else {
                string space = " ";
                if (x->valus.size() > 0) {
                    string num = *x->valus.begin();
                    string totalNum = p->stringFixer(num);
                    string s = "set" + space + x->getPath() + space + totalNum;
                    if (x->valus.size() > 1) {
                        x->valus.pop_front();
                    }
                    x->setVal(*x->valus.begin());
                    c->writeData(s);
                }
            }
            flag = 1;
            m.unlock();
        }
        if (flag == 1) {
            server->closeConnect();
            break;
        }
    }
    c->closeIt();
    delete c;
    return;
}

string delSpaces(string &str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

string getPort(list<string> *ls) {
    Interpreter *i = new Interpreter();
    ls->pop_front();
    string port = *ls->begin();
    Expression *e = i->interpret(delSpaces(port));
    ls->pop_front();
    int p = e->calculate();
    port = to_string(p);
    delete e;
    delete i;
    return port;
}

connectControlClient *getclient(list<string> *ls) {
    Interpreter *i = new Interpreter();
    ls->pop_front();
    string port = *ls->begin();
    ls->pop_front();
    string server = *ls->begin();
    Expression *e = i->interpret(delSpaces(server));
    int s = e->calculate();
    server = to_string(s);
    ls->pop_front();
    connectControlClient *c = new connectControlClient(server, port);
    delete i;
    delete e;
    return c;
}

int main(int argc, char *argv[]) {
    list<string> ls;
    readText(argv[1], ls);
    Lexer *lexer = new Lexer(ls);
    //new class
    ls = lexer->lex();
    string port1 = getPort(&ls);
    connectControlClient *c = getclient(&ls);
    Parser *pars = new Parser(ls, c);
    thread thread1(getinfo, port1, &pars->getinfoMap);
    while (pars->getinfoMap.size() == 0) {
        sleep(1);
    }
    c->execute();
    thread thread2(giveinfo, &pars->giveinfolist, pars, c);
    pars->parsIt();
    thread2.join();
    thread1.join();
    delete pars;
    delete lexer;
    return 0;
}