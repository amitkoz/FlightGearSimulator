#ifndef UNTITLED1_OPENDATASERVER_H
#define UNTITLED1_OPENDATASERVER_H

#include "Command.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <arpa/inet.h>

class openDataServer {
    int client_socket;
    string port;
    int server;
public:
    openDataServer(string s) {
        this->port = s;
    }

    //open server
    int execute() {
        Interpreter *I = new Interpreter();
        server = socket(AF_INET, SOCK_STREAM, 0);
        if (server == -1) {
            cerr << "can't open server" << endl;
        }
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        Expression *e = I->interpret(this->port);
        address.sin_port = htons(e->calculate());
        if (bind(server, (struct sockaddr *) &address, sizeof(address)) == -1) {
            cerr << "can't bind server" << endl;
        }
        if (listen(server, 1) == -1) {
            cerr << "can't listen server" << endl;
        }
        client_socket = accept(server, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket == -1) {
            cerr << "can't accept client" << endl;
        }
        delete I;
        delete e;
        return 0;
    }

    //return information that sent from server
    string updateData() {
        char buffer[1024] = {0};
        int val = read(client_socket, buffer, 1024);
        if (val < 0) {
            perror("reading error");
            exit(1);
        }
        return buffer;
    }

    string getName() { return "openDataServer"; }

    // check connection
    int isConnect() {
        if (this->client_socket > 0) {
            return 1;
        } else {
            return -1;
        }
    }

    //change val of client socket
    void closeConnect() {
        this->client_socket = -1;
    }

    //close socket
    void closeIt() {
        close(server);
    }

};

#endif //UNTITLED1_OPENDATASERVER_H