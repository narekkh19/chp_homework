#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_size;
    char buffer[BUFFER_SIZE];

    // Creating socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Binding the socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listening for connections
    if (listen(sockfd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d...\n", PORT);

    while (1) {
        client_size = sizeof(client_addr);
        if ((new_sock = accept(sockfd, (struct sockaddr *)&client_addr, &client_size)) < 0) {
            perror("accept");
            continue;
        }

        printf("Client connected\n");

        // Communication with the client
        while (1) {
            memset(buffer, 0, BUFFER_SIZE);
            int bytes_received = recv(new_sock, buffer, BUFFER_SIZE, 0);
            if (bytes_received <= 0) {
                printf("Client disconnected.\n");
                break;
            }

            printf("Received: %s\n", buffer);

            // Echo back to the client
            send(new_sock, buffer, bytes_received, 0);
        }

        close(new_sock);
    }

    close(sockfd);
    return 0;
}
