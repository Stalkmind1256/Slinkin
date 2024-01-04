
// Создание http клиента

//Клиентский алгоритм
/*
 * Создание сокета + 
 * Определение адреса сервера +
 * Подключение +
 * Чтение и отображение сообщенией
 * Разрыв соединения
 * 
 * int socket(domain, type, protocol);
 * struct sockaddr_in  
 * connect(sd,структура,длина структуры)
 * 
 * */

 // Добавить или нет? ввод IP/port
 // Нужен ли POST запрос?

#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXBUF 1024

//bool check_valid_ip(const char* ip){
	//	struct sockaddr_in sa;
	//	return inet_pton(AF_INET, ip, &(sa.sin_addr)) != 0;
	//}


int main() {
    int socket_descriptor, bytes_read;
  
    
    struct sockaddr_in server_info;
	char input_ip[16];
	char input_port[6];

	/*
	 * typedet struct sockaddr_in{
	 * short sin_family;
	 * unsigned short  sin_port;
	 * struct in_addr sin_addr;
	 * char sin_zero[8];
	 * }server_info;
	 * 
*/
	printf("Enter IP address: ");
	fgets(input_ip, sizeof(input_ip), stdin);
    input_ip[strcspn(input_ip, "\n")] = '\0';
    
  /*  while(!check_valid_ip(input_ip)){
		printf("Invalid IP addres: Please enter a valid IP address: ");
		fgets(input_ip,sizeof(input_ip),stdin);
		input_ip[strcspn(input_ip, "\n")] = '\0';
	}
    */
    
    
    printf("Enter PORT address: ");
	fgets(input_port, sizeof(input_port), stdin);
    input_port[strcspn(input_port, "\n")] = '\0';
    
  
    socket_descriptor = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_descriptor == -1) {
        perror("Error creating socket");
        return 1;  
    }
  
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
    
    while(true){
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
		
		
		if (method[strlen(method) - 1] == '\n') {
			method[strlen(method) - 1] = '\0';
    }
    
    
     if (strcmp(method, "8") == 0) {
		 printf("disconnect\n");
            break;
        }
    
    
    switch(method[0]) {
        case '1':
            snprintf(request, sizeof(request), "GET /mywebsite/put.php HTTP/1.1\r\nHost: %s\r\n\r\n", "localhost");// РАботает 
            break;
        case '2':
            snprintf(request, sizeof(request), "HEAD /mywebsite/put.php HTTP/1.1\r\nHost: %s\r\n\r\n", "localhost");// РАботает 
            break;
        case '3':
            snprintf(request, sizeof(request), "OPTIONS /mywebsite/put.php HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost");// РАботает 
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
	 if (bytes_sent == -1){
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
		
	}
		
  
    close(socket_descriptor);
    if (socket_descriptor == -1) {
        perror("Error closing socket");
    }
		

    return 0;
}
