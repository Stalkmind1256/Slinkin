#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_BYTE_VALUE 256

int main(int argc, char *argv[]) {
    // Проверяем наличие аргумента с периодом ожидания
    if (argc < 2) {
        printf("Ошибка: не указан период ожидания\n");
        return 1;
    }

    // Открываем файл secure.dat в режиме чтения
    FILE *secureFile = fopen("secure.dat", "rb");
    if (secureFile == NULL) {
        printf("Ошибка: файл secure.dat не найден\n");
        return 1;
    }

    // Создаем файл abducted.dat в режиме записи
    FILE *abductedFile = fopen("abducted.dat", "wb");
    if (abductedFile == NULL) {
        printf("Ошибка: не удалось создать файл abducted.dat\n");
        fclose(secureFile);
        return 1;
    }

    // Получаем период ожидания из аргумента командной строки
    int waitPeriod = atoi(argv[1]);

    // Определяем размер файла secure.dat
    fseek(secureFile, 0, SEEK_END);
    long fileSize = ftell(secureFile);
    rewind(secureFile);

    // Создаем массив для хранения информации о уже похищенных позициях
    int *stolenPositions = (int *) malloc(sizeof(int) * fileSize);
    int stolenCount = 0;

    // Инициализируем генератор случайных чисел
    srand((unsigned) time(NULL));

    // Ожидаем полного заполнения файла secure.dat
    while (ftell(secureFile) < fileSize) {
        fseek(secureFile, 0, SEEK_END);
        long newFileSize = ftell(secureFile);
        if (newFileSize > fileSize) {
            fileSize = newFileSize;
            printf("Файл secure.dat заполнен на %ld байт\n", fileSize);
        }
    }

    // Начинаем "похищение" байтов
    while (1) {
        // Генерируем случайную позицию
        int position;
        do {
            position = rand() % fileSize;
        } while (memchr(stolenPositions, position, sizeof(int) * stolenCount) != NULL);

        // Добавляем позицию в массив
        stolenPositions[stolenCount++] = position;

        // Считываем байт
        fseek(secureFile, position, SEEK_SET);
        unsigned char byte;
        fread(&byte, sizeof(unsigned char), 1, secureFile);

        // Записываем байт в файл abducted.dat
        fwrite(&byte, sizeof(unsigned char), 1, abductedFile);

        // Переоткрываем файл secure.dat в режиме записи
        fclose(secureFile);
        secureFile = fopen("secure.dat", "wb");
        if (secureFile == NULL) {
            printf("Ошибка: не удалось переоткрыть файл secure.dat для записи\n");
            break;
        }

        // Заменяем байт в файле secure.dat на 0
        fseek(secureFile, position, SEEK_SET);
        unsigned char zero = 0;
        fwrite(&zero, sizeof(unsigned char), 1, secureFile);

        // Проверяем наличие файла secure.dat
        FILE *checkFile = fopen("secure.dat", "rb");
        if (checkFile == NULL) {
            printf("Тревога, уходим!\n");
            printf("Похищены байты из следующих позиций:\n");
            for (int i = 0; i < stolenCount; i++) {
                printf("Позиция: %d, Значение: %u\n", stolenPositions[i], stolenPositions[i]);
            }
            break;
        } else {
            fclose(checkFile);
        }

        // Задержка перед следующей попыткой похищения
        usleep(waitPeriod * 1000);
    }

    // Освобождаем память
    free(stolenPositions);

    // Закрываем файлы
    if (secureFile != NULL) {
        fclose(secureFile);
    }
    if (abductedFile != NULL) {
        fclose(abductedFile);
    }

    return 0;
}
