#include "RNG.h"

#include <ctime>

double RNG::get_random() {
    return 0.5;
}

double DefaultRNG::get_random() {
    return 0.5;
}

MT_RNG::MT_RNG(): _mt(static_cast<unsigned int>(time(nullptr))) { }

double MT_RNG::get_random() {
    return static_cast<double>(_mt()) / _mt.max();
}
