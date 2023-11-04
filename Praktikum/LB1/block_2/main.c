#include <stdio.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    unsigned short int signature;
    unsigned int fileSize;
    unsigned int reserved;
    unsigned int dataOffset;
} BMPFileHeader;

typedef struct {
    unsigned int headerSize;
    int width;
    int height;
    unsigned short int planes;
    unsigned short int bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xResolution;
    int yResolution;
    unsigned int colorsUsed;
    unsigned int importantColors;
} BMPImageHeader;

#pragma pack(pop)

int main(int argc, char **argv) {
    FILE *file;
    char filename[] = "cosmos.bmp";

    file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Не удалось открыть файл %s\n", filename);
        return 1;
    }

    BMPFileHeader fileHeader;
    BMPImageHeader imageHeader;

    fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
    fread(&imageHeader, sizeof(BMPImageHeader), 1, file);

    // Находим середину BMP-файла
    int centerX = imageHeader.width / 2;
    int centerY = imageHeader.height / 2;

    // Вычисляем размеры диагоналей (половина ширины и высоты)
    int diagonalSize = centerX;

    // Задаём желаемый цвет
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    
	printf("Enter RGB:");
	scanf("%hhu%hhu%hhu",&red,&green,&blue);
    // Рисуем первую диагональ
    for (int i = 0; i < diagonalSize; i++) {
        // Вычисляем координаты текущего пикселя на первой диагонали
        int x1 = centerX - i;
        int y1 = centerY - i;

        // Записываем цвет в текущий пиксель
        int pixelOffset1 = fileHeader.dataOffset + ((imageHeader.height - y1 - 1) * imageHeader.width + x1) * (imageHeader.bitsPerPixel / 8);
        fseek(file, pixelOffset1, SEEK_SET);
        fwrite(&blue, sizeof(uint8_t), 1, file);
        fwrite(&green, sizeof(uint8_t), 1, file);
        fwrite(&red, sizeof(uint8_t), 1, file);

        // Рисуем вторую диагональ
        int x2 = centerX + i;
        int y2 = centerY - i;

        // Записываем цвет в текущий пиксель
        int pixelOffset2 = fileHeader.dataOffset + ((imageHeader.height - y2 - 1) * imageHeader.width + x2) * (imageHeader.bitsPerPixel / 8);
        fseek(file, pixelOffset2, SEEK_SET);
        fwrite(&blue, sizeof(uint8_t), 1, file);
        fwrite(&green, sizeof(uint8_t), 1, file);
        fwrite(&red, sizeof(uint8_t), 1, file);
    }

    // Рисуем третью диагональ
    for (int i = 0; i < diagonalSize; i++) {
        // Вычисляем координаты текущего пикселя на третьей диагонали
        int x3 = centerX - i;
        int y3 = centerY + i;

        // Записываем цвет в текущий пиксель
        int pixelOffset3 = fileHeader.dataOffset + ((imageHeader.height - y3 - 1) * imageHeader.width + x3) * (imageHeader.bitsPerPixel / 8);
        fseek(file, pixelOffset3, SEEK_SET);
        fwrite(&blue, sizeof(uint8_t), 1, file);
        fwrite(&green, sizeof(uint8_t), 1, file);
        fwrite(&red, sizeof(uint8_t), 1, file);

        // Рисуем четвертую диагональ
        int x4 = centerX + i;
        int y4 = centerY + i;

        // Записываем цвет в текущий пиксель
        int pixelOffset4 = fileHeader.dataOffset + ((imageHeader.height - y4 - 1) * imageHeader.width + x4) * (imageHeader.bitsPerPixel / 8);
        fseek(file, pixelOffset4, SEEK_SET);
        fwrite(&blue, sizeof(uint8_t), 1, file);
        fwrite(&green, sizeof(uint8_t), 1, file);
        fwrite(&red, sizeof(uint8_t), 1, file);
    }
    printf("Signature: %x\n", fileHeader.signature);
    printf("File Size: %u\n", fileHeader.fileSize);
    printf("Reserved: %u\n", fileHeader.reserved);
    printf("Data Offset: %u\n", fileHeader.dataOffset);
	printf("\nBMP Image Header:\n");
    printf("Header Size: %u\n", imageHeader.headerSize);
    printf("Image Width: %d\n", imageHeader.width);
    printf("Image Height: %d\n", imageHeader.height);
    printf("Planes: %u\n", imageHeader.planes);
    printf("Bits per Pixel: %u\n", imageHeader.bitsPerPixel);
    printf("Compression: %u\n", imageHeader.compression);
    printf("Image Size: %u\n", imageHeader.imageSize);
    printf("X Resolution: %d\n", imageHeader.xResolution);
    printf("Y Resolution: %d\n", imageHeader.yResolution);
    printf("Colors Used: %u\n", imageHeader.colorsUsed);
    printf("Important Colors: %u\n", imageHeader.importantColors);
	
    fclose(file);

    return 0;
}
    


