#ifndef AGNITIO_NETWORK_H
#define AGNITIO_NETWORK_H

#include <stddef.h>

struct Network
{
    size_t num_layers;

    size_t *sizes;

    size_t max_neuron_layer;

    struct Layer *layers;
};

/**
 * Create a network
 *
 * @param network_input
 * @return the new network
 */
struct Network network_build(size_t num_layers, size_t *sizes);

/**
 * Free the network and its fields
 *
 * @param network
 */
void network_free(struct Network *network);

/**
 * Print a network
 *
 * @param network
 */
void network_print(struct Network *network);

/**
 * Apply feed forward with a given input and store it in output
 *
 * @param network
 * @param input
 * @param output
 */
void network_feedforward(struct Network *network, double *input, double *output);

#endif // AGNITIO_NETWORK_H
