#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class Sphere : public Object
{
private:
    Vector3D center;
    float radius;

public:
    Sphere(const Material &material, Vector3D center, float radius);

    Intersection intersect(const Ray &ray);
};

#endif // SPHERE_H
