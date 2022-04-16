#include "array.h"

#include <stdio.h>
#include <stdlib.h>

void array_print(double *arr, size_t size)
{
    if (size == 0)
        printf("Empty array\n");

    printf("array:");
    for (size_t i = 0; i < size; ++i)
    {
        printf(" %.16f", arr[i]);
    }

    printf("\n");
}

void array_print_it(size_t *start, size_t *end)
{
    if (start == end)
        printf("Empty array\n");

    printf("array:");
    while (start != end)
    {
        printf(" %zu", *start);

        ++start;
    }

    printf("\n");
}

size_t array_max_size_t(size_t *arr, size_t size)
{
    size_t max = 0;

    for (size_t i = 1; i < size; ++i)
    {
        if (arr[i] > arr[max])
            max = i;
    }

    return arr[max];
}

size_t array_max_index_double(double *arr, size_t size)
{
    size_t max = 0;

    for (size_t i = 1; i < size; ++i)
    {
        if (arr[i] > arr[max])
        {
            max = i;
        }
    }

    return max;
}

void array_shuffle(double **array, int *array2, size_t size)
{
    for (size_t i = size - 1; i > 0; --i)
    {
        size_t j = rand() % (i + 1);
        array_swap_pdouble(array, i, j);
        array_swap_int(array2, i, j);
    }
}

void array_swap_pdouble(double **array, size_t i, size_t j)
{
    double *tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void array_swap_int(int *array, size_t i, size_t j)
{
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}
