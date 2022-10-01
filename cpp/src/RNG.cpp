#include "RNG.h"

#include <ctime>

double RNG::get_random()
{
    return 0.0;
}

double DefaultRNG::get_random()
{
    return 0.5;
}

MT_RNG::MT_RNG(): _mt(time(nullptr))
{
}

double MT_RNG::get_random()
{
    return _mt();
}
