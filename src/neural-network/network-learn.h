#ifndef AGNITIO_NETWORK_LEARN_H
#define AGNITIO_NETWORK_LEARN_H

#include <stdlib.h>

#include "database.h"
#include "network.h"

/**
 * Make the network learn
 *
 * @param network
 * @param training_data
 * @param epochs
 * @param mini_batches_size
 * @param eta learning rate
 */
void network_SGD(struct Network *network, struct DataBase *training_data, size_t epochs, size_t mini_batches_size,
                 double eta);

/**
 * Apply stochastic gradient
 *
 * @param network
 * @param training_data
 * @param eta
 * @param mini_batch_size
 * @param begin
 */
void network_update_mini_batch(struct Network *network, struct DataBase *training_data, double eta,
                               size_t mini_batch_size, size_t begin);

/**
 * Apply back propagation
 *
 * @param network
 * @param input
 * @param output
 */
void network_backpropagation(struct Network *network, double *input, int output);

/**
 * Compute the cost derivative
 *
 * @param network
 * @param output
 * @return
 */
double *network_cost_derivative(struct Network *network, double *output);

/**
 * Backpropagate the network
 *
 * @param network
 * @param delta
 */
void network_backpropagate(struct Network *network, double **delta);

/**
 * Compute initial delta
 *
 * @param network
 * @param idx_layer
 * @param delta
 * @param sp
 */
void network_compute_delta(struct Network *network, size_t idx_layer, double **delta, double *sp);

/**
 * Apply prime activation function and store it in sp
 *
 * @param network
 * @param idx_layer
 * @param sp
 */
void network_apply_prime(struct Network *network, size_t idx_layer, double *sp);

/**
 * Init network before backpropagation
 *
 * @param network
 */
void network_init_backpropagation(struct Network *network);

/**
 * Add mabla_delta_w and nabla_delta_b to nabla_w and nabla_b
 *
 * @param network
 */
void network_add_nabla(struct Network *network);

/**
 * Update the network
 *
 * @param network
 * @param eta
 * @param mini_batch_size
 */
void network_update(struct Network *network, double eta, size_t mini_batch_size);

#endif // AGNITIO_NETWORK_LEARN_H
