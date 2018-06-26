#include "render.h"
#include "integrator.h"

#include <QThread>
#include <QDebug>
#include <random>




QImage *Render::getImage() const
{
    return image;
}

int Render::getCurrentProgress() const
{
    if(counter){
        return counter->getCurrPixelsDone();
    }
    return 0;
}

int Render::getTargetProgress() const
{
    return width*height;
}

int Render::getRenderedTime() const
{
    if(activeThreads <= 0){
        return renderFinishedTime;
    }else return timer.elapsed();
}

Render::Render() : counter{}, mutex(), timer(), activeThreads()
{
    image = nullptr;
}

Render::~Render()
{
    //delete [] image;
}


QImage *Render::startRender(Scene *scene, Camera *camera,
                            int width, int height,
                            int threads, int maxSamples, int maxReflections)
{
    //if(image != nullptr)
    //delete [] image;

    //mutex.lock();

    emit stopAll();

    timer.start();

    this->width = width;
    this->height = height;
    this->maxSamples = maxSamples;
    this->maxReflections = maxReflections;
    image = new QImage(width, height, QImage::Format::Format_RGB888);

    activeThreads += threads;

    this->counter = new RenderImpl::Counter(width, height, 0, 0);

    for(int i = 0; i < threads; i++){
        RenderImpl::Worker *thrd = new RenderImpl::Worker(this, counter, camera, scene, maxSamples, maxReflections);
        connect(thrd, SIGNAL(finished()), this, SLOT(finishedOne()));
        connect(thrd, SIGNAL(finished()), thrd, SLOT(deleteLater()));
        connect(this, SIGNAL(stopAll()), thrd, SLOT(kill()));
        thrd->start();
        thrd->setPriority(QThread::HighestPriority);
    }

    return image;
}

void Render::stopThreads()
{
    emit stopAll();
}


void Render::finishedOne()
{
    activeThreads--;
    if(activeThreads <= 0){
        renderFinishedTime = timer.elapsed();
        emit finished(renderFinishedTime);
    }
}


bool RenderImpl::Counter::getNextPixelGroup(int *rx, int *ry, int count){
    //QMutexLocker ml(&mutex);
    mutex.lock();
    *rx = x;
    *ry = y;
    bool ret = x < width && y < height;
    for(int i = 0; i < count; i++){
        x++;
        if(x >= width){
            x = 0;
            y++;
        }
        if(y >= height){
            break;
        }
    }
    mutex.unlock();
    return ret;
}

int RenderImpl::Counter::getCurrPixelsDone()
{
    mutex.lock();
    int ans = y * width + x;
    ans = std::min(ans, width*height);
    mutex.unlock();
    return ans;
}

void RenderImpl::Worker::kill()
{
    active = false;
}

void RenderImpl::Worker::run(){
    QImage *img = render->getImage();
    int width = img->width();
    int height = img->height();

    Integrator integrator{};

    int x,y;
    int count = 128;
    while(active && counter->getNextPixelGroup(&x, &y, count)){
        for(int i = 0; i < count && active; i++){


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
                Vector3D yShift = camera->getUp() * ((y - height/2.0 + dy) / width * camera->getFov());

                Ray ray(camera->getPosition(), camera->getDirection() + xShift + yShift);

                Color color = integrator.trace(scene, ray, maxReflections, 0);

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
            }while(active && samples < maxSamples);

            img->setPixelColor(x,height-1-y, QColor(r/samples,g/samples,b/samples));
            x++;
            if(x >= width){
                x = 0; y++;
            }
            if(y >= height){
                break;
            }
        }
    }
}
