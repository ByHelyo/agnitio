#include "layer-learn.h"

#include "neuron-learn.h"
#include "neuron.h"

void layer_init_backprop(struct Layer *layer)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_init_backpropagation(&layer->neurons[current_neuron]);
    }
}

void layer_cost_derivative(struct Layer *layer, double *output, double *delta)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_cost_derivative(&layer->neurons[current_neuron], &delta[current_neuron], &output[current_neuron]);
    }
}

void layer_compute_delta_nabla(struct Layer *prev_layer, struct Layer *layer, double *delta)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        // nabla_b
        layer->neurons[current_neuron].delta_nabla_b = delta[current_neuron];

        // nabla_w
        for (size_t prev_current_neuron = 0; prev_current_neuron < prev_layer->size; ++prev_current_neuron)
        {
            layer->neurons[current_neuron].delta_nabla_w[prev_current_neuron] =
                prev_layer->neurons[prev_current_neuron].activation * delta[current_neuron];
        }
    }
}

void layer_apply_prime(struct Layer *layer, double *sp)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_apply_prime(&layer->neurons[current_neuron], &sp[current_neuron]);
    }
}

void layer_compute_delta(struct Layer *layer, double *new_delta, double *delta, double *sp)
{
    for (size_t current_weight = 0; current_weight < layer->neurons[0].size; ++current_weight)
    {
        for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
        {
            new_delta[current_weight] += layer->neurons[current_neuron].weights[current_weight] * delta[current_neuron];
        }

        new_delta[current_weight] *= sp[current_weight];
    }
}

void layer_add_nabla(struct Layer *layer)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_add_nabla(&layer->neurons[current_neuron]);
    }
}

void layer_update(struct Layer *layer, double eta, size_t mini_batch_size)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_update(&layer->neurons[current_neuron], eta, mini_batch_size);
    }
}
