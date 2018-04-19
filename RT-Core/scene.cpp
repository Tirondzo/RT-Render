#include "scene.h"

Color Scene::getAmbient() const
{
    return ambient;
}

float Scene::getGamma() const
{
    return gamma;
}

Intersection Scene::findClosestIntersection(const Ray &ray) const
{
    float closestDist = std::numeric_limits<double>::max();
    Intersection closestIntersection;

    for(Object * obj : objects){
        Intersection intersection = obj->intersect(ray);
        if(intersection.isExists() && 1e-4 < intersection.getDistance() && intersection.getDistance() < closestDist){
            closestIntersection = intersection;
            closestDist = intersection.getDistance();
        }
    }
    return closestIntersection;
}

void Scene::setAmbient(const Color &value)
{
    ambient = value;
}
