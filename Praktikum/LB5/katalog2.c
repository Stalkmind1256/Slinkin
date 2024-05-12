#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

void copyDir(const char* src, const char* dest);
void copyFile(const char* src, const char* dest, mode_t mode);
void copySymlink(const char* src, const char* dest);
void createEmptyFile(const char* dest, mode_t mode);

int main() {
    char name[255];
    printf("Enter directory name: ");
    scanf("%s", name);
    copyDir(name, "new");
    return 0;
}

void copyDir(const char* src, const char* dest) {
    struct stat st;
    struct dirent* entry;
    DIR* dir = opendir(src);

    if (dir == NULL) {
        printf("Unable to open directory '%s'\n", src);
        return;
    }

    if (mkdir(dest, 0755) == -1 && errno != EEXIST) {
        printf("Error creating directory: %s\n", dest);
        closedir(dir);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char srcPath[PATH_MAX];
        char destPath[PATH_MAX];

        snprintf(srcPath, sizeof(srcPath), "%s/%s", src, entry->d_name);
        snprintf(destPath, sizeof(destPath), "%s/%s", dest, entry->d_name);

        if (lstat(srcPath, &st) == -1) {
            printf("Cannot get file stat: %s\n", srcPath);
            continue;
        }

        if (S_ISREG(st.st_mode)) {
            copyFile(srcPath, destPath, st.st_mode);
        } else if (S_ISDIR(st.st_mode)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                copyDir(srcPath, destPath);
            }
        } else if (S_ISLNK(st.st_mode)) {
            copySymlink(srcPath, destPath);
        } else {
            createEmptyFile(destPath, st.st_mode);
        }
    }

    closedir(dir);
}

void copyFile(const char* src, const char* dest, mode_t mode) {
    int srcFd, destFd;
    char buffer[4096];
    ssize_t bytesRead;

    srcFd = open(src, O_RDONLY);
    if (srcFd == -1) {
        printf("Error opening file: %s\n", src);
        return;
    }

    destFd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (destFd == -1) {
        printf("Error creating file: %s\n", dest);
        close(srcFd);
        return;
    }

    while ((bytesRead = read(srcFd, buffer, sizeof(buffer))) > 0) {
		    write(destFd, buffer, bytesRead);
    }

    close(srcFd);
    close(destFd);
}

void copySymlink(const char* src, const char* dest) {
    char target[PATH_MAX];
    ssize_t len;

    len = readlink(src, target, sizeof(target) - 1);
    if (len == -1) {
        printf("Error reading symbolic link: %s\n", src);
        return;
    }

    target[len] = '\0';

    if (symlink(target, dest) == -1) {
        printf("Error creating symbolic link: %s\n", dest);
        return;
    }
}

void createEmptyFile(const char* dest, mode_t mode) {
    int fd = open(dest, O_CREAT | O_TRUNC, mode);
    if (fd == -1) {
        printf("Error creating empty file: %s\n", dest);
        return;
    }

    close(fd);
}
