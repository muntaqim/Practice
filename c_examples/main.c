#include "quickSort.h"
#include <stdio.h>

void printArray(int *array, int size);
int main(void)
{
    int array[10] = {3,5,10,67,4,1,2,96,6,7};
    int size = 10;
    quickSort(array, size);
    printArray(array, size);
}

void printArray(int *array, int size)
{
    printf("[");
    for(int x = 0; x < size; x++)
    {
        printf("%d,", array[x]);
    }
    printf("]");
}
