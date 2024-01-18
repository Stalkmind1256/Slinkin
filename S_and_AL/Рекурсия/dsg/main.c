#include <stdio.h>

int max_depth = 0;

void paint1(char mas[9][13], int x, int y, int depth) {
    if (x < 0 || x >= 9 || y < 0 || y >= 13 || mas[x][y] == '1')
        return;
    mas[x][y] = '1';
    depth++;
    paint1(mas, x + 1, y, depth);
    paint1(mas, x, y + 1, depth);
    paint1(mas, x - 1, y, depth);
    paint1(mas, x, y - 1, depth);
    if (depth > max_depth)
        max_depth = depth;
}

void paint2(char mas[9][13], int x, int y, int depth) {
    if (x < 0 || x >= 9 || y < 0 || y >= 13 || mas[x][y] == '1')
        return;
    mas[x][y] = '1';
    depth++;
    paint2(mas, x + 1, y, depth);
    paint2(mas, x, y + 1, depth);
    paint2(mas, x - 1, y, depth);
    //paint2(mas, x, y - 1, depth);
    y--;
    while (y != -1) {
        if (mas[x][y] == '1')
            break;
        mas[x][y] = '1';
        paint2(mas, x + 1, y, depth);
        paint2(mas, x, y + 1, depth);
        paint2(mas, x - 1, y, depth);
        y--;
    }
    if (depth > max_depth)
        max_depth = depth;
}

void paint3(char mas[9][13], int x, int y, int depth) {
    int y_copy = y;
    if (x < 0 || x >= 9 || y < 0 || y >= 13 || mas[x][y] == '1')
        return;
    mas[x][y] = '1';
    depth++;
    paint3(mas, x + 1, y, depth);
    //paint3(mas, x, y + 1, depth);
    paint3(mas, x - 1, y, depth);
    //paint3(mas, x, y - 1, depth);
    y--;
    while (y != -1) {
        if (mas[x][y] == '1')
            break;
        mas[x][y] = '1';
        paint2(mas, x + 1, y, depth);
        paint2(mas, x - 1, y, depth);
        y--;
    }
    y_copy++;
    while (y_copy != 14) {
        if (mas[x][y_copy] == '1')
            break;
        mas[x][y_copy] = '1';
        paint2(mas, x + 1, y_copy, depth);
        paint2(mas, x - 1, y_copy, depth);
        y_copy++;
    }
    if (depth > max_depth)
        max_depth = depth;
}

int main() {
    char array1[9][13] = {"0001010101001",
                          "0001010111001",
                          "0000010101001",
                          "0001010101001",
                          "0001010101001",
                          "1111010101001",
                          "0001010111001",
                          "0001010101001",
                          "0001010101001"
                         },
         array2[9][13] = {"0001010101001",
                          "0001010111001",
                          "0000010101001",
                          "0001010101001",
                          "0001010101001",
                          "1111010101001",
                          "0001000111001",
                          "0001010101001",
                          "0001010101001"
                         },
         array3[9][13] = {"0001010101001",
                          "0001010111001",
                          "0000010101001",
                          "0001010101001",
                          "0001010101001",
                          "1111010101001",
                          "0001000111001",
                          "0001010101001",
                          "0001010101001"
                         };
    int rec = 0;
    printf("Start (array1):\n");
    for (unsigned short i = 0; i < 9; i++) {
        for (unsigned short j = 0; j < 13; j++)
            printf("%c", array1[i][j]);
        printf("\n");
    }
    paint1(array1, 0, 0, rec);
    printf("\nEnd (array1):\n");
    for (unsigned short i = 0; i < 9; i++) {
        for (unsigned short j = 0; j < 13; j++)
            printf("%c", array1[i][j]);
        printf("\n");
    }
    printf("Max depth (array1): %d\n", max_depth);
    max_depth = 0;
    printf("\nStart (array2):\n");
    for (unsigned short i = 0; i < 9; i++) {
        for (unsigned short j = 0; j < 13; j++)
            printf("%c", array2[i][j]);
        printf("\n");
    }
    paint2(array2, 0, 0, rec);
    printf("\nEnd (array2):\n");
    for (unsigned short i = 0; i < 9; i++) {
        for (unsigned short j = 0; j < 13; j++)
            printf("%c", array2[i][j]);
        printf("\n");
    }
    printf("Max depth (array2): %d\n", max_depth);
    max_depth = 0;
    printf("\nStart (array3):\n");
    for (unsigned short i = 0; i < 9; i++) {
        for (unsigned short j = 0; j < 13; j++)
            printf("%c", array3[i][j]);
        printf("\n");
    }
    paint3(array3, 0, 0, rec);
    printf("\nEnd (array3):\n");
    for (unsigned short i = 0; i < 9; i++) {
        for (unsigned short j = 0; j < 13; j++)
            printf("%c", array3[i][j]);
        printf("\n");
    }
    printf("Max depth (array3): %d\n", max_depth);
    return 0;
}
