#include "image-greyscale.h"

void image_greyscale(struct Image *image)
{
    for (size_t row = 0; row < image->height; ++row)
    {
        for (size_t col = 0; col < image->width; ++col)
        {
            Uint8 greyscale = 0.3 * image->matrix[row * image->width + col].red +
                              0.59 * image->matrix[row * image->width + col].green +
                              0.11 * image->matrix[row * image->width + col].blue;

            image->matrix[row * image->width + col].red = greyscale;
            image->matrix[row * image->width + col].green = greyscale;
            image->matrix[row * image->width + col].blue = greyscale;
        }
    }

    image_update_from_matrix(image);
}
