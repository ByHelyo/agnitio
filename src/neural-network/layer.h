#ifndef AGNITIO_LAYER_H
#define AGNITIO_LAYER_H

#include <stddef.h>

struct Layer
{
    size_t size;

    struct Neuron *neurons;
};

/**
 * Create a layer
 *
 * @param nb_neurons : number of neurons
 * @param nb_input_neurons : number of input neurons or numer of weights
 * @return layer created
 */
struct Layer layer_build(size_t nb_neurons, size_t nb_input_neurons);

/**
 * Free layer's fields
 *
 * @param layer
 */
void layer_free(struct Layer *layer);

/**
 * Print the layer
 *
 * @param layer
 */
void layer_print(struct Layer *layer);

/**
 * Apply feed forward in a layer by using the activations of a previous layer
 *
 * @param prev_layer
 * @param layer
 */
void layer_feedforward(struct Layer *prev_layer, struct Layer *layer);

/**
 * Set the activations in layer
 *
 * @param layer
 * @param activation
 */
void layer_set_activation(struct Layer *layer, double *activation);

/**
 * Get the activations of a layer
 *
 * @param layer
 * @param activation
 */
void layer_get_activation(struct Layer *layer, double *activation);

#endif // AGNITIO_LAYER_H
