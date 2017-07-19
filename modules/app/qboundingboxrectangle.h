#ifndef QBOUNDINGBOXRECTANGLE_H
#define QBOUNDINGBOXRECTANGLE_H

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include <qdebug.h>

class QBoundingBoxRectangle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    unsigned int identifier, resizeMode;
    qreal mouseX, mouseY;
    qreal pointXa, pointXb, pointYa, pointYb;

public:
    QBoundingBoxRectangle();
    QBoundingBoxRectangle(unsigned int _id);

    unsigned int getIdentifier();
    void setIdentifier(unsigned int _id);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QBOUNDINGBOXRECTANGLE_H
