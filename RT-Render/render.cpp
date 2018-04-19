#include "render.h"
#include "integrator.h"
#include "random.h"

#include <QThread>
#include <QtConcurrent>





bool Render::nextPixel(int *ret_x, int *ret_y){
     //static QMutex mutex;
     //QMutexLocker locker(&mutex);


     ++x;
     if(x >= width){
         x = 0;
         ++y;
     }
     if(y >= height){
         //locker.unlock();
         return false;
     }
     *ret_x = x;
     *ret_y = y;
     //locker.unlock();
     return true;
}


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

    mutex.lock();

    width = _width;
    height = _height;
    image = new QImage(width, height, QImage::Format::Format_RGB888);

    Scene * _scene = new Scene(scene);
    Camera * _camera = new Camera(camera);

    x = -1;
    y = 0;

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

    for(int i = 0; i < threads; i++){
        QThread *thread= new QThread;
        Worker *worker = new Worker(this, &mutex, _camera, _scene);
        worker->moveToThread(thread);
        connect(thread, SIGNAL(started()), worker, SLOT(doWork()));

        thread->start();
    }

    /*
    int x, y;
    for( y = 0; y < height; y++)
    for( x = 0; x < width; x++){
        int ns = 64;
        int r = 0, g = 0, b = 0, a = 0;
        for (int s = 0; s < ns; ++s) {
            float dx = (float) rand() / RAND_MAX;
            float dy = (float) rand() / RAND_MAX;


            Vector3D xShift = _camera.getRight() * (x - width/2.0 + dx) / width * _camera.getFov();
            Vector3D yShift = _camera.getUp() * (y - height/2.0 + dy) / width * _camera.getFov();

            Ray ray(_camera.getPosition(), _camera.getLookAt() + xShift + yShift - _camera.getPosition());

            Color color = Integrator::trace(_scene, ray, 6, 0);

            r += color.getR();
            g += color.getG();
            b += color.getB();
            a += color.getA();
        }

        image->setPixelColor(x,height-1-y, QColor(r/ns,g/ns,b/ns));
    }*/

    mutex.unlock();
    return image;
}

void Render::stopThreads()
{

}


void Render::process()
{
    int x, y;
    for( y = 0; y < height; y++)
    for( x = 0; x < width; x++){
        /*int ns = 4;
        int r = 0, g = 0, b = 0, a = 0;
        for (int s = 0; s < ns; ++s) {
            float dx = (float) rand() / RAND_MAX;
            float dy = (float) rand() / RAND_MAX;


            Vector3D xShift = _camera.getRight() * (x - width/2.0 + dx) / width * _camera.getFov();
            Vector3D yShift = _camera.getUp() * (y - height/2.0 + dy) / width * _camera.getFov();

            Ray ray(_camera.getPosition(), _camera.getLookAt() + xShift + yShift - _camera.getPosition());

            Color color = Integrator::trace(_scene, ray, 6, 0);

            r += color.getR();
            g += color.getG();
            b += color.getB();
            a += color.getA();
        }*/

        image->setPixelColor(x,y, QColor(100,100,0));
    }
}

void Render::finishedOne()
{
    activeThreads--;
    if(activeThreads <= 0)
        emit finished();
}


void Worker::doWork(){
   int x,y;
   QImage *img = render->getImage();
   int width = img->width();
   int height = img->height();

   //for(y = 0; y < height; y++)
   //for(x = 0; x < width; x++){

   //mutex->lock();
   bool doing = render->nextPixel(&x, &y);
   //mutex->unlock();

   while(doing){
       int ns = 8;
       int r = 0, g = 0, b = 0, a = 0;

       for (int s = 0; s < ns; ++s) {
           double dx = random::randd();
           double dy = random::randd();


           Vector3D xShift = _camera->getRight() * (x - width/2.0 + dx) / width * _camera->getFov();
           Vector3D yShift = _camera->getUp() * ((y - height/2.0 + dy) / width * _camera->getFov());

           Ray ray(_camera->getPosition(), _camera->getLookAt() + xShift + yShift - _camera->getPosition());

           Color color = Integrator::trace(*_scene, ray, 6, 0);

           r += color.getR();
           g += color.getG();
           b += color.getB();
           a += color.getA();
       }

       img->setPixelColor(x,height-1-y, QColor(r/ns,g/ns,b/ns));

       //mutex->lock();
       doing = render->nextPixel(&x, &y);
       //mutex->unlock();
   }

   emit finished();

}

