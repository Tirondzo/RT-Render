#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "color.h"
#include "ray.h"
#include "scene.h"
#include "randomly.h"

class Integrator : protected Randomly
{
public:
    Integrator() : Randomly() {}
    Color trace(Scene *scene, const Ray &ray, int maxDepth, int depth = 0);
};

#endif // INTEGRATOR_H
