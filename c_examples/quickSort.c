#include "quickSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
void quickSort(int *values, int length)
{
    if(length > 1)
        quickSortInternal(values, 0, length - 1);
}

void quickSortInternal(int *values, int start, int end)
{
    if(start >= end)
    {
        return;
    }
    //choose a random pivot
    
    int pivot = rand(); 
    pivot = (pivot % (end - start)) + start;

    pivot = divideQuickSort(values, start, end, pivot);
    quickSortInternal(values, start, values[pivot - 1]);
    quickSortInternal(values, values[pivot + 1], end);
}

int divideQuickSort(int *values, int start, int end, int pivot)
{
    //replace pivot with first in section
    int temp = values[pivot];
    values[pivot] = values[start];
    values[start] = temp;

    pivot = start;
    int left = start;
    int right = end;

    while(left < right)
    {
        if(values[left] <= values[pivot])
            left++;
        else if(values[right] > values[pivot])
            right--;
        else
        {
            temp = values[left];
            values[left] = values[right];
            values[right] = temp;
        }
    }

    temp = values[left - 1];
    values[left - 1] = values[pivot];
    values[pivot] = temp;
    return (left - 1);
}
