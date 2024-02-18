#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main() {
    char username[100];
    printf("Enter username: ");
    scanf("%s", username);

    struct passwd *pw = getpwnam(username);
    if (pw == NULL) {
        printf("User %s not found\n", username);
        return 1;
    }

    printf("odnogroup users %s:\n", username);

    int num_groups = 0;
    gid_t *groups = NULL;

    if(getgrouplist(username, pw->pw_gid, groups, &num_groups) == -1) {
        groups = (gid_t *)malloc(num_groups * sizeof(gid_t));
        getgrouplist(username, pw->pw_gid, groups, &num_groups);
    }

    for (int i = 0; i < num_groups; i++) {
        struct group *gr = getgrgid(groups[i]);
        if (gr != NULL) {
            printf("%s: %s\n", gr->gr_name, gr->gr_mem[0]);

            for (int j = 0; gr->gr_mem[j] != NULL; j++) {
                if (strcmp(gr->gr_mem[j], username) == 0) {
                    printf("Real user\n");
                }else{
					printf("service user\n");
					}
            }
        }
    }
	free(groups);
    return 0;
}

