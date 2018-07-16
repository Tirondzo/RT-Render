#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class Sphere : public Object
{
private:
    Vector3d center;
    float radius;

public:
    Sphere(Material *material, Vector3d center, float radius);

    Intersection intersect(const Ray &ray);
};

#endif // SPHERE_H
