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
#include <sys/socket.h> //Содержит прототипы функций
#include <sys/types.h>
#include <resolv.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int main(){
	int call_protocol, byte_read; // Созадние сокета
	struct sockaddr_in server_info;
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
	 
	call_protocol = socket(PF_INET,SOCK_STREAM,0);
	if(call_protocol == -1){
		perror("Error creating socket");
		return -1;	
	}
	// Создание структуры для заполнения информации о сервере
	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(80);
	server_info.sin_addr.s_addr = inet_addr("127.0.0.1"); // inet_addr принимает строку и возвращает числовое значение в сетевом порядке байтов
	
	int connection;
	connection = connect(call_protocol,(struct sockaddr*)&server_info, sizeof(server_info));
	if(connection == -1){
		perror("Error with connecting server");
	}//else{ printf("Connect :)");}
	
	char buffer[BUFFER_SIZE];
	while((byte_read = read(call_protocol,buffer,BUFFER_SIZE - 1)) > 0){
		buffer[byte_read] = '\0';
		printf("%s",buffer);
	}
	if(byte_read == -1){
		perror("Error reading response");
		close(call_protocol);
		return -1;
	}
	
	if(byte_read == 0){
		perror("Error closing conecting");
	}
	
	int status = close(call_protocol);
	if(status == -1){
		perror("Error closing socket");	
	}
	
	
	return 0;
}
