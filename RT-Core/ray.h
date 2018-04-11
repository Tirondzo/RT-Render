#ifndef RAY_H
#define RAY_H

#include "vector3d.h"

class Ray
{
    Vector3D origin, direction;
public:
    Ray(const Vector3D &origin, const Vector3D &direction) : origin(origin), direction(direction) {}

    Vector3D getOrigin();
    Vector3D getDirection();
};

#endif // RAY_H
