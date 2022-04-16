#ifndef AGNITIO_IMAGE_H
#define AGNITIO_IMAGE_H

#include <SDL/SDL.h>

struct Pixel;

struct Image
{
    SDL_Surface *image_surface;

    struct Pixel *matrix;

    size_t width;

    size_t height;
};

struct Pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

/**
 * Build a struct Image
 * @param path of an image
 * @return
 */
struct Image image_build(char *path);

/**
 * Free ''image'' members
 *
 * @param image
 */
void image_free(struct Image *image);

/**
 * Display image
 * Press a key to undisplay
 *
 * @param image
 */
void image_display(struct Image *image);

/**
 * Update ''image->matrix'' from ''image->surface''
 *
 * @param image
 */
void image_update_matrix(struct Image *image);

/**
 * Update ''image->surface'' from ''image->matrix''
 *
 * @param image
 */
void image_update_from_matrix(struct Image *image);

/**
 * Build input for the neural network
 *
 * @param image
 * @return input for feed forward
 */
double *image_build_input(struct Image *image);

#endif // AGNITIO_IMAGE_H
