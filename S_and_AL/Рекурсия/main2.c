#include <stdio.h>

#define MAX_X 14
#define MAX_Y 9

char a[MAX_Y][MAX_X] = {
    "0011100",
    "1001101",
    "1010010",
    "0000000",
    "1111100",
};

int max_depth = 0;
int current_depth = 0;

void printArray() {
    for (int i = 0; i < MAX_Y; i++) {
        printf("%s\n", a[i]);
    }
    printf("============================\n");
}

void paint(int x, int y) {
    int glub_rec = current_depth;
    int max_glub_rec = max_depth;

    glub_rec++;
    if (glub_rec > max_glub_rec) {
        max_glub_rec = glub_rec;
    }

    while (1) {
        if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y || a[y][x] != '0') {
            glub_rec--;
            return;
        }

        printArray();
        printf("-----------------\n");
        a[y][x] = '-';

        paint(x + 1, y);
        paint(x, y + 1);
        paint(x - 1, y);

        y--;

        printf("REC = %d\nMAX_REC = %d\n", glub_rec, max_glub_rec);
    }

    glub_rec--;
}

int main() {
    printArray();
    paint(0, 0);
    printf("------------------------\n");
    printArray();

    printf("Maximum depth of recursion: %d\n", max_depth);

    return 0;
}
