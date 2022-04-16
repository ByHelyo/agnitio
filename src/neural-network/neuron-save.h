#ifndef AGNITIO_NEURON_SAVE_H
#define AGNITIO_NEURON_SAVE_H

#include <stdio.h>

#include "neuron.h"

/**
 * Save a neuron
 *
 * @param neuron
 * @param file
 */
void neuron_save(struct Neuron *neuron, FILE *file);

/**
 * Get a neuron
 *
 * @param neuron
 * @param file
 */
void neuron_import(struct Neuron *neuron, FILE *file);

#endif // AGNITIO_NEURON_SAVE_H
