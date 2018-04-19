#include "graphicsview.h"

#include <QTimer>
#include <QPixmap>

QTimer *timer;
QGraphicsScene *scn;

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    image = nullptr;
    scn = new QGraphicsScene(this);
    setScene(scn);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateImage()));
    timer->start(200);
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
}


void GraphicsView::updateImage(){
    if(!image) return;
    scn->clear();
    scn->addPixmap(QPixmap::fromImage(*image));
    this->fitInView(scn->itemsBoundingRect(), Qt::KeepAspectRatio);
}
