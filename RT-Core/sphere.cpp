#include "sphere.h"
#include <math.h>

Sphere::Sphere(Material *material, Vector3d center, float radius) :
    Object(material), center(center), radius(radius)
{

}


Intersection Sphere::intersect(const Ray &ray){
    Vector3d dir = ray.getDirection();
    Vector3d orig = ray.getOrigin();

    double a = dir.dot(dir);
    double b = 2.0 * dir.dot(orig - center);
    double c = (orig-center).dot(orig-center) - pow(radius, 2);


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

        Vector3d point = orig + (dir*dist);
        return Intersection(this, dist, point, (point - center).normalized(), true);
    }
}
