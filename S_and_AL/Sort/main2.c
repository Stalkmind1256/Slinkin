#include <stdio.h>
#include <string.h>

int sort_numbers(const void *num1, const void *num2) {
    return *(int *) num1 - *(int *) num2;
}

void bin_insert_sort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *)) {
    char *array = (char *) base;
    char temp[size];
    for (int i = 1; i < num; i++) {
        memcpy(temp, &array[i * size], size);
        int left = 0, right = i;
        while (left < right) {
            int middle = (left + right) / 2;
            if (compar(temp, &array[middle * size]) > 0)
                left = middle + 1;
            else
                right = middle;
        }
        memmove(&array[(left + 1) * size], &array[left * size], (i - left) * size);
        memcpy(&array[left * size], temp, size);
    }
}

int main() {
    int array[5] = {5, 2, 4, 1, 3};
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
