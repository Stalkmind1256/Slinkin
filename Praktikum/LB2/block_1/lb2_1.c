 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#define SET_FILE "set.dat"

#define MAX_NUMBERS 255
#define MAX_SOURSE 20


int ReadNumbersFromFile(char* filename, int* numbers)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }

    int count = 0;

    while (fscanf(file, "%d", &numbers[count]) != EOF)
    {
        count++;
    }

    fclose(file);
    return count;
}

int WriteNumbersToFile(char* filename, int* numbers, int count)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d\n", numbers[i]);
    }

    fclose(file);
    return 0;
}

void MergeSets(char* setFile, char** sourceFiles, int sourceCount)
{
    int setNumbers[MAX_NUMBERS];
    int setCount = ReadNumbersFromFile(setFile, setNumbers);
    if (setCount == -1)
    {
        setCount = 0;
    }

    int numbers[MAX_NUMBERS];
    int counts[MAX_NUMBERS];
    int totalCount = 0;

    for (int i = 0; i < sourceCount; i++)
    {
        counts[i] = ReadNumbersFromFile(sourceFiles[i], numbers);
        if (counts[i] == -1)
        {
            continue;
        }
        printf("Numbers from %s:\n ", sourceFiles[i]);

        for (int j = 0; j < counts[i]; j++)
        {
            int found = 0;
            for (int k = 0; k < setCount; k++)
            {
                if (numbers[j] == setNumbers[k])
                {
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                setNumbers[setCount++] = numbers[j];
            }
            usleep(20000);
            printf("%d\n", numbers[j]);
        }
        totalCount += counts[i];
    }
    usleep(20000);
    WriteNumbersToFile(setFile, setNumbers, setCount);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Use: %s source_file1 source_file2 ...[]\n", argv[0]);
        return 0;
    }

    char* setFile = SET_FILE;
    char* sourceFiles[MAX_SOURSE];
    int sourceCount = argc - 1;

//Cannot including
    for (int i = 1; i <= sourceCount; i++) {
		if(strcmp(argv[i], setFile) == 0){
			printf("Error: 'set.dat' file cannot be including as a sourse file\n");
			return 0;
			}
        sourceFiles[i - 1] = argv[i];
    }

    int lockFile = open(setFile, O_RDWR);
    if (lockFile == -1)
    {
        perror("Error opening file set.dat");
        return 0;
    }

   //printf("File descriptor for set.dat: %d\n", lockFile);

    if (flock(lockFile, LOCK_EX) == -1)
    {
        perror("Error lock file set.dat");
        close(lockFile);
        return 0;
    }

    MergeSets(setFile, sourceFiles, sourceCount);

    flock(lockFile, LOCK_UN);
    close(lockFile);

    return 0;
}
