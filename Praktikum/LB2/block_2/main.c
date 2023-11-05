#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void generate_file(int size) {
    FILE* file = fopen("secure.dat", "wb");
    if (file == NULL) {
        printf("Ошибка при создании файла.\n");
        exit(1);
    }

    srand(time(NULL));
    for (int i = 0; i < size - 1; i++) {
        unsigned char byte = rand() % 255 + 1;
        fwrite(&byte, sizeof(unsigned char), 1, file);
    }

    unsigned char last_byte = 0;
    fwrite(&last_byte, sizeof(unsigned char), 1, file);

    fclose(file);
}

int compare_with_etalon(int size) {
    unsigned char* etalon = (unsigned char*)malloc(size);
    if (etalon == NULL) {
        printf("Ошибка при выделении памяти.\n");
        exit(1);
    }
    memset(etalon, 0, size);

    FILE* file = fopen("secure.dat", "rb");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        free(etalon);
        exit(1);
    }

    fread(etalon, sizeof(unsigned char), size, file);
    fclose(file);

    int differences = 0;
    int* positions = (int*)malloc(size * sizeof(int));
    int current_position = 0;

    for (int i = 0; i < size; i++) {
        if (etalon[i] != 0) {
            positions[differences] = i;
            differences++;
            current_position = i;
        }
    }

    if (differences != 0) {
        printf("Обнаружен похититель!\n");
        printf("Позиции некорректных байтов: ");
        for (int i = 0; i < differences; i++) {
            printf("%d ", positions[i]);
        }
        printf("\n");
        printf("Эталонное содержимое: ");
        for (int i = current_position - 10; i <= current_position + 10; i++) {
            if (i >= 0 && i < size) {
                printf("%d ", etalon[i]);
            }
        }
        printf("\n");

        remove("secure.dat");
        free(etalon);
        free(positions);
        
        return 1;
    }

    free(etalon);
    free(positions);

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Использование: %s <размер файла> <интервал обновления (сек)>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int interval = atoi(argv[2]);

    generate_file(size);

    while (1) {
        if (compare_with_etalon(size)) {
            break;
        }
        sleep(interval);
    }

    return 0;
}
