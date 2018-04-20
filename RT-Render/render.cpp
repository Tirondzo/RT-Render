#include "render.h"
#include "integrator.h"
#include "random.h"

#include <QThread>
#include <QDebug>




QImage *Render::getImage() const
{
    return image;
}

Render::Render() : mutex()
{
    image = nullptr;
}

Render::~Render()
{
    //delete [] image;
}


QImage *Render::startRender(const Scene &scene, const Camera &camera, int _width, int _height, int threads)
{
    //if(image != nullptr)
        //delete [] image;

    //mutex.lock();

    width = _width;
    height = _height;
    image = new QImage(width, height, QImage::Format::Format_RGB888);

    Scene * _scene = new Scene(scene);
    Camera * _camera = new Camera(camera);

    activeThreads = threads;


    /*for(int i = 0; i < threads; i++){
        QThread* thread = new QThread;
        //moveToThread(thread);
        connect(thread, SIGNAL(started()), this, SLOT(process()));
        //connect(this, SIGNAL(finished()), thread, SLOT(quit()));
        connect(this, SIGNAL(stopAll()), thread, SLOT(quit()));
        //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
    }*/

    RenderImpl::Counter *counter = new RenderImpl::Counter(width, height, -1, 0);

    for(int i = 0; i < threads; i++){
        RenderImpl::Worker *thrd = new RenderImpl::Worker(this, counter, _camera, _scene);
        connect(thrd, SIGNAL(finished()), this, SLOT(finishedOne()));
        connect(thrd, SIGNAL(finished()), thrd, SLOT(deleteLater()));
        thrd->start();
        thrd->setPriority(QThread::HighestPriority);
    }

    return image;
}

void Render::stopThreads()
{

}


void Render::finishedOne()
{
    activeThreads--;
    if(activeThreads <= 0)
        emit finished();
}


bool RenderImpl::Counter::getNextPixel(int *rx, int *ry){
    //QMutexLocker ml(&mutex);
    mutex.lock();
    x++;
    if(x >= width){
        x = 0;
        y++;
    }
    if(y >= height){
        mutex.unlock();
        return false;
    }

    *rx = x; *ry = y;
    mutex.unlock();
    return true;
}

void RenderImpl::Worker::run(){
    QImage *img = render->getImage();
    int width = img->width();
    int height = img->height();

    int x,y;
    while(counter->getNextPixel(&x, &y)){
        //qDebug() << x << " " << y << QThread::currentThread();

       //img->setPixelColor(x,height-1-y, QColor(250,120,20));
       //QTest::qSleep(10);
       //continue;
       int ns = 32;
       int r = 0, g = 0, b = 0, a = 0;

       for (int s = 0; s < ns; ++s) {
           //double dx = random::randd();
           //double dy = random::randd();

           double dx = (double)rand() / RAND_MAX;
           double dy = (double)rand() / RAND_MAX;


           Vector3D xShift = camera->getRight() * (x - width/2.0 + dx) / width * camera->getFov();
           Vector3D yShift = camera->getUp() * ((y - height/2.0 + dy) / width * camera->getFov());

           Ray ray(camera->getPosition(), camera->getLookAt() + xShift + yShift - camera->getPosition());

           Color color = Integrator::trace(*scene, ray, 6, 0);

           r += color.getR();
           g += color.getG();
           b += color.getB();
           a += color.getA();
       }

       img->setPixelColor(x,height-1-y, QColor(r/ns,g/ns,b/ns));
    }
}
