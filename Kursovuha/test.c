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
  
#include <sys/socket.h> //Содержит прототипы функций
#include <sys/types.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUF 1024



int main(){
	
	int call_protocol,bytes_read;
	
	struct sockaddr_in server_info;
	//char input_ip[16];
	//char in_port[6];
	
	/*
	 * typedet struct sockaddr_in{
	 * short sin_family;
	 * unsigned short  sin_port;
	 * struct in_addr sin_addr;
	 * char sin_zero[8];
	 * }server_info;
	 * 
	 * 
	 * */
	//Создание сокета 
	//printf("Enter IP address: ");
	//fgets(input_ip, sizeof(input_ip), stdin);
    //input_ip[strcspn(input_ip, "\n")] = '\0';
	
	
	call_protocol = socket(PF_INET,SOCK_STREAM,0);
	if(call_protocol == -1){
		perror("Error creating socket");
		return 1;	
	}
	// Создание структуры для заполнения информации о сервере
	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(80);
	server_info.sin_addr.s_addr = inet_addr("127.0.0.1"); // inet_addr принимает строку и возвращает числовое значение в сетевом порядке байтов
	
	int connection;
	connection = connect(call_protocol,(struct sockaddr*)&server_info, sizeof(server_info));
	if(connection == -1){
		perror("Error with connecting server");
		return 1;
	}
	else{
		printf("Connecting\n");
	}
	
	char request[MAXBUF];
	
	//snprintf(request,sizeof(request), "GET /html/index.html/HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost");
	//printf("%s",request);
	
		
	char response[MAXBUF];
	char method[4]; // Добавление запроса PUT
	printf("Enter method\n");
	printf("1. GET\n");
	printf("2. HEAD\n");
	printf("3. DELETE\n");
	printf("4. POST\n");
	printf("Method number: ");
	fgets(method,sizeof(method),stdin);
	
	if (method[strlen(method) - 1] == '\n') {
        method[strlen(method) - 1] = '\0';
    }
    
	switch(method[0]){
		case '1':
			snprintf(request,sizeof(request), "GET /mywebsite/ HTTP/1.1\r\nHost: %s\r\n\r\n", "localhost");break;
		case '2':
			snprintf(request,sizeof(request), "HEAD /mywebsite/1.1\r\nHost:%s\r\n\r\n", "localhost");break;
		case '3':
			snprintf(request,sizeof(request), "DELETE /mywebsite/1.1\r\nHost:%s\r\n\r\n", "localhost");break;
		case '4':
			snprintf(request,sizeof(request), "POST /mywebsite/1.1\r\nHost:%s\r\n\r\n", "localhost");break;
		default:printf("Invalid method number\n");
		
		close(call_protocol);
		if (call_protocol == -1) {
			perror("Error closing socket");
		}
		return 1;		
}
	printf("%s",request); 
    
    int bytes_send  = 	send(call_protocol, request, sizeof(request),0);
	if(bytes_send == -1){
		perror("Error dending request");
		return 1;
		}
    
    
	
   bytes_read = recv(call_protocol, response, sizeof(response), 0);
    if (bytes_read < 0) {
        perror("Error reading data");
        return 1;
    }
    printf("Response from server:\n");
    printf("%.*s\n", bytes_read, response);

    

    return 0;
}
