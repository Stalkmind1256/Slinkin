#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

void print_group(const char* username) {
    struct group *grp;
    struct passwd *pwd;
    char **members;

    pwd = getpwnam(username);
    if (pwd == NULL) {
        printf("User not found\n");
        return;
    }

    FILE *group_file = fopen("/etc/group", "r");
    if (group_file == NULL) {
        printf("Unable to open group file\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), group_file) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char *group_name = strtok(line, ":");
        if (group_name == NULL) {
            printf("Error processing group file\n");
            return;
        }

        members = strtok(NULL, ":");
        if (members != NULL && strstr(members, username) != NULL) {
            printf("Group: %s\n", group_name);
            char *member = strtok(members, ",");
            while (member != NULL) {
                pwd = getpwnam(member);
                if (pwd != NULL) {
                    printf("- %s (", member);
                    if (pwd->pw_gid == grp->gr_gid) {
                        printf("Real user");
                    } else {
                        printf("Service user");
                    }
                    printf(")\n");
                }
                member = strtok(NULL, ",");
            }
        }
    }

    fclose(group_file);
}

int main() {
    char username[64];
    printf("Enter username:\n");
    scanf("%s", username);
    print_group(username);

    return 0;
}
