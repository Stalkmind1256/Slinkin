#include <stdio.h>
#include <string.h>

int sort_numbers(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void bin_insert_sort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *)) {
    char *arr = (char *) base;
    char temp[size];
    for (int i = 1; i < num; i++) {
        memcpy(temp, arr + i * size, size);
        int left = 0, right = i;
        while (left < right) {
            int middle = (left + right) / 2;
            if (compar(temp, arr + middle * size) > 0)
                left = middle + 1;
            else
                right = middle;
        }
        memmove(arr + (left + 1) * size, arr + left * size, (i - left) * size);
        memcpy(arr + left * size, temp, size);
    }
}

int main() {
    int array[5] = {57, 22, 49, 12, 38};
    printf("Bin: ");
    for (unsigned short i = 0; i < 5; i++)
        printf("%d ", array[i]);
    printf("\n");
    bin_insert_sort(array, 5, sizeof(int), sort_numbers);
    printf("Bin: ");
    for (unsigned short i = 0; i < 5; i++)
        printf("%d ", array[i]);
    printf("\n");
    return 0;
}
