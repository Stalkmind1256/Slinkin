
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    #define MAX_X 13
    #define MAX_Y 9

int max_depth=0;
char **matr;


void paint3(char a[MAX_Y][MAX_X], int x, int y, int depth)
{
	if (y < 0 || y >= 9 || x < 0 || x >= 13 || a[y][x] == '1' || a[y][x] == '*')
		return;
	a[y][x] = '*';
    depth++;
    if (depth > max_depth)
		max_depth = depth;
		
    while((x+1!=13) && (a[y][x+1]=='0')){
		x++;
		a[y][x]='*';
	}
	
    int ny=y;
	while(ny+1!=13 && a[ny+1][x]=='0'){
		paint3(a, x, ny+1, depth);
		ny++;
    }
    
    while(x-1!=-1 && a[y][x-1]=='0'){
		x--;
		a[y][x]='*';
    }   
    
    int py=y;
	while((py-1!=-1) && (a[py-1][x]=='0')){
		paint3(a, x, py-1, depth);
		py--;
    }
     
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

    char matr[MAX_Y][MAX_X]=         {"0001010101001",
									  "0001010111001",
									  "0000010101001",
									  "0001010101001",
									  "0001010101001",
									  "1111010101001",
									  "0001000111001",
									  "0001010101001",
									  "0001010101001"
								  };
	
	printf("Start paint3:\n");
    vivod(matr);
	printf("\n");
	max_depth=0;
	paint3(matr,0,0,0);
	
	printf("End paint3:\n");
	vivod(matr);
	
	printf("MAX_GLUB_REC = %d\n",max_depth);
	return 0;
}

