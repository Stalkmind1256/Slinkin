#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void printHelp(){
    printf("Cml utility - copy/move files and create links\n");
    printf("Usage:\n");
    printf("cml [-h|-l|-m] source_file result_file\n");
}

int fileExists(char *filename){
    if(access(filename, F_OK) != -1){
        return 1;
    } 
    else{
        return 0;
    }
}

int isRegularFile(char *filename){
    struct stat st;
    if(stat(filename, &st) == 0){
        if(S_ISREG(st.st_mode)){
            return 1;
        }
        else{
            return 0;
        }
    } 
    return 0;
}

int isLink(char *filename){
    struct stat st;
    if(stat(filename, &st) == 0){
        if(S_ISLNK(st.st_mode)){
            return 1;
        }
        else{
            return 0;
        }
    } 
    else{
        return 0;
    }
}

int confirmDeletion(char *filename){
    char choice;
    printf("File %s exists. Do you want to delete it? (y/n): ", filename);
    scanf(" %c", &choice);
    if(choice == 'y' || choice == 'Y'){
        unlink(filename);
        return 1;
    }
    else{
        printf("error\n");
		    return 0;
    }
}

void copyFile(char *sourceFile, char *destFile){
    FILE *source = fopen(sourceFile, "rb");
    if(source == NULL){
        printf("Error opening source file.\n");
        return;
    }
    
    FILE *dest = fopen(destFile, "wb");
    if(dest == NULL){
        fclose(source);
        printf("Error opening result file.\n");
        return;
    }
    
    int ch;
    while((ch = fgetc(source)) != EOF){
        fputc(ch, dest);
    }
    
    fclose(source);
    fclose(dest);
    
    printf("File copied successfully.\n");
}

void moveFile(char *sourceFile, char *destFile){
    if(rename(sourceFile, destFile) == 0){
        printf("File moved successfully.\n");
    }
    else{
        printf("Error moving file.\n");
    }
}

void createHardLinkCustom(char *sourceFile, char *links){
    if(link(sourceFile, links) == 0){
        printf("Hard link created successfully.\n");
    }
    else{
        printf("Error creating hard link.\n");
    }
}

void createSymbolicLink(char *sourceFile, char *link){
    if(symlink(sourceFile, link) == 0){
        printf("Symbolic link created successfully.\n");
    }
    else{
        printf("Error creating symbolic link.\n");
    }
}

int main(int argc, char *argv[]){
    if(argc < 3 || argc > 4){
        printf("Error: incorrect number of parameters\n");
        printHelp(); 
        return 1;
    }
    
    char *options = argv[1];
    char *sourceFile;
    char *destFile;
    
    if(argc == 3){
        sourceFile = argv[1];
        destFile = argv[2];
    }
    else{
		if(argc == 4 && strcmp(options, "-h") != 0 && strcmp(options, "-l") != 0 && strcmp(options, "-m") != 0){
        printf("Error: invalid option\n");
        printHelp();
        return 1;
      }else{
		options = argv[1];
        sourceFile = argv[2];
        destFile = argv[3];
    
		  } 
        
}
    if(!fileExists(sourceFile)){
        printf("Error: source file does not exist\n");
        return 1;
    }
    if(!isRegularFile(sourceFile) && !isLink(sourceFile)){
        printf("Error: source file is not a regular file or a link\n");
        return 1;
    }
    
    if(fileExists(destFile)){
        if(!isRegularFile(destFile) && !isLink(destFile)){ 
    
     printf("Error: destination file is not a regular file or a link\n");
            return 1;
        }
        else{
            if(!confirmDeletion(destFile)){ 
                return 0;
            }
        }
    }
    
    if(argc == 3 ){
		 copyFile(sourceFile, destFile);
		}
    else if(strcmp(options, "-h") == 0){
        createHardLinkCustom(sourceFile, destFile);
    }
    else if(strcmp(options, "-l") == 0){

        createSymbolicLink(sourceFile, destFile);
    }
    else if(strcmp(options, "-m") == 0){
        moveFile(sourceFile, destFile);
    }else{
		printHelp();
		}
    
    return 0;
}
