#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** a;
unsigned int MAX_X, MAX_Y=0;

int max_glub_rec = 0;
int glub_rec = 0;

void print(char** matr, int x, int y) {
	for(int i=0; i<y; i++) {
		for(int j=0; j<x; j++) {
			printf("%c ", a[i][j]);
		}
		printf("\n");
	}
}

void paint(int x,int y)
{
	glub_rec++;
	if (glub_rec > max_glub_rec){
		max_glub_rec = glub_rec;
	}
	
	if ((x < 0) || (x >= MAX_X) || (y < 0) || (MAX_Y <= y) || (a[y][x] != '0')){
		glub_rec--;
		return;
	}
	print(a, MAX_X, MAX_Y);
	printf("-----------------\n");
	a[y][x] = '-';
	
	printf("DEBUG: %d\n",glub_rec);
	paint(x+1,y);
	paint(x,y+1);
	paint(x-1,y);
	paint(x,y-1);
	
	
	glub_rec--;
	printf("REC = %d\nMAX_REC = %d\n",glub_rec,max_glub_rec);
}

int main(int argc, char **argv)
{
	scanf("%d %d", &MAX_X, &MAX_Y);
	int x,y;
	scanf("%d %d", &x, &y);
	a = malloc(MAX_Y * sizeof(char*));
	for(int i=0;i<MAX_Y;i++) {
		a[i] = malloc((MAX_X) * sizeof(char));
		scanf("%s", a[i]);
	}
	paint(x,y);
	print(a, MAX_X, MAX_Y);
	printf("MAX_GLUB_REC = %d\n",max_glub_rec);
	return 0;
}
