#include "graphicsview.h"

#include <QTimer>
#include <QPixmap>
#include <QPainter>


GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    image = nullptr;
    scn = new QGraphicsScene(this);
    setScene(scn);

    this->setCacheMode(CacheNone);
    this->optimizationFlags() |= DontSavePainterState;
    this->optimizationFlags() &= ~DontAdjustForAntialiasing;
    this->setViewportUpdateMode(FullViewportUpdate);

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateImage()));
    timer->start(1000);
}



GraphicsView::~GraphicsView()
{
    if(!timer){
        timer->stop();
        delete [] timer;
    }
    //delete [] scn;
}

QImage *GraphicsView::getImage() const
{
    return image;
}

void GraphicsView::setImage(QImage *value)
{
    image = value;

    scn->clear();

    QGraphicsItem *item = new MyImage(image);
    scn->addItem(item);
    this->fitInView(scn->itemsBoundingRect(), Qt::KeepAspectRatio);
    scn->setSceneRect(scn->itemsBoundingRect());
}


void GraphicsView::updateImage(){
    if(!image) return;
    //scn->clear();
    //scn->addPixmap(QPixmap::fromImage(*image));
    //painter->drawImage(0,0,*image);
    //scn->drawBackground(painter, QRectF(0,0,512,512));
    //scn->update();
    this->fitInView(scn->itemsBoundingRect(), Qt::KeepAspectRatio);
}

QRectF MyImage::boundingRect() const
{
    return QRectF(0,0,img->width(),img->height());
}

void MyImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(0,0,*img);
}
