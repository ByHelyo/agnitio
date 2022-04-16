#ifndef AGNITIO_DATABASE_H
#define AGNITIO_DATABASE_H

#include <stdio.h>
#include <stdlib.h>

struct DataBase
{
    size_t size;
    double **input;
    int *output;
};

/**
 * Build a struct Database from a file
 *
 * @param path
 * @return
 */
struct DataBase database_build(char *path);

/**
 * Get the number of tests in a file and update it in ''database''
 *
 * @param database
 * @param file
 * @param lineptr
 * @param n
 */
void database_set_size(struct DataBase *database, FILE *file, char **lineptr, size_t *n);

/**
 * Add all tests in ''database''
 *
 * @param database
 * @param file
 * @param lineptr
 * @param n
 */
void database_set_tests(struct DataBase *database, FILE *file, char **lineptr, size_t *n);

/**
 * Add a test in ''database''
 *
 * @param database
 * @param current_test
 * @param lineptr
 */
void database_set_test(struct DataBase *database, size_t current_test, char *lineptr);

/**
 * add a test input in ''database''
 *
 * @param input
 * @param p_str
 */
void database_set_test_input(double *input, char *p_str);

/**
 * Free ''database'' members
 *
 * @param database
 */
void database_free(struct DataBase *database);

#endif // AGNITIO_DATABASE_H
