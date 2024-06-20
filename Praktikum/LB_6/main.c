#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>

int pam = 2;

typedef struct {
    char name[50];
    int count;
} statserver;

void parse_logfile(char* filename, statserver* server, int* servercount){
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s.\n", filename);
        return;
    }
    char line[4000];
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file)!=NULL){
        int exist = 0;
        char* token = strtok(line, ";");
        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ";");
        }
        for (int i = 0; i < *servercount; i++) {
            if (strcmp(server[i].name, token) == 0) {
                server[i].count += 1;
                exist = 1;
                continue;
            }
        }
        if (!exist) {
            if (*servercount < pam) {
                strcpy(server[*servercount].name, token);
                server[*servercount].count = 1;
                (*servercount)++;
            } else {
                server = realloc(server, (pam) * 1.5 * sizeof(statserver));
                pam = pam * 1.5;
                strcpy(server[*servercount].name, token);
                server[*servercount].count = 1;
                (*servercount)++;
            }	
        }
    }
    fclose(file);
}

void update_result_file(char* resultfile, char* sourse, statserver* server, int servercount)
{
    FILE* block = fopen(sourse,"r");
    //printf("Попытка блокировки файла %s процессом с PID %d\n", sourse, getpid());
    flock(fileno(block), LOCK_EX);
    //printf("Файл %s заблокирован процессом с PID %d\n", sourse, getpid());
    FILE* result = fopen(resultfile, "r");

    statserver checkresult;
    while(fscanf(result, "%[^:]: %d\n",checkresult.name,&checkresult.count)==2){
        int exist = 0;
        int i = 0;
        for(i=0; i<servercount; i++){
            if(strcmp(checkresult.name,server[i].name)==0){
                exist = 1;
                break;
            }

        }
        
       if(!exist){
        if (servercount < pam) {
            strcpy(server[servercount].name,checkresult.name);
            server[servercount].count = checkresult.count;
            servercount++;
        } else {
            server = realloc(server, (pam) * 1.5 * sizeof(statserver));
            pam = pam * 1.5;
            if (server == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            strcpy(server[servercount].name,checkresult.name);
            server[servercount].count = checkresult.count;
            servercount++;
        }
    }else{
        server[i].count += checkresult.count;
    }
}
    result = freopen(resultfile,"w",result);
    for (int i = 0; i < servercount; i++) {
        fprintf(result, "%s: %d\n", server[i].name, server[i].count);
    }
    fclose(result);
    //free(server);
    flock(fileno(block), LOCK_EX);
    fclose(block);
    
}

int main(int argc, char** argv)
{
    int i;
    if (argc < 3) {
        printf("You must specify the result file name and at least one log file.\n");
        return 1;
    }
    FILE* result = fopen(argv[1], "w");
    if (!result) {
        printf("Error opening file %s.\n", argv[1]);
        return 1;
    }
    fclose(result);

    int servercount=0;

    for (i = 2; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Error create process.\n");
            return 1;
        } else if (pid == 0) {
            statserver *server = malloc(pam * sizeof(statserver));
                            //printf("%d\n",pam); 
            parse_logfile (argv[i], server, &servercount);
            update_result_file(argv[1], argv[0], server, servercount);
            free(server);
            return 0;
        }
        
    }

    for (i = 2; i < argc; i++){
  wait(NULL);
  }

    return 0;
}
