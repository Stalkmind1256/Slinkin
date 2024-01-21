#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXBUF 1024

int main() {
    int socket_descriptor, bytes_read;
    struct sockaddr_in server_info;
    char input_ip[16];
    char input_port[6];

    socket_descriptor = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_descriptor == -1) {
        perror("Error creating socket");
        return 1;
    }

    printf("Enter IP address: ");
    fgets(input_ip, sizeof(input_ip), stdin);
    input_ip[strcspn(input_ip, "\n")] = '\0';

    printf("Enter PORT address: ");
    fgets(input_port, sizeof(input_port), stdin);
    input_port[strcspn(input_port, "\n")] = '\0';

    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(atoi(input_port));
    server_info.sin_addr.s_addr = inet_addr(input_ip);

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
    printf("8. EXIT\n");
    printf("Method number: ");
    fgets(method, sizeof(method), stdin);
    printf("--------------------------\n");
    printf("HEADERS ACTIV\n");
    printf("--------------------------\n");

    if (method[strlen(method) - 1] == '\n') {
        method[strlen(method) - 1] = '\0';
    }

    switch(method[0]) {
        case '1':
            sprintf(request, "GET /mywebsite/put.php HTTP/1.1\r\nHost: %s\r\nUser-Agent: Google\r\n\r\n", "localhost");
            break;
        case '2':
            snprintf(request, sizeof(request), "HEAD /mywebsite/put.php HTTP/1.1\r\nHost: %s\r\n\r\n", "localhost"); 
            break;
        case '3':
            snprintf(request, sizeof(request), "OPTIONS /mywebsite/put.php HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost"); 
            break;
        case '4':
            snprintf(request, sizeof(request), "POST /mywebsite/put.php HTTP/1.1\r\nHost:%s\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 14\r\n\r\nHello world!!!\r\n\r\n", "localhost");
            break;
        case '5':
            snprintf(request, sizeof(request), "TRACE /mywebsite/ HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost");
            break;
        case '6':
            snprintf(request, sizeof(request), "PUT /mywebsite/put.php HTTP/1.1\r\nHost: localhost\r\nContent-Type: text/plain\r\nContent-Length: 15\r\n\r\nHello, Server!\r\n");
            break;
        case '7':
            snprintf(request, sizeof(request), "DELETE /mywebsite/put.php HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost");
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

    bytes_read = recv(socket_descriptor, response, sizeof(response) - 1, 0);
	if (bytes_read < 0) {
		perror("Error reading data");
		return 1;
	}
	response[bytes_read] = '\0';

    //Обработка заголовка User-Agent из ответа
	char* userAgentHeader = strstr(response, "User-Agent: ");
	if (userAgentHeader != NULL) {  
    char* lineEnd = strchr(userAgentHeader, '\r');
    if (lineEnd != NULL) {
        int userAgentHeaderLength = lineEnd - (userAgentHeader + strlen("User-Agent: "));
        
        // Выделение динамической памяти для хранения значения User-Agent
        char* userAgentValue = (char*)malloc((userAgentHeaderLength + 1) * sizeof(char));
        strncpy(userAgentValue, userAgentHeader + strlen("User-Agent: "), userAgentHeaderLength);
        userAgentValue[userAgentHeaderLength] = '\0';

        printf("User-Agent Header: %s\n", userAgentValue);

        // Освобождение выделенной динамической памяти
        free(userAgentValue);
    }
	else {
		printf("User-Agent Header Not Found\n");
	}
}

	char* hostHeader = strstr(response, "Host: ");
	if (hostHeader != NULL) {
    char* lineEnd = strchr(hostHeader, '\r');
    if (lineEnd != NULL) {
        int hostHeaderLength = lineEnd - (hostHeader + strlen("Host: "));
        
        // Выделение динамической памяти для хранения значения заголовка Host
        char* hostValue = (char*)malloc((hostHeaderLength + 1) * sizeof(char));
        strncpy(hostValue, hostHeader + strlen("Host: "), hostHeaderLength);
        hostValue[hostHeaderLength] = '\0';

        printf("Host: %s\n", hostValue);

        // Освобождение выделенной динамической памяти
        free(hostValue);
    }
	}
	else {
		printf("Host Header Not Found\n");
	}

    // Вывод ответа от сервера
   printf("Response from server:\n");
	printf("%s\n", response);

    close(socket_descriptor);
    if (socket_descriptor == -1) {
        perror("Error closing socket");
    }

    return 0;
}
