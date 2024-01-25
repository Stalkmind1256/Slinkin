#include <stdio.h>

char a[9][14] = {
"1111010101001",
"1011010101001",
"0001010101001",
"1011010101001",
"0100101010100",
"1111010101001",
"0001010101001",
"0001010101001",
"0001010101001"
};

int max_depth = 0;
//int depth = 0;
//int current_depth = 0;

void printArray() {
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        printf("%s\n", a[i]);
    }
    printf("============================\n");
}

void paint(int x, int y, int depth) {
	depth++;
	if(depth > max_depth){
		max_depth = depth;
		}
    if (y < 0 || y >= sizeof(a) / sizeof(a[0]) || (x < 0 || x >= sizeof(a[0]))   || a[y][x] != '0') {
		//depth--;
        return;
        
    }
    a[y][x] = '$';
    //current_depth++
    paint(x + 1, y,depth);
    paint(x, y + 1,depth);
    paint(x - 1, y,depth);
    paint(x, y - 1,depth);
    
	//printf("Iteration: (%d, %d), Depth: %d\n", x, y, max_depth);
    //printArray();
    //max_depth++;
    //depth--;
}
int main() {
    printArray();
    paint(1, 2,0);
    printf("------------------------\n");
    printArray();

    printf("Maximum depth of recursion: %d\n", max_depth);

    return 0;
}
