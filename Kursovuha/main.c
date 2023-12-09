#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUF 1024
int main(){
	
	int call_protokol;
	
	struct sockaddr_in sock_info;
	
	//Создание сокета
	call_protokol = socket(PF_INET,SOCK_STREAM,0);
	if(call_protokol == -1){
		perror("Error creating socket");
	}
	
	
	
	
	
	
	
	
	
	
 return 0;	
}
