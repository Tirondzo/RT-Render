#include "integrator.h"
#include "intersection.h"

#include <math.h>
#include <cstdlib>

Color Integrator::trace(Scene *scene, const Ray &ray, int maxDepth, int depth)
{
    if(depth >= maxDepth){
        return scene->getAmbient();
    }

    Intersection intersection = scene->findClosestIntersection(ray);

    if(!intersection.isExists()){
        return scene->getAmbient();
    }

    Object *object = intersection.getObject();
    Material *mat = object->getMaterial();

    if(mat->IsLight()){
        return mat->getColor();
    }

    //float rand = random::randf();
    //float rand = (float)std::rand() / RAND_MAX;
    float rand = fDist(mt);

    Ray newRay = mat->getNewRay(intersection, ray, rand);
    Color mat_col = object->getMaterial()->getColor();

    Color traced_col = (trace(scene, newRay, maxDepth, depth+1).array() * mat_col.array()).matrix();

    return Color(((traced_col.cast<double>() * mat->getCoef(intersection, ray, newRay, rand))  / 255.0).cast<int>());
}
