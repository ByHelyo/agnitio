#include "neuron-learn.h"

#include "sigmoid.h"

void neuron_init_backpropagation(struct Neuron *neuron)
{
    for (size_t current_weight = 0; current_weight < neuron->size - 1; ++current_weight)
    {
        neuron->delta_nabla_w[current_weight] = 0.;
        neuron->nabla_w[current_weight] = 0.;
    }

    neuron->nabla_b = 0.;
    neuron->delta_nabla_b = 0.;
    neuron->activation = 0.;
    neuron->z = 0;
}

void neuron_cost_derivative(struct Neuron *neuron, double *delta, double *output)
{
    *delta = (neuron->activation - *output) * sigmoid_prime(neuron->z);
}

void neuron_apply_prime(struct Neuron *neuron, double *sp)
{
    *sp = sigmoid_prime(neuron->z);
}

void neuron_add_nabla(struct Neuron *neuron)
{
    neuron->nabla_b += neuron->delta_nabla_b;

    for (size_t current_weight = 0; current_weight < neuron->size; ++current_weight)
    {
        neuron->nabla_w[current_weight] += neuron->delta_nabla_w[current_weight];
    }
}

void neuron_update(struct Neuron *neuron, double eta, size_t mini_batch_size)
{
    neuron->bias = neuron->bias - (eta / mini_batch_size) * neuron->nabla_b;

    for (size_t current_weight = 0; current_weight < neuron->size; ++current_weight)
    {
        neuron->weights[current_weight] =
            neuron->weights[current_weight] - (eta / mini_batch_size) * neuron->nabla_w[current_weight];
    }
}
