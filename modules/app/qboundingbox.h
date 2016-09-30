#ifndef SCENE_H
#define SCENE_H

#include <QAction>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include "draggablerectitem.h"

class QBoundingBox : public QGraphicsScene
{
public:
    QBoundingBox(QObject* parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool drawEnabled;
    
    DraggableRectItem* itemToDraw;
    
    qreal origPoint, origPoint2;
    qreal endPoint, endPoint2;
    qreal weigth;
    qreal heigth;
    
    void makeItemsControllable(bool areControllable);
    
public slots:
    void enableDraw();
};

#endif // SCENE_H
