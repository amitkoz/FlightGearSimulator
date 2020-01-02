#ifndef UNTITLED1_CONNECTCONTROLCLIENT_H
#define UNTITLED1_CONNECTCONTROLCLIENT_H

#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <arpa/inet.h>
#include <cstring>

class connectControlClient {
    int client_socket;
    int is_connect;
    string port;
    string server;
public:


    connectControlClient(string _port, string _server) {
        this->port = _port;
        this->server = _server;
        this->server.erase(std::remove(this->server.begin(), this->server.end(), '\"'), this->server.end());
    }

    void writeData(string s) {
        string send = s + "\r\n";
        //Send message to the server
        int n = write(client_socket, send.c_str(), send.size());
        if (n < 0) {
            cerr << "ERROR writing to socket";
            exit(1);
        }
    }

    //connect as a client to the server
    int execute() {
        Interpreter *I = new Interpreter();
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1) {
            cerr << "can't open server" << endl;
            return -1;
        }
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(this->server.c_str());
        Expression *e = I->interpret(this->port);
        address.sin_port = htons(e->calculate());
        is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
        if (is_connect == -1) {
            cerr << "can't connect server" << endl;
            return -2;
        }
        delete I;
        delete e;
        return 0;
    }

    // close socket
    void closeIt() {
        close(client_socket);
    }

    //check if we connect
    int isConnect() {
        return is_connect;
    }

    string getName() { return "connectControlClient"; }
};

#endif //UNTITLED1_CONNECTCONTROLCLIENT_H