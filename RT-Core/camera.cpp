#include "camera.h"
#include "vector3d.h"

float Camera::getFov() const
{
    return fov;
}


Camera::Camera(Vector3D position, Vector3D lookAt, float fov, float focus, float focal) :
    position(position), lookAt(lookAt), fov(fov), focus(focus), focal(focal)
{
    direction = (lookAt - position).normalize();
    up = Vector3D::cross(direction, Vector3D::cross(Vector3D(0.0f, 0.0f, 1.0f), direction)).normalize();
    right = Vector3D::cross(up, direction);
}


Vector3D Camera::getLookAt() const
{
    return lookAt;
}

Vector3D Camera::getUp() const
{
    return up;
}

Vector3D Camera::getRight() const
{
    return right;
}

Vector3D Camera::getPosition() const
{
    return position;
}
