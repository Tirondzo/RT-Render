#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QImage>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
private:
    QImage* image;

public:
    explicit GraphicsView(QWidget *widget = 0);
    ~GraphicsView();

    QImage *getImage() const;
    void setImage(QImage *value);

public slots:
    void updateImage();
};

#endif // GRAPHICSVIEW_H
