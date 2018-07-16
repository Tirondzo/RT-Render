#include "camera.h"

float Camera::getFov() const
{
    return fov;
}


Camera::Camera(const Vector3d position, const Vector3d lookAt, float fov, float focus, float focal) :
    position(position), lookAt(lookAt), fov(fov), focus(focus), focal(focal)
{
    direction = (lookAt - position).normalized();
    up = direction.cross(Vector3d(0.0, 0.0, 1.0)).cross(direction).normalized();
    right = up.cross(direction).normalized();
}


Vector3d& Camera::getLookAt()
{
    return lookAt;
}

Vector3d& Camera::getUp()
{
    return up;
}

Vector3d& Camera::getRight()
{
    return right;
}

Vector3d& Camera::getPosition()
{
    return position;
}

Vector3d& Camera::getDirection()
{
    return direction;
}
