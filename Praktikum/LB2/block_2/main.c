#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define FILE_NAME "secure.dat"

void generate_file(int size) {
    FILE* file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error creating file!\n");
        exit(1);
    }
    
    srand(time(NULL));
    for (int i = 0; i < size - 1; i++) {
        unsigned char byte = rand() % 255 + 1;
        fwrite(&byte, sizeof(unsigned char), 1, file);
    }
    
    unsigned char zero = 0;
    fwrite(&zero, sizeof(unsigned char), 1, file);
    
    fclose(file);
}

void check_file(int size, int interval) {
    unsigned char *expected = (unsigned char*) malloc(size * sizeof(unsigned char));
    if (expected == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    
    FILE* file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    fread(expected, sizeof(unsigned char), size, file);
    fclose(file);
    
    while (1) {
        sleep(interval);
        
        file = fopen(FILE_NAME, "rb");
        if (file == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
        
        unsigned char *actual = (unsigned char*) malloc(size * sizeof(unsigned char));
        if (actual == NULL) {
            printf("Memory allocation error!\n");
            exit(1);
        }
        
        fread(actual, sizeof(unsigned char), size, file);
        fclose(file);
        
        int diff = 0;
        for (int i = 0; i < size; i++) {
            if (actual[i] != expected[i]) {
                diff = 1;
                printf("Обнаружен похититель! Позиция байта: %d, Значение: %d\n", i, actual[i]);
            }
        }
        
        if (diff) {
            printf("Эталон:\n");
            for (int i = 0; i < size; i++) {
                printf("%d ", expected[i]);
            }
            printf("\n");
            
            remove(FILE_NAME);
            free(actual);
            free(expected);
            exit(1);
        }
        
        free(actual);
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Использование: ./main <размер файла> <интервал проверки (мс)>\n");
        return 1;
    }
    
    int size = atoi(argv[1]);
    int interval = atoi(argv[2]);
    
    generate_file(size);
    check_file(size, interval);
    
    return 0;
}
