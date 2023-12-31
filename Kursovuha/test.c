#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUF 1024

int main() {
    int socket_descriptor, bytes_read;

    struct sockaddr_in server_info;

    socket_descriptor = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_descriptor == -1) {
        perror("Error creating socket");
        return 1;
    }

    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(80);
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");

    int connection = connect(socket_descriptor, (struct sockaddr*)&server_info, sizeof(server_info));
    if (connection == -1) {
        perror("Error connecting to server");
        return 1;
    } else {
        printf("Connected\n");
    }

    char request[MAXBUF];

    char response[MAXBUF];
    char method[8];
    printf("Enter method\n");
    printf("1. GET\n");
    printf("2. HEAD\n");
    printf("3. OPTIONS\n");
    printf("4. POST\n");
    printf("5. TRACE\n");
    printf("6. PUT\n");
    printf("7. DELETE\n");
    printf("Method number: ");
    fgets(method, sizeof(method), stdin);

    if (method[strlen(method) - 1] == '\n') {
        method[strlen(method) - 1] = '\0';
    }

    switch(method[0]) {
        case '1':
            snprintf(request, sizeof(request), "GET /mywebsite/ HTTP/1.1\r\nHost: %s\r\n\r\n", "localhost");
            break;
        case '2':
            snprintf(request, sizeof(request), "HEAD /mywebsite/ HTTP/1.1\r\nHost: %s\r\n\r\n", "localhost");
            break;
        case '3':
            snprintf(request, sizeof(request), "OPTIONS /mywebsite/ HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost");
            break;
        case '4':
            snprintf(request, sizeof(request), "POST / HTTP/1.1\r\nHost:%s\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 5\r\n\r\nHello\r\n\r\n", "localhost");
            break;
        case '5':
            snprintf(request, sizeof(request), "TRACE /mywebsite/ HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost"); //Head, Get, Post, Trace, Options
            break;
        case '6':
            snprintf(request, sizeof(request), "PUT /mywebsite/put.php HTTP/1.1\r\nHost: localhost\r\nContent-Type: text/plain\r\nContent-Length: 15\r\n\r\nHello, Server!\r\n"); // Работает через скрикт put.php
            break;
        case '7':
            snprintf(request, sizeof(request), "DELETE /mywebsite/ HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost");
            break;
        default:
            printf("Invalid method number\n");
            close(socket_descriptor);
            if (socket_descriptor == -1) {
                perror("Error closing socket");
            }
            return 1;
    }

    int bytes_sent = send(socket_descriptor, request, strlen(request), 0);
    if (bytes_sent == -1) {
        perror("Error sending request");
        return 1;
    }

    bytes_read = recv(socket_descriptor, response, sizeof(response), 0);
    if (bytes_read < 0) {
        perror("Error reading data");
        return 1;
    }

    printf("Response from server:\n");
    printf("%.*s\n", bytes_read, response);

    close(socket_descriptor);
    if (socket_descriptor == -1) {
        perror("Error closing socket");
    }

    return 0;
}
