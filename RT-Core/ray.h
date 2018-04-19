#ifndef RAY_H
#define RAY_H

#include "vector3d.h"

class Ray
{
    Vector3D origin, direction;
public:
    Ray(const Vector3D &origin, const Vector3D &direction) : origin(origin), direction(direction) {}
    Ray() : origin(), direction() {}

    Vector3D getOrigin() const;
    Vector3D getDirection() const;
};

#endif // RAY_H
