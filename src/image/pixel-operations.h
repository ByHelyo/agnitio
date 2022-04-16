#ifndef AGNITIO_PIXEL_OPERATIONS_H
#define AGNITIO_PIXEL_OPERATIONS_H

#include <SDL/SDL.h>

/**
 * Get (x, y) pixel from the surface
 *
 * @param surface
 * @param x : width
 * @param y : height
 * @return the pixel
 */
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);

/**
 * Put ''pixel'' in (x. y) in the ''surface''
 *
 * @param surface
 * @param x : width
 * @param y :height
 * @param pixel to put in the surface
 */
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

/**
 * Update ''screen'' surface from ''image'' surface
 *
 * @param screen surface
 * @param image surface
 */
void update_surface(SDL_Surface *screen, SDL_Surface *image);

#endif // AGNITIO_PIXEL_OPERATIONS_H
