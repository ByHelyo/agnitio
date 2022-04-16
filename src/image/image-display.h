#ifndef AGNITIO_IMAGE_DISPLAY_H
#define AGNITIO_IMAGE_DISPLAY_H

#include <SDL/SDL.h>

void init_sdl();

/**
 * Load an image from a file
 *
 * @param image path
 */
SDL_Surface *load_image(char *path);

/**
 * Surface of an image
 *
 * @param img SDL surface
 */
SDL_Surface *display_image(SDL_Surface *img);

/**
 * Waiting an key to be pressed
 */
void wait_for_keypressed();

#endif // AGNITIO_IMAGE_DISPLAY_H
