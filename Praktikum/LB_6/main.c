#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <string.h>


int user(struct passwd *user) {
    return user->pw_uid >= 1000;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }

    struct passwd *pwd = getpwnam(argv[1]);
    if (pwd == NULL) {
        printf("User %s not found\n", argv[1]);
        return 1;
    }

    int num_groups = 20;
    gid_t groups[num_groups];
    getgrouplist(argv[1], pwd->pw_gid, groups, &num_groups);

    printf("Groupmates for user %s:\n", argv[1]);
    for (int i = 0; i < num_groups; i++) {
        struct group *grp = getgrgid(groups[i]);
        if (grp) {
            for (int j = 0; grp->gr_mem[j] != NULL; j++) {
                if (strcmp(grp->gr_mem[j], argv[1]) == 0) {
                    continue; 
                }
                struct passwd *user_pwd = getpwnam(grp->gr_mem[j]);
                if (user_pwd) {
					char* userType;
					if (user(user_pwd)){
						userType = "real";
					} else {
						userType = "service";
					}
					printf("%s - %s\n", grp->gr_mem[j], userType);
				}

            }
        }
    }

    return 0;
}
