#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_UNAME 100
#define MAX_GNAME 100
#define MAX_MEMBERS 257

void find_group_members(char *username) {
    FILE *passwd, *group;
    char buf[MAX_LINE];
    char uname[MAX_UNAME];
    char gname[MAX_GNAME];
    char members[MAX_LINE];
    int uid, gid;
    int ngroups = 0;
    int nusers = 0;
    int user_gid = -1;
    char *groups[100]; 
    char *users[100]; 
    int user_uids[100];
    int user_gids[100]; 

    passwd = fopen("/etc/passwd", "r");
    if (passwd == NULL) {
        perror("error opening file");
        return;
    }


    while (fgets(buf, sizeof(buf), passwd) != NULL) {
        sscanf(buf, "%[^:]:%*[^:]:%d:%d", uname, &uid, &gid);
        if (strcmp(uname, username) == 0) {
            user_gid = gid;
            printf("%s is a %s user\n", username, uid < 1000 ? "system" : "real");
        }
        users[nusers] = strdup(uname);
        user_uids[nusers] = uid;
        user_gids[nusers] = gid;
        nusers++;
    }
    fclose(passwd);

    if (user_gid == -1) {
        printf("User %s not found.\n", username);
        return;
    }

    group = fopen("/etc/group", "r");
    if (group == NULL) {
        perror("error opening file");
        return;
    }


    while (fgets(buf, sizeof(buf), group) != NULL) {
        sscanf(buf, "%[^:]:%*[^:]:%*d:%[^\n]", gname, members);
        if (strstr(members, username) != NULL) {
            groups[ngroups++] = strdup(gname);
        } else if (strstr(members, "*") == NULL) {
            char *member = strtok(members, ",");
            while (member != NULL) {
                if (strcmp(member, username) == 0) {
                    groups[ngroups++] = strdup(gname);
                    break;
                }
                member = strtok(NULL, ",");
            }
        }
    }
    fclose(group);

    printf("Groups: \n");
    for (int i = 0; i < ngroups; i++) {
        printf("%s\n", groups[i]);
    }


    printf("\nGroup members:\n");
    for (int i = 0; i < nusers; i++) {
        for (int j = 0; j < ngroups; j++) {
            group = fopen("/etc/group", "r");
            if (group == NULL) {
                perror("error opening file");
                return;
            }

            while (fgets(buf, sizeof(buf), group) != NULL) {
                sscanf(buf, "%[^:]:%*[^:]:%*d:%[^\n]", gname, members);
                if (strcmp(gname, groups[j]) == 0 && (strstr(members, users[i]) != NULL || user_gids[i] == user_gid)) {
                    printf("%s is a %s user\n", users[i], user_uids[i] < 1000 ? "system" : "real");
                    break;
                }
            }
            fclose(group);
        }
    }

    for (int i = 0; i < ngroups; i++) {
        free(groups[i]);
    }

    for (int i = 0; i < nusers; i++) {
        free(users[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }

    find_group_members(argv[1]);

    return 0;
}
