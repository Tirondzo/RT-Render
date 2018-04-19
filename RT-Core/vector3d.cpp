#include "vector3d.h"
#include <cmath>


NVector<double, 3> Vector3D::normalize() const
{
    return (*this) / this->length();
}

double Vector3D::length() const
{
    return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
}
