#include "database.h"
#include "../config.h"
#include "../utils/string.h"
#include <err.h>

struct DataBase database_build(char *path)
{
    struct DataBase database;

    FILE *file = fopen(path, "r");
    if (file == NULL)
        err(1, "Cannot open file");

    char *lineptr = NULL;
    size_t n = 0;

    database_set_size(&database, file, &lineptr, &n);

    database_set_tests(&database, file, &lineptr, &n);

    free(lineptr);
    fclose(file);
    return database;
}

void database_set_size(struct DataBase *database, FILE *file, char **lineptr, size_t *n)
{
    ssize_t nread = getline(lineptr, n, file);
    if (nread == -1)
        err(1, "Cannot get number of inputs");

    database->size = strtol(*lineptr, NULL, 10);

    database->input = calloc(database->size, sizeof(double *));
    if (database->input == NULL)
        err(1, "Cannot alloc database->input");

    database->output = calloc(database->size, sizeof(int));
    if (database->input == NULL)
        err(1, "Cannot alloc database->input");
}

void database_set_tests(struct DataBase *database, FILE *file, char **lineptr, size_t *n)
{
    size_t current_test = 0;

    ssize_t nread = 0;

    while (1)
    {
        nread = getline(lineptr, n, file);
        if (nread <= 0)
            break;

        database_set_test(database, current_test, *lineptr);

        ++current_test;
    }
}

void database_set_test(struct DataBase *database, size_t current_test, char *lineptr)
{
    database->input[current_test] = calloc(INPUT_NEURONS, sizeof(double));
    if (database->input[current_test] == NULL)
        err(1, "Cannot calloc for a test");

    database->output[current_test] = strtol(lineptr, &lineptr, 10);

    database_set_test_input(database->input[current_test], lineptr);
}

void database_set_test_input(double *input, char *p_str)
{
    size_t current_index = 0;

    string_skip_delim(&p_str, ": ");

    while (*p_str != '\n')
    {
        input[current_index] = strtol(p_str, &p_str, 10);
        string_skip_delim(&p_str, ": ");

        ++current_index;
    }
}

void database_free(struct DataBase *database)
{
    for (size_t current_test = 0; current_test < database->size; ++current_test)
    {
        free(database->input[current_test]);
    }
    free(database->input);
    free(database->output);
}
