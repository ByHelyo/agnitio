#ifndef AGNITIO_CONFIG_H
#define AGNITIO_CONFIG_H

#include <stdlib.h>

#define INPUT_NEURONS 784
#define OUTPUT_NEURONS 62

#define NUM_LAYERS 3
#define NEURONS_FIRST_LAYER 70

#define EPOCHS 1
#define MINI_BATCH_SIZE 10
#define LEARNING_RATE 3.0

#define NETWORK_SAVE "assets/data.txt"

extern size_t sizes_layers[NUM_LAYERS];

#endif // AGNITIO_CONFIG_H
