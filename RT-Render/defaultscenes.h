#ifndef DEFAULTSCENES_H
#define DEFAULTSCENES_H

#include "rendersettings.h"
#include "sphere.h"
#include "plane.h"

class Spheres1 : public RenderSettings{
public:
    Spheres1() : RenderSettings(){
        scene = new Scene();
        camera = new Camera(Vector3D(0.0f, 0.0f, 1.0f), Vector3D(1.0f, 0.0f, 1.0f), 1.0f, 9.5f, 2.0f);

        Material *whiteMat = new Material(Color(255,255,255), 1.f, .0f, .0f);
        Material *redMat = new Material(Color(255,0,0));
        Material *greenMat = new Material(Color(0,255,0));
        Material *yellowMat = new Material(Color(255,255,0));
        Material *light = new Material(Color(255,255,255));
        Material *glass = new Material(Color(255,255,255), 0,0,1);
        light->setIsLight(true);

        scene->addObject(new Plane(light, Vector3D(50.0f, 0.0f, 10.0f), Vector3D(-1.0f, 0.0f, 0.0f)));
        scene->addObject(new Plane(whiteMat, Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 1.0f)));

        scene->addObject(new Sphere(glass, Vector3D(10.0f, -0.5f, 1.5f), 1.5f));
        scene->addObject(new Sphere(yellowMat, Vector3D(12, -4.8, 2.15), 2.15f));
        scene->addObject(new Sphere(redMat, Vector3D(5.5, -2.6, 0.83), 0.83f));
        scene->addObject(new Sphere(glass, Vector3D(6.6, 1, 0.5), 0.5f));
        scene->addObject(new Sphere(redMat, Vector3D(8.5, 2.2, 0.5), 0.5f));
        scene->addObject(new Sphere(yellowMat, Vector3D(4.6, 2.15, 0.9), 0.9f));
    }
};

class Spheres2 : public RenderSettings{
public:
    Spheres2() : RenderSettings(){
        scene = new Scene();
        camera = new Camera(Vector3D(0.0f, 0.0f, 1.0f), Vector3D(1.0f, 0.0f, 1.0f), 1.0f, 9.5f, 2.0f);

        Material *whiteMat = new Material(Color(255,255,255), 1.f, .0f, .0f);
        Material *redMat = new Material(Color(255,0,0));
        Material *greenMat = new Material(Color(0,255,0));
        Material *yellowMat = new Material(Color(255,255,0));
        Material *light = new Material(Color(255,255,255));
        Material *conductor = new Material(Color(255,255,255), 0,1,0);
        light->setIsLight(true);

        scene->addObject(new Plane(light, Vector3D(50.0f, 0.0f, 10.0f), Vector3D(-1.0f, 0.0f, 0.0f)));
        scene->addObject(new Plane(whiteMat, Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 1.0f)));

        scene->addObject(new Sphere(conductor, Vector3D(10.0f, -0.5f, 1.5f), 1.5f));
        scene->addObject(new Sphere(yellowMat, Vector3D(12, -4.8, 2.15), 2.15f));
        scene->addObject(new Sphere(redMat, Vector3D(5.5, -2.6, 0.83), 0.83f));
        scene->addObject(new Sphere(conductor, Vector3D(6.6, 1, 0.5), 0.5f));
        scene->addObject(new Sphere(redMat, Vector3D(8.5, 2.2, 0.5), 0.5f));
        scene->addObject(new Sphere(yellowMat, Vector3D(4.6, 2.15, 0.9), 0.9f));
    }
};


class Corner1 : public RenderSettings{
public:
    Corner1() : RenderSettings(){
        scene = new Scene();
        camera = new Camera(Vector3D(1.0f, 1.0f, 20.0f), Vector3D(50.f, 50.f, 1.f), 1.f, 9.5f, 2.0f);

        Material *whiteMat = new Material(Color(255,255,255), 1.f, .0f, .0f, .8f);


        Material *dielectric = new Material(Color(255,255,255), 0,0,1);
        Material *conductor = new Material(Color(255,255,255), 0,1,0);


        Material *light = new Material(Color(255,255,255));
        light->setIsLight(true);
        Material *greenLightMat = new Material(Color(64,255,64), 1,0,0, .9f);
        greenLightMat->setIsLight(true);
        Material *blueLightMat = new Material(Color(64,64,255), 1,0,0, .9f);
        blueLightMat->setIsLight(true);

        scene->addObject(new Plane(whiteMat, Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 1.0f))); //floor
        scene->addObject(new Plane(whiteMat, Vector3D(0.0f, 50.0f, 0.0f), Vector3D(0.0f, -1.0f, 0.0f))); //wall
        scene->addObject(new Plane(whiteMat, Vector3D(50.0f, 0.0f, 0.0f), Vector3D(-1.0f, 0.0f, 0.0f))); //wall
        scene->addObject(new Plane(whiteMat, Vector3D(0.0f, 0.0f, 30.0f), Vector3D(0.0f, 0.0f, -1.0f))); //ceil

        scene->addObject(new Plane(whiteMat, Vector3D(-1.0f, 0.0f, 0.0f), Vector3D(1.0f, 0.0f, .0f))); //wall
        scene->addObject(new Plane(whiteMat, Vector3D(0.0f, -1.0f, 0.0f), Vector3D(0.0f, 1.0f, .0f))); //wall

        scene->addObject(new Plane(greenLightMat, Vector3D(30.0f, 49.99f, 15.0f), Vector3D(0.0f, -1.0f, 0.0f), 15,15));
        scene->addObject(new Plane(blueLightMat, Vector3D(49.99f, 30.0f, 15.0f), Vector3D(-1.0f, 0.0f, 0.0f), 15,15));
        scene->addObject(new Plane(light, Vector3D(25.f, 25.f, 29.99f), Vector3D(.0f, 0.0f, -1.0f), 25,25));

        scene->addObject(new Sphere(dielectric, Vector3D(25.0f, 25.f, 6.f), 6.f));
        scene->addObject(new Sphere(dielectric, Vector3D(25.0f, 25.f, 15.1f), 3.f));
        //scene->addObject(new Sphere(yellowMat, Vector3D(12, -4.8, 2.15), 2.15f));
        scene->addObject(new Sphere(conductor, Vector3D(25.f, 40.f, 3.f), 3.f));
        scene->addObject(new Sphere(conductor, Vector3D(40.f, 25.f, 3.f), 3.f));
        //scene->addObject(new Sphere(yellowMat, Vector3D(4.6, 2.15, 0.9), 0.9f));
    }
};

#endif // DEFAULTSCENES_H
