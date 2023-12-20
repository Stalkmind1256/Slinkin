#include <stdio.h>

char a[9][14] = {
    "0001010101001",
    "0001010101001",
    "0001010101001",
    "0001010101001",
    "0001010101001",
    "1111010101001",
    "0001000101001",
    "0001010101001",
    "0001010101001"
};

void printArray() {
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%s\n", a[i]);
    }
    printf("============================\n");
}

void paint(int x, int y, int depth) {
    char kek[9 * 14][2];
    int front = 0;
    int next = 0;

    if (x < 0 || x >= sizeof(a[0]) || y < 0 || y >= sizeof(a) / sizeof(a[0]) || a[y][x] == '1')
        return;
    a[y][x] = '1';

    printf("Iteration: (%d, %d), Depth: %d\n", x, y, depth);
    printArray();

    paint(x + 1, y, depth + 1);

    int i = x + 1;
    while (i <= sizeof(a[0]) && a[y][i - 1] != '1') {
        a[y][i - 1] = '1';
        kek[next][0] = i;
        kek[next][1] = y;
        next++;
        i++;
    }

    paint(x, y + 1, depth + 1);
    paint(x - 1, y, depth + 1);
    paint(x, y - 1, depth + 1);
}

int main() {
    printArray();
    paint(0, 0, 0);
    printf("------------------------\n");
    printArray();
    return 0;
}
