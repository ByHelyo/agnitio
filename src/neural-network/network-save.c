#include <err.h>
#include <stdio.h>

#include "../config.h"
#include "layer-save.h"
#include "network.h"

void network_save(struct Network *network)
{
    FILE *file = fopen(NETWORK_SAVE, "w");
    if (file == NULL)
        err(1, "Can not open file");

    // network composition
    fprintf(file, "%zu\n\n", network->num_layers);

    for (size_t size = 0; size < network->num_layers; ++size)
    {
        fprintf(file, "%zu\n", network->sizes[size]);
    }

    fprintf(file, "\n");

    // save weights and biases
    for (size_t current_layer = 1; current_layer < network->num_layers; ++current_layer)
    {
        layer_save(&network->layers[current_layer], file);
    }

    fclose(file);
}

void network_import(struct Network *network)
{
    FILE *file = fopen(NETWORK_SAVE, "r");
    if (file == NULL)
        err(1, "Can not open file");

    // network composition
    size_t ret = 0;

    fscanf(file, "%zu\n\n", &ret);
    if (ret != network->num_layers)
        errx(1, "Number of layers is incorrect");

    for (size_t size = 0; size < network->num_layers; ++size)
    {
        fscanf(file, "%zu\n", &ret);
        if (ret != network->sizes[size])
            errx(1, "Number of neuron in a layer is incorrect");
    }

    fscanf(file, "\n");

    for (size_t current_layer = 1; current_layer < network->num_layers; ++current_layer)
    {
        layer_import(&network->layers[current_layer], file);
    }

    fclose(file);
}
