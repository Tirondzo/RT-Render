#ifndef SCENE_H
#define SCENE_H

#include "color.h"
#include <vector>
#include "object.h"
#include "intersection.h"

class Scene
{
    Color ambient;
    float gamma;

    std::vector<Object *> objects;

public:
    Scene(Color ambient = Color(0,0,0), float gamma = .1f) : ambient(ambient), gamma(gamma), objects() {}
    Color getAmbient() const;
    void setAmbient(const Color &value);
    float getGamma() const;
    void addObject(Object * object) { objects.push_back(object); }

    Intersection findClosestIntersection(const Ray &ray) const;
};

#endif // SCENE_H
