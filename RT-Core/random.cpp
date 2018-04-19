#include "random.h"
#include <random>


std::random_device rd;
std::ranlux48 mt(rd());
std::uniform_real_distribution<float> fDist(.0, 1.);
std::uniform_real_distribution<double> dDist(.0, 1.);

float random::randf()
{
    return fDist(mt);
}

double random::randd()
{
    return dDist(mt);
}
