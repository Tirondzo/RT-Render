#include "plane.h"
#include <cmath>

Plane::Plane(Material *material, Vector3D center, Vector3D normal, double w, double l) :
    Object(material), center(center), normal(normal.normalize()), w(w), l(l)
{
    if (std::fabs(normal.getX()) > std::fabs(normal.getY()))
        right = Vector3D(normal.getZ(), 0, -normal.getX()).normalize();
    else right = Vector3D(0, -normal.getZ(), normal.getY()).normalize();
    forward = Vector3D::cross(right, normal);
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
        if(w != -1){
            if(std::fabs(Vector3D::dot(point-center, right)) > w/2){
                return Intersection(this);
            }
        }
        if(l != -1){
            if(std::fabs(Vector3D::dot(point-center, forward)) > l/2){
                return Intersection(this);
            }
        }
        return Intersection(this, dist, point, normal, true);
    }
}
