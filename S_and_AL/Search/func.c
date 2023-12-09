#include <stdio.h>
#include "findunit.h"

int line_find_one(const int src[], int src_size, testfunc func){
	int find_count = 0;
	for(int i = 0; i < src_size;i++){
		find_count++;
		if(func(src[i])!=0){
			printf("Find count:%d\n",find_count);
			return i;
			}
		}
	printf("Find count:%d\n",find_count);
	return -1;
	}

int line_find_all(const int src[], int src_size,  testfunc func,int result[], int result_maxsize){
	int counter = 0;
	find_count = 0;
	for(int i = 0; i < src_size;i++){
		find_count++;
		if(func(src[i]) !=0 ){
			if(result_maxsize != counter){
				result[counter] = i;
				counter++;
			 }else{
				 break;
				 }
			}
		}
		printf("Find_count: %d\n", find_count);
		return counter;			  
	}

int bin_find_one(const int src[], int src_size, testfunc func) {
    int left = 0, right = src_size - 1;
    find_count = 0;
    while (left <= right) {
        find_count++;
        int middle = left + (right - left) / 2;
        if (func(src[middle]) == 1)
            right = middle - 1;
        else if (func(src[middle]) == -1)
            left = middle + 1;
        else {
            printf("Find_count: %d\n", find_count);
            return middle;
        }
    }
    printf("Find_count: %d\n", find_count);
    return -1;
}

int bin_find_all(const int src[], int src_size, testfunc func, int *res_beg, int *res_end) {
    int left = 0, right = src_size - 1;
    find_count = 0;
    while (left <= right) {
        find_count++;
        int middle = left + (right - left) / 2;
        if (func(src[middle]) == 1)
            right = middle - 1;
        else if (func(src[middle]) == -1)
            left = middle + 1;
        else {
            *res_beg = middle;
            *res_end = middle;
            while (res_beg > 0) {
                if (func(src[*res_beg-1]) != 0)
                    break;
                res_beg--;
            }
            while (*res_end < src_size - 1) {
                if (func(src[*res_end+1]) != 0)
                    break;
                res_end++;
            }
            printf("Find_count: %d\n", find_count);
            return *res_end - *res_beg + 1;
        }
    }
    printf("Find_count: %d\n", find_count);
    return 0;
}
