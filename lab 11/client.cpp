#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <fstream>
#include <iostream>

#define PORT 8080

std::string name;
int sockfd;
char readbuf[1024];
char writebuf[1024];

std::ofstream outLog("outgoing.log", std::ios::app);
std::ofstream inLog("incoming.log", std::ios::app);

void* ThreadWrite(void* arg) {
    while (true) {
        std::string userInput;

        std::getline(std::cin, userInput);

        if (userInput.length() > sizeof(readbuf) - name.length() - 2) {
            userInput = userInput.substr(0, sizeof(readbuf) - name.length() - 2);
        }

        std::string message = name + " " + userInput;

        if (outLog.is_open()) {
            outLog << message << std::endl;
        }

        if (send(sockfd, message.c_str(), message.length() + 1, 0) == -1) { 
            perror("send");
            exit(1);
        }
    }
    return nullptr;
}

void* ThreadRead(void* arg) {
    while (true) {
        memset(readbuf, 0, sizeof(readbuf)); 

        int bytes_received = recv(sockfd, readbuf, sizeof(readbuf), 0);
        if (bytes_received <= 0) {
            perror("recv");
            exit(1);
        }

        std::string receivedMessage = readbuf;

        if (inLog.is_open()) {
            inLog << receivedMessage << std::endl;
        }

        std::cout << receivedMessage << std::endl;
    }
    return nullptr;
}

int main() {
    struct sockaddr_in sock;

    if (!outLog.is_open() || !inLog.is_open()) {
        std::cerr << "Error opening log files" << std::endl;
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    name += ":";

    sock.sin_family = AF_INET;
    sock.sin_port = htons(PORT);
    if (inet_aton("127.0.0.1", &sock.sin_addr) == 0) {
        perror("inet_aton");
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr*)&sock, sizeof(sock)) == -1) {
        perror("connect");
        exit(1);
    }

    if (send(sockfd, name.c_str(), name.length() + 1, 0) == -1) { 
        perror("send");
        exit(1);
    }

    pthread_t threadwrite, threadread;
    pthread_create(&threadwrite, nullptr, ThreadWrite, nullptr);
    pthread_create(&threadread, nullptr, ThreadRead, nullptr);
    pthread_join(threadwrite, nullptr);
    pthread_join(threadread, nullptr);

    outLog.close();
    inLog.close();
    close(sockfd);
    return 0;
}
