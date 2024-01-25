#include <stdio.h>

char a[9][14] = {
"1111010101001",
"1011110101001",
"0000010101001",
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

void paint(int x, int y, int depth)
{
    depth++;
    if (depth > max_depth)
		max_depth = depth;
		
	if (y < 0 || y >= sizeof(a) / sizeof(a[0]) || (x < 0 || x >= sizeof(a[0]))   || a[y][x] != '0')
		return;
	a[y][x] = '*';
	
	int leftX, lx, rightX, rx;
	
	rx=x;
	rightX = rx;
	while(!(y < 0 || y >= sizeof(a) / sizeof(a[0]) || (rx < 0 || rx >= sizeof(a[0]))   || a[y][rx + 1] != '0')){
		rx++;
		a[y][rx]='*';
		rightX = rx;
	}
	
	lx=x;
	leftX = lx;	
	while(!(y < 0 || y >= sizeof(a) / sizeof(a[0]) || (lx < 0 || lx >= sizeof(a[0]))   || a[y][lx - 1] != '0')){
		lx--;
		a[y][lx]='*';
		leftX = lx;	
    }
    
    for(int x=leftX; x<=rightX; x++){
		paint(x, y+1, depth);
    	paint(x, y-1, depth);
	}
}
int main() {
    printArray();
    paint(1, 2,0);
    printf("------------------------\n");
    printArray();

    printf("Maximum depth of recursion: %d\n", max_depth);

    return 0;
}
