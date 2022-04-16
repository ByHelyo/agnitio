#include "image-binarization.h"
#include <err.h>

#define MAX_INTENSITY 256

void image_binarization(struct Image *image)
{
    // Init histogram
    unsigned long histogram[MAX_INTENSITY];

    for (size_t i = 0; i < MAX_INTENSITY; ++i)
    {
        histogram[i] = 0;
    }

    // Compute image histogram
    size_t len = image->width * image->height;
    for (size_t i = 0; i < len; ++i)
    {
        size_t value = image->matrix[i].red;

        histogram[value] += 1;
    }

    // Auxiliary value for computing mu_2
    double sum = 0;
    for (size_t i = 0; i < MAX_INTENSITY; ++i)
    {
        sum += i * histogram[i];
    }

    // Update q_1
    unsigned char threshold = 0;

    double var_max = 0;
    double q_1 = 0;
    double sumB = 0;
    for (size_t t = 0; t < MAX_INTENSITY; ++t)
    {
        q_1 += histogram[t];
        if (q_1 == 0)
            continue;

        double q_2 = len - q_1;

        sumB += t * histogram[t];
        double u_1 = sumB / q_1;
        double u_2 = (sum - sumB) / q_2;

        // Compute between class variant
        double sigma_square = q_1 * q_2 * ((u_1 - u_2) * (u_1 - u_2));

        if (sigma_square > var_max)
        {
            threshold = t;
            var_max = sigma_square;
        }
    }

    for (size_t i = 0; i < len; ++i)
    {
        if (image->matrix[i].red > threshold)
        {
            image->matrix[i].red = 255;
            image->matrix[i].green = 255;
            image->matrix[i].blue = 255;
        }
        else
        {
            image->matrix[i].red = 0;
            image->matrix[i].green = 0;
            image->matrix[i].blue = 0;
        }
    }

    image_update_from_matrix(image);
}
