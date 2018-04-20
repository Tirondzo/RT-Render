#ifndef RENDER_H
#define RENDER_H

#include "camera.h"
#include "scene.h"
#include <QImage>
#include <QMutex>
#include <QThread>
#include <QSharedData>

#include <QTest>

class Render : public QObject
{
    Q_OBJECT

    QImage *image;

public:
    Render();
    ~Render();

    QImage* startRender(const Scene &scene, const Camera &camera, int width, int height, int threads = 1);
    QImage *getImage() const;

private:
    void stopThreads();
    mutable QMutex mutex;

    int activeThreads;

    int width, height;

public slots:
    void finishedOne();

signals:
    void stopAll();
    void finished();
};


namespace RenderImpl {
class Counter{
    int width;
    int height;
    int x,y;
    mutable QMutex mutex;
    Q_DISABLE_COPY(Counter)

public:
    Counter(int w, int h, int x = 0, int y = 0) : width(w), height(h), x(x), y(y), mutex(){}

    bool getNextPixel(int *rx, int *ry);
};


class Worker : public QThread{
    Q_OBJECT

    Counter *counter;
    Render *render;
    Camera *camera;
    Scene *scene;

public:
    Worker(Render* render, Counter *cnt, Camera *cam, Scene *scn) :
        render(render), counter(cnt), camera(cam), scene(scn) {}
protected:
    virtual void run();

};

}

#endif // RENDER_H
