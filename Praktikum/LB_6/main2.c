#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

void check_permissions(struct stat *file_stat, struct passwd *user_pwd, const char *file_name) {
    printf("Permissions for user %s on file %s:\n", user_pwd->pw_name, file_name);

    if (file_stat->st_uid == user_pwd->pw_uid) {
		if (file_stat->st_mode & S_IRUSR) {
			printf("  Read: Allowed\n");
		} else {
			printf("  Read: Denied\n");
		}

		if (file_stat->st_mode & S_IWUSR) {
			printf("  Write: Allowed\n");
		} else {
			printf("  Write: Denied\n");
		}

		if (file_stat->st_mode & S_IXUSR) {
			printf("  Execute: Allowed\n");
		} else {
			printf("  Execute: Denied\n");
		}
		return;
	}


	if (file_stat->st_gid == user_pwd->pw_gid) {
		if (file_stat->st_mode & S_IRGRP) {
			printf("  Read: Allowed\n");
		} else {
			printf("  Read: Denied\n");
		}

		if (file_stat->st_mode & S_IWGRP) {
			printf("  Write: Allowed\n");
		} else {
			printf("  Write: Denied\n");
		}

		if (file_stat->st_mode & S_IXGRP) {
			printf("  Execute: Allowed\n");
		} else {
			printf("  Execute: Denied\n");
		}
		return;
	}


	if (file_stat->st_mode & S_IROTH) {
		printf("  Read: Allowed\n");
	} else {
		printf("  Read: Denied\n");
	}

	if (file_stat->st_mode & S_IWOTH) {
		printf("  Write: Allowed\n");
	} else {
		printf("  Write: Denied\n");
	}

	if (file_stat->st_mode & S_IXOTH) {
		printf("  Execute: Allowed\n");
	} else {
		printf("  Execute: Denied\n");
	}

	}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <username> <file>\n", argv[0]);
        return 1;
    }

    const char *username = argv[1];
    const char *file_name = argv[2];

    struct passwd *user_pwd = getpwnam(username);
    if (!user_pwd) {
        perror("Could not get user information");
        return 1;
    }

    struct stat file_stat;
    if (stat(file_name, &file_stat) == -1) {
        perror("Could not get file information");
        return 1;
    }

    check_permissions(&file_stat, user_pwd, file_name);

    return 0;
}
