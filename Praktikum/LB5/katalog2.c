#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>


void simpleCopy(char *srcDir, char *destDir) {
    DIR *dirPoint;
    struct dirent *dirEntry;
    struct stat statBuf;
    char srcPath[PATH_MAX], destPath[PATH_MAX];
    
    if (stat(srcDir, &statBuf) != 0 || mkdir(destDir, statBuf.st_mode) != 0) {
        perror("Error creating destination directory");
        return;
    }


    if ((dirPoint = opendir(srcDir)) == NULL) {
        perror("Error opening source directory");
        return;
    }

    while ((dirEntry = readdir(dirPoint)) != NULL) {
        if (!strcmp(dirEntry->d_name, ".") || !strcmp(dirEntry->d_name, "..")) continue;
        
        snprintf(srcPath, PATH_MAX, "%s/%s", srcDir, dirEntry->d_name);
        snprintf(destPath, PATH_MAX, "%s/%s", destDir, dirEntry->d_name);

        if (lstat(srcPath, &statBuf) == -1) {
            perror("Error getting status of file/directory");
            continue;
        }

        if (S_ISDIR(statBuf.st_mode)) {
            simpleCopy(srcPath, destPath);
        } else if (S_ISLNK(statBuf.st_mode)) {
            char linkPath[PATH_MAX];
            ssize_t linkSize = readlink(srcPath, linkPath, PATH_MAX - 1);
            if (linkSize != -1) {
                linkPath[linkSize] = '\0';
                symlink(linkPath, destPath);
            } else {
                perror("Error reading symlink");
            }
        } else if (S_ISREG(statBuf.st_mode)) {
            int fileDest = open(destPath, O_WRONLY | O_CREAT | O_TRUNC, statBuf.st_mode);
            if (fileDest >= 0) close(fileDest);
            else perror("Error creating file");
        }
    }

    closedir(dirPoint);
}

int main() {
    char srcDir[255];
    printf("Enter the directory to copy: ");
    scanf("%s", srcDir);
    simpleCopy(srcDir, "SimpleCopyDir");

    printf("Directory copied successfully.\n");

    return 0;
}

