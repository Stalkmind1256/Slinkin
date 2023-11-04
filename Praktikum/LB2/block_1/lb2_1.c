#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>

#define MAX_NUMBERS 2001

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
        return;
    }

    for (int i = 0; i < sourceCount; i++)
    {
        int sourceNumbers[MAX_NUMBERS];
        int sourceCount = ReadNumbersFromFile(sourceFiles[i], sourceNumbers);
        if (sourceCount == -1)
        {
            continue;
        }

        for (int j = 0; j < sourceCount; j++)
        {
            int found = 0;
            for (int k = 0; k < setCount; k++)
            {
                if (sourceNumbers[j] == setNumbers[k])
                {
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                setNumbers[setCount++] = sourceNumbers[j];
            }
        }
    }

    WriteNumbersToFile(setFile, setNumbers, setCount);
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Use: %s set_file source_file1 source_file2 ...\n", argv[0]);
        return 0;
    }

    char* setFile = argv[1];
    int sourceCount = argc - 2;
    char** sourceFiles = &argv[2];

    int lockFile = open(setFile, O_RDWR);
    if (lockFile == -1)
    {
        perror("Error opening file set.dat");
        return 0;
    }

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
