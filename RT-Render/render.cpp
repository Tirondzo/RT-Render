#include "render.h"
#include "integrator.h"

#include <QThread>
#include <QDebug>
#include <random>




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


QImage *Render::startRender(Scene *scene, Camera *camera, int width, int height, int threads)
{
    //if(image != nullptr)
        //delete [] image;

    //mutex.lock();

    this->width = width;
    this->height = height;
    image = new QImage(width, height, QImage::Format::Format_RGB888);


    activeThreads = threads;

    RenderImpl::Counter *counter = new RenderImpl::Counter(width, height, -1, 0);

    for(int i = 0; i < threads; i++){
        RenderImpl::Worker *thrd = new RenderImpl::Worker(this, counter, camera, scene);
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

    std::random_device rd;
    std::ranlux48_base mt(rd());
    //XorShiftRandomEngine mt;
    std::uniform_real_distribution<float> fDist(.0, 1.);
    std::uniform_real_distribution<double> dDist(.0, 1.);

    int x,y;
    while(counter->getNextPixel(&x, &y)){
        //qDebug() << x << " " << y << QThread::currentThread();

       //img->setPixelColor(x,height-1-y, QColor(250,120,20));
       //QTest::qSleep(10);
       //continue;
       int r = 0, g = 0, b = 0, a = 0;

       NVector<uint64_t, 4> summ_squares{};
       NVector<uint64_t, 4> summ_colors{};
       double rs = 0;
       double rn = 0;
       int samples{};

       do{
           //double dx = random::randd();
           //double dy = random::randd();

           //double dx = (double)rand() / RAND_MAX;
           //double dy = (double)rand() / RAND_MAX;

           double dx = dDist(mt);
           double dy = dDist(mt);

           Vector3D xShift = camera->getRight() * ((x - width/2.0 + dx) / width * camera->getFov());
           Vector3D yShift = camera->getUp() * ((y - height/2.0 + dy) / height * camera->getFov());

           Ray ray(camera->getPosition(), camera->getLookAt() + xShift + yShift - camera->getPosition());

           Color color = Integrator::trace(scene, ray, 36, 0);

           summ_squares += color * color;
           summ_colors += color;

           rs += (color.getR() * color.getR());
           rn += color.getR();

           r += color.getR();
           g += color.getG();
           b += color.getB();
           a += color.getA();

           samples++;
           //qDebug() << x << y << (rs/samples) << (rn * rn / samples / samples);
           //for some reasons dispersion convergence doesn't work or infinitly slow
       //}while(samples < 1000 && (samples < 20 || (((summ_squares-(summ_colors*summ_colors/samples))/samples).slength() > 1000)));
       }while(samples < 128);

       img->setPixelColor(x,height-1-y, QColor(r/samples,g/samples,b/samples));
    }
}
