#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class Plane : public Object
{
private:
    Vector3d center, normal;
    Vector3d right, forward;
    double w,l;

public:
    Plane(Material *material, Vector3d center, Vector3d normal, double w = -1, double l = -1);

    Intersection intersect(const Ray &ray);
};

#endif // PLANE_H
