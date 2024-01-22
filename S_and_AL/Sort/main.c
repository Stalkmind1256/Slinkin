#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
    // a < b = -1
    // a > b = 1
    // a = b = 0
}

void BubbleSort(void* base, size_t num, size_t size, int (*compare)(const void*, const void*)) {
    char* arr = (char*)base;
    size_t i, j;
    for (i = 0; i < num - 1; i++) {
        for (j = 0; j < num - 1 - i; j++) {
            if (compare(arr + j * size, arr + (j + 1) * size) > 0) {
                char temp[size];
                memcpy(temp, arr + j * size, size);
                memcpy(arr + j * size, arr + (j + 1) * size, size);
                memcpy(arr + (j + 1) * size, temp, size);
            }
        }
    }
}

void InsertSort(void* base, size_t num, size_t size, int (*compare)(const void*, const void*)) {
    char* arr = (char*)base;
    size_t i, j;
    for (i = 1; i < num; i++) {
        char temp[size];
        memcpy(temp, arr + i * size, size);
        j = i - 1;
        while (j != (size_t)-1 && compare(arr + j * size, temp) > 0) {
            memcpy(arr + (j + 1) * size, arr + j * size, size);
            j--;
        }
        memcpy(arr + (j + 1) * size, temp, size);
    }
}

void QuickSort(void* base, size_t num, size_t size, int (*compare)(const void*, const void*)) {
    char* arr = (char*)base;
    if (num <= 1) {
        return;
    }
    char* opornEL = arr + (num / 2) * size;
    char* temp = (char*)malloc(size);
    size_t i, j;
    for (i = 0, j = num - 1;; i++, j--) {
        while (compare(arr + i * size, opornEL) < 0) {
            i++;
        }
        while (compare(arr + j * size,opornEL) > 0) {
            j--;
        }
        if (i >= j) {
            break;
        }
        memcpy(temp, arr + i * size, size);
        memcpy(arr + i * size, arr + j * size, size);
        memcpy(arr + j * size, temp, size);
    }
    free(temp);
    QuickSort(arr, i, size, compare);
    QuickSort(arr + i * size, num - i, size, compare);
}

	int main() {
		
    int arr1[] = {55, 7, 9, 11, 77};
    int arr2[] = {55, 77, 9, 11, 77};
    int arr3[] = {55, 77, 99, 11, 77};
    size_t arrSize = sizeof(arr1) / sizeof(arr1[0]);

    printf("Unsorted array:\n"); 

    for (int i = 0; i < arrSize; i++) { 
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("\nBubbleSort:\n");
    BubbleSort(arr1, arrSize, sizeof(int), compare);
    for (int i = 0; i < arrSize; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("\nUnsorted array:\n");

    for (int i = 0; i < arrSize; i++) { 
        printf("%d ", arr2[i]);
    }
    printf("\n");

    printf("\nInsertSort:\n");
    InsertSort(arr2, arrSize, sizeof(int), compare);
    for (int i = 0; i < arrSize; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    printf("\nUnsorted array:\n");

    for (int i = 0; i < arrSize; i++) { 
        printf("%d ", arr3[i]);
    }
    printf("\n");

    printf("\nQuickSort:\n");
    QuickSort(arr3, arrSize, sizeof(int), compare);
    for (int i = 0; i < arrSize; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");

    return 0;
}
