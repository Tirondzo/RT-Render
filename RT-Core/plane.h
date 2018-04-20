#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class Plane : public Object
{
private:
    Vector3D center, normal;

public:
    Plane(Material *material, Vector3D center, Vector3D normal);

    Intersection intersect(const Ray &ray);
};

#endif // PLANE_H
