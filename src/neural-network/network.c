#include "network.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/array.h"
#include "layer.h"

struct Network network_build(size_t num_layers, size_t *sizes)
{
    if (num_layers < 2)
        errx(1, "Network cannot have less than 2 layers");

    struct Network network;

    network.num_layers = num_layers;
    network.sizes = sizes;
    network.max_neuron_layer = array_max_size_t(network.sizes, network.num_layers);

    network.layers = calloc(num_layers, sizeof(struct Layer));
    if (network.layers == NULL)
        err(1, "Failed allocate for layers in network_build()");

    // Input layer has 0 neurons and 0 input neurons
    network.layers[0] = layer_build(sizes[0], 0);

    for (size_t current_layer = 1; current_layer < num_layers; ++current_layer)
    {
        network.layers[current_layer] = layer_build(sizes[current_layer], sizes[current_layer - 1]);
    }

    return network;
}

void network_free(struct Network *network)
{
    for (size_t current_layer = 0; current_layer < network->num_layers; ++current_layer)
    {
        layer_free(&network->layers[current_layer]);
    }

    free(network->layers);
}

void network_print(struct Network *network)
{
    printf("Network:\n");
    printf("number of layers: %zu\n", network->num_layers);
    printf("Maximum of neurons in a layer in this network: %zu\n", network->max_neuron_layer);

    for (size_t current_layer = 1; current_layer < network->num_layers; ++current_layer)
    {
        printf("Layer %zu:\n", current_layer);

        layer_print(&network->layers[current_layer]);
    }
}

void network_feedforward(struct Network *network, double *input, double *output)
{
    // Set the activation in the input layer
    layer_set_activation(&network->layers[0], input);

    // Start the feedforward at layer 1 since layer 0 is the input layer
    for (size_t current_layer = 1; current_layer < network->num_layers; ++current_layer)
    {
        layer_feedforward(&network->layers[current_layer - 1], &network->layers[current_layer]);
    }

    if (output != NULL)
        layer_get_activation(&network->layers[network->num_layers - 1], output);
}
