#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int fileExists(const char *filename) {
    int f1 = open(filename, O_RDONLY);
	if (f1 == -1){
		return 0;
	}
	close(f1);
	return 1;
    
}

int regularcheck(const char *file){
	struct stat fileStat;
	 if (stat(file, &fileStat) == 0) {
        if (S_ISREG(fileStat.st_mode)) {
        } else if (S_ISLNK(fileStat.st_mode)) {
        } else {
            printf("not regular/link \n");
            return 0;
        }
    } else {
        printf("error stat\n");
        return 0;
    }
    return 1;
}



int copy_file(const char *source_file, const char *result_file) {
    
	FILE *sourcefile = fopen(source_file, "rb");
	 if (sourcefile == NULL) {
        printf("error opening source %s\n",source_file);
        fclose(sourcefile);
        return -1;
    }
    FILE *resultfile = fopen(result_file, "wb+");
    if (resultfile == NULL) {
        printf("error opening result\n");
        fclose(sourcefile);
		fclose(resultfile);
        return -1;
    }
     char ch;
     while ((ch = fgetc(sourcefile)) != EOF) {
        fputc(ch, resultfile);
    }
	printf("file copied\n");
    fclose(sourcefile);
    fclose(resultfile);
    return 0;
}

void move_file(const char *source_file, const char *result_file) {
    rename(source_file,result_file);
	printf("file moved/renamed\n");
}

void hardlink(const char *source_file, const char *hardlink_file){
	if (link(source_file, hardlink_file) != 0) {
        printf("error create hard link\n");
    }else{
    printf("hard link created\n");
    }
}
void softlink(const char *source_file, const char *softlink_file){
	if (symlink(source_file, softlink_file) != 0) {
        printf("error create soft link\n");
    }else{
    printf("soft link created\n");
	}
}

int main(int argc, char *argv[]) {
	
	
	if (argc < 3 || argc > 4) {
        printf("how to use: ./as [-h|-l|-m] source_file result_file\n");
        return -1;
    }
    const char *source_file, *result_file;
    const char *option;
    if(argc==3){
		source_file = argv[1];
		result_file = argv[2];
	}else{
		source_file = argv[2];
		result_file = argv[3];
		option = argv[1];
    }
    if(!fileExists(source_file)){
		printf("file with name: '%s' not exists\n",source_file);
		return -1;
	}
	if(!regularcheck(source_file)){
		printf("file with name: '%s' not regular/link\n",source_file);
		return -1;
	}
		if(fileExists(result_file) && !regularcheck(result_file)){
		printf("file with name: '%s' not regular/link\n",result_file);
		return -1;
	}
	
	if(fileExists(result_file)){
		char del;
		printf("file with name: '%s' exists.\n",result_file);
		printf("delete file? (y/n) \n");
		scanf("%c", &del);
		if(del == 'y'){
		    unlink(result_file);
		}else{
		    printf("error\n");
		    return -1;
		}
	}
	
	if(argc == 3 ){
		copy_file(source_file, result_file);
		}else{
		if(strcmp(option,"-m")==0) move_file(source_file, result_file);
		else if(strcmp(option,"-l")==0) softlink(source_file, result_file);
		else if(strcmp(option,"-h")==0) hardlink(source_file, result_file);
		else printf("wrong argumentdef %s\n",option);
	}
	return 0;
}
