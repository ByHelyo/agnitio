#ifndef AGNITIO_LAYER_SAVE_H
#define AGNITIO_LAYER_SAVE_H

#include <stdio.h>

#include "layer.h"

/**
 * Save the layer
 *
 * @param layer
 * @param file
 */
void layer_save(struct Layer *layer, FILE *file);

/**
 * Import the layer
 *
 * @param layer
 * @param file
 */
void layer_import(struct Layer *layer, FILE *file);

#endif // AGNITIO_LAYER_SAVE_H
