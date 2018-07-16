#ifndef SCENE_H
#define SCENE_H

#include "color.h"
#include "object.h"
#include "intersection.h"

class Scene
{
    Color ambient;
    float gamma;

    std::vector<Object *, Eigen::aligned_allocator<Object*>> objects;

public:
    Scene(const Color &ambient = Color(0,0,0), float gamma = .1f) : ambient(ambient), gamma(gamma), objects() {}
    Color getAmbient() const;
    void setAmbient(const Color &value);
    float getGamma() const;
    void setGamma(float value);

    void addObject(Object * object) { objects.push_back(object); }

    Intersection findClosestIntersection(const Ray &ray) const;
};

#endif // SCENE_H
