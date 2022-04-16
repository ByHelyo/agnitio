#include "layer.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "neuron.h"
#include "sigmoid.h"

struct Layer layer_build(size_t nb_neurons, size_t nb_input_neurons)
{
    struct Layer layer = {.size = nb_neurons, .neurons = NULL};

    if (nb_neurons == 0)
        errx(1, "Build a layer with 0 neuron");

    layer.neurons = calloc(nb_neurons, sizeof(struct Neuron));
    if (layer.neurons == NULL)
        err(1, "Failed allocation in layer_build");

    for (size_t current_neuron = 0; current_neuron < nb_neurons; ++current_neuron)
    {
        layer.neurons[current_neuron] = neuron_build(nb_input_neurons);
    }

    return layer;
}

void layer_free(struct Layer *layer)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_free(&layer->neurons[current_neuron]);
    }

    free(layer->neurons);
}

void layer_print(struct Layer *layer)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        printf("    Neuron %zu:\n", current_neuron);

        neuron_print(&layer->neurons[current_neuron]);
    }
}

void layer_feedforward(struct Layer *prev_layer, struct Layer *layer)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        layer->neurons[current_neuron].z = 0.;

        for (size_t current_weight = 0; current_weight < prev_layer->size; ++current_weight)
        {
            layer->neurons[current_neuron].z +=
                prev_layer->neurons[current_weight].activation * layer->neurons[current_neuron].weights[current_weight];
        }

        layer->neurons[current_neuron].z += layer->neurons[current_neuron].bias;

        layer->neurons[current_neuron].activation = sigmoid(layer->neurons[current_neuron].z);
    }
}

void layer_set_activation(struct Layer *layer, double *activation)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_set_activation(&layer->neurons[current_neuron], activation[current_neuron]);
    }
}

void layer_get_activation(struct Layer *layer, double *activation)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_get_activation(&layer->neurons[current_neuron], &activation[current_neuron]);
    }
}
