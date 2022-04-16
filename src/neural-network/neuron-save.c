#include "neuron-save.h"

void neuron_save(struct Neuron *neuron, FILE *file)
{
    fprintf(file, "%.16f\n", neuron->bias);

    for (size_t current_weight = 0; current_weight < neuron->size; ++current_weight)
    {
        fprintf(file, "%.16f\n", neuron->weights[current_weight]);
    }
}

void neuron_import(struct Neuron *neuron, FILE *file)
{
    fscanf(file, "%lf\n", &neuron->bias);

    for (size_t current_weight = 0; current_weight < neuron->size; ++current_weight)
    {
        fscanf(file, "%lf\n", &neuron->weights[current_weight]);
    }
}
