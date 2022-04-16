#include "sigmoid.h"

#include <math.h>

double sigmoid(double z)
{
    return 1. / (1. + exp(-z));
}

double sigmoid_prime(double z)
{
    return sigmoid(z) * (1.0 - sigmoid(z));
}
