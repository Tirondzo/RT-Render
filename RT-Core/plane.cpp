#include "plane.h"
#include <cmath>

Plane::Plane(Material *material, Vector3d center, Vector3d normal, double w, double l) :
    Object(material), center(center), normal(normal.normalized()), w(w), l(l)
{
    if (std::fabs(normal.x()) > std::fabs(normal.y()))
        right = Vector3d(normal.z(), 0, -normal.x()).normalized();
    else right = Vector3d(0, -normal.z(), normal.y()).normalized();
    forward = right.cross(normal);
}


Intersection Plane::intersect(const Ray &ray){
    float dot = normal.dot(ray.getDirection());

    Intersection res = Intersection(this);

    if (dot == 0.0f) {
        return Intersection(this);
    } else {
        float dist = (center - ray.getOrigin()).dot(normal) / dot;

        if (dist < 0.0f)
            return Intersection(this);

        Vector3d point = ray.getOrigin() + ray.getDirection() * dist;
        if(w != -1){
            if(std::fabs((point-center).dot(right)) > w/2){
                return Intersection(this);
            }
        }
        if(l != -1){
            if(std::fabs((point-center).dot(forward)) > l/2){
                return Intersection(this);
            }
        }
        return Intersection(this, dist, point, normal, true);
    }
}
