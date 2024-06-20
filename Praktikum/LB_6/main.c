#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>

int pam = 4;

typedef struct {
    char name[50];
    int count;
} statserver;

void parse_logfile(char* filename, statserver** server, int* servercount, int* pam) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s.\n", filename);
        return;
    }
    char line[4000];
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file) != NULL) {
        int exist = 0;
        char* token = strtok(line, ";");
        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ";");
        }
        if (token == NULL) {
            continue;
        }
        for (int i = 0; i < *servercount; i++) {
            if (strcmp((*server)[i].name, token) == 0) {
                (*server)[i].count += 1;
                exist = 1;
                break;
            }
        }
        if (!exist) {
            if (*servercount >= *pam) {
                *pam = *pam * 1.5;	
                statserver* temp = realloc(*server, (*pam) * sizeof(statserver));
                if (!temp) {
                    perror("Memory allocation error");
                    fclose(file);
                    free(*server);
                    *server = NULL;
                    return;
                }
                *server = temp;
                //printf("Memory reallocated: %d elements (%lu bytes)\n", *pam, (*pam) * sizeof(statserver));
            }
            strncpy((*server)[*servercount].name, token, sizeof((*server)[*servercount].name) - 1);
            (*server)[*servercount].name[sizeof((*server)[*servercount].name) - 1] = '\0';
            (*server)[*servercount].count = 1;
            (*servercount)++;
        }
    }
    fclose(file);
}

void update_result_file(char* resultfile, char* argv0, statserver** server, int* servercount, int* pam) {
    
    FILE *block = fopen(argv0,"r");
    flock(fileno(block),LOCK_EX);
    
    FILE* result = fopen(resultfile, "r");
    if (!result) {
        perror("Error opening result file");
        return;
    }

    statserver checkresult;
    while (fscanf(result, "%[^:]: %d\n", checkresult.name, &checkresult.count) == 2) {
        int exist = 0;
        for (int i = 0; i < *servercount; i++) {
            if (strcmp(checkresult.name, (*server)[i].name) == 0) {
                (*server)[i].count += checkresult.count;
                exist = 1;
                break;
            }
        }

        if (!exist) {
            if (*servercount >= *pam) {
                *pam = *pam * 1.5;
                statserver* temp = realloc(*server, (*pam) * sizeof(statserver));
                if (!temp) {
                    perror("Memory allocation error");
                    fclose(result);
                    free(*server);
                    *server = NULL;
                    return;
                }
                *server = temp;
            }
            strncpy((*server)[*servercount].name, checkresult.name, sizeof((*server)[*servercount].name) - 1);
            (*server)[*servercount].name[sizeof((*server)[*servercount].name) - 1] = '\0';
            (*server)[*servercount].count = checkresult.count;
            (*servercount)++;
        }
    }

    result = freopen(resultfile, "w", result);
    if (!result) {
        perror("Error reopening result file");
        return;
    }

    for (int i = 0; i < *servercount; i++) {
        fprintf(result, "%s: %d\n", (*server)[i].name, (*server)[i].count);
    }
    fclose(result);
    flock(fileno(block), LOCK_UN);
    fclose(block);
}


int main(int argc, char** argv) {
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



    for (int i = 2; i < argc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Error creating process.\n");
            return 1;
        } else if (pid == 0) {
            int servercount = 0;
            statserver* server = malloc(pam * sizeof(statserver));
            if (!server) {
                perror("Memory allocation error");
                return 1;
            }
            //printf("Memory allocated: %d elements (%lu bytes)\n", pam, pam * sizeof(statserver));
            parse_logfile(argv[i], &server, &servercount, &pam);
            update_result_file(argv[1], argv[0], &server, &servercount, &pam);
            free(server);
            return 0;
        }
    }

    for (int i = 2; i < argc; i++) {
        wait(NULL);
    }

    
    return 0;
}
