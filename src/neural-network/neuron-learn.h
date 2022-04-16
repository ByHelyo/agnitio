#ifndef AGNITIO_NEURON_LEARN_H
#define AGNITIO_NEURON_LEARN_H

#include "neuron.h"

/**
 * Back propagate the neuron
 *
 * @param neuron
 */
void neuron_init_backpropagation(struct Neuron *neuron);

/**
 * Compute the cost derivative of the neuron with a given output
 *
 * @param neuron
 * @param delta
 * @param output
 */
void neuron_cost_derivative(struct Neuron *neuron, double *delta, double *output);

/**
 * Apply prime activation in a neuron
 *
 * @param neuron
 * @param sp
 */
void neuron_apply_prime(struct Neuron *neuron, double *sp);

/**
 * Add delta_nabla_w and delta_nabla_b to nabla_w and nabla_b
 *
 * @param neuron
 */
void neuron_add_nabla(struct Neuron *neuron);

/**
 * Update the neuron
 *
 * @param neuron
 * @param eta
 * @param mini_batch_size
 */
void neuron_update(struct Neuron *neuron, double eta, size_t mini_batch_size);

#endif // AGNITIO_NEURON_LEARN_H
