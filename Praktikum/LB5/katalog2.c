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
    mode_t originalPermissions;
    
    if (stat(srcDir, &statBuf) != 0) {
        perror("Error getting status of source directory");
        return;
    }
    originalPermissions = statBuf.st_mode;


    if (mkdir(destDir, statBuf.st_mode) != 0 && errno != EEXIST) {
        perror("Error creating destination directory");
        return;
    }
   
    
	 //chmod(destDir,statBuf.st_mode);	
     //printf("Права доступа к каталогу: %o\n", statBuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
	chmod(destDir, 0777); 
    
    
	if (!(statBuf.st_mode & S_IRUSR) || !(statBuf.st_mode & S_IWUSR)) {
		chmod(destDir, statBuf.st_mode | S_IRUSR | S_IWUSR);
	}


    if ((dirPoint = opendir(srcDir)) == NULL) {
        perror("Error opening source directory");
        printf("\t%s\n",srcDir);
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
            int linkSize = readlink(srcPath, linkPath, PATH_MAX - 1);
            if (linkSize != -1) {
                linkPath[linkSize] = '\0';
                if(symlink(linkPath, destPath) == -1) {
                    perror("Error creating symlink");
                }
            } else {
                perror("Error reading symlink");
            }
        } else {
            int fileDest = open(destPath, O_WRONLY | O_CREAT | O_TRUNC, statBuf.st_mode);
            chmod(destPath,statBuf.st_mode);
            if (fileDest >= 0) {
                close(fileDest);
            } else {
                perror("Error creating empty file");
            }
        }
    }

    closedir(dirPoint);
    
    if (chmod(destDir, originalPermissions) != 0) {
        perror("Error restoring original permissions of the directory");
    }
}
    


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source directory> <destination directory>\n", argv[0]);
        return 1;
    }



    struct stat srcStat;
    if (stat(argv[1], &srcStat) == -1) {
        perror("Error checking source directory");
        return 1;
    }

    if (!S_ISDIR(srcStat.st_mode)) {
        fprintf(stderr, "%s is not a directory.\n", argv[1]);
        return 1;
    }

    simpleCopy(argv[1], argv[2]);

    return 0;
}

