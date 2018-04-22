#ifndef CAMERA_H
#define CAMERA_H

#include "vector3d.h"


class Camera
{
private:
    Vector3D position;
    Vector3D lookAt;
    Vector3D direction;
    Vector3D up;
    Vector3D right;

    float fov;
    float focus;
    float focal;

public:
    Camera(Vector3D position, Vector3D lookAt, float fov = 10.0f, float focus = 3.8f, float focal = 7.5f);

    Vector3D& getPosition();
    Vector3D& getLookAt();
    Vector3D& getUp();
    Vector3D& getRight();
    Vector3D& getDirection();
    float getFov() const;
};

#endif // CAMERA_H
