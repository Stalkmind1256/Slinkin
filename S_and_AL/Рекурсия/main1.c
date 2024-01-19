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

int max_depth = 0;
int current_depth = 0;

void printArray() {
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%s\n", a[i]);
    }
    printf("============================\n");
}

void paint(int x, int y) {
	    current_depth++;
	 if (current_depth > max_depth) {
        max_depth = current_depth;
    }
	
    if (x < 0 || x >= sizeof(a[0]) || y < 0 || y >= sizeof(a) / sizeof(a[0]) || a[y][x] != '0') {
		current_depth--;
        return;
    }
    
    
    printf("Iteration: (%d, %d), Depth_current: %d  Depth_max %d\n", x, y, current_depth, max_depth);
    printArray();

    a[y][x] = '=';
    paint(x + 1, y);
    paint(x, y + 1);
    paint(x - 1, y);
    paint(x, y - 1);

    current_depth--;
}

int main() {
    printArray();
    paint(0, 0);
    printf("------------------------\n");
    printArray();

    printf("Maximum depth of recursion: %d\n", max_depth);

    return 0;
}
