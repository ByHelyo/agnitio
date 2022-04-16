#include "image.h"

#include <err.h>

#include "image-display.h"
#include "pixel-operations.h"

struct Image image_build(char *path)
{
    struct Image image;

    image.image_surface = load_image(path);

    image.width = image.image_surface->w;
    image.height = image.image_surface->h;

    image.matrix = calloc(image.width * image.height, sizeof(struct Pixel));
    image_update_matrix(&image);

    return image;
}

void image_free(struct Image *image)
{
    free(image->matrix);

    SDL_FreeSurface(image->image_surface);
}

void image_display(struct Image *image)
{
    SDL_Surface *screen_surface;

    screen_surface = display_image(image->image_surface);

    wait_for_keypressed();

    SDL_FreeSurface(screen_surface);
}

void image_update_matrix(struct Image *image)
{
    for (size_t row = 0; row < image->height; ++row)
    {
        for (size_t col = 0; col < image->width; ++col)
        {
            Uint32 pixel = get_pixel(image->image_surface, col, row);

            Uint8 r = 0;
            Uint8 g = 0;
            Uint8 b = 0;

            SDL_GetRGB(pixel, image->image_surface->format, &r, &g, &b);

            struct Pixel tmp = {.red = r, .green = g, .blue = b};

            image->matrix[row * image->width + col] = tmp;
        }
    }
}

void image_update_from_matrix(struct Image *image)
{
    for (size_t row = 0; row < image->height; ++row)
    {
        for (size_t col = 0; col < image->width; ++col)
        {
            Uint8 r = image->matrix[row * image->width + col].red;
            Uint8 g = image->matrix[row * image->width + col].green;
            Uint8 b = image->matrix[row * image->width + col].blue;

            Uint32 pixel = SDL_MapRGB(image->image_surface->format, r, g, b);

            put_pixel(image->image_surface, col, row, pixel);
        }
    }
}

double *image_build_input(struct Image *image)
{
    size_t len = image->width * image->height;

    double *output = calloc(len, sizeof(double));
    if (output == NULL)
        err(1, "Can not alloc");

    for (size_t current_pixel = 0; current_pixel < len; ++current_pixel)
    {
        if (image->matrix[current_pixel].red == 255)
            output[current_pixel] = 0;
        else
            output[current_pixel] = 1;
    }

    return output;
}
