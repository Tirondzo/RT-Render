#include "integrator.h"
#include "intersection.h"
#include "vector3d.h"

#include <math.h>
#include <cstdlib>

Integrator::Integrator()
{
}

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
    float rand = (float)std::rand() / RAND_MAX;

    Ray newRay = mat->getNewRay(intersection, ray, rand);
    Color mat_col = object->getMaterial()->getColor();

    Color traced_col = trace(scene, newRay, maxDepth, depth+1);
    for(int i = 0; i < 4; i++)
        traced_col[i] *= mat_col[i];

    return (traced_col * mat->getCoef(intersection, ray, newRay, rand))  / 255.0;
}
