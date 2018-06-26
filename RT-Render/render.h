#ifndef RENDER_H
#define RENDER_H

#include "camera.h"
#include "scene.h"
#include <QImage>
#include <QMutex>
#include <QThread>
#include <QSharedData>

#include <QTest>

namespace RenderImpl {
    class Counter;
}

class Render : public QObject
{
    Q_OBJECT

    QImage *image;

public:
    Render();
    ~Render();

    QImage* startRender(Scene *scene, Camera *camera,
                        int width, int height,
                        int threads = 1, int maxSamples = 512,
                        int maxReflections = 64);
    QImage *getImage() const;
    int getCurrentProgress() const;
    int getTargetProgress() const;
    QTime timer;
    int getRenderedTime() const;

private:
    void stopThreads();
    mutable QMutex mutex;

    int activeThreads{};

    int width{}, height{};
    int maxSamples;
    int maxReflections;
    int renderFinishedTime{};
    RenderImpl::Counter *counter;

public slots:
    void finishedOne();

signals:
    void stopAll();
    void finished(int ms);
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

    bool getNextPixelGroup(int *rx, int *ry, int count = 10);
    int getCurrPixelsDone();
};


class Worker : public QThread, protected Randomly{
    Q_OBJECT

    Counter *counter{};
    Render *render{};
    Camera *camera{};
    Scene *scene{};
    bool active;
    int maxSamples;
    int maxReflections;

public:
    Worker(Render* render, Counter *cnt,
           Camera *cam, Scene *scn,
           int maxSamples = 512, int maxReflections = 64) :
        render(render), counter(cnt),
        camera(cam), scene(scn),
        active(true), maxSamples(maxSamples),
        maxReflections(maxReflections), Randomly(){}

public slots:
    void kill();
protected:
    virtual void run();
};
}

#endif // RENDER_H
