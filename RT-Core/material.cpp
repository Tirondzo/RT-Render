#define _USE_MATH_DEFINES
#include <cmath>

#include "material.h"
#include "sphere.h"
#include <algorithm>
#include <cstdlib>


const float EPSILON = 1e-4;

void Material::setIsLight(bool value)
{
    isLight = value;
}

Ray Material::refract(const Intersection &intersection, const Ray &ray) const
{
    float etai = 1, etat = ior;
    // ior from, ior to

    Vector3D Nrefr = intersection.getNormal();
    double NdotI = Vector3D::dot(Nrefr, ray.getDirection());
    if (NdotI < 0) {
        // we are outside the surface
        NdotI = -NdotI;
    }
    else {
        // we are inside the surface
        Nrefr = -intersection.getNormal();
        // swap the refraction indices
        std::swap(etai, etat);
    }
    float eta = etai / etat;


    float k = 1 - eta * eta * (1 - NdotI * NdotI);
    if (k < 0) {
        // total internal reflection. There is no refraction in this case
        Vector3D direction = ray.getDirection() - Nrefr * 2 * Vector3D::dot(ray.getDirection().normalize(), Nrefr);
        return Ray(intersection.getPoint() + Nrefr * EPSILON, direction);
    }else {
        Vector3D direction = ray.getDirection() * eta + Nrefr * (eta * NdotI - sqrtf(k));
        return Ray(intersection.getPoint() - Nrefr * EPSILON, direction);
    }
}

Ray Material::reflect(const Intersection &intersection, const Ray &ray) const
{
    Vector3D direction = ray.getDirection() - intersection.getNormal() * 2 * Vector3D::dot(ray.getDirection(), intersection.getNormal());
    return Ray(intersection.getPoint() + intersection.getNormal() * EPSILON, direction);
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
        //return abs(Vector3D::dot(newRay.getDirection(), intersection.getNormal()));
        return reflectivity;
    }else if(rand < kd + ks){ //specullar

    }else{ //transmittion

    }
    return 1.0;
}

Ray Material::getNewRay(const Intersection &intersection, const Ray &ray, float rand_k) const
{
    Vector3D N = intersection.getNormal();
    if(rand_k < kd){ //diffusive
        //double r1 = random::randd();
        //double r2 = random::randd();
        double r1 = (double)rand() / RAND_MAX;
        double r2 = (double)rand() / RAND_MAX;

        double phi = 2 * M_PI * r1;
        double cosTheta = sqrt(1-r2);
        double sinTheta = sqrt(1 - pow(cosTheta, 2));

        Vector3D direction = Vector3D(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);

        // gen basis

        Vector3D Nt;
        if (std::fabs(N.getX()) > std::fabs(N.getY()))
            Nt = Vector3D(N.getZ(), 0, -N.getX()).normalize();
        else Nt = Vector3D(0, -N.getZ(), N.getY()).normalize();

        Vector3D Nb = Vector3D::cross(Nt, N);

        Vector3D translated(
                    direction.getX() * Nb.getX() + direction.getY() * Nt.getX() + direction.getZ() * N.getX(),
                    direction.getX() * Nb.getY() + direction.getY() * Nt.getY() + direction.getZ() * N.getY(),
                    direction.getX() * Nb.getZ() + direction.getY() * Nt.getZ() + direction.getZ() * N.getZ());


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

    }else if(rand_k < kd + ks){ //specullar
        return reflect(intersection, ray);
    }else{ //transmittion

        float kr{};
        float cosi = Vector3D::dot(ray.getDirection(), intersection.getNormal());
        float etai = 1, etat = ior;
        if (cosi > 0) { std::swap(etai, etat); }
        // Compute sini using Snell's law
        float sint = etai / etat * sqrtf(1 - cosi * cosi);
        // Total internal reflection
        if (sint >= 1) {
            kr = 1;
        }
        else {
            float cost = sqrtf(1 - sint * sint);
            cosi = fabsf(cosi);
            float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
            float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
            kr = (Rs * Rs + Rp * Rp) / 2;
        }

        float rand_trans = 1.f / (1 - kd - ks) * (rand_k - kd - ks); //rand_k => 0..1
        if(rand_trans > kr){
            return refract(intersection, ray);
        }else{
            return reflect(intersection, ray);
        }

    }

    return Ray();
}
