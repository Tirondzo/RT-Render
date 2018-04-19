#include "plane.h"
#include <math.h>

Plane::Plane(const Material &material, Vector3D center, Vector3D normal) :
    Object(material), center(center), normal(normal)
{

}


Intersection Plane::intersect(const Ray &ray){
    float dot = Vector3D::dot(normal, ray.getDirection());

    Intersection res = Intersection(this);

    if (dot == 0.0f) {
        return Intersection(this);
    } else {
        float dist = Vector3D::dot(center - ray.getOrigin(), normal) / dot;

        if (dist < 0.0f)
            return Intersection(this);

        Vector3D point = ray.getOrigin() + ray.getDirection() * dist;
        return Intersection(this, dist, point, normal, true);
    }
}
