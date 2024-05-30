#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

void listDir(char *path, int depth) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct stat fileStat;

    if (dir == NULL) {
        printf("Cannot open directory: %s\n", path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char fullPath[1024];
        sprintf(fullPath, "%s/%s", path, entry->d_name);

        if (lstat(fullPath, &fileStat) < 0) {
            printf("Unable to get file stats for: %s\n", fullPath);
            continue;
        }

        for (int i = 0; i < depth; i++) {
            printf("  ");
        }

        printf("%s | Type: ", entry->d_name);

        switch (fileStat.st_mode & S_IFMT) {
            case S_IFREG:
                printf("Regular File");
                break;
            case S_IFDIR:
                printf("Directory");
                break;
            case S_IFLNK:
                printf("Symbolic Link");
                break;
            case S_IFIFO:
                printf("FIFO/Pipe");
                break;
            case S_IFSOCK:
                printf("Socket");
                break;
            default:
                printf("Unknown");
                break;
        }

        printf(" : Owner: %s : Group: %s : Permissions: %o\n",
               getpwuid(fileStat.st_uid)->pw_name,
               getgrgid(fileStat.st_gid)->gr_name,
               fileStat.st_mode & 0777);

        if (S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode)) {
            listDir(fullPath, depth + 1);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    listDir(argv[1], 0);

    return 0;
}
