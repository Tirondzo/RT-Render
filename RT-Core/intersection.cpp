#include "intersection.h"

float Intersection::getDistance() const
{
    return distance;
}

Vector3d Intersection::getPoint() const
{
    return point;
}

Object *Intersection::getObject() const
{
    return object;
}

Vector3d Intersection::getNormal() const
{
    return normal;
}

Intersection::Intersection(Object *object, float distance, Vector3d point, Vector3d normal, bool exists) :
    object(object), distance(distance), point(point), normal(normal), exists(exists)
{

}

bool Intersection::isExists() const
{
    return exists;
}
