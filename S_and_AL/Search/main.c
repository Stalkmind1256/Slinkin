#include <stdio.h>
#include <stdlib.h>
#include "func.c"

int check_line(int number){
	if(number % 20){
		return 0;
	}
	else{
		return 1;
	}
}

int check_bin(int number) {
    if (number > 15)
        return 1;
    else if (number < 15)
        return -1;
    return 0;
}

int main(){
	
	int result, size = 100, *mas, *indexes;
	
    mas = (int *) malloc(sizeof(int) * size);
    
    indexes = (int *) malloc(sizeof(int) * size);
    
    for (int i = 0; i < size; i++){
			mas[i] = i + 1;
		}
        
        
        
    result = line_find_one(mas, size, check_line);
    printf("Line_find_one: %d\n\n", result);
    
    result = line_find_all(mas, size, check_line, indexes, size);
     printf("Line_find_all: %d\n", find_count);
    printf("Line_find_all: %d\n", result);
    printf("Line indexes: ");
    for (int i = 0; i < result; i++)
        printf("%d ", indexes[i]);
    printf("\n\n");
   
    
    
    result = bin_find_one(mas, size, check_bin);
    printf("Bin_find_one: %d\n\n", result);
    
    int beg = 0, end = 0;
    result = bin_find_all(mas, size, check_bin, &beg, &end);
    printf("Find_count: %d\n", find_count);
    printf("Bin_find_all: %d\n", result);
    printf("Range: %d to %d\n", beg, end);
    
	free(mas);
	free(indexes);
	return 0;
}
