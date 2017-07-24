#ifndef QBOUNDINGBOXRECTANGLE_H
#define QBOUNDINGBOXRECTANGLE_H

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include <qdebug.h>

#include <opencv2/core.hpp>
using cv::Rect;

class QBoundingBoxRectangle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    unsigned int id, key, resizeMode;
    qreal mouseX, mouseY;
    qreal pointXa, pointXb, pointYa, pointYb;

public:
    QBoundingBoxRectangle();
    QBoundingBoxRectangle(unsigned int _id);

    int getId();
    int getKey();
    void setId(int _id);
    void setKey(int _key);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QBOUNDINGBOXRECTANGLE_H
