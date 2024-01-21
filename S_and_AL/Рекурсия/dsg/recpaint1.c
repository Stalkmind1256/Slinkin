
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    #define MAX_X 13
    #define MAX_Y 9

int max_depth=0;
char **matr;


void paint1(char a[MAX_Y][MAX_X], int x, int y, int depth) {
    if (y < 0 || y >= 9 || x < 0 || x >= 13 || a[y][x] == '1' || a[y][x] == '*')
        return;
    a[y][x] = '*';
    depth++;
    if (depth > max_depth)
        max_depth = depth;

    paint1(a, x + 1, y, depth);
    paint1(a, x, y + 1, depth);
    paint1(a, x - 1, y, depth);
    paint1(a, x, y - 1, depth);
}

void vivod(char a[MAX_Y][MAX_X])
{
	for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++)
            printf("%c", a[i][j]);
        printf("\n");
	}
}
	

int main(int argc, char **argv)
{	

    char matr[MAX_Y][MAX_X]={		  "0001010101001",
									"0001010101001",
									"0001010101001",
									"0001010101001",
									"0001010101001",
									"1011010101001",
									"0001010101001",
									"0001010101001",
									"0001010101001"
								  };
	
	printf("Start paint1:\n");
    vivod(matr);
	printf("\n");
	max_depth=0;
	paint1(matr,0,0,0);
	
	printf("End paint1:\n");
	vivod(matr);
	
	printf("MAX_GLUB_REC = %d\n",max_depth);
	return 0;
}

