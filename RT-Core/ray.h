#ifndef RAY_H
#define RAY_H

#include <Eigen/Core>
using namespace Eigen;

class Ray
{
    Vector3d origin, direction;
public:
    Ray(const Vector3d &origin, const Vector3d &direction) : origin(origin), direction(direction.normalized()) {}
    Ray() : origin(), direction() {}

    Vector3d getOrigin() const;
    Vector3d getDirection() const;
};

#endif // RAY_H
