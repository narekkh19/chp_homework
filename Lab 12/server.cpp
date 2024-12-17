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
#include <vector>

#define PORT 8080
#define MAX_CLIENT 3

typedef struct info {
    struct sockaddr_in ip;
    int newfd;
    char name[20];
} info;

info Clients[MAX_CLIENT];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
std::ofstream logfile;

void LogMessage(const std::string& message) {
    pthread_mutex_lock(&lock);
    if (logfile.is_open()) {
        logfile << message << std::endl;
    }
    pthread_mutex_unlock(&lock);
}

void* FunctionThread(void* arg) {
    info* ptr = (info*)arg;

    while (true) {
        char readbuf[1024];
        memset(readbuf, 0, sizeof(readbuf));

        int bytes_received = recv(ptr->newfd, readbuf, sizeof(readbuf), 0);
        if (bytes_received <= 0) {
            if (bytes_received == 0) {
                printf("%s disconnected.\n", ptr->name);
            } else {
                perror("recv");
            }

            close(ptr->newfd);
            LogMessage(std::string(ptr->name) + " disconnected.");
            break;
        }

        std::string receivedMessage = std::string(ptr->name) + ": " + std::string(readbuf);
        printf("Received: %s\n", receivedMessage.c_str());
        LogMessage(receivedMessage);

        pthread_mutex_lock(&lock);

        for (int i = 0; i < MAX_CLIENT; i++) {
            if (Clients[i].newfd != ptr->newfd && Clients[i].newfd > 0) {
                if (send(Clients[i].newfd, readbuf, bytes_received, 0) == -1) {
                    perror("send");
                    close(Clients[i].newfd);
                    Clients[i].newfd = 0; 
                }
            }
        }

        pthread_mutex_unlock(&lock);
    }

    return nullptr;
}

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;

    logfile.open("server_log.txt", std::ios::app);
    if (!logfile.is_open()) {
        std::cerr << "Failed to open server log file." << std::endl;
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, MAX_CLIENT) == -1) {
        perror("listen");
        exit(1);
    }

    printf("Server is running and waiting for connections...\n");

    for (int i = 0; i < MAX_CLIENT; i++) {
        socklen_t clientSize = sizeof(serverAddr);
        Clients[i].newfd = accept(sockfd, (struct sockaddr*)&serverAddr, &clientSize);

        if (Clients[i].newfd == -1) {
            perror("accept");
            continue;
        }

        if (recv(Clients[i].newfd, Clients[i].name, sizeof(Clients[i].name), 0) == -1) {
            perror("recv");
            exit(1);
        }

        printf("%s connected\n", Clients[i].name);
        LogMessage(std::string(Clients[i].name) + " connected.");

        pthread_t thread;
        pthread_create(&thread, nullptr, FunctionThread, (void*)&Clients[i]);
    }

    while (true) {
        sleep(1);
    }

    close(sockfd);
    logfile.close();
    return 0;
}
