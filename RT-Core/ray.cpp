#include "ray.h"


Ray::Ray()
{
}

Vector3D Ray::getDirection() const { return direction; }
Vector3D Ray::getOrigin() const { return origin; }
