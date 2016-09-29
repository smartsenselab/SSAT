#ifndef SCENE_H
#define SCENE_H

#include <QAction>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>

class BoundingBox : public QGraphicsScene
{
public:
    BoundingBox(QObject* parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal origPoint, origPoint2;
    qreal endPoint, endPoint2;
    qreal weigth;
    qreal heigth;

    QGraphicsRectItem* itemToDraw;
    void makeItemsControllable(bool areControllable);
};

#endif // SCENE_H