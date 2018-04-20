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

    QImage* startRender(Scene *scene, Camera *camera, int width, int height, int threads = 1);
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

class XorShiftRandomEngine{

    uint_fast64_t s[2]{123456789, 362436069};
public:
    constexpr static uint_fast64_t max(){
        return UINT_FAST64_MAX;
    }
    constexpr static uint_fast64_t min(){
        return 0;
    }

    //xorshift+ right from wiki
    uint_fast64_t operator()(){
        uint_fast64_t x = s[0];
        uint_fast64_t const y = s[1];
        s[0] = y;
        x ^= x << 23; // a
        s[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
        return s[1] + y;
    }
};

}

#endif // RENDER_H
