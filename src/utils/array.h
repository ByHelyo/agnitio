#ifndef AGNITIO_ARRAY_H
#define AGNITIO_ARRAY_H

#include <stddef.h>

void array_print(double *arr, size_t size);

void array_print_it(size_t *start, size_t *end);

size_t array_max_size_t(size_t *arr, size_t size);

/**
 * Shuffle the ''array'' using the Fisher-Yates algorithm
 *
 * @param array
 * @param size
 */

size_t array_max_index_double(double *arr, size_t size);

void array_shuffle(double **array, int *array2, size_t size);

void array_swap_pdouble(double **array, size_t i, size_t j);

void array_swap_int(int *array, size_t i, size_t j);

#endif // AGNITIO_ARRAY_H
