#include "network-learn.h"

#include <err.h>

#include "../utils/array.h"
#include "layer-learn.h"

void network_SGD(struct Network *network, struct DataBase *training_data, size_t epochs, size_t mini_batches_size,
                 double eta)
{
    for (size_t epoch = 0; epoch < epochs; ++epoch)
    {
        array_shuffle(training_data->input, training_data->output, training_data->size);

        for (size_t mini_batch_start = 0; mini_batch_start < training_data->size; mini_batch_start += mini_batches_size)
        {
            network_update_mini_batch(network, training_data, eta, mini_batches_size, mini_batch_start);
        }

        printf("Epoch %zu completed\n", epoch + 1);
    }
}

void network_update_mini_batch(struct Network *network, struct DataBase *training_data, double eta,
                               size_t mini_batch_size, size_t begin)
{
    size_t end = begin + mini_batch_size;

    while (begin != end)
    {
        network_backpropagation(network, training_data->input[begin], training_data->output[begin]);
        network_add_nabla(network);

        ++begin;
    }

    network_update(network, eta, mini_batch_size);

    network_init_backpropagation(network);
}

void network_backpropagation(struct Network *network, double *input, int output)
{
    double *output_ref_array = calloc(network->sizes[network->num_layers - 1], sizeof(double));
    if (output_ref_array == NULL)
        err(1, "failed calloc in network_backpropagation");
    output_ref_array[output] = 1.;

    network_feedforward(network, input, NULL);

    double *delta = network_cost_derivative(network, output_ref_array);

    network_backpropagate(network, &delta);

    free(output_ref_array);
    free(delta);
}

double *network_cost_derivative(struct Network *network, double *output)
{
    double *delta = calloc(network->max_neuron_layer, sizeof(double));
    if (delta == NULL)
        err(1, "Failed to allocate delta");

    layer_cost_derivative(&network->layers[network->num_layers - 1], output, delta);

    return delta;
}

void network_backpropagate(struct Network *network, double **delta)
{
    layer_compute_delta_nabla(&network->layers[network->num_layers - 2], &network->layers[network->num_layers - 1],
                              *delta);

    double *sp = calloc(network->max_neuron_layer, sizeof(double));
    if (sp == NULL)
        err(1, "Failed allocate sp");

    for (size_t l = 2; l < network->num_layers; ++l)
    {
        network_apply_prime(network, network->num_layers - l, sp);

        network_compute_delta(network, network->num_layers - l + 1, delta, sp);

        layer_compute_delta_nabla(&network->layers[network->num_layers - l - 1],
                                  &network->layers[network->num_layers - l], *delta);
    }

    free(sp);
}

void network_apply_prime(struct Network *network, size_t idx_layer, double *sp)
{
    layer_apply_prime(&network->layers[idx_layer], sp);
}

void network_init_backpropagation(struct Network *network)
{
    for (size_t current_layer = 1; current_layer < network->num_layers; ++current_layer)
    {
        layer_init_backprop(&network->layers[current_layer]);
    }
}

void network_compute_delta(struct Network *network, size_t idx_layer, double **delta, double *sp)
{
    double *new_delta = calloc(network->max_neuron_layer, sizeof(double));

    layer_compute_delta(&network->layers[idx_layer], new_delta, *delta, sp);

    free(*delta);
    *delta = new_delta;
}

void network_add_nabla(struct Network *network)
{
    for (size_t current_layer = 1; current_layer < network->num_layers; ++current_layer)
    {
        layer_add_nabla(&network->layers[current_layer]);
    }
}

void network_update(struct Network *network, double eta, size_t mini_batch_size)
{
    for (size_t current_layer = 1; current_layer < network->num_layers; ++current_layer)
    {
        layer_update(&network->layers[current_layer], eta, mini_batch_size);
    }
}
