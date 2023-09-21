#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

	int count_char=0;
	int count_words =0;
	int count_lines=0;

void count(FILE *myfile){
	int tek;
	int pred=0;
		while ((tek = fgetc(myfile)) != EOF) {
		 count_char++;
		 if((tek<33)&(pred>=33)){
			 count_words++;
			 }
		 pred=tek;
		 if (tek == '\n') {
		   count_lines++;
		}
	}
}

void vivod(char* arg){
		if (!strcmp(arg,"-c")){
			printf("\n Количество байт = %d \n",count_char);
		}
		if (!strcmp(arg,"-w")){
			printf("\n Количесвто слов = %d \n",count_words);
		}
		if (!strcmp(arg,"-l")){
			printf("\n Количесвто строк = %d \n",count_lines);
		}
		if (!strcmp(arg,"0")){
			printf("\n Количество байт = %d \n Количесвто слов %d \n Количесвто строк %d \n",count_char, count_words, count_lines);
		} 
		if ((strcmp(arg,"-c"))&(strcmp(arg,"-w"))&(strcmp(arg,"-l"))&(strcmp(arg,"0"))){
			printf("неверный аругмент \n");
		}
			
	}

int main(int argc, char* argv[]) {
	FILE *file;

	switch(argc){
		case 1:
			file=stdin;
			count(file);
			vivod("0");
			break;
		case 2:
			if ((strcmp(argv[1],"-c"))&(strcmp(argv[1],"-w"))&(strcmp(argv[1],"-l"))){
				file=fopen(argv[1],"r");
				if(!file){ 
					printf("нет такого файла \n"); 
					return 0;
				}else{
					count(file);
					vivod("0");
				}
			}else{
				file=stdin;
				count(file);
				vivod("0");
				}
			break;
		case 3: 
			file=fopen(argv[2],"r");
			if(!file){ 
				printf("нет такого файла \n"); 
				return 0;
			}
			count(file);
			vivod(argv[1]);
			break;
		case 4: 
			file=fopen(argv[3],"r");
			if(!file){
				 printf("нет такого файла \n"); 
				 return 0;
			}
			count(file);
			vivod(argv[1]);
			vivod(argv[2]);
			break;
		case 5: 
			file=fopen(argv[4],"r");
			if(!file){
				 printf("нет такого файла \n"); 
				 return 0;
			}
			count(file);
			vivod(argv[1]);
			vivod(argv[2]);
			vivod(argv[3]);

			break;
		default: printf("ошибка ввода \n"); return 0;
	}
fclose(file);
return 0;
}
