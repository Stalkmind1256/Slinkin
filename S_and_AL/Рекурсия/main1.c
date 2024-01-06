#include <stdio.h>

char a[9][14] = {
    "11101",
	"11001",
	"10001",
	"00011",
	"11100",
};

int max_depth = 0;
int current_depth = 0;

void printArray() {
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%s\n", a[i]);
    }
    printf("============================\n");
}

void paint(int x, int y) {
    if (x < 0 || x >= sizeof(a[0]) || y < 0 || y >= sizeof(a) / sizeof(a[0]) || a[y][x] != '0') {
        return;
    }
    a[y][x] = '1';
    current_depth++;

    if (current_depth > max_depth) {
        max_depth = current_depth;
    }

    printf("Iteration: (%d, %d), Depth: %d\n", x, y, current_depth);
    printArray();

    paint(x + 1, y);
    paint(x, y + 1);
    paint(x - 1, y);
    paint(x, y - 1);

    current_depth--;
}

int main() {
    printArray();
    paint(2, 2);
    printf("------------------------\n");
    printArray();

    printf("Maximum depth of recursion: %d\n", max_depth);

    return 0;
}
