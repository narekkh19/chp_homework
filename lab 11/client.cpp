#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Creating socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connecting to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message to server
        send(sockfd, buffer, strlen(buffer), 0);

        memset(buffer, 0, BUFFER_SIZE);
        // Receive response from server
        int bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            printf("Server disconnected.\n");
            break;
        }

        printf("Server response: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
