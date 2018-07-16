#ifndef INTERSECTION_H
#define INTERSECTION_H

class Object;

#include <Eigen/Core>
using namespace Eigen;

class Intersection
{
private:
    Object* object;
    float distance;
    Vector3d point;
    Vector3d normal;
    bool exists;

public:
    Intersection(Object *object = nullptr,
                 float distance = .0f,
                 Vector3d point = Vector3d(),
                 Vector3d normal = Vector3d(),
                 bool exists = false);

    bool isExists() const;
    float getDistance() const;
    Vector3d getPoint() const;
    Object *getObject() const;
    Vector3d getNormal() const;
};

#endif // INTERSECTION_H
