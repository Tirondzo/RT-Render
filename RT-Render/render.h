#ifndef RENDER_H
#define RENDER_H

#include "camera.h"
#include "scene.h"
#include <QImage>
#include <QMutex>
#include <QThread>
#include <QSharedData>

class Render : public QObject, QSharedData
{
    Q_OBJECT

    QImage *image;

public:
    Render();
    ~Render();

    QImage* startRender(const Scene &scene, const Camera &camera, int width, int height, int threads = 1);

    QImage *getImage() const;
    bool nextPixel(int *ret_x, int *ret_y);

private:
    void stopThreads();
    mutable QMutex mutex;
    int x;
    int y;
    int activeThreads;

    int width, height;

public slots:
    void process();
    void finishedOne();

signals:
    void stopAll();
    void finished();
};


class Worker : public QObject{
    Q_OBJECT

    Render *render;
    Camera *_camera;
    Scene *_scene;
    QMutex *mutex;
public:
    Worker(Render *render, QMutex *mutex, Camera *camera, Scene *scene) : render(render), mutex(mutex), _camera(camera), _scene(scene){

    }
public slots:
    void doWork();
signals:
    void finished();
private:
};

#endif // RENDER_H
