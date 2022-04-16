#ifndef AGNITIO_NETWORK_SAVE_H
#define AGNITIO_NETWORK_SAVE_H

#include "network.h"

/**
 * Save the network
 *
 * @param network
 */
void network_save(struct Network *network);

/**
 * import the network
 *
 * @param network
 */
void network_import(struct Network *network);

#endif // AGNITIO_NETWORK_SAVE_H
