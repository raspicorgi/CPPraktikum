#include "utils.h"
#include <cstdlib>

// Zufallszahl zwischen 0 und 1
double getRandom() {
    return rand() / (RAND_MAX + 1.0);
}

// Zufallszahl zwischen min und max
int getRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}
