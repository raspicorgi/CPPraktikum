#include "utils.h"
#include <cstdlib>

double getRandom() {
    return rand() / (RAND_MAX + 1.0);
}

int getRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}
