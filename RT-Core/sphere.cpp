#include "sphere.h"
#include <math.h>

Sphere::Sphere(Material *material, Vector3D center, float radius) :
    Object(material), center(center), radius(radius)
{

}


Intersection Sphere::intersect(const Ray &ray){
    Vector3D dir = ray.getDirection();
    Vector3D orig = ray.getOrigin();

    double a = Vector3D::dot(dir, dir);
    double b = 2.0 * Vector3D::dot(dir, orig - center);
    double c = Vector3D::dot(orig-center, orig-center) - pow(radius, 2);


    double discr = b*b - 4*a*c;
    if(discr <= 1e-8){
        return Intersection(this);
    }else{
        double dist1 = (-b + sqrt(discr)) / (2.0 * a);
        double dist2 = (-b - sqrt(discr)) / (2.0 * a);
        double dist;

        if( dist1 <= 1e-8 && dist2 <= 1e-8){
            return Intersection(this);
        }else if(dist1 <= 1e-8 || dist2 <= 1e-8){
            dist = fmax(dist1, dist2);
        }else{
            dist = fmin(dist1, dist2);
        }

        Vector3D point = orig + (dir*dist);
        return Intersection(this, dist, point, (point - center).normalize(), true);
    }
}
