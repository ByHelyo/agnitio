#include "neuron.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/random.h"

struct Neuron neuron_build(size_t nb_weights)
{
    struct Neuron neuron = {.size = nb_weights, .bias = gaussrand()};

    if (nb_weights != 0)
    {
        neuron.weights = calloc(nb_weights, sizeof(double));
        if (neuron.weights == NULL)
            err(1, "Failed allocate neuron.weights in neuron_build()");
        neuron.nabla_w = calloc(nb_weights, sizeof(double));
        if (neuron.nabla_w == NULL)
            err(1, "Failed allocate neuron.nabla_w in neuron_build()");
        neuron.delta_nabla_w = calloc(nb_weights, sizeof(double));
        if (neuron.nabla_w == NULL)
            err(1, "Failed allocate neuron.delta_nabla_w in neuron_build()");

        for (size_t current_weight = 0; current_weight < nb_weights; ++current_weight)
        {
            neuron.weights[current_weight] = gaussrand();

            neuron.nabla_w[current_weight] = 0.;
            neuron.delta_nabla_w[current_weight] = 0.;
        }

        neuron.bias = gaussrand();

        neuron.nabla_b = 0.;
        neuron.delta_nabla_b = 0.;

        neuron.z = 0.;
        neuron.activation = 0.;
    }
    else
    {
        neuron.weights = NULL;
        neuron.nabla_w = NULL;
        neuron.delta_nabla_w = NULL;
        neuron.bias = 0.;
        neuron.nabla_b = 0.;
        neuron.delta_nabla_b = 0.;
        neuron.z = 0.;
        neuron.activation = 0.;
    }

    return neuron;
}

void neuron_free(struct Neuron *neuron)
{
    free(neuron->weights);
    free(neuron->nabla_w);
    free(neuron->delta_nabla_w);
}

void neuron_print(struct Neuron *neuron)
{
    printf("        bias = %.16f\n", neuron->bias);
    for (size_t current_weight = 0; current_weight < neuron->size; ++current_weight)
    {
        printf("        weight %zu = %.16f\n", current_weight, neuron->weights[current_weight]);
    }
}

void neuron_set_activation(struct Neuron *neuron, double activation)
{
    neuron->activation = activation;
}

void neuron_get_activation(struct Neuron *neuron, double *activation)
{
    *activation = neuron->activation;
}
