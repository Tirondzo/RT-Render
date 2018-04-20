#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QImage>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
private:
    QImage* image;
    QTimer *timer;
    QGraphicsScene *scn;

    QPainter *painter;

public:
    explicit GraphicsView(QWidget *widget = 0);
    ~GraphicsView();

    QImage *getImage() const;
    void setImage(QImage *value);

public slots:
    void updateImage();
};


class MyImage : public QGraphicsItem {
    QImage *img;
public:
    MyImage(QImage *img) : img(img){}

    QRectF boundingRect() const;

    // overriding paint()
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);
};

#endif // GRAPHICSVIEW_H
