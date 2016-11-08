#ifndef SCENE_H
#define SCENE_H

#include <QAction>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>

class QBoundingBox : public QGraphicsScene
{
public:
    BoundingBox(QObject* parent = 0);
    void setMode();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
   QGraphicsRectItem* itemToDraw;

private:
    qreal origPoint, origPoint2;
    qreal endPoint, endPoint2;
    qreal weigth;
    qreal heigth;
    //void makeItemsControllable(bool areControllable);
    bool drawEnabled;
    //DraggableRectItem* itemToDraw;
    void makeItemsControllable(bool areControllable);
public slots:
    void enableDraw();
};

#endif // SCENE_H
