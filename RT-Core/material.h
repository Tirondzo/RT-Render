#ifndef MATERIAL_H
#define MATERIAL_H

class Intersection;

#include "color.h"
#include "intersection.h"
#include "vector3d.h"
#include "ray.h"

class Material
{
private:
    Color color;
    float kd;
    float ks;
    float kt;
    float reflectivity;
    float shiness;
    float ior;

    bool isLight;


    Ray refract(const Intersection &intersection, const Ray &ray) const;
    Ray reflect(const Intersection &intersection, const Ray &ray) const;
public:
    Material(const Color &color,
             float kd = 0.6f,
             float ks = 0.4f,
             float kt = 0.0f,
             float reflectivity = 0.13f,
             float shininess = 100.0f) :
        color(color),
        kd(kd), ks(ks), kt(kt),
        reflectivity(reflectivity),
        ior(1.5f),
        shiness(shininess), isLight(false) {}

    float getReflectivity() const;
    float getShiness() const;

    bool IsLight() const;
    void setIsLight(bool value);
    Color getColor() const;


    double getCoef(const Intersection &intersection, const Ray &ray, const Ray &newRay, float rand) const;
    Ray getNewRay(const Intersection &intersection, const Ray &ray, float rand = .0f) const;

};

#endif // MATERIAL_H
