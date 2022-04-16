#ifndef AGNITIO_LAYER_LEARN_H
#define AGNITIO_LAYER_LEARN_H

#include "layer.h"

/**
 * Set neuron->nabla_b and neuron->nabla_w to 0 in each neuron
 *
 * @param layer
 */
void layer_init_backprop(struct Layer *layer);

/**
 * Given an output, get the derivative cost of layer and store it in delta
 *
 * @param layer
 * @param delta
 * @param output
 */
void layer_cost_derivative(struct Layer *layer, double *output, double *delta);

/**
 * Given Compute delta_nabla_w and delta_nabla_b
 *
 * @param prev_layer
 * @param layer
 * @param delta
 */
void layer_compute_delta_nabla(struct Layer *prev_layer, struct Layer *layer, double *delta);

/**
 * Given an layer, compute the sigmoid prime of each neuron and store it in sp
 *
 * @param layer
 * @param sp
 */
void layer_apply_prime(struct Layer *layer, double *sp);

/**
 * Given a delta, compute the new_delta and store in new_delta
 *
 * @param layer
 * @param new_delta
 * @param delta
 * @param sp
 */
void layer_compute_delta(struct Layer *layer, double *new_delta, double *delta, double *sp);

/**
 * Add delta_nabla_b and delta_nabla_w to nabla_b and nabla_w
 *
 * @param layer
 */
void layer_add_nabla(struct Layer *layer);

/**
 * Update the neural network
 *
 * @param layer
 * @param eta
 * @param mini_batch_size
 */
void layer_update(struct Layer *layer, double eta, size_t mini_batch_size);

#endif // AGNITIO_LAYER_LEARN_H
