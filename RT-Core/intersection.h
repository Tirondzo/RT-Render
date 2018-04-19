#ifndef INTERSECTION_H
#define INTERSECTION_H

class Object;

#include "vector3d.h"

class Intersection
{
private:
    Object* object;
    float distance;
    Vector3D point;
    Vector3D normal;
    bool exists;

public:
    Intersection(Object *object = nullptr,
                 float distance = .0f,
                 Vector3D point = Vector3D(),
                 Vector3D normal = Vector3D(),
                 bool exists = false);

    bool isExists() const;
    float getDistance() const;
    Vector3D getPoint() const;
    Object *getObject() const;
    Vector3D getNormal() const;
};

#endif // INTERSECTION_H
