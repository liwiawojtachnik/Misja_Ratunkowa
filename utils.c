#include "utils.h"
#include <stdlib.h>

// Funkcja random_double zwraca losową liczbę rzeczywistą z zakresu [min, max]
double random_double(double min, double max) {
    double scale = rand() / (double) RAND_MAX; 
    return min + scale * (max - min);
}

