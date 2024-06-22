#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_BUF 1024
#define MAX_UNAME 100
#define MAX_GNAME 100
#define SHELL_INFO 100
#define MAX_SHELLS 100

void find_group_members(char *username) {
    FILE *passwd, *group, *shell;
    char buf[MAX_BUF];
    char uname[MAX_UNAME];
    char gname[MAX_GNAME];
    char shellBuf[SHELL_INFO];
    char shells[MAX_SHELLS][SHELL_INFO];
    int uid, gid;
    int num_shells = 0;

    passwd = fopen("/home/andrey/Рабочий стол/gruppp/passwd", "r");
    if (passwd == NULL) {
        perror("error opening passwd file");
        return;
    }

    group = fopen("/home/andrey/Рабочий стол/gruppp/group", "r");
    if (group == NULL) {
        perror("error opening group file");
        fclose(passwd);
        return;
    }

    shell = fopen("/home/andrey/Рабочий стол/gruppp/shells", "r");
    if (shell == NULL) {
        perror("error opening shells file");
        fclose(passwd);
        fclose(group);
        return;
    }

    // Read valid shells
    while (fgets(buf, sizeof(buf), shell) != NULL) {
        strtok(buf, "\n");
        strncpy(shells[num_shells], buf, SHELL_INFO);
        printf("Shell %d: %s\n", num_shells, shells[num_shells]);
        num_shells++;
    }
    fclose(shell);

    // Find the user's primary group ID and shell
    int user_found = 0;
    while (fgets(buf, sizeof(buf), passwd) != NULL && !user_found) {
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

        if (strcmp(uname, username) == 0) {
            user_found = 1;
            printf("username: %s\n", uname);
            printf("uid: %d\n", uid);
            printf("gid: %d\n", gid);
            printf("shell: %s\n", shellBuf);
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

    if (!user_found) {
        printf("User %s not found\n", username);
        fclose(group);
        return;
    }

    // Find all groups the user belongs to
    char group_buf[MAX_BUF];
    printf("Groups:\n");
    while (fgets(group_buf, sizeof(group_buf), group) != NULL) {
        char *group_line = strdup(group_buf);
        char *group_token = strtok(group_line, ":");
        int group_field = 0;
        char *group_members = NULL;
        int group_gid = -1;
        while (group_token != NULL) {
            if (group_field == 0) {
                strncpy(gname, group_token, MAX_GNAME);
            } else if (group_field == 2) {
                group_gid = atoi(group_token);
            } else if (group_field == 3) {
                group_members = group_token;
            }
            group_token = strtok(NULL, ":");
            group_field++;
        }

        if (group_gid == gid || (group_members && strstr(group_members, username))) {
            printf("Group name: %s\n", gname);
            printf("Group members:\n");
            // Find and print all group members
            FILE *passwd2 = fopen("/home/andrey/Рабочий стол/gruppp/passwd", "r");
            if (passwd2 == NULL) {
                perror("error opening passwd file");
                free(group_line);
                fclose(group);
                return;
            }
            while (fgets(buf, sizeof(buf), passwd2) != NULL) {
                char *line = strdup(buf);
                char *token = strtok(line, ":");
                char member_name[MAX_UNAME];
                int member_gid = -1;
                int field = 0;
                while (token != NULL) {
                    if (field == 0) {
                        strncpy(member_name, token, MAX_UNAME);
                    } else if (field == 3) {
                        member_gid = atoi(token);
                    }
                    token = strtok(NULL, ":");
                    field++;
                }
                if (member_gid == group_gid || (group_members && strstr(group_members, member_name))) {
                    int is_service_user = 1;
                    char *last_colon = strrchr(buf, ':');
                    if (last_colon != NULL) {
                        strncpy(shellBuf, last_colon + 1, SHELL_INFO);
                        shellBuf[strcspn(shellBuf, "\n")] = 0;
                    }
                    for (int i = 0; i < num_shells; i++) {
                        if (strcmp(shellBuf, shells[i]) == 0) {
                            is_service_user = 0;
                            break;
                        }
                    }
                    printf("  %s (%s)\n", member_name, is_service_user ? "service user" : "real user");
                }
                free(line);
            }
            fclose(passwd2);
        }
        free(group_line);
    }
    fclose(group);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }

    find_group_members(argv[1]);

    return 0;
}
