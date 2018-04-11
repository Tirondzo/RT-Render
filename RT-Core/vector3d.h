#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D {
    double x, y, z;
public:
    Vector3D(double x=0, double y=0, double z=0);
    Vector3D(double val);

    Vector3D normalize();

    Vector3D cross(Vector3D const &v) const;

    double dot(Vector3D const &v) const;

    double length() const;

    Vector3D operator + (Vector3D const &v) const;
    Vector3D& operator += (Vector3D const &v);

    Vector3D operator - (Vector3D const & v) const;
    Vector3D& operator -= (Vector3D const & v);

    Vector3D operator * (Vector3D const & v) const;
    Vector3D& operator *= (Vector3D const & v);

    Vector3D operator * (double const s) const;
    Vector3D& operator *= (double const s);

    Vector3D operator / (Vector3D const & v) const;
    Vector3D& operator /= (Vector3D const & v);

    Vector3D operator / (double const s) const;
    Vector3D& operator /= (double const s);

    double getX() const { return x; }
    Vector3D& setX(double value) { x = value; return *this; }
    double getY() const { return y; }
    Vector3D& setY(double value) { y = value; return *this; }
    double getZ() const { return z; }
    Vector3D& setZ(double value) { z = value; return *this; }
}


#endif // VECTOR3D_H
