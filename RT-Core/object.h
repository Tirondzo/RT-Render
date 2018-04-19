#ifndef OBJECT_H
#define OBJECT_H

class Intersection;

#include "ray.h"
#include "intersection.h"
#include "material.h"

class Object
{
protected:
    Material material;

public:
    Object(const Material material);

    virtual Intersection intersect(const Ray &ray) = 0;

    Material getMaterial() const;
    void setMaterial(const Material &value);
};

#endif // OBJECT_H
