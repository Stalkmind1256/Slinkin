#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_BUF 1024
#define MAX_UNAME 100
#define MAX_GNAME 100
#define SHELL_INFO 100
#define MAX_SHELLS 100

void find_group_members(char *username){
    FILE *passwd, *shell;
    char buf[MAX_BUF];
    char uname[MAX_UNAME];
    char shellBuf[SHELL_INFO];
    char shells[MAX_SHELLS][SHELL_INFO];
    int uid,gid;
    int num_shells = 0;

    passwd = fopen("/home/andrey/Рабочий стол/gruppp/passwd","r");
    if(passwd == NULL){
        perror("error opening file");
    }

    shell = fopen("/home/andrey/Рабочий стол/gruppp/shells","r");
    if(shell == NULL){
        perror("error opening file");
    }
    
    while(fgets(buf,sizeof(buf),shell) != NULL){
        strtok(buf, "\n");
        strncpy(shells[num_shells], buf, SHELL_INFO);
        printf("Shell %d: %s\n", num_shells, shells[num_shells]);
        num_shells++;
    }
    fclose(shell);

    while(fgets(buf,sizeof(buf),passwd) != NULL){
        char *line = strdup(buf); 
        char *token = strtok(line, ":");
        int field = 0;
        while (token != NULL) {
            if (field == 0) {
                strncpy(uname, token, MAX_UNAME);
            } else if (field == 2) {
                uid = atoi(token);
            } else if (field == 3) {
                gid = atoi(token);
            }
            token = strtok(NULL, ":");
            field++;
        }
        
        char *last_colon = strrchr(buf, ':');
        if (last_colon != NULL) {
            strncpy(shellBuf, last_colon + 1, SHELL_INFO);
            shellBuf[strcspn(shellBuf, "\n")] = 0; 
        }

        if(strcmp(uname,username) == 0){
            printf("username: %s\n",uname);
            printf("uid: %d\n",uid);
            printf("gid: %d\n",gid);
            printf("shell: %s\n",shellBuf);
            int is_service_user = 1;
            for (int i = 0; i < num_shells; i++) {
                if (strcmp(shellBuf, shells[i]) == 0) {
                    is_service_user = 0;
                    break;
                }
            }
            if (is_service_user) {
                printf("This is a service user.\n");
            } else {
                printf("This is a real user.\n");
            }
        }
        free(line);
    }
    fclose(passwd);
}   

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }

    find_group_members(argv[1]);

    return 0;
} 
