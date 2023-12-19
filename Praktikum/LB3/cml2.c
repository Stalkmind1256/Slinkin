#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
 
void printHelp(){
	printf("Утилита cml - копирование/перемещение файлов и создание ссылок\n");
	printf("Использование:\n");
	printf("cml [-h|-l|-m] исходный_файл результирующий_файл\n");
}


 
 
int main(int argc, char *argv[]){
	if(argc != 4){
		printf("Ошибка не верное количество параметров\n");
		printHelp();
		return 1;
	}
	
	char *options = argv[1];
	char *soursefile = argv[2];
	char *resfile = argv[3];
	
	//Проверка сущ файла
	if(access(soursefile,F_OK) == -1){
		printf("Ошибка: файл не существует\n");
        return 1;
		}
	
	if(access(resfile,F_OK) == -1){
		struct stat st;
		stat(resfile, &st);
		
		if(S_ISREG(st.st_mode)|| S_ISLNK(st.st_mode)){
			
			char choice;
			printf("Файл %s существует. Вы хотите удалить? (Y/N)\n",resfile);
			scanf("%c",&choice);
			if(choice != 'y' && choice != 'Y'){
				return 0;
				}
				unlink(resfile);
		}
		else{
			printf("Ошибка:Результирующий файл не является регулярным или ссылкой\n");
			}
		
		
		}
	
	if(strcmp(options,"-h")!=0 && strcmp(options,"-l") !=0 && strcmp(options,"-m")!=0){
		printf("Ошибка не верный параметр\n");
		printHelp();
		return 1;
		}
	
	if(strcmp(options,"-h") == 0){
			if(link(soursefile,resfile) == 0){
				printf("Жесткая ссылка создана успешно\n");
			}
			else{
				printf("Ошибка: Жесткая ссылка не создана\n");
				}
	}else if(strcmp(options,"-l") == 0){
		if(symlink(soursefile,resfile) == 0){
			printf("Символьная ссылка создана успешно\n");
		}else{
			printf("Ошибка: Символьная ссылка не создана\n");
			}
	}else if(strcmp(options,"-m") == 0){
		if(rename(soursefile, resfile) == 0){
			printf("Файл успешно переименован\n");
		}else{
			printf("Ошибка: переименования файла\n");
			}
	}else{
		FILE *sourse = fopen(soursefile,"rb");
		FILE *dest = fopen(resfile,"wb");
	
	if(sourse == NULL || dest == NULL){
		printf("Ошибка при открытии файлов\n");
		return 1;
		}
	int ch;
	while((ch = fgetc(sourse))!= EOF){
		fputc(ch,dest);
		}
	fclose(sourse);
	fclose(dest);
	printf("Копирование прошло успешно\n");	
}
	

	return 0;
	}
