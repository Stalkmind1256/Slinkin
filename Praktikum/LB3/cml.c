#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printHelp(){
	printf("Утилита cml - копирование/перемещение файлов и создание ссылок");
	printf("Использование:\n");
	printf("cml [-h|-l|-m] исходный_файл результирующий_файл\n");
	}

int fileCheck(char *filename){
 if(access(filename, F_OK) != -1){
  return 1;
 } 
 else{
  return 0;
 }
}


int main(int argc, char *argv[])
{
	
	if(argc !=4){
		printf("Ошибка не верное количество парамметров\n");
		printHelp();	
	}
	
	//char *command = argv[1];
	char *ishodnFile = argv[2];
	char *resfile = argv[3];
	
	
	if(!fileCheck(ishodnFile)){
		printf("Ошибка, исходного файла нет\n");
		}	
	
	FILE *source = fopen(ishodnFile,"rb");
	FILE *dest = fopen(resfile,"wb");
	//int sourceCount = argc - 1;
	
	if(source == NULL || dest == NULL){
		printf("Ошибка при открытии файлов.\n");
		return 1;
	}
	
	int ch;
	while((ch = fgetc(source)) !=EOF){
		fputc(ch,dest);
		}
	fclose(source);
	fclose(dest);
	
	return 0;
}

