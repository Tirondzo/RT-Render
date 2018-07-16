#ifndef MATERIAL_H
#define MATERIAL_H

class Intersection;

#include "color.h"
#include "intersection.h"
#include "ray.h"
#include "randomly.h"
#include <Eigen/Core>
using namespace Eigen;

class Material : protected Randomly
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
             float reflectivity = 0.9f,
             float shininess = 100.0f) :
        Randomly(),
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

    double getIOR(double A, double B, double C, double D, double E, double wlen) const;

    double getCoef(const Intersection &intersection, const Ray &ray, const Ray &newRay, float rand);
    Ray getNewRay(const Intersection &intersection, const Ray &ray, float rand = .0f);

};

#endif // MATERIAL_H
