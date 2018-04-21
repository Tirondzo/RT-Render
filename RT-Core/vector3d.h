#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "nvector.h"

class Vector3D : public NVector<double, 3>{
public:

    Vector3D(NVector<double, 3> v) : NVector<double, 3>(v) {}
    Vector3D() : NVector<double, 3>() {}
    Vector3D(double x, double y, double z) : NVector<double, 3>(x,y,z){}

    double getX() const { return data[0]; }
    Vector3D& setX(double value) { data[0] = value; return *this; }
    double getY() const { return data[1]; }
    Vector3D& setY(double value) { data[1] = value; return *this; }
    double getZ() const { return data[2]; }
    Vector3D& setZ(double value) { data[2] = value; return *this; }
};


#endif // VECTOR3D_H
