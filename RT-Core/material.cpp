#include "material.h"
#include "random.h"

#define _USE_MATH_DEFINES
#include <cmath>


const float EPSILON = 1e-4;

void Material::setIsLight(bool value)
{
    isLight = value;
}

float Material::getReflectivity() const
{
    return reflectivity;
}

float Material::getShiness() const
{
    return shiness;
}

bool Material::IsLight() const
{
    return isLight;
}

Color Material::getColor() const
{
    return color;
}

double Material::getCoef(const Intersection &intersection, const Ray &ray, const Ray &newRay, float rand) const
{
    if(rand < kd){ //diffusive
        return abs(Vector3D::dot(newRay.getDirection(), intersection.getNormal()));
    }else if(rand < kd + ks){ //specullar

    }else{ //transmittion

    }
    return 1.f;
}

Ray Material::getNewRay(const Intersection &intersection, const Ray &ray, float rand) const
{
    Vector3D N = intersection.getNormal();
    if(rand < kd){ //diffusive
        double r1 = random::randd();
        double r2 = random::randd();
        double phi = 2 * M_PI * r1;
        double cosTheta = sqrt(1-r2);
        double sinTheta = sqrt(1 - pow(cosTheta, 2));

        Vector3D direction = Vector3D(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);

        // gen basis

        Vector3D Nt = Vector3D(N.getZ(), 0, -N.getX()).normalize();
        Vector3D Nb = Vector3D::cross(Nt, N);

        Vector3D translated(
                    direction.getX() * Nb.getX() + direction.getY() * N.getX() + direction.getZ() * Nt.getX(),
                    direction.getX() * Nb.getY() + direction.getY() * N.getY() + direction.getZ() * Nt.getY(),
                    direction.getX() * Nb.getZ() + direction.getY() * N.getZ() + direction.getZ() * Nt.getZ());


        return Ray(intersection.getPoint() + intersection.getNormal() * EPSILON, translated);

        /* wrong
        double r1 = random::randd();
        double r2 = random::randd();
        double phi = 2 * M_PI * r1;
        double h = 2 * r2 - 1;
        double w = sqrt(1 - h*h);
        Vector3D direction = Vector3D(sin(phi)*w, cos(phi)*w, h);
        return Ray(intersection.getPoint() + intersection.getNormal() * EPSILON, direction);
        */

    }else if(rand < kd + ks){ //specullar
        Vector3D direction = ray.getDirection() - N * 2 * Vector3D::dot(ray.getDirection(), N);
        return Ray(intersection.getPoint() + intersection.getNormal() * EPSILON, direction);
    }else{ //transmittion

    }

    return Ray();
}
