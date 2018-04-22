#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class Plane : public Object
{
private:
    Vector3D center, normal;
    Vector3D right, forward;
    double w,l;

public:
    Plane(Material *material, Vector3D center, Vector3D normal, double w = -1, double l = -1);

    Intersection intersect(const Ray &ray);
};

#endif // PLANE_H
