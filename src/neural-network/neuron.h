#ifndef AGNITIO_NEURON_H
#define AGNITIO_NEURON_H

#include <stddef.h>

struct Neuron
{
    size_t size;

    double bias;

    double nabla_b;

    double delta_nabla_b;

    double *weights;

    double *nabla_w;

    double *delta_nabla_w;

    double z;

    double activation;
};

/**
 * Create a neuron
 *
 * @param nb_weights : number of weights
 * @return neuron created
 */
struct Neuron neuron_build(size_t nb_weights);

/**
 * Free neuron's fields
 *
 * @param neuron
 */
void neuron_free(struct Neuron *neuron);

/**
 * Print the neuron
 *
 * @param neuron
 */
void neuron_print(struct Neuron *neuron);

/**
 * Set activation of a neuron
 *
 * @param neuron
 * @param activation
 */
void neuron_set_activation(struct Neuron *neuron, double activation);

/**
 * Get the activation of a neuron
 *
 * @param neuron
 * @param activation
 */
void neuron_get_activation(struct Neuron *neuron, double *activation);

#endif // AGNITIO_NEURON_H
