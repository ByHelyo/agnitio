#include "layer-save.h"

#include <stdio.h>

#include "neuron-save.h"

void layer_save(struct Layer *layer, FILE *file)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_save(&layer->neurons[current_neuron], file);
    }
}

void layer_import(struct Layer *layer, FILE *file)
{
    for (size_t current_neuron = 0; current_neuron < layer->size; ++current_neuron)
    {
        neuron_import(&layer->neurons[current_neuron], file);
    }
}
