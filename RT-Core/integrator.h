#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "color.h"
#include "ray.h"
#include "scene.h"

class Integrator
{
public:
    Integrator();
    static Color trace(Scene *scene, const Ray &ray, int maxDepth, int depth = 0);
};

#endif // INTEGRATOR_H
