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
	
	int xm,x1;
	int xp,x2;
	xm = x;
	xp = x;
	
	if ((x < 0) || (x >= MAX_X) || (y < 0) || (MAX_Y <= y) || (a[y][x] != '0')){
		glub_rec--;
		return;
	}
	
		
	x1 = a[y][xm-1];
	while(x1 == '0'){            
		a[y][xm] = '-';
		print(a, MAX_X, MAX_Y);
		printf("X = %d\n",x);
		printf("Y = %d\n",y);
		printf("XLevo = %d\n",xm);
		printf("XPravo = %d\n",xp);
		printf("-----------------\n");
		xm--;
		x1 = a[y][xm];                    
	}	
		
	x2 = a[y][xp+1];
	while(x2 == '0'){             
		a[y][xp] = '-';
		print(a, MAX_X, MAX_Y);
		printf("X = %d\n",x);
		printf("Y = %d\n",y);
		printf("XLevo = %d\n",xm);
		printf("XPravo = %d\n",xp);
		printf("-----------------\n");
		xp++;
		x2 = a[y][xp];
		if (a[y][xp] == '1'){xp--;break;}                         
	}
		
	print(a, MAX_X, MAX_Y);
		
	printf("X = %d\n",x);
	printf("Y = %d\n",y);
	printf("XLevo = %d\n",xm);
	printf("XPravo = %d\n",xp);
	printf("-----------------\n");
	a[y][x] = '-';
		
	for (int i = xm ;i <= xp;i++){ // xm - самая левая граница закрашенной области по Х, а xp - самая правая граница закрашенной области по Х
		paint(i,y+1);
		paint(i,y-1);
		
	}
	
	glub_rec--;
	printf("REC = %d\nMAX_REC = %d\n",glub_rec,max_glub_rec);
}

/*void paint(int x,int y)
{
	while(1){
		if ((x < 0) || (x >= MAX_X) || (y < 0) || (MAX_Y <= y) || (a[y][x] != '0')){
			return;
		}
		// print(a, MAX_X, MAX_Y);
		printf("-----------------\n");
		a[y][x] = '-';
		//x1 = a[y][x];
		
		
		paint(x,y+1);
		//paint(x-1,y);
		paint(x,y-1); 
			while (a[y][x-1] == '0'){ 
				x1 = a[y][x];
				a[y][x] = '-';
				x--;
			}
			while (a[y][x+1] == '0'){ 
				x1 = a[y][x];
				a[y][x] = '-';
				x++;
			}
		//x++; //
		x1 = a[y][x-1];
		while (x1 == '0'){
			a[y][x] = '-';
			x--;
			x1 = a[y][x];
		}
		
		x++;
	}
}*/

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

/*void paint(int x,int y)
{
	while(1){
		if ((x < 0) || (x >= MAX_X) || (y < 0) || (MAX_Y <= y) || (a[y][x] != '0')){
			//fprintf(stderr,"err\n");
			return;
		}
		print(a, MAX_X, MAX_Y);
		printf("-----------------\n");
		while (1) {
			if (a[y][x-1]=='0'){
				//printf("DEBUG : %d\n",a[y][x-1]);
				a[y][x] = '-';
				x--;
			}
			else if (a[y][x+1]=='0'){
				//printf("DEBUG : %d\n",a[y][x+1]);
				a[y][x] = '-';
				x++;
			}
			//else break;
			else {
			print(a, MAX_X, MAX_Y);
			printf("-----------------\n");
			break;}
		}
		a[y][x] = '-';
		//paint(x+1,y);
		paint(x,y+1);
		//paint(x-1,y);
		paint(x,y-1);
		y--;
	}
}*/
