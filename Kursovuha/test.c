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
	}
	else{
		printf("Connecting\n");
	}
	
	char request[MAXBUF];
	
	snprintf(request,sizeof(request), "GET /mywebsite/ HTTP/1.1\r\nHost:%s\r\n\r\n", "localhost");
	
	int bytes_send  = 	send(call_protocol, request, strlen(request),0);
	if(bytes_send == -1){
		perror("Error dending request");
		return 1;
		}
		
	char response[MAXBUF];
	
	bytes_read = recv(call_protocol,response,sizeof(response),0); //recv != read контролирует работу сокета ОТВЕТ
		if(bytes_read < 0){
			perror("Error reading data");
			return 1;
			}
	printf("Response from server:\n");
	printf("%.*s\n",bytes_read,response);	
	

	
	//Закрытик сокета
	close(call_protocol);
	if(call_protocol == -1){
		perror("Error closing socket");	
	}
	
	
	return 0;
}
