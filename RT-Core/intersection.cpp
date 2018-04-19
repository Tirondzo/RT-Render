#include "intersection.h"

float Intersection::getDistance() const
{
    return distance;
}

Vector3D Intersection::getPoint() const
{
    return point;
}

Object *Intersection::getObject() const
{
    return object;
}

Vector3D Intersection::getNormal() const
{
    return normal;
}

Intersection::Intersection(Object *object, float distance, Vector3D point, Vector3D normal, bool exists) :
    object(object), distance(distance), point(point), normal(normal), exists(exists)
{

}

bool Intersection::isExists() const
{
    return exists;
}
