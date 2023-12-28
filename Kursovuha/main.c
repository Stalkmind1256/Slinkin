#define MAXBUF 1024
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int call_protocol, bytes_read;
    struct sockaddr_in server_info;
    call_protocol = socket(PF_INET, SOCK_STREAM, 0);
    if (call_protocol == -1) {
        perror("Error creating socket");
        return 1;
    }
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(80);
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    int connection = connect(call_protocol,(struct sockaddr*)&server_info, sizeof(server_info));
    if (connection == -1) {
        perror("Error with connecting server");
        return 1;
    } else {
        printf("Connecting\n");
    }
    char request[MAXBUF];
    char method[4];
    printf("Select the request method:\n");
    printf("1. GET\n");
    printf("2. PUT\n");
    printf("Enter the method number: ");
    fgets(method, sizeof(method), stdin);
    if (method[strlen(method) - 1] == '\n') {
        method[strlen(method) - 1] = '\0';
    }
    switch (method[0]) {
        case '1':
            snprintf(request, sizeof(request), "GET /html/index.html/HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost");
            break;
        case '2':
            snprintf(request, sizeof(request), "PUT /html/index.html/HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost");
            break;
        default:
            printf("Invalid method number. Exiting...\n");
            close(call_protocol);
            return 1;
    }
    printf("%s",request);
    int bytes_send = send(call_protocol, request, sizeof(request), 0);
    if (bytes_send == -1) {
        perror("Error sending request");
        return 1;
    }
    char response[MAXBUF];
    bytes_read = recv(call_protocol, response, sizeof(response), 0);
    if (bytes_read < 0) {
        perror("Error reading data");
        return 1;
    }
    printf("Response from server:\n");
    printf("%.*s\n", bytes_read, response);
    close(call_protocol);
    if (call_protocol == -1) {
        perror("Error closing socket");
    }
    return 0;
}
