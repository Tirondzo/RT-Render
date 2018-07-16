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

    Vector3d Nrefr = intersection.getNormal();
    double NdotI = Nrefr.dot(ray.getDirection());
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
        Vector3d direction = ray.getDirection() - Nrefr * (2 * ray.getDirection().normalized().dot(Nrefr));
        return Ray(intersection.getPoint() + Nrefr * EPSILON, direction);
    }else {
        Vector3d direction = ray.getDirection() * eta + Nrefr * (eta * NdotI - sqrtf(k));
        return Ray(intersection.getPoint() - Nrefr * EPSILON, direction);
    }
}

Ray Material::reflect(const Intersection &intersection, const Ray &ray) const
{
    Vector3d direction = ray.getDirection() - intersection.getNormal() * (2 * ray.getDirection().dot(intersection.getNormal()));
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

double Material::getIOR(double A, double B, double C, double D, double E, double wlen) const
{
    double wlenMicrons = wlen / 1000.;
    double wlenMicroSq = wlenMicrons * wlenMicrons;
    double L = 1. / (wlenMicroSq - 0.028);
    double ior = A + B*L + C*L*L + D*wlenMicroSq + E * wlenMicroSq * wlenMicroSq;
    return ior;
}

double Material::getCoef(const Intersection &intersection, const Ray &ray, const Ray &newRay, float rand)
{
    if(rand < kd){ //diffusive
        //return abs(Vector3d::dot(newRay.getDirection(), intersection.getNormal()));
        return reflectivity;
    }else if(rand < kd + ks){ //specullar

    }else{ //transmittion

    }
    return 1.0;
}

Ray Material::getNewRay(const Intersection &intersection, const Ray &ray, float rand_k)
{
    Vector3d N = intersection.getNormal();
    if(rand_k < kd){ //diffusive
        double r1 = dDist(mt);
        double r2 = dDist(mt);

        double phi = 2 * M_PI * r1;
        double cosTheta = sqrt(1-r2);
        double sinTheta = sqrt(1 - pow(cosTheta, 2));

        Vector3d direction = Vector3d(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);

        // gen basis

        Vector3d Nt;
        if (std::fabs(N.x()) > std::fabs(N.y()))
            Nt = Vector3d(N.z(), 0, -N.x()).normalized();
        else Nt = Vector3d(0, -N.z(), N.y()).normalized();

        Vector3d Nb = Nt.cross(N);

        // move generated vec to new basis

        Matrix3d newBasis;
        newBasis << Nb, Nt, N;
        Vector3d translated = newBasis * direction;


        return Ray(intersection.getPoint() + intersection.getNormal() * EPSILON, translated);

        /* wrong
        double r1 = random::randd();
        double r2 = random::randd();
        double phi = 2 * M_PI * r1;
        double h = 2 * r2 - 1;
        double w = sqrt(1 - h*h);
        Vector3d direction = Vector3d(sin(phi)*w, cos(phi)*w, h);
        return Ray(intersection.getPoint() + intersection.getNormal() * EPSILON, direction);
        */

    }else if(rand_k < kd + ks){ //specullar
        return reflect(intersection, ray);
    }else{ //transmittion

        float kr{};
        float cosi = ray.getDirection().dot(intersection.getNormal());
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
