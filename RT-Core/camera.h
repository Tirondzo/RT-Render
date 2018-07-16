#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Core>
#include <Eigen/Dense>
using namespace Eigen;

class Camera
{
private:
    Vector3d position;
    Vector3d lookAt;
    Vector3d direction;
    Vector3d up;
    Vector3d right;

    float fov;
    float focus;
    float focal;

public:
    Camera(const Vector3d position, const Vector3d lookAt, float fov = 10.0f, float focus = 3.8f, float focal = 7.5f);

    Vector3d& getPosition();
    Vector3d& getLookAt();
    Vector3d& getUp();
    Vector3d& getRight();
    Vector3d& getDirection();
    float getFov() const;
};

#endif // CAMERA_H
